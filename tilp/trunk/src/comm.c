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

#include <gtk/gtk.h>
#include <glade/glade.h>
#include <string.h>

#include "comm.h"
#include "toolbar.h"
#include "ctree.h"
#include "tilp_core.h"

// uncomment it to get more than 1 USB port
//#define MORE_USB_PORTS

static TicableLinkParam tmp_lp;
static gint ad;
static GtkWidget *button = NULL;

gint display_comm_dbox()
{
	GladeXML *xml;
	GtkWidget *dbox;
	GtkWidget *data;
	gint result;

	xml = glade_xml_new
	    (tilp_paths_build_glade("comm-2.glade"), "comm_dbox", PACKAGE);
	if (!xml)
		g_error(_("comm.c: GUI loading failed !\n"));
	glade_xml_signal_autoconnect(xml);

	dbox = glade_xml_get_widget(xml, "comm_dbox");
	ad = options.auto_detect;

	// Cable  
	data = glade_xml_get_widget(xml, "entry_comm_cable");
	switch (options.lp.link_type) {
	case LINK_TGL:
	  gtk_entry_set_text(GTK_ENTRY(data), "GrayLink");
	  break;
		
	case LINK_SER:
	  gtk_entry_set_text(GTK_ENTRY(data), "BlackLink");
	  break;

	case LINK_PAR:
	  gtk_entry_set_text(GTK_ENTRY(data), "ParallelLink");
	  break;

	case LINK_AVR:
	  gtk_entry_set_text(GTK_ENTRY(data), "AvrLink");
	  break;

	case LINK_VTL:
	  gtk_entry_set_text(GTK_ENTRY(data), "virtual");
	  break;

	case LINK_TIE:
	  gtk_entry_set_text(GTK_ENTRY(data), "TiEmu");
	  break;

	case LINK_VTI:
	  gtk_entry_set_text(GTK_ENTRY(data), "VTi");
	  break;

	case LINK_SLV:
	  gtk_entry_set_text(GTK_ENTRY(data), "SilverLink");
	  break;
	
	default:
	  gtk_entry_set_text(GTK_ENTRY(data), "GrayLink");
	  break;
	}

	// Port
	data = glade_xml_get_widget(xml, "entry_comm_port");
	switch (options.lp.port) {
	case PARALLEL_PORT_1:
	case SERIAL_PORT_1:
	case USB_PORT_1:
	case VIRTUAL_PORT_1:
	  gtk_entry_set_text(GTK_ENTRY(data), "#1");
	  break;
	 
	case PARALLEL_PORT_2:
	case SERIAL_PORT_2:
	case USB_PORT_2:
	case VIRTUAL_PORT_2:
	  gtk_entry_set_text(GTK_ENTRY(data), "#2");
	  break;

	case PARALLEL_PORT_3:
	case SERIAL_PORT_3:
	case USB_PORT_3:
	  gtk_entry_set_text(GTK_ENTRY(data), "#3");
	  break;

	case SERIAL_PORT_4:
	case USB_PORT_4:
	  gtk_entry_set_text(GTK_ENTRY(data), "#4");
	  break;
	  
	case USER_PORT:
	  gtk_entry_set_text(GTK_ENTRY(data), "custom");
	  break;

	default:
	  gtk_entry_set_text(GTK_ENTRY(data), "#2");
	  break;
	}

	// Calc
	data = glade_xml_get_widget(xml, "entry_comm_calc");
	switch (options.lp.calc_type) {
	case CALC_TI73:
	  gtk_entry_set_text(GTK_ENTRY(data), "TI73");
	  break;
	  
	case CALC_TI82:
	  gtk_entry_set_text(GTK_ENTRY(data), "TI82");
	  break;

	case CALC_TI83:
	  gtk_entry_set_text(GTK_ENTRY(data), "TI83");
	  break;
	  
	case CALC_TI83P:
	  gtk_entry_set_text(GTK_ENTRY(data), "TI83+");
	  break;
	  
	case CALC_TI85:
	  gtk_entry_set_text(GTK_ENTRY(data), "TI85");
	  break;
	  
	case CALC_TI86:
	  gtk_entry_set_text(GTK_ENTRY(data), "TI86");
	  break;
	  
	case CALC_TI89:
	  gtk_entry_set_text(GTK_ENTRY(data), "TI89");
	  break;
	  
	case CALC_TI92:
	  gtk_entry_set_text(GTK_ENTRY(data), "TI92");
	  break;
	  
	case CALC_TI92P:
	  gtk_entry_set_text(GTK_ENTRY(data), "TI92+");
	  break;
	  
	case CALC_V200:
	  gtk_entry_set_text(GTK_ENTRY(data), "V200PLT");
	  break;
	
	default:
	  gtk_entry_set_text(GTK_ENTRY(data), "TI89");
	  break;
	}

	// Auto-detect
	button = glade_xml_get_widget(xml, "checkbutton_calc_auto");
	if (ad)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),
					     TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),
					     FALSE);

	// Timeout
	data = glade_xml_get_widget(xml, "spinbutton_comm_timeout");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), options.lp.timeout);
	
	// Delay
	data = glade_xml_get_widget(xml, "spinbutton_comm_delay");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), options.lp.delay);

	// Avoid callbacks
	memcpy(&tmp_lp, &options.lp, sizeof(TicableLinkParam));
	
	// Loop
	while (gtk_events_pending())
		gtk_main_iteration();
 loop:
	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) {
	case GTK_RESPONSE_OK:
		if (tilp_error(link_cable.exit()))
		  goto loop;//break;	//return;
		memcpy(&options.lp, &tmp_lp, sizeof(TicableLinkParam));
		ticable_set_param(&options.lp);
		tilp_error(ticable_set_cable
			   (options.lp.link_type, &link_cable));
		ticalc_set_cable(&link_cable);
		ticalc_set_calc(options.lp.calc_type, &ti_calc);
		if (tilp_error(link_cable.init()))
			break;	//return;
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



void
comm_combo_cable_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
  gchar *ed = "";
  ed = gtk_editable_get_chars(editable, 0, -1);

  if(!strcmp(ed, "GrayLink"))
    tmp_lp.calc_type = LINK_TGL;
  else if(!strcmp(ed, "BlackLink"))
    tmp_lp.calc_type = LINK_SER;
  else if(!strcmp(ed, "SilverLink"))
    tmp_lp.calc_type = LINK_SLV;
  else if(!strcmp(ed, "parallel"))
    tmp_lp.calc_type = LINK_PAR;
  else if(!strcmp(ed, "AVRlink"))
    tmp_lp.calc_type = LINK_AVR;
  else if(!strcmp(ed, "VTi"))
    tmp_lp.calc_type = LINK_VTI;
  else if(!strcmp(ed, "TiEmu"))
    tmp_lp.calc_type = LINK_TIE;
  else if(!strcmp(ed, "virtual"))
    tmp_lp.calc_type = LINK_VTL;
  else {
    DISPLAY("Warning: value not in list: '%s' (combo_cable_changed).\n", ed);
  }
}


void
comm_combo_port_changed                (GtkEditable     *editable,
                                        gpointer         user_data)
{
  gchar *ed = "";
  ed = gtk_editable_get_chars(editable, 0, -1);
  
  if(!strcmp(ed, "custom"))
    tmp_lp.calc_type = USER_PORT;
  else {
    switch(tmp_lp.link_type)
      {
      case LINK_TGL:
      case LINK_SER:
      case LINK_AVR:
	if(!strcmp(ed, "custom"))
	  tmp_lp.port = USER_PORT;
	else if(!strcmp(ed, "#1"))
	  tmp_lp.port = SERIAL_PORT_1;
	else if(!strcmp(ed, "#2"))
	  tmp_lp.port = SERIAL_PORT_2;
	else if(!strcmp(ed, "#3"))
	  tmp_lp.port = SERIAL_PORT_3;
	else if(!strcmp(ed, "#4"))
	  tmp_lp.port = SERIAL_PORT_4;
	break;

      case LINK_SLV:
	if(!strcmp(ed, "custom"))
	  tmp_lp.port = USER_PORT;
	else if(!strcmp(ed, "#1"))
	  tmp_lp.port = USB_PORT_1;
	else if(!strcmp(ed, "#2"))
	  tmp_lp.port = USB_PORT_2;
	else if(!strcmp(ed, "#3"))
	  tmp_lp.port = USB_PORT_3;
	else if(!strcmp(ed, "#4"))
	  tmp_lp.port = USB_PORT_4;
	break;

      case LINK_PAR:
	if(!strcmp(ed, "custom"))
	  tmp_lp.port = USER_PORT;
	else if(!strcmp(ed, "#1"))
	  tmp_lp.port = PARALLEL_PORT_1;
	else if(!strcmp(ed, "#2"))
	  tmp_lp.port = PARALLEL_PORT_2;
	else if(!strcmp(ed, "#3"))
	  tmp_lp.port = PARALLEL_PORT_3;
	break;
	
      case LINK_VTL:
      case LINK_TIE:
      case LINK_VTI:
	if(!strcmp(ed, "#1"))
	  tmp_lp.port = VIRTUAL_PORT_1;
	else if(!strcmp(ed, "#2"))
	  tmp_lp.port = VIRTUAL_PORT_2;
	break;

      default: 
	break;
      }
  }
}


void
comm_entry_calc_changed                (GtkEditable     *editable,
                                        gpointer         user_data)
{
  gchar *ed = "";
  ed = gtk_editable_get_chars(editable, 0, -1);

  if(!strcmp(ed, "TI73")) {
    tmp_lp.calc_type = CALC_TI73;
    gtk_widget_set_sensitive(button, TRUE);
  } else if(!strcmp(ed, "TI82")) {
    tmp_lp.calc_type = CALC_TI82;
    gtk_widget_set_sensitive(button, FALSE);
  } else if(!strcmp(ed, "TI83")) {
    tmp_lp.calc_type = CALC_TI83;
    gtk_widget_set_sensitive(button, FALSE);
  } else if(!strcmp(ed, "TI83+")) {
    tmp_lp.calc_type = CALC_TI83P;
    gtk_widget_set_sensitive(button, TRUE);
  } else if(!strcmp(ed, "TI85")) {
    tmp_lp.calc_type = CALC_TI85;
    gtk_widget_set_sensitive(button, FALSE);
  } else if(!strcmp(ed, "TI86")) {
    tmp_lp.calc_type = CALC_TI86;
    gtk_widget_set_sensitive(button, FALSE);
  } else if(!strcmp(ed, "TI89")) {
    tmp_lp.calc_type = CALC_TI89;
    gtk_widget_set_sensitive(button, TRUE);
  } else if(!strcmp(ed, "TI92")) {
    tmp_lp.calc_type = CALC_TI92;
    gtk_widget_set_sensitive(button, FALSE);
  } else if(!strcmp(ed, "TI92+")) {
    tmp_lp.calc_type = CALC_TI92P;
    gtk_widget_set_sensitive(button, TRUE);
  } else if(!strcmp(ed, "V200PLT")) {
    tmp_lp.calc_type = CALC_V200;
    gtk_widget_set_sensitive(button, TRUE);
  } else {
    tmp_lp.calc_type = CALC_TI89;
    DISPLAY("Warning: value not in list: '%s' (entry_calc_changed).\n", ed);
  }
}


void
comm_checkbutton_calc_auto_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if (togglebutton->active == TRUE)
    ad = TRUE;
  else
    ad = FALSE;
}


void
comm_spinbutton_delay_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_lp.delay =
    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}


void
comm_spinbutton_timeout_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_lp.timeout =
    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}
