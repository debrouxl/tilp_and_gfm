/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *  Copyright (C) 2007  Kevin Kofler
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
#include "clist.h"
#include "tilp_core.h"
#include "gtk_update.h"

static DeviceOptions	tmp;
static GtkWidget* lbl;
static GtkWidget* om_cable;
static GtkWidget* om_calc;
static GtkWidget* om_port;

static GtkListStore *store = NULL;

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
			gchar** row = g_malloc0((CLIST_NVCOLS + 1) * sizeof(gchar *));

			gtk_list_store_append(store, &iter);

			row[COL_CABLE] = g_strdup(list[i] == PID_TIGLUSB ? "SilverLink" : "DirectLink");
			row[COL_PORT] = g_strdup_printf("#%i", i+1);
			row[COL_CALC] = g_strdup((list[i] == PID_TIGLUSB) ? "" : ticables_usbpid_to_string(list[i]));

			gtk_list_store_set(store, &iter, 
				COL_CABLE, row[COL_CABLE], 
				COL_PORT, row[COL_PORT],
				COL_CALC, row[COL_CALC],
				-1);
			g_strfreev(row);
		}

		//free(list);
	}
	else
	{
		int **array;
		int i, j;

		gtk_label_set_text(GTK_LABEL(lbl), "Searching for devices (~20 seconds)...");
		GTK_REFRESH();
		tilp_device_probe_all(&array);

		for(i = CABLE_GRY; i <= CABLE_USB; i++)
		for(j = PORT_1; j <= PORT_4; j++)
		if(array[i][j] != CALC_NONE)
		{
			GtkTreeIter iter;
			gchar** row = g_malloc0((CLIST_NVCOLS + 1) * sizeof(gchar *));

			gtk_list_store_append(store, &iter);

			//calc = tilp_remap_from_usb(cable, calc);
			row[COL_CABLE] = g_strdup(ticables_model_to_string(i));
			row[COL_PORT] = g_strdup_printf("#%i", j);
			row[COL_CALC] = g_strdup(ticalcs_model_to_string(array[i][j]));

			gtk_list_store_set(store, &iter, 
				COL_CABLE, row[COL_CABLE], COL_PORT, row[COL_PORT], COL_CALC, row[COL_CALC],
				-1);
			g_strfreev(row);
		}

		gtk_label_set_text(GTK_LABEL(lbl), "Done !");
		ticables_probing_finish(&array);
	}
}

static void list_refresh(GtkListStore *store, int full)
{
	gtk_list_store_clear(store);
	clist_populate(store, full);
}

GLADE_CB gboolean
comm_treeview1_button_press_event  (GtkWidget       *widget,
                                    GdkEventButton  *event,
                                    gpointer         user_data)
{	
	GtkWidget *list = GTK_WIDGET(widget);
	GtkTreeView *view = GTK_TREE_VIEW(list);
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	gboolean valid;
	GtkTreeIter iter;
	gchar** row_text = g_malloc0((CLIST_NVCOLS + 1) * sizeof(gchar *));

	CableModel cbm;
	CablePort cbp;
	CalcModel clm, cm;

	// is double click ?
	if(event->type != GDK_2BUTTON_PRESS)
		return FALSE;

	// get selection
	selection = gtk_tree_view_get_selection(view);
	valid = gtk_tree_selection_get_selected(selection, &model, &iter);
	gtk_tree_model_get(model, &iter, 
		COL_CABLE, &row_text[COL_CABLE], COL_PORT, &row_text[COL_PORT], 
		COL_CALC, &row_text[COL_CALC], -1);

	cbm = ticables_string_to_model(row_text[COL_CABLE]);
	cbp = ticables_string_to_port(row_text[COL_PORT]);
	clm = ticalcs_string_to_model(row_text[COL_CALC]);
	cm = tilp_remap_from_usb(cbm, clm);

	gtk_option_menu_set_history(GTK_OPTION_MENU(om_cable), cbm);
	gtk_option_menu_set_history(GTK_OPTION_MENU(om_port), cbp);
	gtk_option_menu_set_history(GTK_OPTION_MENU(om_calc), 
		cm >= CALC_NSPIRE ? cm-CALC_NSPIRE+13 : cm);

    g_strfreev(row_text);

    return FALSE;
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
	gtk_dialog_set_alternative_button_order(GTK_DIALOG(dbox), GTK_RESPONSE_OK,
	                                        GTK_RESPONSE_CANCEL,-1);
	lbl = glade_xml_get_widget(xml, "label7");

	// Tree View
	data = glade_xml_get_widget(xml, "treeview1");
	store = clist_create(data);
	gtk_widget_show_all(data);
	if(options.usb_avail)
		clist_populate(store, 0);

#ifdef __WIN32__
	data = glade_xml_get_widget(xml, "lnx1");
	gtk_widget_hide(data);
#endif

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

	case CABLE_DEV:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 9);
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

	case CALC_NSPIRE:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 13);
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
	gtk_widget_set_sensitive(GTK_WIDGET(data), options.usb_avail);

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
		// set cable
		tilp_device_close();

		// copy options
		options.cable_delay = tmp.cable_delay;
		options.cable_model = tmp.cable_model;
		options.cable_port = tmp.cable_port;
		options.cable_timeout = tmp.cable_timeout;
		options.calc_model = tmp.calc_model;
		options.calc_model = tilp_remap_to_usb(options.cable_model, options.calc_model);

		// set cable
		tilp_device_open();

		// and refresh
		toolbar_refresh_buttons();
		ctree_set_basetree();
		clist_refresh();

#ifdef __LINUX__
		if(options.cable_model == CABLE_USB && options.calc_model == CALC_TI89T_USB)
			gif->msg_box1(_("Information"), _("Please note that Titanium through DirectLink USB works under Linux but it suffers from a limitation: the cable has to unplugged/plugged whenever TiLP is exited."));
#endif

		if(options.calc_model == CALC_NSPIRE)
			gif->msg_box1(_("Information"), _("Please note you will have to restart TiLP if connection fails."));

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
	case 9: tmp.cable_model = CABLE_DEV; break;
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
	case 9: tmp.calc_model = CALC_TI89T; break;
	case 10:tmp.calc_model = CALC_TI92;  break;
	case 11:tmp.calc_model = CALC_TI92P; break;
	case 12:tmp.calc_model = CALC_V200;  break;
	case 13:tmp.calc_model = CALC_NSPIRE;break;
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
	list_refresh(store, !0);	
}
