/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <string.h>

#include "tilp_core.h"

/* Destroy the selection of the clist window */
void tilp_clist_selection_destroy(void)
{
	if (clist_win.selection != NULL) {
		g_list_free(clist_win.selection);
		clist_win.selection = NULL;
	}
	return;
}


/* Destroy the selection of the ctree window */
void tilp_ctree_selection_destroy(void)
{
	if (ctree_win.selection != NULL) {
		g_list_free(ctree_win.selection);
		ctree_win.selection = NULL;
	}
	if (ctree_win.selection2 != NULL) {
		g_list_free(ctree_win.selection2);
		ctree_win.selection2 = NULL;
	}
	return;
}


/* Destroy the selection of the clist window */
void tilp_clist_file_selection_destroy(void)
{
	if (clist_win.file_selection != NULL) {
		g_list_foreach(clist_win.file_selection, (GFunc) g_free,
			       NULL);
		g_list_free(clist_win.file_selection);
		clist_win.file_selection = NULL;
	}
	return;
}


/* Add a file to the file_selection (if it does not exist in the list) */
void tilp_add_file_to_file_selection(const char *filename)
{
	GList *ptr;
	ptr = clist_win.file_selection;
	while (ptr != NULL) {
		if (!strcmp((char *) ptr->data, filename))
			return;
		ptr = g_list_next(ptr);
	}
	clist_win.file_selection =
	    g_list_append(clist_win.file_selection, (gpointer) filename);
}

#ifndef __MACOSX__
/* Delete files which are in clist_win.file_selection */
void tilp_delete_selected_files()
{
	GList *ptr;
	gint ret;

	if (clist_win.selection == NULL)
		return;

	if (g_list_length(clist_win.selection) == 1) {
		ret = gif->msg_box2(_("Warning"), _
				    ("Are you sure you want to remove this file ?\n\n"));
	} else {
		ret = gif->msg_box2(_("Warning"), _
				    ("Are you sure you want to remove these files ?\n\n"));
	}

	if (ret == BUTTON2)
		return;

	ptr = clist_win.selection;
	while (ptr != NULL) {
		TilpFileInfo *fi = ptr->data;
		tilp_file_delete(fi->name);
		ptr = ptr->next;
	}

	tilp_dirlist_local();
}


/* Rename files which are in clist_win.file_selection */
void tilp_rename_selected_files()
{
	gchar *filename;
	GList *ptr;
	if (clist_win.selection == NULL)
		return;
	ptr = clist_win.selection;
	while (ptr != NULL) {
		TilpFileInfo *fi = ptr->data;
		printf("<<%s>>\n", fi->name);
		filename =
		    gif->msg_entry(_("Rename the file"), _("Name: "),
				   fi->name);
		if (filename == NULL)
			return;
		if (tilp_file_move(fi->name, filename) < 0) {
			gif->msg_box(_("Information"), _
				     ("Unable to rename the file or directory."));
			g_free(filename);
		}
		g_free(filename);
		ptr = ptr->next;
	}
}
#endif /* !__MACOSX__ */

/* Check for files in the list */
int tilp_clist_selection_ready(void)
{
	if (clist_win.selection == NULL) {
#ifndef __MACOSX__
		gif->msg_box(_("Information"), _
			     ("A file must have been selected in the right window."));
#endif /* !__MACOSX__ */
		return 0;
	}
	return !0;
}
int tilp_ctree_selection_ready(void)
{
	if (ctree_win.selection == NULL) {
#ifndef __MACOSX__
		gif->msg_box(_("Information"), _
			     ("A variable must have been selected in the left window."));
#endif /* !__MACOSX__ */
		return 0;
	}
	return !0;
}
int tilp_ctree_selection2_ready(void)
{
	if (ctree_win.selection2 == NULL) {
#ifndef __MACOSX__
		gif->msg_box(_("Information"), _
			     ("A variable must have been selected in the left window."));
#endif /* !__MACOSX__ */
		return 0;
	}
	return !0;
}

#ifndef __MACOSX__
void tilp_clist_selection_display(void)
{
	GList *ptr = clist_win.selection;
	if (clist_win.selection == NULL)
		return;
	while (ptr != NULL) {
		TilpFileInfo *fi = ptr->data;
		printf("<%s>\n", fi->name);
		ptr = ptr->next;
	}
}
#endif /* !__MACOSX__ */
