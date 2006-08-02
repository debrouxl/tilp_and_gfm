/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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

#include "tilp_core.h"
#include "gtk_update.h"
#include "ctree.h"
#include "dboxes.h"

#ifdef __WIN32__
# define strcasecmp _stricmp
#endif

/*
	Get list of counters to refresh
 */
int tilp_pbar_type(CalcFnctsIdx op)
{
	const char **array = calc_handle->calc->counters;
	const char *str = array[op];

	if(!strcmp(str, "1P"))
		return 1;
	else if(!strcmp(str, "1L"))
		return 2;
	else if(!strcmp(str, "2P"))
		return 3;
	else if(!strcmp(str, "1P1L"))
		return 4;
	else if(!strcmp(str, "2P1L"))
		return 5;

	return 0;
}

/*
  Check whether the calc is ready (with or without auto-detection)
*/
int tilp_calc_isready(void)
{
	int err;
	int to;
	CalcModel cm = tilp_remap_to_usb(options.cable_model, options.calc_model);
	
	// DirectLink cable need re-opening to clear error (STALL)
	if(cm == CALC_TI89T_USB || cm == CALC_TI84P_USB /*|| options.cable_model == CABLE_SLV*/)
	{
		tilp_device_close();
		tilp_device_open();
	}

	// first check: fast
	to = ticables_options_set_timeout(cable_handle, 10);
	err = ticalcs_calc_isready(calc_handle);
	ticables_options_set_timeout(cable_handle, to);

	if(err == 257)	/* 257 = ERR_NOT_READY */
	{
		switch(options.calc_model)
		{
		case CALC_TI89:
		case CALC_TI89T:
			err = ticalcs_calc_send_key(calc_handle, 277);
			break;
		case CALC_TI92:
		case CALC_TI92P:
		case CALC_V200:
			err = ticalcs_calc_send_key(calc_handle, 8273);
			break;

		default: break;
		}
	}
	
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

	ret = gif->msg_box4(_("Warning"), _("You are going to restore the content\nof your calculator with a backup.\nThe whole memory will be erased.\nAre you sure you want to do that?"));
	if(ret != BUTTON1)
		return -1;

	if(tilp_calc_isready())
		return -1;

	gif->create_pbar_(FNCT_SEND_BACKUP, _("Restoring"));

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

	gif->create_pbar_(FNCT_RECV_BACKUP, _("Backing up"));
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
		(options.calc_model == CALC_TI86)));

	g_free(filename);
	gif->destroy_pbar();

	if(tilp_err(err))
		return -1;

	return 0;
}

/*
  Receive the IDlist (msg box or file)
*/
int tilp_calc_idlist(int to_file)
{
	int err;
	char buffer[MAXCHARS];
	char idlist[32];

	if(tilp_calc_isready())
		return -1;

	err = ticalcs_calc_recv_idlist(calc_handle, (uint8_t *)idlist);
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

	gif->create_pbar_(FNCT_DUMP_ROM, _("Dumping ROM"));
	err = ticalcs_calc_dump_rom(calc_handle, ROMSIZE_AUTO, tmp_filename);
	gif->destroy_pbar();

	if(tilp_err(err))
		return -1;

	return 0;
}

int tilp_calc_rom_dump(void)
{
	gint ret;

	ret = gif->msg_box4(_("Warning"), _("An assembly program is about to be sent on your calculator.\nIf you have not made a backup yet, you should do one before\nproceeding with ROM dumping...\n\nFor the way of proceeding, take a look at the TiLP manual \n(especially if you have a USB cable)."));
	if(ret != BUTTON1)
		return -1;

	return do_rom_dump(0);
}


/*
  Send one or more FLASH application(s).
  Note: the timeout is increased to 10 seconds during the operation.
  Note2: the timeout is set to 30 seconds during operation due to garbage collection attempt
	(TI83+ only, bug #738486)
*/
int tilp_calc_send_app(void)
{
	GList *sel;
	gint i, l;

	if(!tilp_clist_selection_ready())
		return 0;

	// Check for selection consistence
	for (sel = local.selection2, l = 0; sel; sel = sel->next) 
	{
		FileEntry *f = (FileEntry *)sel->data;

		if(tifiles_file_is_flash(f->name) && 
			!strcasecmp(tifiles_fext_get(f->name), tifiles_fext_of_flash_os(options.calc_model)))
		{
			gif->msg_box1(_("Error"),
				_("You can not send variables/applications and upgrades simultaneously."));
			return 0;
		}
	}

	if(tilp_calc_isready())
		return -1;
	
	if(options.calc_model == CALC_TI83P)
		ticables_options_set_timeout(cable_handle, 300);
	else
		ticables_options_set_timeout(cable_handle, 100);

	gif->create_pbar_(FNCT_SEND_APP, _("Sending app"));

	// Now, send files
	l = g_list_length(local.selection2);
	for(sel = local.selection2, i = 0; sel != NULL; sel = sel->next, i++)
	{
		FileEntry *f = (FileEntry *)sel->data;
		int err;

		if(tifiles_file_is_regular(f->name))
			continue;

		gtk_update.cnt3 = i+1;
		gtk_update.max3 = l;
		gtk_update.pbar();
		gtk_update.refresh();

		err = ticalcs_calc_send_app2(calc_handle, f->name);
		if(err)
		{
			tilp_err(err);
			gif->destroy_pbar();

			return -1;
		}
	}
	ticables_options_set_timeout(cable_handle, options.cable_timeout);

	gif->destroy_pbar();
	
	return 0;
}


/*
  Send a FLASH Operating System (AMS).
  Note: the timeout is increased to 10 seconds during the operation.
  Note2: the timeout is set to 30 seconds during operation due to garbage collection attempt
	(TI83+ only, bug #738486)

  No ready check is made in this function. The RDY command is often rejected in boot mode.
*/
int tilp_calc_send_os(const char *filename)
{
	int err, ret;
	char *msg = _("You are going to upgrade the Operating System\nof your calculator.\nYou are advised to eventually turn off\nyour screen saver, which could cause the transfer to crash.\nIf the transfer fails, wait until the TI89/TI92+ displays\n\"Waiting to receive\"\nand restart the transfer again.\nTI73/83+ users need to turn the calculator off and press a key.");

	if(g_list_length(remote.selection) > 1)
	{
		gif->msg_box1(_("Error"),
			     _("You have to select _one_ upgrade to send."));
		return -1;
	}

	if(strcasecmp(tifiles_fext_get(filename), tifiles_fext_of_flash_os(options.calc_model)) &&
		!tifiles_file_is_tib(filename)) 
	{
		gif->msg_box1(_("Error"),
			     _("It's not an FLASH upgrade or this FLASH upgrade is not intended for this calculator type."));
		return -1;
	}

	ret = gif->msg_box4(_("Warning"), msg);
	if(ret == BUTTON2)
		return -1;

	if(options.calc_model == CALC_TI83P || options.calc_model == CALC_TI84P)
		ticables_options_set_timeout(cable_handle, 300);
	else
		ticables_options_set_timeout(cable_handle, 100);

	gif->create_pbar_(FNCT_SEND_OS, _("Upgrading OS"));
	err = ticalcs_calc_send_os2(calc_handle, filename);
	gif->destroy_pbar();

	ticables_options_set_timeout(cable_handle, options.cable_timeout);

	if(tilp_err(err))
		return -1;

	return 0;
}


/*
  Receive an FLASH application
*/
int tilp_calc_recv_app(void)
{
	GList *ptr;
	char filename[256];
	char *dst;
	int i, l;

	if(!tilp_ctree_selection2_ready())
		return 0;

	if(!(ticalcs_calc_features(calc_handle) & FTS_FLASH))
		return -1;

	if(tilp_calc_isready())
		return -1;

	gif->create_pbar_(FNCT_RECV_APP, _("Receiving app"));

	l = g_list_length(remote.selection2);
	for(ptr = remote.selection2, i = 0; ptr; ptr = ptr->next, i++) 
	{
		VarEntry *ve = (VarEntry *) ptr->data;
		int err, ret;
		char *str;

		gtk_update.cnt3 = i+1;
		gtk_update.max3 = l;
		gtk_update.pbar();
		gtk_update.refresh();

		str = ticonv_varname_to_filename(options.calc_model, ve->name);
		strcpy(filename, str);
		strcat(filename, ".");
		strcat(filename, tifiles_vartype2fext(options.calc_model, ve->type));
		g_free(str);

		ret = tilp_file_check(filename, &dst);
		if(ret == 0)
			continue;
		else if(ret == -1)
		{
			gif->destroy_pbar();
			return -1;
		}

		err = ticalcs_calc_recv_app2(calc_handle, dst, ve);
		if(err) 
		{
			tilp_err(err);

			g_free(dst);
			gif->destroy_pbar();

			return -1;
		}
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
	gint i, l;
	int mode = MODE_NORMAL;

	if(!tilp_clist_selection_ready())
		return 0;

	// Check for selection consistence
	for (sel = local.selection, l = 0; sel; sel = sel->next) 
	{
		FileEntry *f = (FileEntry *)sel->data;

		if(tifiles_file_is_flash(f->name) && 
			!strcasecmp(tifiles_fext_get(f->name), tifiles_fext_of_flash_os(options.calc_model)))
		{
			gif->msg_box1(_("Error"), _("You can not send both variables/applications and upgrades simultaneously."));
			return 0;
		}
		else if(tifiles_file_is_flash(f->name) && 
			!strcasecmp(tifiles_fext_get(f->name), tifiles_fext_of_flash_app(options.calc_model)))
		{
			continue;
		}
		else if(tifiles_file_is_backup(f->name) && !tifiles_file_is_group(f->name)) 
		{
			gif->msg_box1(_("Error"), _("You can not send backups in this way. Use the 'Restore' button instead."));
			return 0;
		}
		else if(!tifiles_file_is_regular(f->name) && !tifiles_file_is_tigroup(f->name)) 
		{
			gif->msg_box1(_("Error"), _("There is an unknown file type in the selection or the path is incorrect."));
			return 0;
		}
		else if(!tifiles_calc_are_compat(options.calc_model, tifiles_file_get_model(f->name)))
		{
			gif->msg_box1(_("Error"), _("There is a file type incompatible with the target hand-held in the selection."));
			return 0;
		}
	}

	if(tilp_calc_isready())
		return -1;

	// Set options
	if(options.local_path == PATH_LOCAL)
		mode |= MODE_LOCAL_PATH;

	gif->create_pbar_(FNCT_SEND_VAR, _("Sending var(s)"));

	// Now, send files
	l = g_list_length(local.selection);
	for(sel = local.selection, i = 0; sel != NULL; sel = sel->next, i++)
	{
		FileEntry *f = (FileEntry *)sel->data;
		int err;

		gtk_update.cnt3 = i+1;
		gtk_update.max3 = l;
		gtk_update.pbar();
		gtk_update.refresh();

		// It is not the last file to send
		if(((sel->next) != NULL) && (l > 1)) 
		{
			// More than one file to send
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
			err = ticalcs_calc_send_var(calc_handle, mode | MODE_SEND_LAST_VAR, f->content);
			if(err)
			{
				tilp_err(err);
				gif->destroy_pbar();

				return -1;
			}
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

// non TI82 & 85
static int tilp_calc_recv_var1(void)
{
	int i, l;
	int err, ret=0;
	FileContent **array;

	if(!tilp_ctree_selection_ready())
		return -1;

	if(tilp_calc_isready())
		return -1;
	
	gif->create_pbar_(FNCT_RECV_VAR, _("Receiving var(s)"));

	l = g_list_length(remote.selection);
	if(l == 1) 
	{
		// One variable
		VarEntry *ve = (VarEntry *)remote.selection->data;
		gchar *tmp_filename;
		gchar *dst_filename;
		char *varname, *fldname;

		gtk_update.cnt3 = 1;
		gtk_update.max3 = l;
		gtk_update.pbar();
		gtk_update.refresh();

		tmp_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_GROUP, 
			".", tifiles_fext_of_group(options.calc_model), NULL);

		err = ticalcs_calc_recv_var2(calc_handle, MODE_NORMAL, tmp_filename, ve);
		if(err)
		{
			gif->destroy_pbar();
			tilp_err(err);
			return -1;
		}

		varname = ticonv_varname_to_filename(options.calc_model, ve->name);
		fldname = ticonv_varname_to_filename(options.calc_model, ve->folder);

		if(tifiles_has_folder(options.calc_model))
			dst_filename = g_strconcat(local.cwdir, G_DIR_SEPARATOR_S, 
				fldname, ".", varname, ".",
				tifiles_vartype2fext(options.calc_model, ve->type), NULL);
		else
			dst_filename = g_strconcat(local.cwdir, G_DIR_SEPARATOR_S, 
							  varname, ".",
				tifiles_vartype2fext(options.calc_model, ve->type), NULL);
		tilp_file_move_with_check(tmp_filename, dst_filename);

		g_free(fldname);
		g_free(varname);
		g_free(tmp_filename);
		g_free(dst_filename);
	}
	else
	{
		// Multiple variables (single or group depending on global option)
		GList *sel;
		gchar *src_filename;
		gchar *tmp_filename;
		gchar *dst_filename;

		array = tifiles_content_create_group(l);
		if(array == NULL)
			return -1;

		for(sel = remote.selection, i = 0; sel; sel = sel->next, i++)
		{
			VarEntry *ve = (VarEntry *)sel->data;

			gtk_update.cnt3 = i+1;
			gtk_update.max3 = l;
			gtk_update.pbar();
			gtk_update.refresh();

			array[i] = tifiles_content_create_regular(options.calc_model);
			err = ticalcs_calc_recv_var(calc_handle, MODE_NORMAL, array[i], ve);
			if(err)
			{
				tilp_err(err);
				gif->destroy_pbar();
				break;
			}
		}

		if(options.recv_as_group)
		{
			FileContent* content;

			tmp_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_GROUP, 
				".", tifiles_fext_of_group(options.calc_model), NULL);

			tifiles_group_contents(array, &content);
			strcpy(content->comment, tifiles_comment_set_group());
			tifiles_file_write_regular(tmp_filename, content, NULL);
			tifiles_content_delete_regular(content);

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
		tifiles_content_delete_group(array);
	}

	gif->destroy_pbar();

	return ret;
}

// TI82 & 85
static int tilp_calc_recv_var2(void)
{
	gchar *tmp_filename;
	gchar *dst_filename;
	VarEntry* ve;
	//char *varname;
	int err;
	char *basename;

	//
	// Receive one variable or several variables packed into a group.
	//
	tmp_filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_GROUP, 
		".", tifiles_fext_of_group(options.calc_model), NULL);

	gif->create_pbar_(FNCT_RECV_VAR, _("Receiving var(s)"));
	err = ticalcs_calc_recv_var_ns2(calc_handle, MODE_NORMAL, tmp_filename, &ve);
	gif->destroy_pbar();

	if(err)
	{
		tilp_err(err);
		return -1;
	}

	// Check for single/group
	if(ve)
	{
		//single
		basename = ticonv_varname_to_filename(options.calc_model, ve->name);
		dst_filename = g_strconcat(local.cwdir, G_DIR_SEPARATOR_S, basename, 
			".", tifiles_vartype2fext(options.calc_model, ve->type), NULL);
		tilp_file_move_with_check(tmp_filename, dst_filename);

		tifiles_ve_delete(ve);
		g_free(basename);
		g_free(tmp_filename);
		g_free(dst_filename);

		return 0;
	}
	else
	{
		if(!options.recv_as_group)
		{
			tifiles_ungroup_file(tmp_filename, NULL);
			g_free(tmp_filename);
			
			return 0;
		}
		else
		{
			return 1;
		}
	}

	return 0;
}

int tilp_calc_recv_var(void)
{
	if(options.calc_model == CALC_TI82 || options.calc_model == CALC_TI85)
		return tilp_calc_recv_var2();
	else
		return tilp_calc_recv_var1();

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

	if(options.calc_model == CALC_TI89 || options.calc_model == CALC_TI92P ||
		options.calc_model == CALC_TI89T || options.calc_model == CALC_V200)
	{
		CalcInfos infos;

		err = ticalcs_calc_get_version(calc_handle, &infos);
		if(tilp_err(err))
			return -1;

		if(strcmp(infos.os_version, "2.09") < 0)
		{
			gif->msg_box1(_("Information"), _("You need AMS 2.09 mini for this operation."));
			return -1;
		}
	}

	if(options.overwrite)
	{
		int ret = gif->msg_box2(_("Warning"), _("You are about to delete variable(s).\nAre you sure you want to do that?"));
		if(ret == BUTTON2)
			return 0;
	}

	gif->create_pbar_(FNCT_DEL_VAR, _("Deleting..."));

	for(sel = remote.selection; sel; sel = sel->next)
	{
		VarEntry *ve = (VarEntry *)sel->data;
		err = ticalcs_calc_del_var(calc_handle, ve);
		if(tilp_err(err))
		{
			gif->destroy_pbar();
			return -1;
		}
		else
		{
			ticalcs_dirlist_ve_del(remote.var_tree, ve);
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
	VarEntry vr;
	VarEntry ve;

	if(tilp_calc_isready())
		return -1;

	if(!(ticalcs_calc_features(calc_handle) & OPS_NEWFLD))
		return 0;

	fldname = gif->msg_entry(_("New Folder"), _("Name: "), _("folder"));
	if (fldname == NULL)
		return 0;

	gif->create_pbar_(FNCT_NEW_FOLDER, _("Creating..."));

	memset(&ve, 0, sizeof(ve));
	memset(&vr, 0, sizeof(vr));
	strcpy(vr.folder, fldname);
	err = ticalcs_calc_new_fld(calc_handle, &vr);
	if(tilp_err(err))
	{
		gif->destroy_pbar();
		return -1;
	}
	else
	{
		strcpy(ve.folder, fldname);	// vr is modified by ticalcs_calc_new_fld
		ticalcs_dirlist_ve_add(remote.var_tree, &ve);
		ctree_refresh();
	}

	gif->destroy_pbar();
	return 0;
}

#ifdef _DEBUG
# define EXTRA_INFOS 1
#else
# define EXTRA_INFOS 0
#endif

#ifdef __WIN32__
#define snprintf _snprintf
#endif

const char* format_bytes(unsigned long value)
{
	static char str[16];

	if(value < 64*1024)
	{
		snprintf(str, sizeof(str), "%lu bytes", value);
	}
	else if(value < 1024*1024)
	{
		snprintf(str, sizeof(str), "%lu KB", value >> 10);
	}
	else
	{
		snprintf(str, sizeof(str), "%lu MB", value >> 20);
	}

	return (const char *)str;
}

int tilp_calc_get_infos(CalcInfos *infos)
{
	int err;
	gchar *str = g_strdup("");
	gchar *tmp;

	if(tilp_calc_isready())
		return -1;

	if(!(ticalcs_calc_features(calc_handle) & OPS_VERSION))
		return 0;

	err = ticalcs_calc_get_version(calc_handle, infos);
	if(tilp_err(err))
		return -1;

#if EXTRA_INFOS
	if(infos->mask & INFOS_PRODUCT_NUMBER)
	{
		tmp = g_strdup_printf("%sProduct Number: %08x\n", str, infos->product_number);
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_LANG_ID)
	{
		tmp = g_strdup_printf("%sLanguage Id: %i %i\n", str, infos->language_id, infos->sub_lang_id);
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_DEVICE_TYPE)
	{
		tmp = g_strdup_printf("%sDevice Type: %02x\n", str, infos->device_type);
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_LCD_WIDTH)
	{
		tmp = g_strdup_printf("%sLCD width: %i pixels\n", str, infos->lcd_width);
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_LCD_HEIGHT)
	{
		tmp = g_strdup_printf("%sLCD height: %i pixels\n", str, infos->lcd_height);
		g_free(str);
		str = tmp;
	}
	
	{
		tmp = g_strdup_printf("%s\n\n", str);
		g_free(str);
		str = tmp;
	}
#endif
	if(infos->mask & INFOS_PRODUCT_NAME)
	{
		tmp = g_strdup_printf("%sProduct Name: <%s>\n", str, infos->product_name);
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_MAIN_CALC_ID)
	{
		tmp = g_strdup_printf("%sCalculator Id: %s\n", str, infos->main_calc_id);
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_HW_VERSION)
	{
		tmp = g_strdup_printf("%sHardware Version: %i\n", str, infos->hw_version);
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_BOOT_VERSION)
	{
		tmp = g_strdup_printf("%sBoot Version: %s\n", str, infos->boot_version);
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_OS_VERSION)
	{
		tmp = g_strdup_printf("%sOs Version: %s\n", str, infos->os_version);
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_RAM_PHYS)
	{
		tmp = g_strdup_printf("%sPhysical RAM: %s\n", str, 
				      format_bytes((unsigned int)infos->ram_phys));
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_RAM_USER)
	{
		tmp = g_strdup_printf("%sUser RAM: %s\n", str, 
				      format_bytes((unsigned int)infos->ram_user));
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_RAM_FREE)
	{
		tmp = g_strdup_printf("%sFree RAM: %s\n", str, 
				      format_bytes((unsigned int)infos->ram_free));
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_FLASH_PHYS)
	{
		tmp = g_strdup_printf("%sPhysical FLASH: %s\n", str, 
				      format_bytes((unsigned int)infos->flash_phys));
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_FLASH_USER)
	{
		tmp = g_strdup_printf("%sUser FLASH: %s\n", str, 
				      format_bytes((unsigned int)infos->flash_user));
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_FLASH_FREE)
	{
		tmp = g_strdup_printf("%sFree FLASH: %s\n", str, 
				      format_bytes((unsigned int)infos->flash_free));
		g_free(str);
		str = tmp;
	}
	if(infos->mask & INFOS_BATTERY)
	{
		tmp = g_strdup_printf("%sBattery: %s\n", str, infos->battery ? "good" : "low");
		g_free(str);
		str = tmp;
	}

	gif->msg_box1(_("Information"), str);
	g_free(str);

	return 0;
}

/*
	Receive main certificate (exprimental)
 */
int tilp_calc_recv_cert(void)
{
	int err;
	gchar *filename = g_strconcat(local.cwdir, G_DIR_SEPARATOR_S, 
			tifiles_model_to_string(options.calc_model), ".", tifiles_fext_of_certif(options.calc_model),
			NULL);

	if(tilp_calc_isready())
		return -1;

	if(!(ticalcs_calc_features(calc_handle) & FTS_CERT))
		return -1;

	gif->create_pbar_(FNCT_RECV_CERT, _("Receiving cert"));

	err = ticalcs_calc_recv_cert2(calc_handle, filename);
	g_free(filename);
	if(err) 
		tilp_err(err);

	gif->destroy_pbar();

	return 0;
}

/*
	Send certificate (experimental)
 */
int tilp_calc_send_cert(const char *filename)
{
	int err;

	if(strcasecmp(tifiles_fext_get(filename), tifiles_fext_of_certif(options.calc_model))) 
	{
		gif->msg_box1(_("Error"),
			     _("It's not a certificate or this certificate is not targetted for this calculator type."));
		return -1;
	}

	if(tilp_calc_isready())
		return -1;
	
	gif->create_pbar_(FNCT_SEND_CERT, _("Sending cert"));
	err = ticalcs_calc_send_cert2(calc_handle, filename);
	gif->destroy_pbar();

	if(tilp_err(err))
		return -1;

	return 0;
}

/*
  Send a TiGroup from the specified filename
  - [in] filename: the file to use
  - [out]: -1 if error, 0 otherwise
*/
int tilp_calc_send_tigroup(const char *filename, TigMode mode)
{
	int ret;
	int err;

	ret = gif->msg_box4(_("Warning"), _("You are about to restore the content\nof your calculator with a backup.\nThe whole memory will be erased.\nAre you sure you want to do that?"));
	if(ret != BUTTON1)
		return -1;

	if(tilp_calc_isready())
		return -1;

	if(options.calc_model == CALC_TI83P)
		ticables_options_set_timeout(cable_handle, 300);
	else
		ticables_options_set_timeout(cable_handle, 100);

	gif->create_pbar_type5(_("Restoring"));
	err = ticalcs_calc_send_tigroup2(calc_handle, filename, mode);
	if(err)
		tilp_err(err);
	gif->destroy_pbar();

	ticables_options_set_timeout(cable_handle, options.cable_timeout);

	return 0;
}


/*
	Receive a TiGroup
*/
int tilp_calc_recv_tigroup(TigMode mode)
{
	int err = 0;
	char *filename;

	if(tilp_calc_isready())
		return -1;

	gif->create_pbar_type5(_("Backing up"));
	filename = g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S, TMPFILE_TIGROUP, NULL);

	err = ticalcs_calc_recv_tigroup2(calc_handle, filename, mode);
	
	g_free(filename);
	gif->destroy_pbar();

	if(tilp_err(err))
		return -1;

	return 0;
}