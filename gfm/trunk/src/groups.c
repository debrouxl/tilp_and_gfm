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
  along with this program if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
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
#include "groups.h"
#include "support.h"

GFileStruct GFile;

int	tigroup_create(CalcModel model)
{
	TreeInfo *ti;

	// Create TiGroup file
	GFile.contents.tigroup = tifiles_content_create_tigroup(model, 0);
	GFile.type = TIFILE_TIGROUP;
	GFile.model = GFile.contents.tigroup->model;

	// Recreate folder listing (ticalcs2 compatible)
    GFile.trees.vars = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFile.contents.tigroup->model;
	ti->type = VAR_NODE_NAME;
	GFile.trees.vars->data = ti;

	GFile.trees.apps = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFile.contents.tigroup->model;
	ti->type = APP_NODE_NAME;
	GFile.trees.apps->data = ti;
  
	return 0;
}

typedef struct
{
	int		found;
	GNode*	node;
	gchar	folder[20];
} SearchArg;

static gboolean	search_for_folder(GNode *node, gpointer data)
{
	SearchArg *sa = (gpointer)data;
	VarEntry *ve = (VarEntry *)node->data;

	if(!strcmp(ve->name, sa->folder))
	{
		sa->node = node;
		sa->found = TRUE;
		return TRUE;
	}

	return FALSE;
}

static int create_table_of_entries(TigContent *content)
{
	TigEntry **ptr;
	GNode *node, *folder;
	char prv_fld[20] = "";

	for(ptr = content->entries; *ptr; ptr++)
	{
		TigEntry* te = *ptr;

		if(te->type & TIFILE_SINGLE || te->type & TIFILE_GROUP)
		{
			VarEntry *ve = te->content.regular->entries[0];
			SearchArg sa;
	
			if(strcmp(ve->folder, prv_fld))
			{	// cache: make searching faster if previous folder is the same than current
				memset(&sa, 0, sizeof(sa));
				strcpy(sa.folder, ve->folder);
				g_node_children_foreach(GFile.trees.vars, G_TRAVERSE_ALL, search_for_folder, (gpointer)&sa);
				strcpy(prv_fld, sa.folder);
			}
			else
				sa.found = TRUE;
			
			if(!sa.found)
			{	// create folder, if needed
				VarEntry *fe = tifiles_ve_dup(ve);

				strcpy(fe->name, ve->folder);
				strcpy(fe->folder, "");
				fe->type = tifiles_folder_type(GFile.model);
				
				node = g_node_new(fe);
				folder = g_node_append(GFile.trees.vars, node);
			}
			
			{	// add var
				node = g_node_new(tifiles_ve_dup(ve));
				g_node_append(sa.node ? sa.node : folder, node);
			}

			//ticalcs_dirlist_display(GFile.trees.vars);
		}
	}

	return 0;
}

int tigroup_load(const char *filename)
{
	int ret;
	TreeInfo *ti;
	TigContent *content;
	int k, m, n;
	
	// Progress bar & message
	gtk_widget_show(gfm_widget.pbar);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gfm_widget.pbar), _("Loading..."));
	GTK_REFRESH();

	// Create and load tigroup file
	GFile.type = TIFILE_TIGROUP;

	GFile.contents.tigroup = content = tifiles_content_create_tigroup(CALC_NONE, 0);
	ret = tifiles_file_read_tigroup(filename, GFile.contents.tigroup);
	if(ret)
	{
		msgbox_error("Failed to load TiGroup file!");
		tifiles_content_delete_tigroup(GFile.contents.tigroup);
		return -1;
	}
	GFile.model = GFile.contents.tigroup->model;

	// Recreate folder listing (ticalcs2 compatible)
    GFile.trees.vars = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFile.contents.tigroup->model;
	ti->type = VAR_NODE_NAME;
	GFile.trees.vars->data = ti;

	GFile.trees.apps = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFile.contents.tigroup->model;
	ti->type = APP_NODE_NAME;
	GFile.trees.apps->data = ti;

	tifiles_te_sizeof_array(GFile.contents.tigroup->entries, &m, &n);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gfm_widget.pbar), "");

	// Vars
	if(tifiles_calc_is_ti8x(GFile.model))
	{
		GNode *folder;
		TigEntry **ptr;

		folder = g_node_new(NULL);
		g_node_append(GFile.trees.vars, folder);

		for(ptr = content->entries; *ptr; ptr++)
		{
			TigEntry* entry = *ptr;

			if(entry->type & TIFILE_SINGLE || entry->type & TIFILE_GROUP)
			{
				VarEntry *ve = entry->content.regular->entries[0];
				GNode *node;

				node = g_node_new(tifiles_ve_dup(ve));
				g_node_append(folder, node);

				gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gfm_widget.pbar), (gdouble)k++ / (m+n));
				GTK_REFRESH();
			}
		}
	}
	else if(tifiles_calc_is_ti9x(GFile.model))
	{
		//GFile.contents.tigroup->entries[0]->content.regular->entries[0]->	
		create_table_of_entries(GFile.contents.tigroup);
	}

	// Apps
	{
		GNode *folder;
		TigEntry **ptr;

		folder = g_node_new(NULL);
		g_node_append(GFile.trees.apps, folder);

		for(ptr = content->entries; *ptr; ptr++)
		{
			TigEntry* entry = *ptr;

			if(entry->type == TIFILE_FLASH)
			{
				VarEntry *ve = tifiles_ve_create();
				GNode *node;

				strcpy(ve->name, entry->content.flash->name);
				ve->type = entry->content.flash->data_type;
				ve->size = entry->content.flash->data_length;

				node = g_node_new(ve);
				g_node_append(folder, node);
				
				gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gfm_widget.pbar), (gdouble)k++ / (m+n));
				GTK_REFRESH();
			}
		}
	}	

	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(gfm_widget.pbar), 0.0);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gfm_widget.pbar), "");
	gtk_widget_hide(gfm_widget.pbar);

	return 0;
}

int tigroup_save(const char *filename)
{
#if 0
	int ret;

	ret = tifiles_file_write_tigroup(filename, GFile.contents.tigroup);
	if(ret)
	{
		msgbox_error("Failed to save TiGroup file!");
		tifiles_content_delete_tigroup(GFile.contents.tigroup);
		return -1;
	}
#else
	msgbox_one(MSGBOX_INFO, "Not implemented yet.");
#endif

	return 0;
}

int tigroup_destroy(void)
{
	if(GFile.contents.tigroup)
		tifiles_content_delete_tigroup(GFile.contents.tigroup);
	GFile.contents.tigroup = NULL;
	GFile.model = CALC_NONE;

	ticalcs_dirlist_destroy(&GFile.trees.vars);
	GFile.trees.vars = NULL;
	ticalcs_dirlist_destroy(&GFile.trees.apps);
	GFile.trees.apps = NULL;

	return 0;
}


int	group_create(CalcModel model)
{
	TreeInfo *ti;
	FileContent *content;

	// Create regular file
	content = GFile.contents.group = tifiles_content_create_regular(model);
	GFile.type = TIFILE_GROUP;
	GFile.model = GFile.contents.group->model;

	// Recreate folder listing (ticalcs2 compatible)
    GFile.trees.vars = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFile.contents.group->model;
	ti->type = VAR_NODE_NAME;
	GFile.trees.vars->data = ti;

	GFile.trees.apps = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFile.contents.group->model;
	ti->type = APP_NODE_NAME;
	GFile.trees.apps->data = ti;

	return 0;
}

int group_load(const char *filename)
{
	int ret, i;
	TreeInfo *ti;
	FileContent *content;

	// Create and load regular file
	GFile.model = tifiles_file_get_model(filename);
	GFile.type = TIFILE_GROUP;

	GFile.contents.group = content = tifiles_content_create_regular(GFile.model);
	ret = tifiles_file_read_regular(filename, GFile.contents.group);
	if(ret)
	{
		msgbox_error("Failed to load Group file!");
		tifiles_content_delete_regular(GFile.contents.group);
		return -1;
	}

	// Recreate folder listing (ticalcs2 compatible)
    GFile.trees.vars = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFile.contents.group->model;
	ti->type = VAR_NODE_NAME;
	GFile.trees.vars->data = ti;

	GFile.trees.apps = g_node_new(NULL);
	ti = (TreeInfo *)g_malloc(sizeof(TreeInfo));
	ti->model = GFile.contents.group->model;
	ti->type = APP_NODE_NAME;
	GFile.trees.apps->data = ti;

	if(tifiles_calc_is_ti9x(GFile.model))
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
			int j, index = table[i][0];
			ve = content->entries[index];

			fe = tifiles_ve_dup(ve);
			strcpy(fe->name, ve->folder);
			strcpy(fe->folder, "");
			fe->type = tifiles_folder_type(GFile.model);
			node = g_node_new(fe);
			folder = g_node_append(GFile.trees.vars, node);

			for (j = 0; table[i][j] != -1; j++) 
			{
				int index = table[i][j];
				VarEntry *ve = content->entries[index];

				node = g_node_new(tifiles_ve_dup(ve));
				g_node_append(folder, node);
			}
		}
	}
	else if(tifiles_calc_is_ti8x(GFile.model))
	{
		GNode *folder, *root;

		folder = g_node_new(NULL);
		g_node_append(GFile.trees.vars, folder);

		for(i = 0; i < content->num_entries; i++)
		{
			VarEntry *ve = content->entries[i];
			GNode *node;

			node = g_node_new(tifiles_ve_dup(ve));
			g_node_append(folder, node);
		}

		root = g_node_new(NULL);
		g_node_append(GFile.trees.apps, root);
	}

	ticalcs_dirlist_display(GFile.trees.vars);
	ticalcs_dirlist_display(GFile.trees.apps);

	return 0;
}

static gboolean node_to_varentry(GNode* node, gpointer data)
{
	if(node)
	{
		if(node->data)
		{
			VarEntry* ve = node->data;

			printf("<%s-%s>\n", ve->folder, ve->name);
			tifiles_content_add_entry((FileContent *)data, ve);
		}
	}

	return FALSE;
}

int group_save(const char *filename)
{
	int ret;

	// Turns tree into group file
	tifiles_content_delete_regular(GFile.contents.group);
	GFile.contents.group = tifiles_content_create_regular(GFile.model);

	if((GFile.trees.vars)->children != NULL)
	{
		g_node_traverse(GFile.trees.vars, G_IN_ORDER, G_TRAVERSE_LEAVES, -1, node_to_varentry, GFile.contents.group);
	}

	// Write group file
	ret = tifiles_file_write_regular(filename, GFile.contents.group, NULL);
	if(ret)
	{
		msgbox_error("Failed to save Group file!");
		tifiles_content_delete_regular(GFile.contents.group);
		return -1;
	}

	return 0;
}

int group_destroy(void)
{
	if(GFile.contents.group)
		tifiles_content_delete_regular(GFile.contents.group);
	GFile.contents.group = NULL;
	GFile.model = CALC_NONE;

	ticalcs_dirlist_destroy(&GFile.trees.vars);
	GFile.trees.vars = NULL;
    
	return 0;
}

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

	if(GFile.type == TIFILE_TIGROUP)
		ret = tigroup_load(filename);
	else
		ret = group_load(filename);

	return ret;
}

int file_save(const char *filename)
{
	int ret = 0;

	if(GFile.type == TIFILE_TIGROUP)
		ret = tigroup_save(filename);
	else
		ret = group_save(filename);

	return ret;
}

int file_destroy(void)
{
	int ret = 0;

	if(GFile.type == TIFILE_TIGROUP)
		ret = tigroup_destroy();
	else
		ret = group_destroy();

	return ret;
}
