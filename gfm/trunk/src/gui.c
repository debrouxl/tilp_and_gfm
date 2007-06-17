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
#include "groups.h"
#include "labels.h"
#include "ctree.h"

// Global Widget Access Structure
GFMWidget gfm_widget;

void enable_save(int state)
{
	GFile.saved = !state;
	gtk_widget_set_sensitive(gfm_widget.save, state);
}

/*
// Nothing to do with GFM, just for test
static int cnt = 0;

static gint to_cb (gpointer data)
{
	gchar *str;

	str = g_strdup_printf("%04i", cnt += 50);
    gtk_label_set_text(GTK_LABEL(gfm_widget.test), str);
	g_free(str);

    return TRUE;
}
*/

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
	gfm_widget.model = glade_xml_get_widget(xml, "label6");
	gfm_widget.entries = glade_xml_get_widget(xml, "label7");
	gfm_widget.comment = glade_xml_get_widget(xml, "label8");
	gfm_widget.ram = glade_xml_get_widget(xml, "label9");
	gfm_widget.flash = glade_xml_get_widget(xml, "label10");
	gfm_widget.save = glade_xml_get_widget(xml, "toolbutton3");
	//gfm_widget.test = glade_xml_get_widget(xml, "label11");
	
    // Show the Widget
	enable_save(FALSE);
	ctree_init();
    gtk_widget_show(widget);

	//g_timeout_add(250, (GtkFunction)to_cb, NULL);

    // Return
    return 0;
}

/* Callback Functions */

GLADE_CB void
on_new_clicked                         (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	CalcModel model;
	int result;
	
	result = msgbox_three("TiGroup", "Single/Group", "File type?");
	model = msgbox_model();

	file_create(result == MSGBOX_YES ? TIFILE_TIGROUP : TIFILE_GROUP, model);

	g_free(GFile.filename);
	GFile.filename = NULL;
	enable_save(TRUE);

	ctree_refresh();
	labels_refresh();
}


GLADE_CB void
on_save_clicked                        (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	// Newly created file, ask for name
	if(GFile.filename == NULL)
	{
		gchar *fn, *ext;

		if(GFile.type == TIFILE_TIGROUP)
			ext = "*.tig";
		else if(GFile.type == TIFILE_GROUP)
			ext = "*.??g";

		fn = (char *)file_selector(inst_paths.home_dir, "", ext, FALSE);
		if(fn == NULL)
			return;

		//file_save(fn);

		g_free(GFile.filename);
		GFile.filename = g_strdup(fn);
	}
	else
	{
		//file_save(GFile.filename);
	}

	enable_save(FALSE);
}


GLADE_CB void
on_open_clicked                        (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	gchar *fn;

	if(GFile.contents.group || GFile.contents.tigroup)
	{
		int result = msgbox_two(MSGBOX_YESNO, _("Do you want to save previous file?"));
		if(result == MSGBOX_YES)
			on_save_clicked(toolbutton,user_data);
	}

	fn = (char *)file_selector(inst_paths.home_dir, "", "*.*", FALSE);
	if(fn == NULL)
		return;

	if(tifiles_file_is_tigroup(fn))
		GFile.type = TIFILE_TIGROUP;
	else
		GFile.type = TIFILE_GROUP;

	file_load(fn);

	g_free(GFile.filename);
	GFile.filename = g_strdup(fn);

	enable_save(FALSE);

	ctree_refresh();
	labels_refresh();
}


GLADE_CB void
on_quit_clicked                        (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	file_destroy();

	gtk_main_quit();
}


GLADE_CB void
on_gfm_dbox_destroy                    (GtkObject       *object,
                                        gpointer         user_data)
{
	// Quit Main GTK Loop
	printf("on_gfm_dbox_destroy\n");
}

GLADE_CB gboolean
on_gfm_dbox_delete_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	enable_save(TRUE);

	if(!GFile.saved)
	{
		int result;
		
		result = msgbox_three(_("Save"), _("Quit"), _("File has not been saved yet. Do you want to quit?"));
		switch(result)
		{
		case MSGBOX_BUTTON1: 
			on_save_clicked(NULL, NULL);
			return FALSE;
			break;
		case MSGBOX_BUTTON2:
			on_quit_clicked(NULL, NULL);
			return FALSE;
			break;
		case MSGBOX_NO: 
			return TRUE; 
			break;
		}
	}

	return FALSE;
}


GLADE_CB void
on_delete_clicked                      (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	GList *ptr;

	if(GFile.trees.vars == NULL)
		return;

	for(ptr = gfm_widget.sel1; ptr; ptr = ptr->next)
	{
		VarEntry *ve = (VarEntry *)ptr->data;

		printf("<%s>\n", ve->name);
	}
}


GLADE_CB void
on_mkdir_clicked                       (GtkToolButton   *toolbutton,
                                        gpointer         user_data)
{
	gchar *ret;
	GNode *node;
	VarEntry *ve;

	if(GFile.trees.vars == NULL)
		return;

	if(tifiles_calc_is_ti8x(GFile.model))
		return;

	ret = msgbox_input(_("New Folder"), _("folder"), _("Name of folder to create:"));
	if(ret == NULL)
		return;

	ret[8] = (char)'/0';
	ve = tifiles_ve_create();
	strcpy(ve->name, ret);
	ve->type = tifiles_folder_type(GFile.model);

	node = g_node_new(ve);
	g_node_append(GFile.trees.vars, node);

	ctree_refresh();
	labels_refresh();
}
