/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
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

#include "gui.h"
#include "support.h"
#include "paths.h"
#include "tilibs.h"
#include "dialog.h"
#include "file.h"
#include "tifiles.h"

// Global Widget Access Structure
GFMWidget gfm_widget;

/* The Main Interface Launcher */
int launch_gfmgui(void)
{
    GladeXML *xml;
    GtkWidget *widget;

    // Load the GFM Dialog from gfm.glade
    xml = glade_xml_new(gfm_paths_build_glade("gfm.glade"), "gfm_dbox", NULL);

    // Glade File Error
    if (!xml)
        g_error("Failure GFM GUI (%s)!\n", __FILE__);
		
    // Connect The Symbols
    glade_xml_signal_autoconnect(xml);
		
    // Retrieve the dialog widget
    widget = glade_xml_get_widget(xml, "gfm_dbox");

    // Global Widget Access
	gfm_widget.tree = glade_xml_get_widget(xml, "treeview1");
	gfm_widget.model = glade_xml_get_widget(xml, "label1");
	gfm_widget.entries = glade_xml_get_widget(xml, "label3");
	gfm_widget.comment = glade_xml_get_widget(xml, "label5");
	gfm_widget.ram = glade_xml_get_widget(xml, "label2");
	gfm_widget.flash = glade_xml_get_widget(xml, "label4");
		
	// To write...
	
    
    // Show the Widget
    gtk_widget_show(widget);

    // Return
    return 0;
}

/* Callback Functions */

GLADE_CB void
on_gfm_dbox_destroy                    (GtkObject       *object,
                                        gpointer         user_data)
{
	// Quit Main GTK Loop
	gtk_main_quit();
}


GLADE_CB void
on_new_clicked                         (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	CalcModel model;
	int result;
	
	result = msgbox_three("TiGroup", "Single/Group", "File type?");
	model = msgbox_model();

	if (result == MSGBOX_YES)
		tigfile_create(model);
	else
		group_create(model);
}

GLADE_CB void
on_open_clicked                        (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	printf("<%s>\n", file_selector(inst_paths.home_dir, "", "*.*", FALSE));
}


GLADE_CB void
on_save_clicked                        (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{

}


GLADE_CB void
on_quit_clicked                        (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	gtk_main_quit();
}


GLADE_CB void
on_delete_clicked                      (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{

}

