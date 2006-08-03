/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  28/05/06 20:33 - cmdline.c
  
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

#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>

#include "cmdline.h"

static void my_log_handler(const gchar *log_domain,
                           GLogLevelFlags log_level,
                           const gchar *message,
                           gpointer user_data) { }

/* Launch Command Line Function */
void gfm_cmdline(void)
{
    // Show the Disclaimer
    printf("\nTHIS PROGRAM COMES WITH ABSOLUTELY NO WARRANTY\nPLEASE READ THE DOCUMENTATION FOR DETAILS\n\n");

    // Get rid of GTK+ Logging if need-be (GTK, GDK, GLib, libglade)
    #if !defined(_DEBUG)
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING | 
                             G_LOG_LEVEL_MESSAGE | 
                             G_LOG_LEVEL_INFO | 
                             G_LOG_LEVEL_DEBUG,
		                     my_log_handler, NULL); // GTK
    g_log_set_handler("Gdk", G_LOG_LEVEL_WARNING | 
                             G_LOG_LEVEL_MESSAGE | 
                             G_LOG_LEVEL_INFO | 
                             G_LOG_LEVEL_DEBUG,
		                     my_log_handler, NULL); // Gdk
    g_log_set_handler("GLib", G_LOG_LEVEL_WARNING | 
                              G_LOG_LEVEL_MESSAGE | 
                              G_LOG_LEVEL_INFO | 
                              G_LOG_LEVEL_MASK | 
                              G_LOG_FLAG_FATAL | 
                              G_LOG_FLAG_RECURSION | 
                              G_LOG_LEVEL_DEBUG,
                              my_log_handler, NULL); // GLib
    #endif
     
    return;
}
