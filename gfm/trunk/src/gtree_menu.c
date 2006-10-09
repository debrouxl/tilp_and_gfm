/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  04/10/06 19:56 - gtree_menu.c

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

#include <stdio.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include "dialog.h"
#include "gfm.h"
#include "group_tree.h"
#include "gtree_menu.h"
#include "gui.h"
#include "paths.h"
#include "support.h"

/* Load Menu Function */
GtkWidget *create_group_menu(void)
{
  GladeXML *xml;
  GtkWidget *menu;
  gpointer data;
	
  xml = glade_xml_new(gfm_paths_build_glade("gfm.glade"), "group_menu", NULL);

  // Glade File Error
  if (!xml)
    g_error("GUI loading failed!\n");

  // Connect Signals
  glade_xml_signal_autoconnect(xml);
  
  // Load the Menu Now
  menu = glade_xml_get_widget(xml, "group_menu");

  // Return the Menu
  return menu;
}
