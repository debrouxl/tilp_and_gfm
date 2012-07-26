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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <time.h>

#include "support.h"
#include "clock.h"
#include "tilp_core.h"

static GtkBuilder *builder;
static gboolean modified;
static CalcClock tmp_clk;

static void update_fields(const CalcClock* clk)
{
	GtkWidget *data;

	data = GTK_WIDGET (gtk_builder_get_object (builder, "spinbutton1"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), clk->day);
	
	data = GTK_WIDGET (gtk_builder_get_object (builder, "combobox1"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(data), clk->month - 1);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "spinbutton3"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), clk->year);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "spinbutton4"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), clk->hours);
	
	data = GTK_WIDGET (gtk_builder_get_object (builder, "spinbutton5"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), clk->minutes);
	
	data = GTK_WIDGET (gtk_builder_get_object (builder, "spinbutton6"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), clk->seconds);
	
	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton1"));
	if(clk->time_format == 12)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "radiobutton2"));
	if(clk->time_format == 24)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data), TRUE);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "combobox2"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(data), clk->date_format - 1);
}

gint display_clock_dbox()
{
	GError* error = NULL;
	GtkWidget *dbox;
	gint result;
	int err;

	if(!(ticalcs_calc_features(calc_handle) & OPS_CLOCK))
	{
		gif->msg_box1(_("Error"), _("No clock support!"));
		return -1;
	}

	err = ticalcs_calc_isready(calc_handle);
	if(err)
	{
		tilp_err(err);
		return -1;
	}

	if(tilp_calc_check_version("2.08") < 0)
		return -1;

	err = ticalcs_calc_get_clock(calc_handle, &tmp_clk);
	if(err)
	{
		tilp_err(err);
		return -1;
	}

	tilp_info("%02i/%02i/%02i %02i:%02i:%02i, %s, %s\n", tmp_clk.day,
		tmp_clk.month, tmp_clk.year, tmp_clk.hours,
		tmp_clk.minutes, tmp_clk.seconds,
		(tmp_clk.time_format == 12) ? "12" : "24",
		ticalcs_clock_format2date(options.calc_model, tmp_clk.date_format));

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("clock.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return 0; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	dbox = GTK_WIDGET (gtk_builder_get_object (builder, "clock_dbox"));
	gtk_dialog_set_alternative_button_order(GTK_DIALOG(dbox), GTK_RESPONSE_OK,
	                                        GTK_RESPONSE_CANCEL,-1);
	update_fields(&tmp_clk);
	modified = FALSE;

	result = gtk_dialog_run(GTK_DIALOG(dbox));
	switch (result) 
	{
	case GTK_RESPONSE_OK:
		if(modified == FALSE)
			break;

		tilp_info("%02i/%02i/%02i %02i:%02i:%02i, %s, %s\n",
			tmp_clk.day, tmp_clk.month, tmp_clk.year,
			tmp_clk.hours, tmp_clk.minutes, tmp_clk.seconds,
			(tmp_clk.time_format == 12) ? "12" : "24",
			ticalcs_clock_format2date(options.calc_model, tmp_clk.date_format));

		err = ticalcs_calc_isready(calc_handle);
		if(err)
		{
			tilp_err(err);
			return -1;
		}

		err = ticalcs_calc_set_clock(calc_handle, &tmp_clk);
		if(err)
		{
			tilp_err(err);
			return -1;
		}

		modified = FALSE;
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
clock_radiobutton3_toggled(GtkToggleButton * togglebutton,
			   gpointer user_data)
{
	tmp_clk.state = 1;
} 

GLADE_CB void
clock_radiobutton4_toggled(GtkToggleButton * togglebutton,
			   gpointer user_data)
{
	tmp_clk.state = 0;
} 

GLADE_CB void
clock_radiobutton1_toggled(GtkToggleButton * togglebutton,
			   gpointer user_data)
{
	tmp_clk.time_format = 12;
	modified = TRUE;
} 

GLADE_CB void
clock_radiobutton2_toggled(GtkToggleButton * togglebutton,
			   gpointer user_data)
{
	tmp_clk.time_format = 24;
	modified = TRUE;
} 

GLADE_CB void
on_clock_combobox1_changed             (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	gint nitem = gtk_combo_box_get_active(combobox);
	tmp_clk.month = nitem + 1;
}

GLADE_CB void
on_clock_combobox2_changed             (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
	gint nitem = gtk_combo_box_get_active(combobox);
	tmp_clk.date_format = nitem + 1;
}

GLADE_CB void clock_spinbutton3_changed(GtkEditable * editable,
					gpointer user_data)
{
	tmp_clk.year =
	    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
	modified = TRUE;
} 

GLADE_CB void clock_spinbutton4_changed(GtkEditable * editable,
					  gpointer user_data)
{
	tmp_clk.hours =
	    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
	modified = TRUE;
} 

GLADE_CB void clock_spinbutton5_changed(GtkEditable * editable,
					  gpointer user_data)
{
	tmp_clk.minutes =
	    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
	modified = TRUE;
} 

GLADE_CB void clock_spinbutton6_changed(GtkEditable * editable,
					  gpointer user_data)
{
	tmp_clk.seconds =
	    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
	modified = TRUE;
} 

GLADE_CB void clock_spinbutton1_changed(GtkEditable * editable,
					  gpointer user_data)
{
	tmp_clk.day =
	    gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
	modified = TRUE;
} 

GLADE_CB void clock_sync_button_clicked(GtkButton * button,
					  gpointer user_data)
{
	time_t tt;
	struct tm *lt;
	CalcClock tc;
	int err;

	time(&tt);
	lt = localtime(&tt);
	memcpy(&tc, &tmp_clk, sizeof(CalcClock));
	tc.day = lt->tm_mday;
	tc.month = lt->tm_mon + 1;
	tc.year = lt->tm_year + 1900;
	tc.hours = lt->tm_hour;
	tc.minutes = lt->tm_min;
	tc.seconds = lt->tm_sec;

	err = ticalcs_calc_isready(calc_handle);
	if(err)
	{
		tilp_err(err);
		return;
	}

	err = ticalcs_calc_set_clock(calc_handle, &tc);
	if(err)
	{
		tilp_err(err);
		return;
	}

	update_fields(&tc);
	modified = FALSE;
}
