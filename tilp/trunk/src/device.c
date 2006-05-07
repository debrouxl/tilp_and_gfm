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
comm_checkbutton_calc_auto_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  	//if (togglebutton->active == TRUE)
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

static CableModel cable_model;
static CalcModel calc_model;
static CablePort cable_port;

GLADE_CB void
comm_button_search_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
#if 0
	int i, j;
	int **cables;
	CableHandle* handle;
	int err;
	gchar *s;

	// search for cables
	tilp_info("Searching for link cables...");
	gtk_label_set_text(GTK_LABEL(lbl), "Searching for cables...");
	GTK_REFRESH();
	ticables_probing_do(&cables, 5, PROBE_ALL);
	for(i = 1; i <= 5/*7*/; i++)
		printf("%i: %i %i %i %i\n", i, cables[i][1], cables[i][2], cables[i][3], cables[i][4]);

	cable_model = cable_port = calc_model = 0;
	for(i = CABLE_GRY; i <= CABLE_TIE; i++)
		for(j = PORT_1; j <= PORT_4; j++)
			if(cables[i][j])	// && ((i >= CABLE_VTI) && (j == PORT_2)))
			{
				cable_model = i;
				cable_port = j;
				goto finished;
			}
finished:
	ticables_probing_finish(&cables);

	if(!cable_model && !cable_port)
	{
		gtk_label_set_text(GTK_LABEL(lbl), "Not found !");
		return;
	}

	// search for devices
	tilp_info("Searching for hand-helds on %i:%i...", 
		  cable_model, cable_port);
	gtk_label_set_text(GTK_LABEL(lbl), "Searching for hand-helds...");
	GTK_REFRESH();
	
	handle = ticables_handle_new(cable_model, cable_port);
	ticables_options_set_timeout(handle, 10);

	err = ticables_cable_open(handle);
	if(err)
	{
		tilp_err(err);
		ticables_handle_del(handle);
		gtk_label_set_text(GTK_LABEL(lbl), "Not found !");
		return;
	}

	if(cable_model != CABLE_USB)
	{
		ticalcs_probe_calc(handle, &calc_model);
	}
	else
	{
		ticalcs_probe_usb_calc(handle, &calc_model);
	}
	s = g_strdup_printf("Found: %s %s %s", 
		ticalcs_model_to_string(calc_model),
		ticables_model_to_string(cable_model),
		ticables_port_to_string(cable_port));
	gtk_label_set_text(GTK_LABEL(lbl), s);
	GTK_REFRESH();
	g_free(s);

	ticables_cable_close(handle);
	ticables_handle_del(handle);

	calc_model = tilp_remap_from_usb(cable_model, calc_model);

	gtk_option_menu_set_history(GTK_OPTION_MENU(om_cable), cable_model);
	gtk_option_menu_set_history(GTK_OPTION_MENU(om_port), cable_port);
	gtk_option_menu_set_history(GTK_OPTION_MENU(om_calc), calc_model);
#endif
}
