/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
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
#endif				/*  */

#undef GTK_DISABLE_DEPRECATED

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>

#include "comm.h"
#include "toolbar.h"
#include "ctree.h"
#include "tilp_core.h"
#include "logfile.h"

// uncomment it to get more than 1 USB port
//#define MORE_USB_PORTS

static TicableLinkParam tmp_lp;
static gint ad;
static GtkWidget *button = NULL;
static gint init = !0;
static GtkWidget *port = NULL;


gint display_comm_dbox()
{
	GladeXML *xml;
	GtkWidget *dbox;
	GtkWidget *data;
	gint result;

	init = !0;

	xml = glade_xml_new
	    (tilp_paths_build_glade("comm-2.glade"), "comm_dbox", PACKAGE);
	if (!xml)
		g_error(_("comm.c: GUI loading failed !\n"));
	glade_xml_signal_autoconnect(xml);

	dbox = glade_xml_get_widget(xml, "comm_dbox");
	ad = options.auto_detect;

	// Auto-detect
	button = glade_xml_get_widget(xml, "checkbutton_calc_auto");
	if (ad)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),
					     TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),
					     FALSE);

	// Cable  
	data = glade_xml_get_widget(xml, "optionmenu_comm_cable");
	switch (options.lp.link_type) {
	case LINK_TGL:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 0);
		break;
		
	case LINK_SER:
		gtk_option_menu_set_history(GTK_OPTION_MENU(data), 1);
		break;

	case LINK_SLV:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 2);
	  break;

	case LINK_PAR:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 3);
	  break;

	case LINK_TIE:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 4);
	  break;

	case LINK_VTI:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 5);
	  break;
	
	case LINK_VTL:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 6);
	  break;

    case LINK_NUL:
      gtk_option_menu_set_history(GTK_OPTION_MENU(data), 7);
	  break;

	default:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 7);
	  break;
	}

	// Port
	port = data = glade_xml_get_widget(xml, "optionmenu_comm_port");
	switch (options.lp.port) {
	case PARALLEL_PORT_1:
	case SERIAL_PORT_1:
	case USB_PORT_1:
	case VIRTUAL_PORT_1:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 1);
	  break;
	 
	case PARALLEL_PORT_2:
	case SERIAL_PORT_2:
	case USB_PORT_2:
	case VIRTUAL_PORT_2:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 2);
	  break;

	case PARALLEL_PORT_3:
	case SERIAL_PORT_3:
	case USB_PORT_3:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 3);
	  break;

	case SERIAL_PORT_4:
	case USB_PORT_4:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 4);
	  break;

    case NULL_PORT:
      gtk_option_menu_set_history(GTK_OPTION_MENU(data), 5);
	  break;
	  
	case USER_PORT:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 0);
	  break;

	default:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 0);
	  break;
	}

	// Calc
	data = glade_xml_get_widget(xml, "optionmenu_comm_calc");
	switch (options.lp.calc_type) {
	case CALC_TI73:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 0);
	  break;
	  
	case CALC_TI82:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 1);
	  break;

	case CALC_TI83:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 2);
	  break;
	  
	case CALC_TI83P:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 3);
	  break;
	  
	case CALC_TI85:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 4);
	  break;
	  
	case CALC_TI86:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 5);
	  break;
	  
	case CALC_TI89:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 6);
	  break;
	  
	case CALC_TI92:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 7);
	  break;
	  
	case CALC_TI92P:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 8);
	  break;
	  
	case CALC_V200:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 9);
	  break;
	
	default:
	  gtk_option_menu_set_history(GTK_OPTION_MENU(data), 10);
	  break;
	}

	// Timeout
	data = glade_xml_get_widget(xml, "spinbutton_comm_timeout");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), options.lp.timeout);
	
	// Delay
	data = glade_xml_get_widget(xml, "spinbutton_comm_delay");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), options.lp.delay);

	// Avoid early callbacks
	memcpy(&tmp_lp, &options.lp, sizeof(TicableLinkParam));
	
	// Loop
	init = 0;
 loop:
	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) {
	case GTK_RESPONSE_OK:
	  	if (tilp_error(link_cable.exit()))
		  goto loop;
		memcpy(&options.lp, &tmp_lp, sizeof(TicableLinkParam));
		ticable_set_param(&options.lp);
		if(tilp_error(ticable_set_cable
			      (options.lp.link_type, &link_cable)))
		  goto loop;
		ticalc_set_cable(&link_cable);
		ticalc_set_calc(options.lp.calc_type, &ti_calc);
		if(tilp_error(link_cable.init()))
		  goto loop;
		options.auto_detect = ad;
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
	case 0: tmp_lp.link_type = LINK_TGL; break;
	case 1: tmp_lp.link_type = LINK_SER; break;
	case 2: tmp_lp.link_type = LINK_SLV; break;
	case 3:	tmp_lp.link_type = LINK_PAR; break;
	case 4: tmp_lp.link_type = LINK_VTI; break;
	case 5: tmp_lp.link_type = LINK_TIE; break;
	case 6: tmp_lp.link_type = LINK_VTL; break;
    case 7: tmp_lp.link_type = LINK_NUL; break;
	}

    printf("nitem = %i\n", nitem);
	
	// force port to avoid libticables bad argument 
	if(!init) {
		switch(tmp_lp.link_type) {
		case LINK_TGL:
		case LINK_SER:
		case LINK_AVR:
		case LINK_VTI:
		case LINK_TIE:
		case LINK_VTL:
			gtk_option_menu_set_history(GTK_OPTION_MENU(port), 2);
			break;
		case LINK_PAR:
		case LINK_SLV:
			gtk_option_menu_set_history(GTK_OPTION_MENU(port), 1);
                        break;
        case LINK_NUL:
            gtk_option_menu_set_history(GTK_OPTION_MENU(port), 5);
                        break;
		default:
			break;
		}
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
	
	if(!strcmp(ed, "custom1"))
    		tmp_lp.calc_type = USER_PORT;
  	else {
    		switch(tmp_lp.link_type)
      		{
      		case LINK_TGL:
      		case LINK_SER:
      		case LINK_AVR:
			if(!strcmp(ed, "custom1"))
			  	tmp_lp.port = USER_PORT;
			else if(!strcmp(ed, "number1"))
			  	tmp_lp.port = SERIAL_PORT_1;
			else if(!strcmp(ed, "number2"))
			  	tmp_lp.port = SERIAL_PORT_2;
			else if(!strcmp(ed, "number3"))
			  	tmp_lp.port = SERIAL_PORT_3;
			else if(!strcmp(ed, "number4"))
			  	tmp_lp.port = SERIAL_PORT_4;
		break;

      		case LINK_SLV:
			if(!strcmp(ed, "custom1"))
			  tmp_lp.port = USER_PORT;
			else if(!strcmp(ed, "number1"))
			  tmp_lp.port = USB_PORT_1;
			else if(!strcmp(ed, "number2"))
			  tmp_lp.port = USB_PORT_2;
			else if(!strcmp(ed, "number3"))
			  tmp_lp.port = USB_PORT_3;
			else if(!strcmp(ed, "number4"))
			  tmp_lp.port = USB_PORT_4;
		break;

	      	case LINK_PAR:
			if(!strcmp(ed, "custom1"))
			  tmp_lp.port = USER_PORT;
			else if(!strcmp(ed, "number1"))
			  tmp_lp.port = PARALLEL_PORT_1;
			else if(!strcmp(ed, "number2"))
			  tmp_lp.port = PARALLEL_PORT_2;
			else if(!strcmp(ed, "number3"))
			  tmp_lp.port = PARALLEL_PORT_3;
		break;
	
	      	case LINK_VTL:
	      	case LINK_TIE:
	      	case LINK_VTI:
			if(!strcmp(ed, "number1"))
			  tmp_lp.port = VIRTUAL_PORT_1;
			else if(!strcmp(ed, "number2"))
			  tmp_lp.port = VIRTUAL_PORT_2;
		break;

            case LINK_NUL:
                tmp_lp.port = NULL_PORT;

      		default: 
		break;
      		}
  	}
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
	case 0: 
			tmp_lp.calc_type = CALC_TI73;
    		gtk_widget_set_sensitive(button, TRUE);
	break;

	case 1:
    		tmp_lp.calc_type = CALC_TI82;
    		gtk_widget_set_sensitive(button, FALSE);
  	break;

	case 2:
	    	tmp_lp.calc_type = CALC_TI83;
	    	gtk_widget_set_sensitive(button, FALSE);
  	break;

	case 3:
    		tmp_lp.calc_type = CALC_TI83P;
    		gtk_widget_set_sensitive(button, TRUE);
  	break;

	case 4:
    		tmp_lp.calc_type = CALC_TI85;
    		gtk_widget_set_sensitive(button, FALSE);
  	break;

	case 5:
    		tmp_lp.calc_type = CALC_TI86;
    		gtk_widget_set_sensitive(button, FALSE);
  	break;

	case 6:
    		tmp_lp.calc_type = CALC_TI89;
    		gtk_widget_set_sensitive(button, TRUE);
  	break;

	case 7:
    		tmp_lp.calc_type = CALC_TI92;
    		gtk_widget_set_sensitive(button, FALSE);
  	break;

	case 8:
    		tmp_lp.calc_type = CALC_TI92P;
    		gtk_widget_set_sensitive(button, TRUE);
  	break;

	case 9:
    		tmp_lp.calc_type = CALC_V200;
    		gtk_widget_set_sensitive(button, TRUE);
	break;
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
  	if (togglebutton->active == TRUE)
    		ad = TRUE;
  	else
    		ad = FALSE;
}


GLADE_CB void
comm_spinbutton_delay_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
  	tmp_lp.delay =
    		gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}


GLADE_CB void
comm_spinbutton_timeout_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
  	tmp_lp.timeout =
    		gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}


GLADE_CB void
comm_button_log_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  	display_logfile_dbox();
}
