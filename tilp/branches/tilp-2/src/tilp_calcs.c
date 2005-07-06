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

/*
	This file contains utility functions about hand-helds functions.
	These functions are mainly used by the left window.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef __MACOSX__
# include "tilibs.h"
#else				/*  */
# include <libticables/ticables.h>
# include <libticalcs/calc_int.h>
# include <libticalcs/calc_err.h>
# include <glib/glib.h>
# include <stdlib.h>
#endif				/*  */

#include "gtk_update.h"
#include "tilp_core.h"

#ifdef __WIN32__
# define strcasecmp _stricmp
#endif

/*
  Check whether the calc is ready (with or without auto-detection)
*/
int tilp_calc_isready(void)
{
	int err;
	int to;
	
	// first check: fast
	to = ticables_options_set_timeout(cable_handle, 10);
	err = ticalcs_calc_isready(calc_handle);
	ticables_options_set_timeout(cable_handle, to);

	if(err) 
	{
		// second check: slower
		err = ticalcs_calc_isready(calc_handle);
		if(err)
		{
			tilp_err(err);
			return -1;
		}
	}

	return 0;
}

/*
  Do a directory listing
*/
int tilp_calc_dirlist(void)
{
	if(tilp_calc_isready())
		return -1;

	if(tilp_dirlist_remote())
		return -1;

	return 0;
}

/*
  Send a backup from the specified filename
  - [in] filename: the file to use
  - [out]
*/
int tilp_calc_send_backup(const char *filename)
{
	int ret;
	int err;

	ret = gif->msg_box4(_("Warning"), _("You are going to restore the content\nof your calculator with a backup.\nThe whole memory will be erased.\nAre you sure you want to do that ?"));
	if(ret != BUTTON1)
		return -1;

	if(tilp_calc_isready())
		return -1;

	switch (calc_handle->model) 
	{
	case CALC_TI82:
	case CALC_TI85:
	case CALC_TI86:
		gif->create_pbar_type5(_("Backup"), _("Waiting for confirmation on calc..."));
		break;
	case CALC_TI73:
	case CALC_TI83:
	case CALC_TI83P:
	case CALC_TI84P:
	case CALC_TI92:
		gif->create_pbar_type3(_("Backup"));
		break;
	case CALC_TI89:
	case CALC_TI89T:
	case CALC_TI92P:
	case CALC_V200:
		gif->create_pbar_type5(_("Backup"), "");
		break;
	default:
	    return 0;
		break;
	}

	err = ticalcs_calc_send_backup2(calc_handle, filename);
	if(err)
		tilp_err(err);

	gif->destroy_pbar();

	return 0;
}


/*
  Receive a backup
*/
int tilp_calc_recv_backup(void)
{
	int err = 0;
	char *filename;

	if(tilp_calc_isready())
		return -1;

	switch (calc_handle->model) 
	{
	case CALC_TI82:
	case CALC_TI85:
	case CALC_TI86:
		gif->create_pbar_type5(_("Backup"), _("Waiting for backup from calc..."));
		break;
	case CALC_TI73:
	case CALC_TI83:
	case CALC_TI83P:
	case CALC_TI84P:
		gif->create_pbar_type3(_("Backup"));
		break;
	case CALC_TI89:
	case CALC_TI89T:
	case CALC_TI92P:
	case CALC_V200:
		gif->create_pbar_type5(_("Backup"), "");
		break;
	case CALC_TI92:
		gif->create_pbar_type2(_("Backup"), _("Receiving blocks"));
		break;
	default:
	    return 0;
	}

	filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_BACKUP, NULL);

	do 
	{
		gtk_update.refresh();
		if(gtk_update.cancel)
			break;

		err = ticalcs_calc_recv_backup2(calc_handle, filename);
	} 
	while ((err == ERROR_READ_TIMEOUT) && 
		((!(ticalcs_calc_features(calc_handle) & FTS_SILENT)) || 
		(calc_handle->model == CALC_TI86)));

	g_free(filename);
	gif->destroy_pbar();

	if(tilp_err(err))
		return -1;

	return 0;
}

/*
  Receive the IDlist
*/
int tilp_calc_idlist(int to_file)
{
	int err;
	char buffer[MAXCHARS];
	char idlist[32];

	if(tilp_calc_isready())
		return -1;

	err = ticalcs_calc_recv_idlist(calc_handle, (char *)idlist);
	if(err)
	{
		tilp_err(err);
		return -1;
	}
	
	strcpy(buffer, _("ID-LIST : "));
	strncat(buffer, idlist, 5);
	strcat(buffer, "-");
	strncat(buffer, idlist + 5, 5);
	strcat(buffer, "-");
	strncat(buffer, idlist + 5 + 5, 4);
	strcat(buffer, "\0");

	if(to_file)
	{
		gchar *filename = g_strconcat(local.cwdir, G_DIR_SEPARATOR_S, "IDLIST.txt", NULL);
		FILE *f;

		f = fopen(filename, "wt");
		g_free(filename);

		if(f == NULL)
			return -1;

		fwrite(buffer, strlen(buffer), 1, f);
		fclose(f);
	}
	else
		gif->msg_box1(_("Information"), buffer);

	return 0;
}

/*
  Dump the ROM (get a ROM image)
*/
static int do_rom_dump(int mode)
{
	gchar tmp_filename[MAXCHARS];
	int err;

	strcpy(tmp_filename, g_get_tmp_dir());
	strcat(tmp_filename, G_DIR_SEPARATOR_S);
	strcat(tmp_filename, TMPFILE_ROMDUMP);

	gif->create_pbar_type5(_("ROM dump"), _("Receiving data"));
	err = ticalcs_calc_dump_rom(calc_handle, ROMSIZE_AUTO, tmp_filename);
	gif->destroy_pbar();

	if(tilp_err(err))
		return -1;

	return 0;
}

int tilp_calc_rom_dump(void)
{
	gint ret;

	ret = gif->msg_box4(_("Warning"), _("An assembly program is about to be\nsent on your calculator. If you have not made\na backup yet, you should do one before\nproceeding with ROM dumping..."));
	if(ret != BUTTON1)
		return -1;

	switch (calc_handle->model) 
	{
	case CALC_TI73:
	case CALC_TI83P:
	case CALC_TI84P:
	case CALC_TI89:
	case CALC_TI89T:
	case CALC_TI92:
	case CALC_TI92P:
	case CALC_V200:
		return do_rom_dump(0);
	break;
	default:
		gif->msg_box(_("Information"), _("Currently unsupported !"));
		break;
	}

	return 0;
}


/*
  Send a FLASH application
  Note: the timeout is increased to 10 seconds during the operation.
  Note2: the timeout is set to 30 seconds during operation due to garbage collection attempt
	(TI83+ only, bug #738486)
*/
int tilp_calc_send_flash_app(char *filename)
{
	int err;
	gint old_timeout;

	if(strcasecmp(tifiles_fext_get(filename), 
					tifiles_fext_of_flash_app(calc_handle->model))) 
	{
		gif->msg_box(_("Error"),
			     _("It's not an FLASH application or this FLASH application is not intended for this calculator type."));
		return -1;
	}

	if(tilp_calc_isready())
		return -1;
	
	old_timeout = calc_handle->cable->timeout;
	if(calc_handle->model == CALC_TI83P)
		ticables_options_set_timeout(cable_handle, 300);
	else
		ticables_options_set_timeout(cable_handle, 100);

	gif->create_pbar_type3(_("Flash"));
	err = ticalcs_calc_send_flash2(calc_handle, filename);
	gif->destroy_pbar();

	ticables_options_set_timeout(cable_handle, old_timeout);
	
	if(tilp_err(err))
		return -1;

	return 0;
}


/*
  Send a FLASH Operating System (AMS).
  Note: the timeout is increased to 10 seconds during the operation.
  Note2: the timeout is set to 30 seconds during operation tdue to garbage collection attempt
	(TI83+ only, bug #738486)
*/
int tilp_calc_send_flash_os(char *filename)
{
	int err, ret;
	gint old_timeout;
	char *msg = _("You are going to upgrade the Operating System\nof your calculator.\nYou are advised to eventually turn off\nyour screen saver, which could cause the transfer to crash.\nIf the transfer fails, wait until the TI89/TI92+ displays\n\"Waiting to receive\"\nand restart the transfer again.\nTI73/83+ users need to turn the calculator off and press a key.");

	if(strcasecmp(tifiles_fext_get(filename), tifiles_fext_of_flash_os(calc_handle->model)) &&
		!tifiles_file_is_tib(filename)) 
	{
		gif->msg_box(_("Error"),
			     _("It's not an FLASH upgrade or this FLASH upgrade is not intended for this calculator type."));
		return -1;
	}

	ret = gif->msg_box4(_("Warning"), msg);
	if(ret == BUTTON2)
		return -1;

	if(tilp_calc_isready())
		return -1;

	old_timeout = calc_handle->cable->timeout;
	if(calc_handle->model == CALC_TI83P || calc_handle->model == CALC_TI84P)
		ticables_options_set_timeout(cable_handle, 300);
	else
		ticables_options_set_timeout(cable_handle, 100);

	gif->create_pbar_type3(_("Flash"));
	err = ticalcs_calc_send_flash2(calc_handle, filename);
	gif->destroy_pbar();

	ticables_options_set_timeout(cable_handle, old_timeout);

	if(tilp_err(err))
		return -1;

	return 0;
}


/*
  Receive an FLASH application
*/
int tilp_calc_recv_flash_app(void)
{
	GList *ptr;
	char filename[256];
	char *dst;

	if(!tilp_ctree_selection2_ready())
		return 0;

	if(tilp_calc_isready())
		return -1;

	if(!(ticalcs_calc_features(calc_handle) & FTS_FLASH))
		return -1;

	gif->create_pbar_type5(_("Receiving application(s)"), "");

	ptr = remote.selection2;
	while (ptr != NULL) 
	{
		VarEntry *ve = (VarEntry *) ptr->data;
		int err;

		strcpy(filename, ve->name);
		strcat(filename, ".");
		strcat(filename, tifiles_vartype2fext(calc_handle->model, ve->type));

		if(!tilp_file_check(filename, &dst)) 
		{
			gif->destroy_pbar();
			return 0;
		}

		err = ticalcs_calc_recv_flash2(calc_handle, dst, ve);
		if(err) 
		{
			tilp_err(err);

			g_free(dst);
			gif->destroy_pbar();

			return -1;
		}
		ptr = ptr->next;
	}

	g_free(dst);
	gif->destroy_pbar();

	return 0;
}

/*
  Send one or more selected variables
*/
int tilp_calc_send_var(void)
{
	GList *sel;
	int mode = MODE_NORMAL;
	gint i, l = 0;

	if(!tilp_clist_selection_ready())
		return 0;

	// Check for selection consistence
	for (sel = local.selection; sel; sel = sel->next) 
	{
		FileEntry *f = (FileEntry *)sel->data;

		if(tifiles_file_is_flash(f->name)) 
		{
			gif->msg_box(_("Error"),
				_("You can not send both variables and applications simultaneously."));
			return 0;
		}

		if(tifiles_file_is_backup(f->name) && !tifiles_file_is_group(f->name)) 
		{
			gif->msg_box(_("Error"),
				     _("You can not send backups in this way. Use the 'Restore' button instead."));
			return 0;
		}

		if(!tifiles_file_is_regular(f->name)) 
		{
			gif->msg_box(_("Error"), _("There is an unknown file type in the selection."));
			return 0;
		}
	}

	if(tilp_calc_isready())
		return -1;

	// Set options
	if(options.local_path == PATH_LOCAL)
		mode |= MODE_LOCAL_PATH;

	// Display the appropriate dialog box
	l = g_list_length(sel = local.selection);
	if(l == 1) 
	{
		FileEntry *f = (FileEntry *) sel->data;

		if(tifiles_file_is_group(f->name))
			gif->create_pbar_type5(_("Sending group file"), "");
		else
			gif->create_pbar_type4(_("Sending variables"), "");
	} 
	else
	{
		gif->create_pbar_type5(_("Sending variables"), "");
	}

	// Now, send files
	for(sel = local.selection, i =0; sel != NULL; sel = sel->next, i++)
	{
		FileEntry *f = (FileEntry *)sel->data;
		int err;

		// It is not the last file to send
		if(((sel->next) != NULL) && (l > 1)) 
		{
			// More than one file to send
			//err = ticalcs_calc_send_var2(calc_handle, mode, f->name);
			err = ticalcs_calc_send_var(calc_handle, mode, f->content);
			if(err) 
			{
				tilp_err(err);
				gif->destroy_pbar();

				return -1;
			}
		} 
		else 
		{
			// It is the first or the last one
			//err = ticalcs_calc_send_var2(calc_handle, mode | MODE_SEND_LAST_VAR, f->name);
			err = ticalcs_calc_send_var(calc_handle, mode | MODE_SEND_LAST_VAR, f->content);
			{
				tilp_err(err);
				gif->destroy_pbar();

				return -1;
			}
		}

		if(l > 1) 
		{
			gtk_update.cnt2 = i;
			gtk_update.max2 = l;

			gtk_update.pbar();
			gtk_update.refresh();
		}
	} 

	gif->destroy_pbar();

	return 0;
}

/*
  Receive one or more selected variables.
  Returned value:
  - negative if error
  - zero if successful (single)
  - positive if successful (group to save)
*/

static int tilp_calc_recv_var1(void)
{
	int i, l;
	int err, ret=0;
	FileContent **array;

	l = g_list_length(remote.selection);

	if(tilp_calc_isready())
		return -1;

	if(!tilp_ctree_selection_ready())
		return -1;
	
	if(l == 1) 
	{
		// One file
		VarEntry *ve = (VarEntry *)remote.selection->data;
		gchar *tmp_filename;
		gchar *dst_filename;
		char *varname;

		tmp_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_GROUP, NULL);

		gif->create_pbar_type4(_("Receiving variable(s)"), "");
		err = ticalcs_calc_recv_var2(calc_handle, MODE_NORMAL, tmp_filename, ve);
		gif->destroy_pbar();

		if(err)
		{
			tilp_err(err);
			return -1;
		}

		varname = tifiles_transcode_varname_static(calc_handle->model, ve->name, ve->type);
		dst_filename = g_strconcat(local.cwdir, G_DIR_SEPARATOR_S, varname, 
			".", tifiles_vartype2fext(calc_handle->model, ve->type), NULL);
		tilp_file_move_with_check(tmp_filename, dst_filename);

		g_free(tmp_filename);
		g_free(dst_filename);
	}
	else
	{
		// Multiple files (single or group depending on global option)
		GList *sel;
		gchar *src_filename;
		gchar *tmp_filename;
		gchar *dst_filename;

		gif->create_pbar_type5(_("Receiving variable(s)"), "");

		array = tifiles_content_create_group(l);
		if(array == NULL)
			return -1;

		for(sel = remote.selection, i = 0; sel; sel = sel->next, i++)
		{
			VarEntry *ve = (VarEntry *)sel->data;
			
			array[i] = tifiles_content_create_regular();

			err = ticalcs_calc_recv_var(calc_handle, MODE_NORMAL, array[i], ve);
			if(err)
			{
				tilp_err(err);
				break;
			}

			gtk_update.cnt2 = i;
			gtk_update.max2 = l;
			printf("%i %i\n", i, l);
			gtk_update.pbar();
			gtk_update.refresh();
		}

		if(options.recv_as_group)
		{
			FileContent* content;

			tmp_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_GROUP, NULL);

			tifiles_group_contents(array, &content);
			strcpy(content->comment, tifiles_comment_set_group());
			tifiles_file_write_regular(tmp_filename, content, NULL);
			tifiles_content_free_regular(content);

			g_free(tmp_filename);
			ret = 1;
		}
		else
		{
			tilp_file_chdir(g_get_tmp_dir());

			for(i = 0; i < l; i++)
			{
				err = tifiles_file_write_regular(NULL, array[i], &tmp_filename);
				if(err)
				{
					tilp_err(err);
					break;
				}

				src_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, 
					g_basename(tmp_filename), NULL);
				dst_filename = g_strconcat(local.cwdir, G_DIR_SEPARATOR_S, 
					g_basename(tmp_filename), NULL);

				tilp_file_move_with_check(src_filename, dst_filename);

				g_free(src_filename);
#ifndef __WIN32__
				  free(tmp_filename);
#endif
				g_free(dst_filename);
			}

			tilp_file_chdir(local.cwdir);
		}

		gif->destroy_pbar();
		tifiles_content_free_group(array);
	}

	return ret;
}

static int tilp_calc_recv_var2(void)
{
	/*
	case CALC_TI82:
	case CALC_TI85:
		{

			//
			// Receive one variable (filename is returned by recv_var) or 
			// several variables packed into a group (used the passed arg as
			// filename)
			//
			char *old_path = g_get_current_dir();
			char *src_path = NULL;
			char *dst_path = NULL;
			char *str;
			char tmp_filename[MAXCHARS];
			int err;
			strcpy(tmp_filename, TMPFILE_GROUP);
			gif->create_pbar_type4(_("Receiving variable(s)"),
					       _("Waiting..."));
			chdir(g_get_tmp_dir());
			err =
			    ti_calc.recv_var(tmp_filename, MODE_NORMAL,
					     NULL);
			chdir(old_path);
			gif->destroy_pbar();
			if(tilp_error(err))
				return -1;

			// Detect for single/group file
			if(!strcmp(tmp_filename, TMPFILE_GROUP))
				return +1;

			// Check for existence and move
			src_path =
			    g_strconcat(g_get_tmp_dir(),
					G_DIR_SEPARATOR_S, tmp_filename,
					NULL);
			str = dst_path =
			    g_strconcat(g_get_current_dir(),
					G_DIR_SEPARATOR_S, tmp_filename,
					NULL);
			tilp_file_move_with_check(src_path, dst_path);
		}
		break;
	}
*/
	return 0;
}

int tilp_calc_recv_var(void)
{
	switch (calc_handle->model) 
	{
	case CALC_TI73:
	case CALC_TI83:
	case CALC_TI83P:
	case CALC_TI84P:
	case CALC_TI86:
	case CALC_TI89:
	case CALC_TI89T:
	case CALC_TI92:
	case CALC_TI92P:
	case CALC_V200:
		return tilp_calc_recv_var1();
		break;
	case CALC_TI82:
	case CALC_TI85:
		return tilp_calc_recv_var2();
		break;
		    default:
			return 0;
	}

	return 0;
}

int tilp_calc_del_var(void)
{
	GList *sel;
	int err;

	if(!remote.selection && !remote.selection2)
		return 0;

	if(tilp_calc_isready())
		return -1;

	if(!(ticalcs_calc_features(calc_handle) & OPS_DELVAR))
		return 0;

	if(options.overwrite)
	{
		int ret = gif->msg_box2(_("Warning"), _("You are about to delete variable(s).\nAre you sure you want to do that ?"));
		if(ret == BUTTON2)
			return 0;
	}

	gif->create_pbar_type2(_("Deleting var(s)"), "Please wait...");

	for(sel = remote.selection; sel; sel = sel->next)
	{
		VarEntry *ve = (VarEntry *)sel->data;
		err = ticalcs_calc_del_var(calc_handle, ve);
		if(tilp_err(err))
		{
			gif->destroy_pbar();
			return -1;
		}
	}

	for(sel = remote.selection2; sel; sel = sel->next)
	{
		VarEntry *ve = (VarEntry *)sel->data;
		err = ticalcs_calc_del_var(calc_handle, ve);
		if(tilp_err(err))
		{
			gif->destroy_pbar();
			return -1;
		}
	}

	gif->destroy_pbar();

	return 0;
}

int tilp_calc_new_fld(void)
{
	gchar *fldname = NULL;
	int err;
	VarEntry ve;

	if(tilp_calc_isready())
		return -1;

	if(!(ticalcs_calc_features(calc_handle) & OPS_NEWFLD))
		return 0;

	fldname = gif->msg_entry(_("New Folder"), _("Name: "), _("folder"));
	if (fldname == NULL)
		return 0;

	gif->create_pbar_type2(_("Creating folder"), "Please wait...");

	strcpy(ve.folder, fldname);
	err = ticalcs_calc_new_fld(calc_handle, &ve);
	if(tilp_err(err))
	{
		gif->destroy_pbar();
		return -1;
	}

	gif->destroy_pbar();

	return 0;
}

int tilp_calc_get_infos(CalcInfos *infos)
{
	int err;
	gchar *str;

	if(tilp_calc_isready())
		return -1;

	if(!(ticalcs_calc_features(calc_handle) & OPS_VERSION))
		return 0;

	err = ticalcs_calc_get_version(calc_handle, infos);
	if(tilp_err(err))
		return -1;

	str = g_strdup_printf(_("OS version: %s\nBOOT version: %s\n"), infos->os, infos->bios);
	gif->msg_box(_("Information"), str);
	g_free(str);

	return 0;
}
