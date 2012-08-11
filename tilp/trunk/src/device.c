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

#include "support.h"
#include "device.h"
#include "toolbar.h"
#include "ctree.h"
#include "clist.h"
#include "tilp_core.h"
#include "gtk_update.h"

static DeviceOptions tmp;
static GtkWidget* lbl;
static GtkWidget* om_cable;
static GtkWidget* om_calc;
static GtkWidget* om_port;

static GtkListStore *store = NULL;

enum { COL_CABLE, COL_PORT, COL_CALC };
#define CLIST_NVCOLS (3)          // 3 visible columns
#define CLIST_NCOLS  (3)          // 3 real columns

static GtkListStore* clist_create(GtkWidget *widget)
{
	GtkTreeView *view = GTK_TREE_VIEW(widget);
	GtkListStore *store2;
	GtkTreeModel *model;
	GtkCellRenderer *renderer;
	GtkTreeSelection *selection;
	const gchar *text[CLIST_NVCOLS] = { _("Cable"), _("Port"), _("Device") };
	gint i;

	store2 = gtk_list_store_new(CLIST_NCOLS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, -1);
	model = GTK_TREE_MODEL(store2);

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

	return store2;
}

static void clist_populate(GtkListStore *_store, int full)
{
	if(!full)
	{
		int i, n, *list;

		ticables_get_usb_devices(&list, &n);

		for(i = 0; i < n; i++)
		{
			GtkTreeIter iter;
			gchar** row = g_malloc0((CLIST_NVCOLS + 1) * sizeof(gchar *));

			gtk_list_store_append(_store, &iter);

			row[COL_CABLE] = g_strdup(list[i] == PID_TIGLUSB ? "SilverLink" : "DirectLink");
			row[COL_PORT] = g_strdup_printf("#%i", i+1);
			row[COL_CALC] = g_strdup((list[i] == PID_TIGLUSB) ? "" : ticables_usbpid_to_string(list[i]));

			gtk_list_store_set(_store, &iter, 
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

			gtk_list_store_append(_store, &iter);

			//calc = tilp_remap_from_usb(cable, calc);
			row[COL_CABLE] = g_strdup(ticables_model_to_string(i));
			row[COL_PORT] = g_strdup_printf("#%i", j);
			row[COL_CALC] = g_strdup(ticalcs_model_to_string(array[i][j]));

			gtk_list_store_set(_store, &iter, 
				COL_CABLE, row[COL_CABLE], COL_PORT, row[COL_PORT], COL_CALC, row[COL_CALC],
				-1);
			g_strfreev(row);
		}

		gtk_label_set_text(GTK_LABEL(lbl), "Done !");
		ticables_probing_finish(&array);
	}
}

static void list_refresh(GtkListStore *_store, int full)
{
	gtk_list_store_clear(_store);
	clist_populate(_store, full);
}

TILP_EXPORT gboolean comm_treeview1_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
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

	gtk_combo_box_set_active(GTK_COMBO_BOX(om_cable), cbm);
	gtk_combo_box_set_active(GTK_COMBO_BOX(om_port), cbp);
	gtk_combo_box_set_active(GTK_COMBO_BOX(om_calc), 
		cm >= CALC_NSPIRE ? cm-CALC_NSPIRE+13 : cm);

	g_strfreev(row_text);

	return FALSE;
}

//=========================================

gint display_device_dbox(void)
{
	GtkBuilder *builder;
	GError* error = NULL;
	GtkWidget *dbox;
	GtkWidget *data;
	gint result;

	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, tilp_paths_build_builder("device.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return 0; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	dbox = GTK_WIDGET (gtk_builder_get_object (builder, "device_dbox"));
	gtk_dialog_set_alternative_button_order(GTK_DIALOG(dbox), GTK_RESPONSE_OK,
	                                        GTK_RESPONSE_CANCEL,-1);
	lbl = GTK_WIDGET (gtk_builder_get_object (builder, "label7"));

	// Tree View
	data = GTK_WIDGET (gtk_builder_get_object (builder, "treeview1"));
	store = clist_create(data);
	gtk_widget_show_all(data);
	if(options.usb_avail)
		clist_populate(store, 0);

	// Cable  
	data = om_cable = GTK_WIDGET (gtk_builder_get_object (builder, "combobox1"));
	switch (options.cable_model) 
	{
	case CABLE_NUL:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 0);
	break;

	case CABLE_GRY:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 1);
	break;
		
	case CABLE_BLK:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 2);
	break;

	case CABLE_PAR:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 3);
	break;

	case CABLE_SLV:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 4);
	break;	

	case CABLE_USB:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 5);
	break;	

	case CABLE_VTI:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 6);
	break;

	case CABLE_TIE:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 7);
	break;

	case CABLE_DEV:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 8);
	break;

	default:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 0);
		break;
	}

	// Port
	data = om_port = GTK_WIDGET (gtk_builder_get_object (builder, "combobox2"));
	switch (options.cable_port) 
	{
	case PORT_0:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 0);
	break;
	case PORT_1:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 1);
	break;
	case PORT_2:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 2);
	break;
	case PORT_3:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 3);
	break;
	case PORT_4:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 4);
	break;
	}

	// Calc
	data = om_calc = GTK_WIDGET (gtk_builder_get_object (builder, "combobox3"));
	switch (options.calc_model) 
	{
	case CALC_NONE:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 0);
		break;

	case CALC_TI73:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 1);
		break;

	case CALC_TI80:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 2);
		break;

	case CALC_TI82:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 3);
		break;

	case CALC_TI83:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 4);
		break;

	case CALC_TI83P:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 5);
		break;

	case CALC_TI84P:
	case CALC_TI84P_USB:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 6);
		break;

	case CALC_TI85:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 7);
		break;

	case CALC_TI86:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 8);
		break;

	case CALC_TI89:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 9);
		break;

	case CALC_TI89T:
	case CALC_TI89T_USB:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 10);
		break;

	case CALC_TI92:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 11);
		break;

	case CALC_TI92P:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 12);
		break;

	case CALC_V200:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 13);
		break;

	case CALC_NSPIRE:
		gtk_combo_box_set_active(GTK_COMBO_BOX(data), 14);
		break;
	}

	// Timeout
	data = GTK_WIDGET (gtk_builder_get_object (builder, "spinbutton_comm_timeout"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), options.cable_timeout);

	// Delay
	data = GTK_WIDGET (gtk_builder_get_object (builder, "spinbutton_comm_delay"));
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(data), options.cable_delay);

	data = GTK_WIDGET (gtk_builder_get_object (builder, "checkbutton1"));
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


TILP_EXPORT void on_device_combobox1_changed (GtkComboBox *combobox, gpointer user_data)
{
	gint nitem = gtk_combo_box_get_active(combobox);

	switch(nitem)
	{
	case 0: tmp.cable_model = CABLE_NUL; break;
	case 1: tmp.cable_model = CABLE_GRY; break;
	case 2: tmp.cable_model = CABLE_BLK; break;
	case 3: tmp.cable_model = CABLE_PAR; break;
	case 4: tmp.cable_model = CABLE_SLV; break;
	case 5: tmp.cable_model = CABLE_USB; break;
	case 6: tmp.cable_model = CABLE_VTI; break;
	case 7: tmp.cable_model = CABLE_TIE; break;
	case 8: tmp.cable_model = CABLE_DEV; break;
	}

#ifdef __WIN32__
	if(tmp.cable_model == CABLE_DEV)
		gtk_combo_box_set_active(GTK_COMBO_BOX(om_cable), 0);
#endif
}


TILP_EXPORT void on_device_combobox2_changed (GtkComboBox *combobox, gpointer user_data)
{
	gint nitem = gtk_combo_box_get_active(combobox);

	switch(nitem)
	{
	case 0: tmp.cable_port = PORT_0; break;
	case 1: tmp.cable_port = PORT_1; break;
	case 2: tmp.cable_port = PORT_2; break;
	case 3: tmp.cable_port = PORT_3; break;
	case 4: tmp.cable_port = PORT_4; break;
	}
}


TILP_EXPORT void on_device_combobox3_changed (GtkComboBox *combobox, gpointer user_data)
{
	gint nitem = gtk_combo_box_get_active(combobox);

	switch(nitem)
	{
	case 0:  tmp.calc_model = CALC_NONE;   break;
	case 1:  tmp.calc_model = CALC_TI73;   break;
	case 2:  tmp.calc_model = CALC_TI80;   break;
	case 3:  tmp.calc_model = CALC_TI82;   break;
	case 4:  tmp.calc_model = CALC_TI83;   break;
	case 5:  tmp.calc_model = CALC_TI83P;  break;
	case 6:  tmp.calc_model = CALC_TI84P;  break;
	case 7:  tmp.calc_model = CALC_TI85;   break;
	case 8:  tmp.calc_model = CALC_TI86;   break;
	case 9:  tmp.calc_model = CALC_TI89;   break;
	case 10: tmp.calc_model = CALC_TI89T;  break;
	case 11: tmp.calc_model = CALC_TI92;   break;
	case 12: tmp.calc_model = CALC_TI92P;  break;
	case 13: tmp.calc_model = CALC_V200;   break;
	case 14: tmp.calc_model = CALC_NSPIRE; break;
	}
}


TILP_EXPORT void comm_checkbutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
	options.auto_detect = togglebutton->active;
}


TILP_EXPORT void comm_spinbutton_delay_changed(GtkEditable *editable, gpointer user_data)
{
	tmp.cable_delay = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}


TILP_EXPORT void comm_spinbutton_timeout_changed(GtkEditable *editable, gpointer user_data)
{
	tmp.cable_timeout = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(user_data));
}

TILP_EXPORT void comm_button_search_clicked(GtkButton  *button, gpointer user_data)
{
	list_refresh(store, !0);
}
