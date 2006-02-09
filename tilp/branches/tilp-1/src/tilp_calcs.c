/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
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

/*
  Register a callback to use whenever the calculator is (not) ready.
  Used for dislaying calculator status.
  The string passed to the callback must be neither modified, nor freed.
*/
static READY_CALLBACK ready_cb = NULL;
READY_CALLBACK tilp_calc_register(READY_CALLBACK new_cb)
{
	READY_CALLBACK old_cb = ready_cb;
	ready_cb = new_cb;
	return old_cb;
}


/*
  Check whether the calc is ready (with or without auto-detection)
*/
int tilp_calc_isready(void)
{
	int err = 0;
	TicalcType c = 0;
	ticalc_get_calc(&c);
	if (options.auto_detect && 
		tifiles_is_flash(options.lp.calc_type) && 
		(options.lp.calc_type != CALC_TI84P) &&
		(options.lp.calc_type != CALC_TI89T) &&
		(options.lp.calc_type != CALC_V200)) 
	{
		err =
		    ticalc_flash_isready((TicalcType *) &
					 (options.lp.calc_type));
		if (tilp_error(err)) {
			if (ready_cb != NULL) {
				ready_cb(READY_NOK);
			}
			return -1;
		}
		ticalc_set_calc(options.lp.calc_type, &ti_calc);
	} else {
		err = ti_calc.isready();
		if (err && (err != ERR_VOID_FUNCTION)) {
			tilp_error(err);
			if (ready_cb != NULL) {
				ready_cb(READY_NOK);
			}
			return -1;
		}
    }
	if (ready_cb != NULL) {
      ready_cb(options.lp.calc_type);
	}
	return 0;
}


/*
  Do a directory listing
*/
int tilp_calc_dirlist(void)
{
	if (tilp_calc_isready())
		return -1;
	if (tilp_dirlist_remote())
		return -1;
	return 0;
}


/*
  Send a backup from the specified filename
  - [in] filename: the file to use
  - [out]
*/
int tilp_calc_send_backup(char *filename)
{
	int ret;
	ret = gif->msg_box4(_("Warning"), _
			    ("You are going to restore the content\nof your calculator with a backup.\nThe whole memory will be erased.\nAre you sure you want to do that ?"));
	if (ret != BUTTON1)
		return -1;
	if (tilp_calc_isready())
		return -1;
	switch (options.lp.calc_type) {
	case CALC_TI82:
	case CALC_TI85:
	case CALC_TI86:
		gif->create_pbar_type5(_("Backup"), _
				       ("Waiting for confirmation on calc..."));
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
		break;
	}
	tilp_error(ti_calc.send_backup(filename, MODE_BACKUP));
	gif->destroy_pbar();
	return 0;
}


/*
  Receive a backup
*/
int tilp_calc_recv_backup(void)
{
	int err = 0;
	char *tmp_filename;
	if (tilp_calc_isready())
		return -1;
	switch (options.lp.calc_type) {
	case CALC_TI82:
	case CALC_TI85:
	case CALC_TI86:
		gif->create_pbar_type5(_("Backup"), _
				       ("Waiting for backup from calc..."));
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
	}
	tmp_filename =
	    g_strconcat(g_get_tmp_dir(), G_DIR_SEPARATOR_S,
			TMPFILE_BACKUP, NULL);

	do {
		info_update.refresh();
		if (info_update.cancel)
			break;
		err = ti_calc.recv_backup(tmp_filename, MODE_BACKUP);
	} while ((err == ERR_READ_TIMEOUT) && ((!ti_calc.is_silent)
					       || (options.lp.calc_type ==
						   CALC_TI86)));
	g_free(tmp_filename);
	gif->destroy_pbar();
	if (tilp_error(err))
		return -1;
	return 0;
}


/*
  Receive the IDlist
*/
int tilp_calc_idlist(void)
{
	char buffer[MAXCHARS];
	char idlist[32];

	if (tilp_calc_isready())
		return -1;

	if (tilp_error(ti_calc.get_idlist(idlist)))
		return -1;

	strcpy(buffer, _("ID-LIST : "));
	strncat(buffer, idlist + 8, 5);
	strcat(buffer, "-");
	strncat(buffer, idlist + 8 + 5, 5);
	strcat(buffer, "-");
	strncat(buffer, idlist + 8 + 5 + 5, 4);
	strcat(buffer, "\0");

	gif->msg_box(_("Information"), buffer);

	return 0;
}


/*
  Dump the ROM (get a ROM image)
*/
static int do_rom_dump(int mode)
{
	gchar tmp_filename[MAXCHARS];
	int err;
	gif->create_pbar_type5(_("ROM dump"), _("Receiving bytes"));
	strcpy(tmp_filename, g_get_tmp_dir());
	strcat(tmp_filename, DIR_SEPARATOR);
	strcat(tmp_filename, TMPFILE_ROMDUMP);
	err = ti_calc.dump_rom(tmp_filename, mode);
	gif->destroy_pbar();
	if (tilp_error(err))
		return -1;
	return 0;
}
int tilp_calc_rom_dump(void)
{
	gint ret;
	ret = gif->msg_box4(_("Warning"), _
			    ("An assembly program is about to be\nsent on your calculator. If you have not made\na backup yet, you should do one before\nproceeding with ROM dumping..."));
	if (ret != BUTTON1)
		return -1;
	switch (options.lp.calc_type) {
	case CALC_TI73:
	case CALC_TI83:
		ret = gif->msg_box4(_("Information"), _
				    ("1: you must have AShell installed on your calculator\n2: TiLP will automatically transfer the ROM dump program\n3: but, it will wait for you to manually launch it from the calculator."));
		if (ret == BUTTON1)
			return do_rom_dump(0);

		else
			return -1;
		break;
	case CALC_TI82:
		ret = gif->msg_box4(_("Information"), _
				    ("1: you must have ASh installed on your calculator\n2: you must be in receive mode (LINK menu)\n3: TiLP will transfer the ROM dumping program\n4: it will wait for you to manually launch it from the calculator."));
		if (ret == BUTTON1)
			return do_rom_dump(0);

		else
			return -1;
		break;
	case CALC_TI85:
		ret = gif->msg_box4(_("Information"), _
				    ("1: you must have Zshell or Usgard installed on your calculator\n2: you must be in receive mode (LINK menu)\n3: TiLP will transfer the ROM dumping program\n4: it will wait for you to manually launch it from the calculator."));
		if (ret == BUTTON1) {

			/* Ask for the shell type */
			ret =
			    gif->msg_box3("Question", "Select a shell",
					  "Zshell", "Usgard", "Cancel");
			if (ret == 3)
				return -1;

			else
				return do_rom_dump((ret == 1) ?
						   SHELL_ZSHELL :
						   SHELL_USGARD);
		} else
			return -1;
		break;
	case CALC_TI83P:
	case CALC_TI84P:
		ret = gif->msg_box4(_("Information"), 
				    _("1: TiLP will automatically transfer the ROM dumping program\n2: but, it will wait for you to manually launch it from the calculator (either by the shell, either by typing 'Asm(prgmROMDUMP)'.\nThanks to Benjamin Moody for the ROM dumper !"));
		if (ret == BUTTON1)
		{
			ret = gif->msg_box3(_("Question"), _("Is your calculator model a SilverEdition ?"), _("Yes"), _("No"), _("Cancel"));
			if(ret == 3)
				return -1;
			else
				return do_rom_dump((ret == BUTTON1) ? ROM_SE : 0);
		}
		else
			return -1;
		break;
	case CALC_TI86:
		ret = gif->msg_box4(_("Information"), _
				    ("1: TiLP will automatically transfer the ROM dumping program\n2: but, it will wait for you to manually launch it from the calculator (either by the shell, either by typing 'Asm(DUMPROM)'."));
		if (ret == BUTTON1)
			return do_rom_dump(0);

		else
			return -1;
		break;
	case CALC_TI89:
	case CALC_TI89T:
	case CALC_TI92P:
	case CALC_V200:
		return do_rom_dump(0);
		break;
	case CALC_TI92:
		ret = gif->msg_box4(_("Information"), _
				    ("1: you must have the FargoII shell installed on your calculator\n2: TiLP will automatically transfer the ROM dumping program\n3: TiLP will automatically launch the program (if you are in HOME).\n"));
		if (ret == BUTTON1) {	// ask for ROM size
			ret =
			    gif->msg_box3("ROM size",
					  "Select the size of your ROM or cancel",
					  "1Mb", "2 Mb", "Cancel");
			if (ret == 3)
				return -1;

			else
				return do_rom_dump(ret);
		} else
			return -1;
		break;
	default:
		printl(0, "Unsupported ROM dump.\n");
		break;
	}
	return 0;
}


#ifdef __WIN32__
# define strcasecmp _stricmp
#endif				/*  */

/*
  Send a FLASH application
  Note: the timeout is increased to 10 seconds during the operation.
  Note2: the timeout is set to 30 seconds during operation tdue to garbage collection attemp
	(TI83+ only, bug #738486)
*/
int tilp_calc_send_flash_app(char *filename)
{
	int err;
	gint old_timeout;
	if (strcasecmp
	    (tifiles_get_extension(filename),
	     tifiles_flash_app_file_ext())) {
		gif->msg_box(_("Error"),
			     _
			     ("It's not an FLASH application or this FLASH application is not intended for this calculator type."));
		return -1;
	}
	if (tilp_calc_isready())
		return -1;
	switch (options.lp.calc_type) {
	case CALC_TI73:
	case CALC_TI82:
	case CALC_TI83:
	case CALC_TI83P:
	case CALC_TI84P:
	case CALC_TI85:
	case CALC_TI92:
		gif->create_pbar_type3(_("Flash"));
		break;
	case CALC_TI89:
	case CALC_TI89T:
	case CALC_TI92P:
	case CALC_V200:
		gif->create_pbar_type3(_("Flash"));
		break;
	}
	old_timeout = ticable_get_timeout();
	if(options.lp.calc_type == CALC_TI83P)
		ticable_set_timeout(300);
	else
		ticable_set_timeout(100);
	err = ti_calc.send_flash(filename, MODE_APPS);
	ticable_set_timeout(old_timeout);
	gif->destroy_pbar();
	if (tilp_error(err))
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
	char *msg = _
	    ("You are going to upgrade the Operating System\nof your calculator.\nYou are advised to eventually turn off\nyour screen saver, which could cause the transfer to crash.\nIf the transfer fails, wait until the TI89/TI92+ displays\n\"Waiting to receive\"\nand restart the transfer again.\nTI73/83+ users need to turn the calculator off and press a key.");
	if (strcasecmp(tifiles_get_extension(filename), tifiles_flash_os_file_ext()) &&
		!tifiles_is_a_tib_file(filename)) {
		gif->msg_box(_("Error"),
			     _
			     ("It's not an FLASH upgrade or this FLASH upgrade is not intended for this calculator type."));
		return -1;
	}
	ret = gif->msg_box4(_("Warning"), msg);
	if (ret == BUTTON2)
		return -1;
	if (tilp_calc_isready())
		return -1;
	switch (options.lp.calc_type) {
	case CALC_TI73:
	case CALC_TI82:
	case CALC_TI83:
	case CALC_TI83P:
	case CALC_TI84P:
	case CALC_TI85:
	case CALC_TI92:
		gif->create_pbar_type3(_("Flash"));
		break;
	case CALC_TI89:
	case CALC_TI89T:
	case CALC_TI92P:
	case CALC_V200:
		gif->create_pbar_type5(_("Flash"), "");
		break;
		break;
	}
	old_timeout = ticable_get_timeout();
	if((options.lp.calc_type == CALC_TI83P) || (options.lp.calc_type == CALC_TI84P))
		ticable_set_timeout(300);
	else
		ticable_set_timeout(100);
	err = ti_calc.send_flash(filename, MODE_AMS);
	ticable_set_timeout(old_timeout);
	gif->destroy_pbar();
	if (tilp_error(err))
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
	if (!tilp_ctree_selection2_ready())
		return 0;
	if (tilp_calc_isready())
		return -1;
	switch (options.lp.calc_type) {
	case CALC_TI73:
	case CALC_TI83P:
	case CALC_TI84P:
	case CALC_TI89:
	case CALC_TI89T:
	case CALC_TI92P:
	case CALC_V200:
		gif->create_pbar_type5(_("Receiving application(s)"), "");
		break;
	default:
		return -1;
		break;
	}
	ptr = ctree_win.selection2;
	while (ptr != NULL) {
		TiVarEntry *ve = (TiVarEntry *) ptr->data;

		strcpy(filename, ve->trans);
		strcat(filename, ".");
		strcat(filename, tifiles_vartype2file(ve->type));
		if (!tilp_file_check(filename, &dst)) {
			gif->destroy_pbar();
			return 0;
		}
		if (tilp_error(ti_calc.recv_flash(dst, MODE_NORMAL, ve))) {
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
  Convert a FLASH OS (AMS) into a ROM image
  Buggy !
  Should be removed !
*/
int tilp_calc_ams2rom(char *filename)
{
	Ti9xFlash content = {
		0
	};
	Ti9xFlash *ptr;
	int i;
	int nheaders = 0;
	FILE *f;
	char filename2[MAXCHARS];
	char *ext;
	if (!tifiles_is_a_flash_file(filename)) {
		gif->msg_box("Error", "It's not a FLASH file !\n");
		return -1;
	}
	ext = strrchr(filename, '.');
	if (ext != NULL) {
		strncpy(filename2, filename,
			strlen(filename) - strlen(ext));
		filename2[strlen(filename) - strlen(ext)] = '\0';
	} else
		strcpy(filename2, filename);
	strcat(filename2, ".rom");
	f = fopen(filename2, "wb");
	if (f == NULL) {
		printl(2, "Unable to open this file: <%s>\n",
			      filename2);
		return -1;
	}
	if (tilp_error(ti9x_read_flash_file(filename, &content)))
		return -1;

	// count headers
	for (ptr = &content; ptr != NULL; ptr = ptr->next)
		nheaders++;

	// keep the last one (data)
	for (i = 0, ptr = &content; i < nheaders - 1; i++)
		ptr = ptr->next;
	printl(0, "FLASH app/os name: \"%s\"\n", ptr->name);
	printl(0, "FLASH app/os size: %i bytes.\n", ptr->data_length);

	// boot block
	for (i = 0; i < 0x05; i++)
		fputc(0xff, f);
	if (content.calc_type == CALC_TI89)
		fputc(0x20, f);	// internal
	else
		fputc(0x40, f);	// external
	for (i = 0x06; i < 0x65; i++)
		fputc(0xff, f);
	fputc(0xf0, f);		// FLASH ROM
	for (i = 0x66; i < 0x12000; i++)
		fputc(0xff, f);
	gif->create_pbar_type1(_("Converting..."));
	info_update.start();

	/* FLASH upgrade */
	for (i = 0; i < (int)ptr->data_length; i++) {

		//info_update.percentage = (float)i/ptr->data_length;
		//info_update.pbar();
		if (info_update.cancel) {
			gif->destroy_pbar();
			fclose(f);
			return -1;
		}
		fputc(ptr->data_part[i], f);
	}
	for (i = 0x12000 + ptr->data_length; i < 2 * 1024 * 1024; i++)
		fputc(0xff, f);
	gif->destroy_pbar();
	fclose(f);
	return 0;
}


#ifdef __WIN32__
# define strcasecmp _stricmp
#endif				/*  */

/*
  Send one or more selected variables
*/
int tilp_calc_send_var(gint to_flash)
{
	GList *sel;
	gint i = 0;
	gint l = 0;
	int mode = MODE_NORMAL;
	if (to_flash) {
		if (options.lp.calc_type == CALC_TI83P)
			mode |= MODE_SEND_TO_FLASH;

		else if (options.lp.calc_type == CALC_TI89
			 || options.lp.calc_type == CALC_TI89T
			 || options.lp.calc_type == CALC_TI92P
			 || options.lp.calc_type == CALC_V200)
			mode |= MODE_BACKUP;
	}
	if (!tilp_clist_selection_ready())
		return 0;

	// Check for selection consistence
	for (sel = clist_win.selection; sel; sel = sel->next) {
		TilpFileInfo *f = (TilpFileInfo *) sel->data;
		if (tifiles_is_a_flash_file(f->name)) {
			gif->msg_box(_("Error"), _
				     ("You can not send both variables and applications simultaneously."));
			return 0;
		}
		if (tifiles_is_a_backup_file(f->name)
		    && !tifiles_is_a_group_file(f->name)) {
			gif->msg_box(_("Error"),
				     _
				     ("You can not send backups in this way. Use the 'Restore' button instead."));
			return 0;
		}
		if (!tifiles_is_a_regular_file(f->name)) {
			gif->msg_box(_("Error"), _
				     ("There is an unknown file type in the selection."));
			return 0;
		}
	}
	if (tilp_calc_isready())
		return -1;
	if (options.path_mode == LOCAL_PATH)
		mode |= MODE_LOCAL_PATH;

	// Display the appropriate dialog box
	l = g_list_length(sel = clist_win.selection);
	if (l == 1) {
		TilpFileInfo *f = (TilpFileInfo *) sel->data;
		if (tifiles_is_a_group_file(f->name))
			gif->create_pbar_type5(_("Sending group file"),
					       "");

		else
			gif->create_pbar_type4(_("Sending variable"), "");
	} else
		gif->create_pbar_type5(_("Sending variables"), "");

	// Now, send files
	sel = clist_win.selection;
	while (sel != NULL) {
		TilpFileInfo *f = (TilpFileInfo *) sel->data;

		// It is not the last file to send
		if (((sel->next) != NULL) && (l > 1)) {

			// More than one file to send
			if (tilp_error
			    (ti_calc.
			     send_var(f->name, mode | MODE_SEND_VARS,
				      f->actions))) {
				gif->destroy_pbar();
				return -1;
			}
		} else {

			// It is the last one
			if (tilp_error
			    (ti_calc.
			     send_var(f->name, mode | MODE_SEND_LAST_VAR,
				      f->actions))) {
				gif->destroy_pbar();
				return -1;
			}
		}
		i++;
		if (l > 1) {
			info_update.main_percentage = (float) i / l;
			info_update.pbar();
			info_update.refresh();
		}
		sel = sel->next;
	} gif->destroy_pbar();
	return 0;
}


/*
  Receive one or more selected variables.
  Returned value:
  - negative if error
  - zero if successful (single file)
  - positive if successful (group file named TMPFILE_GROUP)
*/
int tilp_calc_recv_var(void)
{
	int l, nvars;
	l = g_list_length(ctree_win.selection);
	nvars = 0;
	if (tilp_calc_isready())
		return -1;
	switch (options.lp.calc_type) {
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
		{
			if (!tilp_ctree_selection_ready())
				return -1;
			gif->create_pbar_type5(_("Receiving variable(s)"),
					       "");
			if ((g_list_length(ctree_win.selection) == 1)
			    || (options.single_or_group == RECV_AS_SINGLE)) {

				//
				// One file or single: filename is returned by recv_var
				//
				GList *sel;
				sel = ctree_win.selection;
				while (sel != NULL) {
					TiVarEntry *ve =
					    (TiVarEntry *) sel->data;
					char *old_path =
					    g_get_current_dir();
					char *src_path = NULL;
					char *dst_path = NULL;
					char tmp_filename[MAXCHARS];
					int err;
					strcpy(tmp_filename,
					       TMPFILE_GROUP);
					chdir(g_get_tmp_dir());
					err =
					    ti_calc.recv_var(tmp_filename,
							     MODE_RECEIVE_SINGLE_VAR,
							     ve);
					chdir(old_path);
					if (tilp_error(err)) {
						gif->destroy_pbar();
						return -1;
					}
					// Check for existence and move
					src_path =
					    g_strconcat(g_get_tmp_dir(),
							G_DIR_SEPARATOR_S,
							tmp_filename,
							NULL);
					dst_path =
					    g_strconcat(g_get_current_dir
							(),
							G_DIR_SEPARATOR_S,
							tmp_filename,
							NULL);
					tilp_file_move_with_check(src_path,
								  dst_path);
					nvars++;
					info_update.main_percentage =
					    (float) nvars / l;
					info_update.pbar();
					info_update.refresh();
					sel = sel->next;
				} gif->destroy_pbar();
			} else {

				//
				// Several files, saved as  a group file
				//
				char *old_path = g_get_current_dir();
				GList *sel;
				int err = 0;
				char tmp_filename[MAXCHARS], *tmpf;
				sel = ctree_win.selection;
				while (sel != NULL) {
					TiVarEntry *ve =
					    (TiVarEntry *) sel->data;
					strcpy(tmpf =
					       tmp_filename,
					       TMPFILE_GROUP);
					chdir(g_get_tmp_dir());
					if (nvars == 0)
						err =
						    ti_calc.recv_var(tmpf,
								     MODE_RECEIVE_FIRST_VAR,
								     ve);

					else if (nvars == l - 1)
						err =
						    ti_calc.recv_var(tmpf,
								     MODE_RECEIVE_LAST_VAR,
								     ve);

					else
						err =
						    ti_calc.recv_var(tmpf,
								     MODE_NORMAL,
								     ve);
					chdir(old_path);
					if (tilp_error(err)) {
						gif->destroy_pbar();
						return -1;
					}
					nvars++;
					info_update.main_percentage =
					    (float) nvars / l;
					info_update.pbar();
					info_update.refresh();
					sel = sel->next;
				} gif->destroy_pbar();
				if (tilp_error(err))
					return -1;

                return +1;
			}
		}
		break;
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
			if (tilp_error(err))
				return -1;

			// Detect for single/group file
			if (!strcmp(tmp_filename, TMPFILE_GROUP))
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
	return 0;
}
