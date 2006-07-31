/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy
  Copyright (C) 2006 Romain Lievin
  04/06/06 16:35 - dialog.c
  
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
#include <string.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include "dialog.h"
#include "paths.h"

/* Error Dialog Box */
int msgbox_error(const char *message)
{
    // Show Message Box
    msgbox_one(MSGBOX_ERROR, message);
    
    // Return
    return MSGBOX_YES;
}

/* One Button Dialog Box */
int msgbox_one(int type, const char *message)
{
    GladeXML *xml;
    GtkWidget *widget, *data;
    const gchar *image;
    
    // Load the One Button Dialog from dialogs.glade
    xml = glade_xml_new(gfm_paths_build_glade("dialogs.glade"), "dialog1", NULL);
    
    // Glade File Error
    if (!xml)
       g_error("Failure Loading GUI Dialog!\n", __FILE__);
       
    // Connect The Symbols
    glade_xml_signal_autoconnect(xml);
    
    // Retrieve the Widget into data & widget
    widget = glade_xml_get_widget(xml, "dialog1");
    
    /* Set some Stuff */
    switch(type)
    {
        // Error
        case MSGBOX_ERROR:
             image = "gtk-dialog-error"; // The Image
        break;
        // Information
        case MSGBOX_INFO:
             image = "gtk-dialog-info"; // The Image
        break;
        // Default - Error
        default:
             image = "gtk-dialog-error"; // The Image
        break;
    }
    
    /* Set the Dialog up */
    // Set the message into the label ;)
    data = glade_xml_get_widget(xml, "dialog1_label");
    gtk_label_set_markup(GTK_LABEL(data), message);
    
    // Set the Image
    data = glade_xml_get_widget(xml, "dialog1_image");
    gtk_image_set_from_stock(GTK_IMAGE(data), image, GTK_ICON_SIZE_DIALOG);
    
    // Run Dialog
    gtk_dialog_run(GTK_DIALOG(widget));
    
    // Destroy Dialog
    gtk_widget_destroy(widget);
    
    // Return
    return MSGBOX_YES;
}

/* Message Dialog with Two Buttons */
int msgbox_two(int type, const char *message)
{
    GladeXML *xml;
    GtkWidget *widget, *data;
    int choice, ret;
    gchar *image, *cancel_button, *ok_button;
    
    // Load the Two Button Dialog from dialogs.glade
    xml = glade_xml_new(gfm_paths_build_glade("dialogs.glade"), "dialog2", NULL);
    
    // Glade File Error
    if (!xml)
       g_error("Failure Loading GUI Dialog!\n", __FILE__);
       
    // Connect The Symbols
    glade_xml_signal_autoconnect(xml);
    
    // Retrieve the Widget into data & widget
    widget = glade_xml_get_widget(xml, "dialog2");
    
    /* Set some Stuff */
    switch(type)
    {
        // Continue or Cancel?
        case MSGBOX_CONTINUE:
             image = "gtk-dialog-info"; // The Image
             cancel_button = "_Cancel"; // Cancel Button
             ok_button = "C_ontinue"; // Ok Button
        break;
        // Yes or No
        case MSGBOX_YESNO:
             image = "gtk-dialog-question"; // The Image
             cancel_button = "_No"; // Cancel Button
             ok_button = "_Yes"; // Ok Button
        break;
        // Default
        case MSGBOX_TWO:
        default:
             image = "gtk-dialog-info"; // The Image
             cancel_button = "_Cancel"; // Cancel Button
             ok_button = "_Ok"; // Ok Button
        break;
    }
    
    // The Message
    data = glade_xml_get_widget(xml, "dialog2_label");
    gtk_label_set_markup(GTK_LABEL(data), message);
    
    // The Cancel Button
    data = glade_xml_get_widget(xml, "dialog2_cancelbutton");
    gtk_button_set_label(GTK_BUTTON(data), cancel_button);
    
    // The Ok Button
    data = glade_xml_get_widget(xml, "dialog2_okbutton");
    gtk_button_set_label(GTK_BUTTON(data), ok_button);
    
    // The Main Image
    data = glade_xml_get_widget(xml, "dialog2_image");
    gtk_image_set_from_stock(GTK_IMAGE(data), image, GTK_ICON_SIZE_DND);
    
    /* Launch the Dialog */
    choice = gtk_dialog_run(GTK_DIALOG(widget));
    switch (choice)
    {
        case GTK_RESPONSE_OK:
             ret = MSGBOX_YES;
             break;
        case GTK_RESPONSE_CANCEL:
             ret = MSGBOX_NO; // Just Cancel
             break;
        default:
             ret = MSGBOX_NO; // Just Cancel
             break;       
    }
    gtk_widget_destroy(widget);
    
    // Return
    return ret;
}
