/*
  Name: Group File Manager
  Copyright (C) 2006-2007 Tyler Cassidy, Romain Lievin, Kevin Kofler
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
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>

#include "support.h"
#include "dialog.h"
#include "paths.h"
#include "tilibs.h"

/* One Button Dialog Box */
int msgbox_one(int type, const char *message)
{
    GtkBuilder *builder;
    GError* error = NULL;
    GtkWidget *widget, *data;
    const gchar *image;

    // Load the One Button Dialog from dialogs1.ui
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file (builder, paths_build_builder("dialogs1.ui"), &error))
    {
        g_warning (_("Couldn't load builder file: %s\n"), error->message);
        g_error_free (error);
        return 0; // THIS RETURNS !
    }
    gtk_builder_connect_signals(builder, NULL);

    // Retrieve the Widget into data & widget
    widget = GTK_WIDGET (gtk_builder_get_object (builder, "dialog1"));

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
    data = GTK_WIDGET (gtk_builder_get_object (builder, "dialog1_label"));
    gtk_label_set_markup(GTK_LABEL(data), message);

    // Set the Image
    data = GTK_WIDGET (gtk_builder_get_object (builder, "dialog1_image"));
    gtk_image_set_from_stock(GTK_IMAGE(data), image, GTK_ICON_SIZE_DIALOG);

    // Run Dialog
    gtk_dialog_run(GTK_DIALOG(widget));

    // Destroy Dialog
    gtk_widget_destroy(widget);
    g_object_unref(builder);

    // Return
    return MSGBOX_YES;
}

/* Message Dialog with Two Buttons */
int msgbox_two(int type, const char *message)
{
    GtkBuilder *builder;
    GError* error = NULL;
    GtkWidget *widget, *data;
    int choice, ret;
    const gchar *image, *cancel_button, *ok_button;

    // Load the Two Button Dialog from dialogs2.ui
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file (builder, paths_build_builder("dialogs2.ui"), &error))
    {
        g_warning (_("Couldn't load builder file: %s\n"), error->message);
        g_error_free (error);
        return 0; // THIS RETURNS !
    }
    gtk_builder_connect_signals(builder, NULL);

    // Retrieve the Widget into data & widget
    widget = GTK_WIDGET (gtk_builder_get_object (builder, "dialog2"));
    gtk_dialog_set_alternative_button_order(GTK_DIALOG(widget), GTK_RESPONSE_OK,
                                            GTK_RESPONSE_CANCEL,-1);

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
    data = GTK_WIDGET (gtk_builder_get_object (builder, "dialog2_label"));
    gtk_label_set_markup(GTK_LABEL(data), message);

    // The Cancel Button
    data = GTK_WIDGET (gtk_builder_get_object (builder, "dialog2_cancelbutton"));
    gtk_button_set_label(GTK_BUTTON(data), cancel_button);

    // The Ok Button
    data = GTK_WIDGET (gtk_builder_get_object (builder, "dialog2_okbutton"));
    gtk_button_set_label(GTK_BUTTON(data), ok_button);

    // The Main Image
    data = GTK_WIDGET (gtk_builder_get_object (builder, "dialog2_image"));
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

    // Destroy Dialog
    gtk_widget_destroy(widget);
    g_object_unref(builder);

    // Return
    return ret;
}

/* Message Dialog with Three Buttons */
int msgbox_three(const char *button1, const char *button2, const char *message)
{
    GtkBuilder *builder;
    GError* error = NULL;
    GtkWidget *widget, *data;
    int choice, ret;

    // Load the Three Button Dialog from dialogs3.ui
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file (builder, paths_build_builder("dialogs3.ui"), &error))
    {
        g_warning (_("Couldn't load builder file: %s\n"), error->message);
        g_error_free (error);
        return 0; // THIS RETURNS !
    }
    gtk_builder_connect_signals(builder, NULL);

    // Retrieve the Widget into data & widget
    widget = GTK_WIDGET (gtk_builder_get_object (builder, "dialog3"));
    /* button1, button2, cancel */
    gtk_dialog_set_alternative_button_order(GTK_DIALOG(widget), GTK_RESPONSE_OK,
                                            GTK_RESPONSE_YES, GTK_RESPONSE_CANCEL,-1);

    // The Message
    data = GTK_WIDGET (gtk_builder_get_object (builder, "dialog3_label"));
    gtk_label_set_markup(GTK_LABEL(data), message);

    // Button 1
    data = GTK_WIDGET (gtk_builder_get_object (builder, "dialog3_button1"));
    gtk_button_set_label(GTK_BUTTON(data), button1);

    // The Ok Button
    data = GTK_WIDGET (gtk_builder_get_object (builder, "dialog3_button2"));
    gtk_button_set_label(GTK_BUTTON(data), button2);

    /* Launch the Dialog */
    choice = gtk_dialog_run(GTK_DIALOG(widget));
    switch (choice)
    {
        case GTK_RESPONSE_OK:
            ret = MSGBOX_BUTTON1;
            break;
        case GTK_RESPONSE_YES:
            ret = MSGBOX_BUTTON2;
            break;
        case GTK_RESPONSE_CANCEL:
            ret = MSGBOX_NO; // Just Cancel
            break;
        default:
            ret = MSGBOX_NO; // Just Cancel
            break;       
    }

    // Destroy Dialog
    gtk_widget_destroy(widget);
    g_object_unref(builder);

    // Return
    return ret;
}

/* Input Dialog */
char *msgbox_input(const char *title, const char *input, const char *question)
{
    GtkBuilder *builder;
    GError* error = NULL;
    GtkWidget *widget, *data;
    int result;
    gchar *ret = NULL;  

    // Load the Input Dialog from dialogs4.ui
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file (builder, paths_build_builder("dialogs4.ui"), &error))
    {
        g_warning (_("Couldn't load builder file: %s\n"), error->message);
        g_error_free (error);
        return 0; // THIS RETURNS !
    }
    gtk_builder_connect_signals(builder, NULL);

    // Retrieve the Widget into data & widget
    widget = GTK_WIDGET (gtk_builder_get_object (builder, "inputdialog"));
    gtk_dialog_set_alternative_button_order(GTK_DIALOG(widget), GTK_RESPONSE_OK,
                                            GTK_RESPONSE_CANCEL,-1);

    /* Set the Dialog up */
    // Set the message into the label ;)
    data = GTK_WIDGET (gtk_builder_get_object (builder, "input_label"));
    gtk_label_set_markup(GTK_LABEL(data), question);

    // If data in input variable, place in entrybox and select
    if (input != NULL)
    {
        // Set data
        data = GTK_WIDGET (gtk_builder_get_object (builder, "input_entry"));
        gtk_entry_set_text(GTK_ENTRY(data), input);
        
        // Select
        gtk_editable_select_region(GTK_EDITABLE(data), 0, -1);
    }

    // Set the Title
    gtk_window_set_title(GTK_WINDOW(widget), title);

    // Run Dialog
    result = gtk_dialog_run(GTK_DIALOG(widget));
    switch(result)
    {
        case GTK_RESPONSE_OK:
            data = GTK_WIDGET (gtk_builder_get_object (builder, "input_entry"));
            ret = g_strdup(gtk_entry_get_text(GTK_ENTRY(data)));
        break;
        case GTK_RESPONSE_CANCEL:
            ret = NULL;
        break;
        default: break;
    }

    // Destroy Dialog
    gtk_widget_destroy(widget);
    g_object_unref(builder);

    // Return
    return ret;
}

enum { COL_LABEL, COL_VALUE };	// columns in calc tree models

int msgbox_model(void)
{
    GtkBuilder *builder;
    GError* error = NULL;
    GtkWidget *widget, *data;
    int choice;
    CalcModel calc = CALC_NONE;
    char *str = NULL;
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Load the Combo Dialog from dialogs5.ui
    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file (builder, paths_build_builder("dialogs5.ui"), &error))
    {
        g_warning (_("Couldn't load builder file: %s\n"), error->message);
        g_error_free (error);
        return 0; // THIS RETURNS !
    }
    gtk_builder_connect_signals(builder, NULL);

    // Retrieve the Widget into data & widget
    widget = GTK_WIDGET (gtk_builder_get_object (builder, "combodialog"));
    gtk_dialog_set_alternative_button_order(GTK_DIALOG(widget), GTK_RESPONSE_OK,
                                            GTK_RESPONSE_CANCEL,-1);
    data = GTK_WIDGET (gtk_builder_get_object (builder, "combobox"));

    /* Launch the Dialog */
    choice = gtk_dialog_run(GTK_DIALOG(widget));
    switch (choice)
    {
        case GTK_RESPONSE_OK:
        case GTK_RESPONSE_YES:
        {
            model = gtk_combo_box_get_model(GTK_COMBO_BOX(data));

            if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data), &iter))
            {
                gtk_tree_model_get(model, &iter, COL_VALUE, &str, -1);
                if (str)
                {
                    calc = ticonv_string_to_model(str);
                    g_free(str);
                }
            }

        }
            break;
        case GTK_RESPONSE_CANCEL:
        default:
            break;       
    }

    gtk_widget_destroy(widget);
    g_object_unref(builder);

    return calc;
}
