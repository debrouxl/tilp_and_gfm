/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  04/06/06 17:04 - gui.c

  This program is free software you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#include <glade/glade.h>

#include "folder_tree.h"
#include "gfm.h"
#include "gui.h"
#include "support.h"
#include "paths.h"

// Global Widget Access Structure
GFMWidget gfm_widget;

/* The Main Interface Launcher */
int launch_gfmgui(void)
{
    GladeXML *xml;
    GtkWidget *widget, *data;
    int pane_center, x, y;

    // Load the GFM Dialog from gfm.glade
    xml = glade_xml_new(gfm_paths_build_glade("gfm.glade"), "gfm_dbox", NULL);

    // Glade File Error
    if (!xml)
        g_error("Failure GFM GUI (%s)!\n", __FILE__);

    // Connect The Symbols
    glade_xml_signal_autoconnect(xml);

    // Retrieve the rom8x_dialog widget
    widget = glade_xml_get_widget(xml, "gfm_dbox");

    // Global Widget Access
    gfm_widget.group_tree = glade_xml_get_widget(xml, "group_tree"); // Group Tree
    gfm_widget.comp_tree = glade_xml_get_widget(xml, "folder_tree"); // Folder Tree
    gfm_widget.current_folder = glade_xml_get_widget(xml, "folder_label"); // Current Folder Label
    gfm_widget.group_files = glade_xml_get_widget(xml, "groupfile_numfiles_label"); // # files in Group
    gfm_widget.group_filesize = glade_xml_get_widget(xml, "groupfile_filesize_label"); // Size of Group

    // Set it up so its 50/50
    data = glade_xml_get_widget(xml, "hpaned1");
    gtk_window_get_size(GTK_WINDOW(widget), &x, &y);
    pane_center = (x - 25) / 2;
    gtk_paned_set_position(GTK_PANED(data), pane_center);

    // Setup the Group Tree
    // todo

    // Setup the Folder Tree
    folder_tree_init(); // Init
    folder_tree_refresh(); // Refresh Folder Tree View

    // Show the Widget
    gtk_widget_show(widget);

    // Return
    return 0;
}

/* Callback Functions */
/* The Destroy Dialog Event */
GLADE_CB void gfm_main_destroy(GtkObject *object, gpointer user_data)
{
         // Quit Main GTK Loop
         gtk_main_quit();
}

// Not Used yet!
/*
void
on_folder_tree_drag_begin(GtkWidget * widget,
			  GdkDragContext * drag_context,
			  gpointer user_data)
{

}


void
on_folder_tree_drag_data_get(GtkWidget * widget,
			     GdkDragContext * drag_context,
			     GtkSelectionData * data,
			     guint info, guint time, gpointer user_data)
{

}


void
on_folder_tree_drag_data_received(GtkWidget * widget,
				  GdkDragContext * drag_context,
				  gint x,
				  gint y,
				  GtkSelectionData * data,
				  guint info,
				  guint time, gpointer user_data)
{

}


gboolean
on_group_tree_button_press_event(GtkWidget * widget,
				 GdkEventButton * event,
				 gpointer user_data)
{

    return FALSE;
}


void
on_group_tree_drag_begin(GtkWidget * widget,
			 GdkDragContext * drag_context, gpointer user_data)
{

}


void
on_group_tree_drag_data_get(GtkWidget * widget,
			    GdkDragContext * drag_context,
			    GtkSelectionData * data,
			    guint info, guint time, gpointer user_data)
{

}


void
on_group_tree_drag_data_received(GtkWidget * widget,
				 GdkDragContext * drag_context,
				 gint x,
				 gint y,
				 GtkSelectionData * data,
				 guint info,
				 guint time, gpointer user_data)
{

}


gboolean
on_group_tree_key_press_event(GtkWidget * widget,
			      GdkEventKey * event, gpointer user_data)
{

    return FALSE;
}


void on_users_manual1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_manpage1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_bookmarks1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_tis_web_site1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_calculator_software1_activate(GtkMenuItem * menuitem,
				 gpointer user_data)
{

}


void on_ticalcorg1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_tigenorg1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_ti_frorg1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_the_lpg1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_tilps_web_site1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_bug_report1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_change_log1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_about1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_add1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


GLADE_CB void on_rename1_activate(GtkMenuItem *menuitem, gpointer user_data)


void on_refresh1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_delete1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}



void on_delete2_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_new_folder1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_select_all1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_unselect_all1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void
on_go_to_parent_directory1_activate(GtkMenuItem * menuitem,
				    gpointer user_data)
{

}



void on_refresh4_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_groups1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_ungroup1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_group1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


void on_options1_activate(GtkMenuItem * menuitem, gpointer user_data)
{

}


*/
