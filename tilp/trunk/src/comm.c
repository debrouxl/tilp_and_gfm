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

/*
  Trick: button_xxx is an unused button so that toggling a cable button
  make the right port appear.
 */

// uncomment it to get more than 1 USB port
//#define MORE_USB_PORTS

static TicableLinkParam tmp_lp;
static gint ad;
static GtkWidget *button = NULL;
static GtkWidget *rb1, *rb2, *rb3, *rb4;

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
	memcpy(&tmp_lp, &options.lp, sizeof(TicableLinkParam));
	ad = options.auto_detect;

	// Port
	rb1 = glade_xml_get_widget(xml, "radiobutton_port_1");
	rb2 = glade_xml_get_widget(xml, "radiobutton_port_2");
	rb3 = glade_xml_get_widget(xml, "radiobutton_port_3");
	rb4 = glade_xml_get_widget(xml, "radiobutton_port_4");

	// Cable  
	data = glade_xml_get_widget(xml, "radiobutton_cable_xxx");
	gtk_widget_hide(data);
	data = glade_xml_get_widget(xml, "radiobutton_cable_tgl");
	if (tmp_lp.link_type == LINK_TGL)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_cable_par");
	if (tmp_lp.link_type == LINK_PAR)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_cable_tie");
	if (tmp_lp.link_type == LINK_TIE)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_cable_ser");
	if (tmp_lp.link_type == LINK_SER)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_cable_avr");
	if (tmp_lp.link_type == LINK_AVR)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_cable_vti");
	if (tmp_lp.link_type == LINK_VTI)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_cable_ugl");
	if (tmp_lp.link_type == LINK_UGL)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);

	// Calc
	button = glade_xml_get_widget(xml, "checkbutton_calc_auto");
	if (ad)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),
					     TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),
					     FALSE);
	data = glade_xml_get_widget(xml, "radiobutton_calc_ti73");
	if (tmp_lp.calc_type == CALC_TI73)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_calc_ti82");
	if (tmp_lp.calc_type == CALC_TI82)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_calc_ti83");
	if (tmp_lp.calc_type == CALC_TI83)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_calc_ti83p");
	if (tmp_lp.calc_type == CALC_TI83P)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_calc_ti85");
	if (tmp_lp.calc_type == CALC_TI85)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_calc_ti86");
	if (tmp_lp.calc_type == CALC_TI86)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_calc_ti89");
	if (tmp_lp.calc_type == CALC_TI89)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_calc_ti92");
	if (tmp_lp.calc_type == CALC_TI92)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_calc_ti92p");
	if (tmp_lp.calc_type == CALC_TI92P)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	data = glade_xml_get_widget(xml, "radiobutton_calc_v200");
	if (tmp_lp.calc_type == CALC_V200)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);

	// Misc
	data = glade_xml_get_widget(xml, "spinbutton_comm_timeout");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), tmp_lp.timeout);
	data = glade_xml_get_widget(xml, "spinbutton_comm_delay");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), tmp_lp.delay);
	data = glade_xml_get_widget(xml, "entry_comm_speed");
	switch (tmp_lp.baud_rate) {
	case BR9600:
		gtk_entry_set_text(GTK_ENTRY(data), "9600");
		break;
	case BR19200:
		gtk_entry_set_text(GTK_ENTRY(data), "19200");
		break;
	case BR38400:
		gtk_entry_set_text(GTK_ENTRY(data), "38400");
		break;
	case BR57600:
		gtk_entry_set_text(GTK_ENTRY(data), "57600");
		break;
	default:
		gtk_entry_set_text(GTK_ENTRY(data), "9600");
		break;
	}
	data = glade_xml_get_widget(xml, "checkbutton_comm_hfc");
	if (tmp_lp.hfc == HFC_ON)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data),
					     FALSE);
	while (gtk_events_pending())
		gtk_main_iteration();
	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) {
	case GTK_RESPONSE_OK:
		if (tilp_error(link_cable.exit()))
			break;	//return;
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
GLADE_CB void on_comm_dbox_show_port_1(GtkWidget * widget,
				       gpointer user_data)
{
	switch (tmp_lp.link_type) {
	case LINK_PAR:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Parallel port #1"));
		if (tmp_lp.port == PARALLEL_PORT_1)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(GTK_WIDGET(GTK_BIN(user_data)->child));
		gtk_widget_show(user_data);
		break;
	case LINK_AVR:
	case LINK_TGL:
	case LINK_SER:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Serial port #1"));
		if (tmp_lp.port == SERIAL_PORT_1)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(user_data);
		break;
	case LINK_TIE:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Virtual port #1 (emu)"));
		if (tmp_lp.port == VIRTUAL_PORT_1)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(user_data);
		break;
	case LINK_VTI:

#ifdef __WIN32__
		gtk_widget_hide(user_data);
		break;

#endif				/*  */
	case LINK_VTL:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Virtual port #1 (emu)"));
		if (tmp_lp.port == VIRTUAL_PORT_1)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(user_data);
		break;
	case LINK_UGL:
		gtk_button_set_label(GTK_BUTTON(user_data), "USB port #1");
		if (tmp_lp.port == USB_PORT_1)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(GTK_WIDGET(GTK_BIN(user_data)->child));
		gtk_widget_show(user_data);
		break;
	default:
		break;
	}
}
GLADE_CB void on_comm_dbox_show_port_2(GtkWidget * widget,
				       gpointer user_data)
{
	switch (tmp_lp.link_type) {
	case LINK_PAR:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Parallel port #2"));
		if (tmp_lp.port == PARALLEL_PORT_2)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(user_data);
		break;
	case LINK_AVR:
	case LINK_TGL:
	case LINK_SER:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Serial port #2"));
		if (tmp_lp.port == SERIAL_PORT_2)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(user_data);
		break;
	case LINK_TIE:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Virtual port #2 (tilp)"));
		if (tmp_lp.port == VIRTUAL_PORT_2)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(user_data);
		break;
	case LINK_VTI:

#ifdef __WIN32__
		gtk_widget_hide(user_data);
		break;

#endif				/*  */
	case LINK_VTL:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Virtual port #2 (tilp)"));
		if (tmp_lp.port == VIRTUAL_PORT_2)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(user_data);
		break;
	case LINK_UGL:

#ifdef MORE_USB_PORTS
		gtk_button_set_label(GTK_BUTTON(user_data), "USB port #2");
		if (tmp_lp.port == USB_PORT_2)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(GTK_WIDGET(GTK_BIN(user_data)->child));
		gtk_widget_show(user_data);

#else				/*  */
		gtk_widget_hide(user_data);

#endif				/*  */
		break;
	default:
		break;
	}
}
GLADE_CB void on_comm_dbox_show_port_3(GtkWidget * widget,
				       gpointer user_data)
{
	switch (tmp_lp.link_type) {
	case LINK_PAR:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Parallel port #3"));
		if (tmp_lp.port == PARALLEL_PORT_3)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(user_data);
		break;
	case LINK_AVR:
	case LINK_TGL:
	case LINK_SER:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Serial port #3"));
		if (tmp_lp.port == SERIAL_PORT_3)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(user_data);
		break;
	case LINK_TIE:
		gtk_widget_hide(user_data);
		break;
	case LINK_VTI:
		gtk_widget_hide(user_data);
		break;
	case LINK_VTL:
		gtk_widget_hide(user_data);
		break;
	case LINK_UGL:

#ifdef MORE_USB_PORTS
		gtk_button_set_label(GTK_BUTTON(user_data), "USB port #3");
		if (tmp_lp.port == USB_PORT_3)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(GTK_WIDGET(GTK_BIN(user_data)->child));
		gtk_widget_show(user_data);

#else				/*  */
		gtk_widget_hide(user_data);

#endif				/*  */
		break;
	default:
		break;
	}
}
GLADE_CB void on_comm_dbox_show_port_4(GtkWidget * widget,
				       gpointer user_data)
{
	switch (tmp_lp.link_type) {
	case LINK_PAR:
		gtk_widget_hide(user_data);
		break;
	case LINK_AVR:
	case LINK_TGL:
	case LINK_SER:
		gtk_button_set_label(GTK_BUTTON(user_data),
				     _("Serial port #4"));
		if (tmp_lp.port == SERIAL_PORT_4)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(user_data);
		break;
	case LINK_TIE:
		gtk_widget_hide(user_data);
		break;
	case LINK_VTI:
		gtk_widget_hide(user_data);
		break;
	case LINK_VTL:
		gtk_widget_hide(user_data);
		break;
	case LINK_UGL:

#ifdef MORE_USB_PORTS
		gtk_button_set_label(GTK_BUTTON(user_data), "USB port #4");
		if (tmp_lp.port == USB_PORT_4)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON
						     (user_data), TRUE);
		gtk_widget_show(GTK_WIDGET(GTK_BIN(user_data)->child));
		gtk_widget_show(user_data);

#else				/*  */
		gtk_widget_hide(user_data);

#endif				/*  */
		break;
	default:
		break;
	}
}
void comm_dbox_update_ports(void)
{
	on_comm_dbox_show_port_1(NULL, rb1);
	on_comm_dbox_show_port_2(NULL, rb2);
	on_comm_dbox_show_port_3(NULL, rb3);
	on_comm_dbox_show_port_4(NULL, rb4);
} GLADE_CB void
comm_radiobutton_cable_xxx_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
} GLADE_CB void
comm_radiobutton_cable_tie_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.link_type = LINK_TIE;
	if ((tmp_lp.port != VIRTUAL_PORT_1)
	    && (tmp_lp.port != VIRTUAL_PORT_2))
		tmp_lp.port = VIRTUAL_PORT_2;
	if (gtk_toggle_button_get_active(togglebutton))
		comm_dbox_update_ports();
}
GLADE_CB void
comm_radiobutton_cable_ser_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.link_type = LINK_SER;
	if ((tmp_lp.port != SERIAL_PORT_1)
	    && (tmp_lp.port != SERIAL_PORT_2)
	    && (tmp_lp.port != SERIAL_PORT_3)
	    && (tmp_lp.port != SERIAL_PORT_4))
		tmp_lp.port = SERIAL_PORT_2;
	if (gtk_toggle_button_get_active(togglebutton))
		comm_dbox_update_ports();
}
GLADE_CB void
comm_radiobutton_cable_vti_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.link_type = LINK_VTI;
	if ((tmp_lp.port != VIRTUAL_PORT_1)
	    && (tmp_lp.port != VIRTUAL_PORT_2))
		tmp_lp.port = VIRTUAL_PORT_2;
	if (gtk_toggle_button_get_active(togglebutton))
		comm_dbox_update_ports();
}
GLADE_CB void
comm_radiobutton_cable_tgl_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.link_type = LINK_TGL;
	if ((tmp_lp.port != SERIAL_PORT_1)
	    && (tmp_lp.port != SERIAL_PORT_2)
	    && (tmp_lp.port != SERIAL_PORT_3)
	    && (tmp_lp.port != SERIAL_PORT_4))
		tmp_lp.port = SERIAL_PORT_2;
	if (gtk_toggle_button_get_active(togglebutton))
		comm_dbox_update_ports();
}
GLADE_CB void
comm_radiobutton_cable_avr_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.link_type = LINK_AVR;
	if ((tmp_lp.port != SERIAL_PORT_1)
	    && (tmp_lp.port != SERIAL_PORT_2)
	    && (tmp_lp.port != SERIAL_PORT_3)
	    && (tmp_lp.port != SERIAL_PORT_4))
		tmp_lp.port = SERIAL_PORT_2;
	if (gtk_toggle_button_get_active(togglebutton))
		comm_dbox_update_ports();
}
GLADE_CB void
comm_radiobutton_cable_ugl_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.link_type = LINK_UGL;
	if ((tmp_lp.port != USB_PORT_1) && (tmp_lp.port != USB_PORT_2)
	    && (tmp_lp.port != USB_PORT_3)
	    && (tmp_lp.port != USB_PORT_4))
		tmp_lp.port = USB_PORT_1;
	if (gtk_toggle_button_get_active(togglebutton))
		comm_dbox_update_ports();
}
GLADE_CB void
comm_radiobutton_cable_par_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.link_type = LINK_PAR;
	if ((tmp_lp.port != PARALLEL_PORT_1) &&
	    (tmp_lp.port != PARALLEL_PORT_2)
	    && (tmp_lp.port != PARALLEL_PORT_3))
		tmp_lp.port = PARALLEL_PORT_1;
	if (gtk_toggle_button_get_active(togglebutton))
		comm_dbox_update_ports();
}
GLADE_CB void
comm_radiobutton_port_1_toggled(GtkToggleButton * togglebutton,
				gpointer user_data)
{
	switch (tmp_lp.link_type) {
	case LINK_PAR:
		tmp_lp.port = PARALLEL_PORT_1;
		break;
	case LINK_SER:
	case LINK_AVR:
	case LINK_TGL:
		tmp_lp.port = SERIAL_PORT_1;
		break;
	case LINK_VTL:
		tmp_lp.port = VIRTUAL_PORT_1;
		break;
	case LINK_VTI:
		tmp_lp.port = VIRTUAL_PORT_1;
		break;
	case LINK_TIE:
		tmp_lp.port = VIRTUAL_PORT_1;
		break;
	case LINK_UGL:
		tmp_lp.port = USB_PORT_1;
		break;
	default:
		tmp_lp.port = -1;
		break;
	}
}
GLADE_CB void
comm_radiobutton_port_2_toggled(GtkToggleButton * togglebutton,
				gpointer user_data)
{
	switch (tmp_lp.link_type) {
	case LINK_PAR:
		tmp_lp.port = PARALLEL_PORT_2;
		break;
	case LINK_SER:
	case LINK_AVR:
	case LINK_TGL:
		tmp_lp.port = SERIAL_PORT_2;
		break;
	case LINK_VTL:
		tmp_lp.port = VIRTUAL_PORT_2;
		break;
	case LINK_VTI:
		tmp_lp.port = VIRTUAL_PORT_2;
		break;
	case LINK_TIE:
		tmp_lp.port = VIRTUAL_PORT_2;
		break;
	case LINK_UGL:
		tmp_lp.port = USB_PORT_2;
		break;
	default:
		tmp_lp.port = -1;
		break;
	}
}
GLADE_CB void
cable_radiobutton_port_3_toggled(GtkToggleButton * togglebutton,
				 gpointer user_data)
{
	switch (tmp_lp.link_type) {
	case LINK_PAR:
		tmp_lp.port = PARALLEL_PORT_3;
		break;
	case LINK_AVR:
	case LINK_TGL:
	case LINK_SER:
		tmp_lp.port = SERIAL_PORT_3;
		break;
	case LINK_VTL:
		break;
	case LINK_VTI:
		break;
	case LINK_TIE:
		break;
	case LINK_UGL:
		tmp_lp.port = USB_PORT_3;
		break;
	default:
		tmp_lp.port = -1;
		break;
	}
}
GLADE_CB void
comm_radiobutton_port_4_toggled(GtkToggleButton * togglebutton,
				gpointer user_data)
{
	switch (tmp_lp.link_type) {
	case LINK_PAR:
		break;
	case LINK_SER:
	case LINK_AVR:
	case LINK_TGL:
		tmp_lp.port = SERIAL_PORT_4;
		break;
	case LINK_VTL:
		break;
	case LINK_VTI:
		break;
	case LINK_TIE:
		break;
	case LINK_UGL:
		tmp_lp.port = USB_PORT_4;
		break;
	default:
		tmp_lp.port = -1;
		break;
	}
}
GLADE_CB void
comm_radiobutton_calc_ti86_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.calc_type = CALC_TI86;
	gtk_widget_set_sensitive(button, FALSE);
} GLADE_CB void
comm_radiobutton_calc_ti73_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.calc_type = CALC_TI73;
	gtk_widget_set_sensitive(button, TRUE);
} GLADE_CB void
comm_radiobutton_calc_ti92_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.calc_type = CALC_TI92;
	gtk_widget_set_sensitive(button, FALSE);
} GLADE_CB void
comm_radiobutton_calc_ti82_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.calc_type = CALC_TI82;
	gtk_widget_set_sensitive(button, FALSE);
} GLADE_CB void
comm_radiobutton_calc_ti83_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.calc_type = CALC_TI83;
	gtk_widget_set_sensitive(button, FALSE);
} GLADE_CB void
comm_radiobutton_calc_ti83__toggled(GtkToggleButton * togglebutton,
				    gpointer user_data)
{
	tmp_lp.calc_type = CALC_TI83P;
	gtk_widget_set_sensitive(button, TRUE);
} GLADE_CB void
comm_radiobutton_calc_ti85_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.calc_type = CALC_TI85;
	gtk_widget_set_sensitive(button, FALSE);
} GLADE_CB void
comm_radiobutton_calc_ti89_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.calc_type = CALC_TI89;
	gtk_widget_set_sensitive(button, TRUE);
} GLADE_CB void
comm_radiobutton_calc_ti92__toggled(GtkToggleButton * togglebutton,
				    gpointer user_data)
{
	tmp_lp.calc_type = CALC_TI92P;
	gtk_widget_set_sensitive(button, TRUE);
} GLADE_CB void
comm_radiobutton_calc_v200_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	tmp_lp.calc_type = CALC_V200;
	gtk_widget_set_sensitive(button, FALSE);
} GLADE_CB void
comm_checkbutton_calc_auto_toggled(GtkToggleButton * togglebutton,
				   gpointer user_data)
{
	if (togglebutton->active == TRUE)
		ad = TRUE;

	else
		ad = FALSE;
}
GLADE_CB void comm_combo_speed_changed(GtkEditable * editable,
				       gpointer user_data)
{
	gchar *ed = "????";
	ed = gtk_editable_get_chars(editable, 0, -1);
	sscanf(ed, "%i", (int *) &tmp_lp.baud_rate);
} GLADE_CB void
comm_checkbutton_hfc_toggled(GtkToggleButton * togglebutton,
			     gpointer user_data)
{
	if (togglebutton->active == TRUE)
		tmp_lp.hfc = HFC_ON;

	else
		tmp_lp.hfc = HFC_OFF;
}
GLADE_CB void
comm_spinbutton_timeout_changed(GtkEditable * editable, gpointer user_data)
{
	tmp_lp.timeout =
	    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
} GLADE_CB void comm_spinbutton_delay_changed(GtkEditable * editable,
					      gpointer user_data)
{
	tmp_lp.delay =
	    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}
