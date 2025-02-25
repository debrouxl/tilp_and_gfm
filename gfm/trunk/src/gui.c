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
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "gui.h"
#include "paths.h"
#include "tilibs.h"
#include "dialog.h"
#include "file.h"
#include "rwgroup.h"
#include "labels.h"
#include "ctree.h"
#include "filesel.h"
#include "cmdline.h"
#include "ungroup.h"

// Global Widget Access Structure
GFMWidget gfm_widget;

void enable_save(int state)
{
	GFMFile.saved = !state;
	gtk_widget_set_sensitive(gfm_widget.save, state);
}

void enable_tree(int state)
{
	GFMFile.opened = state;
	gtk_widget_set_sensitive(gfm_widget.tree, state);
}

GFM_EXPORT void on_open_clicked (GtkToolButton *toolbutton, gpointer user_data);

/* The Main Interface Launcher */
int launch_gfmgui(void)
{
	GtkBuilder *builder;
	GError* error = NULL;
	GtkWidget *widget;

	// Load the GFM Dialog from gfm.ui
	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file (builder, paths_build_builder("gfm.ui"), &error))
	{
		g_warning (_("Couldn't load builder file: %s\n"), error->message);
		g_error_free (error);
		return 0; // THIS RETURNS !
	}
	gtk_builder_connect_signals(builder, NULL);

	// Retrieve the dialog widget
	widget = GTK_WIDGET (gtk_builder_get_object (builder, "gfm_dbox"));

	// Global Widget Access
	gfm_widget.tree = GTK_WIDGET (gtk_builder_get_object(builder, "treeview1"));
	gfm_widget.model = GTK_WIDGET (gtk_builder_get_object(builder, "label6"));
	gfm_widget.entries = GTK_WIDGET (gtk_builder_get_object(builder, "label7"));
	gfm_widget.comment = GTK_WIDGET (gtk_builder_get_object(builder, "button1"));
	gfm_widget.ram = GTK_WIDGET (gtk_builder_get_object(builder, "label9"));
	gfm_widget.flash = GTK_WIDGET (gtk_builder_get_object(builder, "label10"));
	gfm_widget.save = GTK_WIDGET (gtk_builder_get_object(builder, "toolbutton3"));
	//gfm_widget.test = GTK_WIDGET (gtk_builder_get_object(builder, "label11"));
	gfm_widget.pbar = GTK_WIDGET (gtk_builder_get_object(builder, "progressbar1"));

	// Inits global vars
	enable_save(FALSE);
	enable_tree(FALSE);

	// Show the Widget
	ctree_init();
	gtk_widget_show(widget);

	if(cmdline_get() != NULL)
		on_open_clicked(NULL, (gpointer)cmdline_get());

	// Return
	return 0;
}

/* Callback Functions */

GFM_EXPORT void on_new_clicked (GtkToolButton *toolbutton, gpointer user_data)
{
	CalcModel model;
	int result;

	result = msgbox_three(_("TiGroup"), _("Single/Group"), _("File type?"));
	if(!result)
		return;

	model = msgbox_model();
	if(!model)
		return;

	file_create(result == MSGBOX_BUTTON1 ? TIFILE_TIGROUP : TIFILE_GROUP, model);

	g_free(GFMFile.filename);
	GFMFile.filename = NULL;
	enable_save(FALSE);
	enable_tree(TRUE);

	ctree_refresh();
	labels_refresh();
}

GFM_EXPORT void on_save_clicked (GtkToolButton *toolbutton, gpointer user_data)
{
	const gchar *fn = NULL;
	gchar *ext = NULL;
	gchar *filename = NULL;

	if(GFMFile.filename != NULL)
		filename = g_strdup(GFMFile.filename);

	if(GFMFile.type & TIFILE_TIGROUP)
	{
		ext = g_strdup("*.tig");
	}
	else if(GFMFile.type & TIFILE_GROUP)
	{
		if(ticalcs_dirlist_ve_count(GFMFile.trees.vars) > 1)
		{
			// Group file
			ext = g_strconcat("*.", tifiles_vartype2fext(GFMFile.model, 0x00), NULL);
			ext[4] = 'g';
		}
		else if(ticalcs_dirlist_ve_count(GFMFile.trees.vars) == 1)
		{
			// Single file
			GNode *parent, *child;
			VarEntry *ve;
			char * filename2;

			parent = g_node_nth_child(GFMFile.trees.vars, 0);
			child = g_node_nth_child(parent, 0);
			ve = (VarEntry *) (child->data);

			filename2 = ticonv_varname_to_filename(GFMFile.model, ve->name, ve->type);
			filename = g_strconcat(filename2, ".", tifiles_vartype2fext(GFMFile.model, ve->type), NULL);
			ticonv_gfe_free(filename2);
			ext = g_strconcat("*.", tifiles_vartype2fext(GFMFile.model, ve->type), NULL);
		}
		else
		{
			g_free(filename);
			return;
		}
	}

	fn = create_fsel(inst_paths.home_dir, filename, ext, TRUE);
	if(fn == NULL)
		return;
	g_free(filename);
	g_free(ext);

	file_save(fn);

	g_free(GFMFile.filename);
	GFMFile.filename = g_strdup(fn);

	enable_save(FALSE);
}


GFM_EXPORT void on_open_clicked (GtkToolButton *toolbutton, gpointer user_data)
{
	const gchar *fn;

	if(user_data == NULL)
	{
		if(GFMFile.contents.group || GFMFile.contents.tigroup)
		{
			int result = msgbox_two(MSGBOX_YESNO, _("Do you want to save previous file?"));
			if(result == MSGBOX_YES)
				on_save_clicked(toolbutton,user_data);
		}

		fn = create_fsel(inst_paths.home_dir, "", "*.73?;*.82?;*.83?;*.8X?;*.85?;*.86?;*.89?;*.92?;*.9x?;*.V2?;*.tig", FALSE);
		if(fn == NULL)
			return;
	}
	else
	{
		// command line
		fn = (const char *)user_data;
	}

	if(tifiles_file_is_tigroup(fn))
		GFMFile.type = TIFILE_TIGROUP;
	else if(tifiles_file_is_regular(fn))
		GFMFile.type = TIFILE_GROUP;
	else
		return;

	file_load(fn);

	g_free(GFMFile.filename);
	GFMFile.filename = g_strdup(fn);

	enable_save(FALSE);
	enable_tree(TRUE);

	ctree_refresh();
	labels_refresh();

	g_free(inst_paths.home_dir);
	inst_paths.home_dir = g_path_get_dirname(GFMFile.filename);
}


GFM_EXPORT void on_quit_clicked (GtkToolButton *toolbutton, gpointer user_data)
{
	file_destroy();
	gtk_main_quit();
}


GFM_EXPORT void on_gfm_dbox_destroy (GtkWidget *object, gpointer user_data)
{
	// Quit Main GTK Loop
	//printf("on_gfm_dbox_destroy\n");
}


GFM_EXPORT gboolean on_gfm_dbox_delete_event (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	if(!GFMFile.saved)
	{
		int result;
		
		result = msgbox_three(_("Save"), _("Quit"), _("File has not been saved yet. Do you want to quit?"));
		switch(result)
		{
		case MSGBOX_BUTTON1: 
			on_save_clicked(NULL, NULL);
			on_quit_clicked(NULL, NULL);
			return FALSE;
			break;
		case MSGBOX_BUTTON2:
			on_quit_clicked(NULL, NULL);
			return FALSE;
			break;
		case MSGBOX_NO:
		default:
			return TRUE; 
			break;
		}
	}
	else
		on_quit_clicked(NULL, NULL);

	return FALSE;
}


GFM_EXPORT void on_add_clicked (GtkToolButton *toolbutton, gpointer user_data)
{
	char **array, **ptr;
	CalcModel model;
	FileContent *content;
	int ret;
	unsigned int i;

	array = create_fsels(inst_paths.home_dir, "", "*.*");
	if(array == NULL)
		return;

	for(ptr = array; *ptr; ptr++)
	{
		char *fn = *ptr;

		if(tifiles_file_is_tigroup(fn))
		{
			msgbox_one(MSGBOX_ERROR, _("Importing of TiGroup files is not allowed."));
			return;
		}

		model = tifiles_file_get_model(fn);
		if(!tifiles_calc_are_compat(GFMFile.model, model))
		{
			msgbox_one(MSGBOX_ERROR, _("File is not compatible with current target."));
			return;
		}

		content = tifiles_content_create_regular(model);
		ret = tifiles_file_read_regular(fn, content);

		if (ret == 0)
		{
			for(i = 0; i < content->num_entries; i++)
			{
				VarEntry *ve = content->entries[i];

				if(ticalcs_dirlist_ve_exist(GFMFile.trees.vars, ve))
				{
					msgbox_one(MSGBOX_ERROR, _("The entry already exists. Skipped!"));
					continue;
				}

				ticalcs_dirlist_ve_add(GFMFile.trees.vars, ve);
			}
		}

		ret = tifiles_content_delete_regular(content);
	}

	enable_save(TRUE);
	enable_tree(TRUE);

	ctree_refresh();
	labels_refresh();
}

GFM_EXPORT void on_delete_clicked (GtkToolButton *toolbutton, gpointer user_data)
{
	GList *ptr;

	if(GFMFile.trees.vars == NULL)
		return;

	ctree_selection_get();

	for(ptr = gfm_widget.sel1; ptr; ptr = ptr->next)
	{
		VarEntry *ve = (VarEntry *)ptr->data;

		ticalcs_dirlist_ve_del(GFMFile.trees.vars, ve);
	}

	for(ptr = gfm_widget.sel2; ptr; ptr = ptr->next)
	{
		VarEntry *ve = (VarEntry *)ptr->data;

		ticalcs_dirlist_ve_del(GFMFile.trees.apps, ve);
	}

	ctree_selection_destroy();

	ctree_refresh();

	enable_save(TRUE);
}


GFM_EXPORT void on_mkdir_clicked (GtkToolButton *toolbutton, gpointer user_data)
{
	gchar *ret;
	GNode *node;
	VarEntry *ve;

	if(GFMFile.trees.vars == NULL)
		return;

	if(tifiles_calc_is_ti8x(GFMFile.model))
		return;

	ret = msgbox_input(_("New Folder"), _("folder"), _("Name of folder to create:"));
	if(ret == NULL)
		return;

	ret[8] = '\0';
	ve = tifiles_ve_create();
	strcpy(ve->name, ret);
	ve->type = tifiles_folder_type(GFMFile.model);

	node = g_node_new(ve);
	g_node_append(GFMFile.trees.vars, node);

	ctree_refresh();
	labels_refresh();
}

GFM_EXPORT void on_group_clicked (GtkButton *button, gpointer user_data)
{
	int result;
	char **array;

	result = msgbox_three(_("TiGroup"), _("Single/Group"), _("File type?"));
	if(!result)
		return;

	array = create_fsels(inst_paths.home_dir, "", "*.73?;*.82?;*.83?;*.8X?;*.85?;*.86?;*.89?;*.92?;*.9x?;*.V2?");
	if(array == NULL)
		return;

	gfm_tifiles_group((const char **)array, result == MSGBOX_BUTTON1 ? TIFILE_TIGROUP : TIFILE_GROUP);
}

GFM_EXPORT void on_ungroup_clicked (GtkButton *button, gpointer user_data)
{
	const gchar *fn;

	fn = create_fsel(inst_paths.home_dir, "", "*.73g;*.82g;*.83g;*.8Xg;*.85g;*.86g;*.89g;*.92g;*.9Xg;*.V2g;*.tig", FALSE);
	if(fn == NULL)
		return;

	if(tifiles_file_is_tigroup(fn))
		gfm_tifiles_ungroup(fn, TIFILE_TIGROUP);
	else if(tifiles_file_is_regular(fn))
		gfm_tifiles_ungroup(fn, TIFILE_GROUP);
	else
		return;
}
