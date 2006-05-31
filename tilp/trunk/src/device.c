/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#undef GTK_DISABLE_DEPRECATED
#include <gtk/gtk.h>
#define GTK_DISABLE_DEPRECATED
#include <glade/glade.h>
#include <string.h>

#include "support.h"
#include "device.h"
#include "toolbar.h"
#include "ctree.h"
#include "tilp_core.h"
#include "gtk_update.h"

static DeviceOptions	tmp;
static GtkWidget* lbl;
static GtkWidget* om_cable;
static GtkWidget* om_calc;
static GtkWidget* om_port;

static GtkListStore *store1 = NULL;

enum { COL_CABLE, COL_PORT, COL_CALC };
#define CLIST_NVCOLS	(3)		// 3 visible columns
#define CLIST_NCOLS		(3)		// 3 real columns

static GtkListStore* clist_create(GtkWidget *widget)
{
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkListStore *store;
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	GtkTreeSelection *selection;
    const gchar *text[CLIST_NVCOLS] = { _("Cable"), _("Port"), _("Device") };
    gint i;
	
	store = gtk_list_store_new(CLIST_NCOLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, -1);
    model = GTK_TREE_MODEL(store);
	
    gtk_tree_view_set_model(view, model); 
    gtk_tree_view_set_headers_visible(view, TRUE);
	gtk_tree_view_set_rules_hint(view, FALSE);
  
	for(i = COL_CABLE; i <= COL_CALC; i++)
	{
		renderer = gtk_cell_renderer_text_new();
		gtk_tree_view_insert_column_with_attributes(view, -1, text[i], renderer, "text", i, NULL);
	}
    
    for (i = 0; i < CLIST_NVCOLS; i++) 
    {
		GtkTreeViewColumn *col;

		col = gtk_tree_view_get_column(view, i);
		gtk_tree_view_column_set_resizable(col, TRUE);
	}
	
	selection = gtk_tree_view_get_selection(view);
	gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

	return store;
}

static void clist_populate(GtkListStore *store, int full)
{
	if(!full)
	{
		int i, n, *list;

		ticables_get_usb_devices(&list, &n);
		
		for(i = 0; i < n; i++)
		{
			GtkTreeIter iter;
			gchar *str1, *str2, *str3;

			gtk_list_store_append(store, &iter);

			str1 = g_strdup(list[i] == PID_TIGLUSB ? "SilverLink" : "DirectLink");
			str2 = g_strdup_printf("#%i", i);
			str3 = g_strdup((list[i] == PID_TIGLUSB) ? "" : ticables_usbpid_to_string(list[i]));

			gtk_list_store_set(store, &iter, 
				COL_CABLE, str1, 
				COL_PORT, str2,
				COL_CALC, str3,
				-1);
			g_free(str1); g_free(str2); g_free(str3);
		}
	}
}

static void clist_refresh(GtkListStore *store, int full)
{
	gtk_list_store_clear(store);
	clist_populate(store, full);
}

//=========================================

gint display_device_dbox()
{
	GladeXML *xml;
	GtkWidget *dbox;
	GtkWidget *data;
	gint result;

	xml = glade_xml_new(tilp_paths_build_glade("device-2.glade"), "device_dbox", PACKAGE);
	if (!xml)
		g_error(_("comm.c: GUI loading failed !\n"));
	glade_xml_signal_autoconnect(xml);

	dbox = glade_xml_get_widget(xml, "device_dbox");
	lbl = glade_xml_get_widget(xml, "label7");

	// Tree View
	data = glade_xml_get_widget(xml, "treeview1");
	store1 = clist_create(data);
	gtk_widget_show_all(data);
	clist_populate(store1, 0);

	// Cable  
	data = om_cable = glade_xml_get_widget(xml, "optionmenu_comm_cable");
	switch (options.cable_model) 
	{
	case CABLE_NUL:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 0);
	break;

	case CABLE_GRY:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 1);
	break;
		
	case CABLE_BLK:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 2);
	break;

	case CABLE_PAR:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 3);
	break;

	case CABLE_SLV:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 4);
	break;	

	case CABLE_USB:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 5);
	break;	

	case CABLE_VTI:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 6);
	break;

    case CABLE_TIE:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 7);
	break;
	
	case CABLE_VTL:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 8);
	break;   

	default:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 0);
	  break;
	}

	// Port
	data = om_port = glade_xml_get_widget(xml, "optionmenu_comm_port");
	switch (options.cable_port) 
	{
	case PORT_0:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 0);
	break;
	case PORT_1:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 1);
	break;
	case PORT_2:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 2);
	break;
	case PORT_3:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 3);
	break;
	case PORT_4:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 4);
	break;
	}

	// Calc
	data = om_calc = glade_xml_get_widget(xml, "optionmenu_comm_calc");
	switch (options.calc_model) 
	{
	case CALC_NONE:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 0);
	  break;

	case CALC_TI73:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 1);
	  break;
	  
	case CALC_TI82:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 2);
	  break;

	case CALC_TI83:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 3);
	  break;
	  
	case CALC_TI83P:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 4);
	  break;

	case CALC_TI84P:
	case CALC_TI84P_USB:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 5);
	  break;
	  
	case CALC_TI85:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 6);
	  break;
	  
	case CALC_TI86:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 7);
	  break;
	  
	case CALC_TI89:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 8);
	  break;

	case CALC_TI89T:
	case CALC_TI89T_USB:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 9);
	  break;
	  
	case CALC_TI92:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 10);
	  break;
	  
	case CALC_TI92P:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 11);
	  break;
	  
	case CALC_V200:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 12);
	  break;
	}

	// Timeout
	data = glade_xml_get_widget(xml, "spinbutton_comm_timeout");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), options.cable_timeout);
	
	// Delay
	data = glade_xml_get_widget(xml, "spinbutton_comm_delay");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), options.cable_delay);

	data = glade_xml_get_widget(xml, "checkbutton1");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), options.auto_detect);

	// expander
	//data = glade_xml_get_widget(xml, "expander1");
	//gtk_expander_set_expanded(GTK_EXPANDER(data), FALSE);

	// Avoid early callbacks
	tmp.cable_delay = options.cable_delay;
	tmp.cable_model = options.cable_model;
	tmp.cable_port = options.cable_port;
	tmp.cable_timeout = options.cable_timeout;
	tmp.calc_model = options.calc_model;
	
	// Dialog box
	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) 
	{
	case GTK_RESPONSE_CANCEL:
		break;
	case GTK_RESPONSE_OK:
#ifdef _NDEBUG
		if(tmp.cable_model == CABLE_USB)
			gif->msg_box1("Information", "Beware: DirectLink cable support is curently experimental and being implemented");
#endif
		// set cable
		tilp_device_close();

		// copy options
		options.cable_delay = tmp.cable_delay;
		options.cable_model = tmp.cable_model;
		options.cable_port = tmp.cable_port;
		options.cable_timeout = tmp.cable_timeout;
		options.calc_model = tmp.calc_model;

		// set cable
		tilp_device_open();

		// and refresh
		toolbar_refresh_buttons();
		ctree_set_basetree();
		break;
	case GTK_RESPONSE_HELP:
		break;
	default:
		break;
	}
	gtk_widget_destroy(dbox);
	return 0;
}


GLADE_CB void
comm_cable_changed                     (GtkOptionMenu   *optionmenu,
                                        gpointer         user_data)
{
	gint nitem = gtk_option_menu_get_history(optionmenu);

	switch(nitem)
	{
	case 0: tmp.cable_model = CABLE_NUL; break;
	case 1: tmp.cable_model = CABLE_GRY; break;
	case 2: tmp.cable_model = CABLE_BLK; break;
	case 3:	tmp.cable_model = CABLE_PAR; break;
	case 4: tmp.cable_model = CABLE_SLV; break;	
	case 5: tmp.cable_model = CABLE_USB; break;	
	case 6: tmp.cable_model = CABLE_VTI; break;
	case 7: tmp.cable_model = CABLE_TIE; break;
	case 8: tmp.cable_model = CABLE_VTL; break;
	}
}

GLADE_CB void
comm_cable_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}


GLADE_CB void
comm_port_changed                      (GtkOptionMenu   *optionmenu,
                                        gpointer         user_data)
{
	GtkWidget *menu_item = optionmenu->menu_item;
	gchar *ed = menu_item->name;

	if(!strcmp(ed, "number0"))
		tmp.cable_port = PORT_0;
	else if(!strcmp(ed, "number1"))
		tmp.cable_port = PORT_1;
	else if(!strcmp(ed, "number2"))
		tmp.cable_port = PORT_2;
	else if(!strcmp(ed, "number3"))
		tmp.cable_port = PORT_3;
	else if(!strcmp(ed, "number4"))
		tmp.cable_port = PORT_4;
}

GLADE_CB void
comm_port_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}


GLADE_CB void
comm_calc_changed                      (GtkOptionMenu   *optionmenu,
                                        gpointer         user_data)
{
	gint nitem = gtk_option_menu_get_history(optionmenu);

	switch(nitem)
	{
	case 0: tmp.calc_model = CALC_NONE;	 break;
	case 1: tmp.calc_model = CALC_TI73;	 break;
	case 2:	tmp.calc_model = CALC_TI82;  break;
	case 3: tmp.calc_model = CALC_TI83;  break;
	case 4: tmp.calc_model = CALC_TI83P; break;
	case 5: tmp.calc_model = CALC_TI84P; break;
	case 6: tmp.calc_model = CALC_TI85;  break;
	case 7: tmp.calc_model = CALC_TI86;  break;
	case 8: tmp.calc_model = CALC_TI89;  break;
	case 9:tmp.calc_model = CALC_TI89T; break;
	case 10:tmp.calc_model = CALC_TI92;  break;
	case 11:tmp.calc_model = CALC_TI92P; break;
	case 12:tmp.calc_model = CALC_V200;  break;
  	}	
}

GLADE_CB void
comm_calc_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}


GLADE_CB void
comm_checkbutton1_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	options.auto_detect = togglebutton->active;
}


GLADE_CB void
comm_spinbutton_delay_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
  	tmp.cable_delay =
    		gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}


GLADE_CB void
comm_spinbutton_timeout_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
  	tmp.cable_timeout =
    		gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}

GLADE_CB void
comm_button_search_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	int **array;
	int i, j;
	int cable, port, calc;
	gchar *s;

	gtk_label_set_text(GTK_LABEL(lbl), "Searching for devices (~20 seconds)...");
	GTK_REFRESH();
	tilp_device_probe_all(&array);

	for(i = CABLE_GRY; i <= CABLE_USB; i++)
		for(j = PORT_1; j <= PORT_4; j++)
			if(array[i][j] != CALC_NONE)
				goto found;

found:
	cable = i;
	port = j;
	calc = array[i][j];

	s = g_strdup_printf("Found: %s %s %s", 
		ticalcs_model_to_string(calc),
		ticables_model_to_string(cable),
		ticables_port_to_string(port));
	gtk_label_set_text(GTK_LABEL(lbl), s);
	GTK_REFRESH();
	g_free(s);

	calc = tilp_remap_from_usb(cable, calc);
	gtk_option_menu_set_history(GTK_OPTION_MENU(om_cable), cable);
	gtk_option_menu_set_history(GTK_OPTION_MENU(om_port), port);
	gtk_option_menu_set_history(GTK_OPTION_MENU(om_calc), calc);

	ticables_probing_finish(&array);
}
