/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  12/10/06 20:39 - group_file.c

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

/*
	Manage creation, loading and saving of TiGroup/Group file 
	from/to GFileStruct structure.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <gtk/gtk.h>

#include "dialog.h"
#include "file.h"
#include "gui.h"
#include "labels.h"
#include "tilibs.h"
#include "rwgroup.h"
#include "support.h"

GFileStruct GFMFile;

int	tigroup_create(CalcModel model)
{
	TreeInfo *ti;

	// Create TiGroup file
	GFMFile.contents.tigroup = tifiles_content_create_tigroup(model, 0);
	GFMFile.type = TIFILE_TIGROUP;
	GFMFile.model = GFMFile.contents.tigroup->model;

	// Recreate folder listing (ticalcs2 compatible)
	GFMFile.trees.vars = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFMFile.contents.tigroup->model;
	ti->type = VAR_NODE_NAME;
	GFMFile.trees.vars->data = ti;

	GFMFile.trees.apps = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFMFile.contents.tigroup->model;
	ti->type = APP_NODE_NAME;
	GFMFile.trees.apps->data = ti;
  
	return 0;
}

typedef struct
{
	int		found;
	GNode*	node;
	gchar	folder[20];
} SearchArg;

static void	search_for_folder(GNode *node, gpointer data)
{
	SearchArg *sa = (gpointer)data;
	VarEntry *ve = (VarEntry *)node->data;

	if(!strcmp(ve->name, sa->folder))
	{
		sa->node = node;
		sa->found = TRUE;
	}
}

static int create_table_of_entries(TigContent *content)
{
	TigEntry **ptr;
	GNode *node;
	GNode *folder = NULL;
	char prv_fld[20] = "";

	for(ptr = content->var_entries; *ptr; ptr++)
	{
		TigEntry* te = *ptr;
		VarEntry *ve = te->content.regular->entries[0];
		SearchArg sa;

		if(strcmp(ve->folder, prv_fld))
		{	// cache: make searching faster if previous folder is the same than current
			memset(&sa, 0, sizeof(sa));
			strcpy(sa.folder, ve->folder);
			g_node_children_foreach(GFMFile.trees.vars, 
						G_TRAVERSE_ALL, 
						search_for_folder, 
						(gpointer)&sa);
			strcpy(prv_fld, sa.folder);
		}
		else
			sa.found = TRUE;
		
		if(!sa.found)
		{	// create folder, if needed
			VarEntry *fe = tifiles_ve_dup(ve);

			strcpy(fe->name, ve->folder);
			strcpy(fe->folder, "");
			fe->type = tifiles_folder_type(GFMFile.model);
			
			node = g_node_new(fe);
			folder = g_node_append(GFMFile.trees.vars, node);
		}
		
		{	// add var
			node = g_node_new(tifiles_ve_dup(ve));
			g_node_append(sa.node ? sa.node : folder, node);
		}
	}

	return 0;
}

int tigroup_load(const char *filename)
{
	int ret;
	TreeInfo *ti;
	TigContent *content;
	int m, n, k=0;
	
	// Progress bar & message
	gtk_widget_show(gfm_widget.pbar);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gfm_widget.pbar), _("Loading..."));
	GTK_REFRESH();

	// Create and load tigroup file
	GFMFile.type = TIFILE_TIGROUP;

	GFMFile.contents.tigroup = content = tifiles_content_create_tigroup(CALC_NONE, 0);
	ret = tifiles_file_read_tigroup(filename, GFMFile.contents.tigroup);
	if(ret)
	{
		msgbox_error("Failed to load TiGroup file!");
		tifiles_content_delete_tigroup(GFMFile.contents.tigroup);
		return -1;
	}
	GFMFile.model = GFMFile.contents.tigroup->model;

	// Recreate folder listing (ticalcs2 compatible)
    GFMFile.trees.vars = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFMFile.contents.tigroup->model;
	ti->type = VAR_NODE_NAME;
	GFMFile.trees.vars->data = ti;

	GFMFile.trees.apps = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFMFile.contents.tigroup->model;
	ti->type = APP_NODE_NAME;
	GFMFile.trees.apps->data = ti;

	m = GFMFile.contents.tigroup->n_vars;
	n = GFMFile.contents.tigroup->n_apps;
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gfm_widget.pbar), "");

	// Vars
	if(tifiles_calc_is_ti8x(GFMFile.model))
	{
		GNode *folder;
		TigEntry **ptr;

		folder = g_node_new(NULL);
		g_node_append(GFMFile.trees.vars, folder);

		for(ptr = content->var_entries; *ptr; ptr++)
		{
			TigEntry* entry = *ptr;
			VarEntry *ve = entry->content.regular->entries[0];
			GNode *node;

			node = g_node_new(tifiles_ve_dup(ve));
			g_node_append(folder, node);

			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gfm_widget.pbar), (gdouble)k++ / (m+n));
			GTK_REFRESH();
		}
	}
	else if(tifiles_calc_is_ti9x(GFMFile.model))
	{
		create_table_of_entries(GFMFile.contents.tigroup);
	}

	// Apps
	{
		GNode *folder;
		TigEntry **ptr;
		int i;

		folder = g_node_new(NULL);
		g_node_append(GFMFile.trees.apps, folder);

		for(ptr = content->app_entries, i =0; *ptr; ptr++, i++)
		{
			TigEntry* entry = *ptr;			
			VarEntry *ve = tifiles_ve_create();
			GNode *node;
			int *p;

			strcpy(ve->name, entry->content.flash->name);
			ve->type = entry->content.flash->data_type;
			ve->size = entry->content.flash->data_length;
			ve->data = (uint8_t *)g_malloc(sizeof(i));
			p = (int *)ve->data;	// hint: create cross-reference on apps 
			*p = i;					// by storing index on TigEntry** array

			node = g_node_new(ve);
			g_node_append(folder, node);
			
			gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gfm_widget.pbar), (gdouble)k++ / (m+n));
			GTK_REFRESH();
		}
	}

	// Extract apps from TiGroup
	GFMFile.array = GFMFile.contents.tigroup->app_entries;
	GFMFile.contents.tigroup->app_entries = NULL;
	GFMFile.contents.tigroup->n_apps = 0;

	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gfm_widget.pbar), 0.0);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gfm_widget.pbar), "");
	gtk_widget_hide(gfm_widget.pbar);

	tifiles_content_delete_tigroup(GFMFile.contents.tigroup);
	GFMFile.contents.tigroup = NULL;

	return 0;
}

static gboolean varnode_to_tigentry(GNode* node, gpointer data)
{
	if(node)
	{
		if(node->data)
		{
			VarEntry* ve = node->data;
			TigEntry* te;
			gchar *basename, *filename;

			// create filename
			basename = ticonv_varname_to_filename(GFMFile.model, ve->name, ve->type);
			filename = g_strconcat(basename, ".", tifiles_vartype2fext(GFMFile.model, ve->type), NULL);
			g_free(basename);

			te = tifiles_te_create(filename, TIFILE_SINGLE, GFMFile.model);
			g_free(filename);

			tifiles_content_add_te((TigContent *)data, te);
			tifiles_content_add_entry(te->content.regular, tifiles_ve_dup(ve));
		}
	}

	return FALSE;
}

static gboolean appnode_to_tigentry(GNode* node, gpointer data)
{
	if(node)
	{
		if(node->data)
		{
			TigContent* content = (TigContent *)data;
			VarEntry* ve = node->data;
			TigEntry* te;
			gchar *basename, *filename;
			int *p;

			// create filename
			basename = ticonv_varname_to_filename(GFMFile.model, ve->name, ve->type);
			filename = g_strconcat(basename, ".", tifiles_vartype2fext(GFMFile.model, ve->type), NULL);
			g_free(basename);

			te = tifiles_te_create(filename, TIFILE_FLASH, GFMFile.model);
			g_free(filename);

			tifiles_content_add_te(content, te);
			tifiles_content_delete_flash(te->content.flash);

			p = (int *)ve->data;	// hint: cross-reference on apps 
			te->content.flash = GFMFile.array[*p]->content.flash;
		}
	}

	return FALSE;
}

int tigroup_save(const char *filename)
{
	int ret;

	// Progress bar & message
	gtk_widget_show(gfm_widget.pbar);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gfm_widget.pbar), _("Saving..."));
	GTK_REFRESH();

	// Turns tree into tigroup file
	GFMFile.contents.tigroup = tifiles_content_create_tigroup(GFMFile.model, 0);
	strcpy(GFMFile.contents.tigroup->comment, tifiles_comment_set_tigroup());

	if((GFMFile.trees.vars)->children != NULL)
	{
		g_node_traverse(GFMFile.trees.vars, G_IN_ORDER, G_TRAVERSE_LEAVES, -1, varnode_to_tigentry, GFMFile.contents.tigroup);
	}

	if((GFMFile.trees.apps)->children != NULL)
	{
		g_node_traverse(GFMFile.trees.apps, G_IN_ORDER, G_TRAVERSE_LEAVES, -1, appnode_to_tigentry, GFMFile.contents.tigroup);
	}

	// Write group file
	ret = tifiles_file_write_tigroup(filename, GFMFile.contents.tigroup);
	if(ret)
	{
		msgbox_error("Failed to save TiGroup file!");
		tifiles_content_delete_tigroup(GFMFile.contents.tigroup);
		return -1;
	}

	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gfm_widget.pbar), 0.0);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gfm_widget.pbar), "");
	gtk_widget_hide(gfm_widget.pbar);

	return 0;
}

int tigroup_destroy(void)
{
	if(GFMFile.contents.tigroup)
		tifiles_content_delete_tigroup(GFMFile.contents.tigroup);
	GFMFile.contents.tigroup = NULL;
	GFMFile.model = CALC_NONE;

	ticalcs_dirlist_destroy(&GFMFile.trees.vars);
	GFMFile.trees.vars = NULL;
	ticalcs_dirlist_destroy(&GFMFile.trees.apps);
	GFMFile.trees.apps = NULL;

	return 0;
}

/* */

int	group_create(CalcModel model)
{
	TreeInfo *ti;
	FileContent *content;

	// Create regular file
	content = GFMFile.contents.group = tifiles_content_create_regular(model);
	GFMFile.type = TIFILE_GROUP;
	GFMFile.model = GFMFile.contents.group->model;

	// Recreate folder listing (ticalcs2 compatible)
    GFMFile.trees.vars = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFMFile.contents.group->model;
	ti->type = VAR_NODE_NAME;
	GFMFile.trees.vars->data = ti;

	GFMFile.trees.apps = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFMFile.contents.group->model;
	ti->type = APP_NODE_NAME;
	GFMFile.trees.apps->data = ti;

	return 0;
}

int group_load(const char *filename)
{
	int ret, i;
	TreeInfo *ti;
	FileContent *content;

	// Create and load regular file
	GFMFile.model = tifiles_file_get_model(filename);
	GFMFile.type = TIFILE_GROUP;

	GFMFile.contents.group = content = tifiles_content_create_regular(GFMFile.model);
	ret = tifiles_file_read_regular(filename, GFMFile.contents.group);
	if(ret)
	{
		msgbox_error("Failed to load Group file!");
		tifiles_content_delete_regular(GFMFile.contents.group);
		return -1;
	}

	// Recreate folder listing (ticalcs2 compatible)
    GFMFile.trees.vars = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFMFile.contents.group->model;
	ti->type = VAR_NODE_NAME;
	GFMFile.trees.vars->data = ti;

	GFMFile.trees.apps = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFMFile.contents.group->model;
	ti->type = APP_NODE_NAME;
	GFMFile.trees.apps->data = ti;

	if(tifiles_calc_is_ti9x(GFMFile.model))
	{
		int **table;
		int num_folders;
		GNode *node, *folder = NULL;

		table = tifiles_create_table_of_entries(content, &num_folders);
		if (table == NULL)
			return -1;

		for (i = 0; table[i] != NULL; i++) 
		{
			VarEntry *fe, *ve;
			int j, idx = table[i][0];
			ve = content->entries[idx];

			fe = tifiles_ve_dup(ve);
			strcpy(fe->name, ve->folder);
			strcpy(fe->folder, "");
			fe->type = tifiles_folder_type(GFMFile.model);
			node = g_node_new(fe);
			folder = g_node_append(GFMFile.trees.vars, node);

			for (j = 0; table[i][j] != -1; j++) 
			{
				idx = table[i][j];
				ve = content->entries[idx];

				node = g_node_new(tifiles_ve_dup(ve));
				g_node_append(folder, node);
			}
		}
	}
	else if(tifiles_calc_is_ti8x(GFMFile.model))
	{
		GNode *folder, *root;

		folder = g_node_new(NULL);
		g_node_append(GFMFile.trees.vars, folder);

		for(i = 0; i < content->num_entries; i++)
		{
			VarEntry *ve = content->entries[i];
			GNode *node;

			node = g_node_new(tifiles_ve_dup(ve));
			g_node_append(folder, node);
		}

		root = g_node_new(NULL);
		g_node_append(GFMFile.trees.apps, root);
	}

	ticalcs_dirlist_display(GFMFile.trees.vars);
	ticalcs_dirlist_display(GFMFile.trees.apps);

	tifiles_content_delete_regular(GFMFile.contents.group);
	GFMFile.contents.group = NULL;

	return 0;
}

static gboolean node_to_varentry(GNode* node, gpointer data)
{
	if(node)
	{
		if(node->data)
		{
			VarEntry* ve = node->data;

			tifiles_content_add_entry((FileContent *)data, tifiles_ve_dup(ve));
		}
	}

	return FALSE;
}

int group_save(const char *filename)
{
	int ret;

	// Turns tree into group file
	GFMFile.contents.group = tifiles_content_create_regular(GFMFile.model);

	if((GFMFile.trees.vars)->children != NULL)
	{
		g_node_traverse(GFMFile.trees.vars, G_IN_ORDER, G_TRAVERSE_LEAVES, -1, node_to_varentry, GFMFile.contents.group);
	}

	if(ticalcs_dirlist_ve_count(GFMFile.trees.vars) == 1)
		strcpy(GFMFile.contents.group->comment, tifiles_comment_set_single());
	else if(ticalcs_dirlist_ve_count(GFMFile.trees.vars) > 1)
		strcpy(GFMFile.contents.group->comment, tifiles_comment_set_group());

	// Write group file
	ret = tifiles_file_write_regular(filename, GFMFile.contents.group, NULL);
	if(ret)
	{
		msgbox_error("Failed to save Group file!");
		tifiles_content_delete_regular(GFMFile.contents.group);
		return -1;
	}

	return 0;
}

int group_destroy(void)
{
	if(GFMFile.contents.group)
		tifiles_content_delete_regular(GFMFile.contents.group);
	GFMFile.contents.group = NULL;
	GFMFile.model = CALC_NONE;

	ticalcs_dirlist_destroy(&GFMFile.trees.vars);
	GFMFile.trees.vars = NULL;
    
	return 0;
}

/* */

int file_create(int type, CalcModel model)
{
	int ret = 0;

	if(type == TIFILE_TIGROUP)
		ret = tigroup_create(model);
	else
		ret = group_create(model);

	return ret;
}

int file_load(const char *filename)
{
	int ret = 0;

	if(GFMFile.type == TIFILE_TIGROUP)
		ret = tigroup_load(filename);
	else
		ret = group_load(filename);

	return ret;
}

int file_save(const char *filename)
{
	int ret = 0;

	if(GFMFile.type == TIFILE_TIGROUP)
		ret = tigroup_save(filename);
	else
		ret = group_save(filename);

	return ret;
}

int file_destroy(void)
{
	int ret = 0;

	if(GFMFile.type == TIFILE_TIGROUP)
		ret = tigroup_destroy();
	else
		ret = group_destroy();

	return ret;
}
