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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef __MACOSX__
#include "tilibs.h"
#else				/*  */
#include <glib/glib.h>
#include <libticables/cabl_int.h>
#include <libticalcs/calc_int.h>
#endif				/*  */

#include "tilp_core.h"

/*********************/
/* Config management */
/*********************/

#ifndef __MACOSX__		/* we use a general preferences system from Mac OS X */
/*
  Save the configuration file
*/
int tilp_config_save(void)
{
	tilp_rcfile_write();
	gif->msg_box(_("Information"), _("Configuration file saved."));
	return 0;
}


/*
  Load the configuration file
*/
int tilp_config_load(void)
{
	tilp_rcfile_read();
	gif->msg_box(_("Information"), _("Configuration file loaded."));
	return 0;
}
#endif				/* !__MACOSX__ */

/*
  Fill the option structure with default values
*/
#if defined(__LINUX__) || defined(__BSD__)
static void default_config_linux(void)	// linux specific options
{
	gchar *locale;
	options.unzip_location = g_strdup("unzip");
	options.unzip_options = g_strdup("");
	options.tar_location = g_strdup("tar");
	options.tar_options = g_strdup("");
	options.appsign_location = g_strdup("/usr/bin/appsign");
	options.appsign_options = g_strdup("-k /usr/bin/0104.key");
	options.web_location = g_strdup("/usr/bin/mozilla");
	options.web_options = g_strdup("");
	strcpy(options.left_font_name, "");
	strcpy(options.right_font_name,
	       "-adobe-courier-medium-r-*-*-*-120-*-*-*-*-*-*");
	options.console_mode = !0;
	locale = setlocale(LC_ALL, NULL);
	strcpy(options.locale, locale);
	options.working_dir = g_strdup(g_get_home_dir());
}
#endif				/*  */

#ifdef __WIN32__
static void default_config_win32(void)
{
	gchar *locale;
	options.unzip_location =
	    g_strdup("\"C:\\Program Files\\WinZip\\wzunzip.exe\"");
	options.unzip_options = g_strdup("");
	options.tar_location =
	    g_strdup("\"C:\\Program Files\\WinZip\\wzunzip.exe\"");
	options.tar_options = g_strdup("");
	options.appsign_location = g_strdup("");
	options.appsign_options = g_strdup("");
	options.web_location =
	    g_strdup("C:\\Program Files\\Internet Explorer\\IExplore.exe");
	options.web_options = g_strdup("");
	strcpy(options.left_font_name, "");
	strcpy(options.right_font_name,
	       "-adobe-courier-medium-r-normal--12-120-75-75-p-70-iso8859-1");
	options.console_mode = 0;
	locale = g_win32_getlocale();
	
	DISPLAY("current locale: <%s>\n", locale);
	
	g_free(locale);
	options.working_dir = g_get_current_dir();
}
#endif				/*  */
#ifndef __MACOSX__
int tilp_config_default(void)
{
	options.xsize = 640 / 2;
	options.ysize = 480 / 2;
	options.clist_sort = SORT_BY_NAME;
	options.clist_sort_order = SORT_DOWN;
	options.ctree_sort = SORT_BY_NAME;
	options.ctree_sort_order = SORT_DOWN;
	options.confirm = CONFIRM_YES;
	options.path_mode = FULL_PATH;
	options.file_disp = SHOW_TIF;
	options.screen_format = PNG;
	options.screen_clipping = CLIPPED_SCREEN;
	options.screen_blurry = 0;
	ticable_get_default_param(&options.lp);
	options.auto_detect = !0;
	options.show_gui = TRUE;
	options.single_or_group = RECV_AS_GROUP;

#if defined(__LINUX__) || defined(__BSD__)
	default_config_linux();

#elif defined(__WIN32__)
	default_config_win32();

#else				/*  */
	return 0;

#endif				/*  */
	return 0;
}
#endif /* !__MACOSX__ */

#ifdef __WIN32__
#define snprintf _snprintf
#endif				/*  */

/*
  Change the current drive (Win32 only)
*/
#ifndef __MACOSX__
int tilp_drive_change(char drive_letter)
{

#ifdef __WIN32__
	char buffer[MAXCHARS];
	gchar *s;
	snprintf(clist_win.current_dir, 8, "%c:\\", (char) drive_letter);

	//s = g_filename_from_utf8(clist_win.cur_dir, NULL);
	s = g_strdup(clist_win.current_dir);
	if (tilp_chdir(s) == -1) {
		gif->msg_box(_("Error"), _("Unable to change directory."));
	}
	g_free(s);

#else				/*  */
	gif->msg_box(_("Information"), _
		     ("This function is not available in the Win version."));

#endif				/*  */
	return 0;
}
#endif				/* !__MACOSX__ */

/*
  This function send files passed on the command line and place them in
  the ClistWin linked list.
  Manage file type, calculator detection and some other things...
*/
int tilp_cmdline_send(void)
{
	TilpFileInfo *fi;
	int last = options.confirm;
	gchar *ext = NULL;
	
	if (clist_win.selection == NULL)
		return -1;

	// Check for a valid file
	fi = (TilpFileInfo *) (g_list_first(clist_win.selection))->data;
	ext = tifiles_get_extension(fi->name);
	if (ext == NULL) {
		DISPLAY_ERROR(_
			      ("Invalid filename. There is no extension !\n"));
		exit(-1);
	}

	// Determine calculator type and override current settings
	options.lp.calc_type = tifiles_which_calc_type(fi->name);
	ticalc_set_calc(options.lp.calc_type, &ti_calc);

	// Send file(s)
	if (g_list_length(clist_win.selection) == 1) {

		// One file
		if (tifiles_is_a_flash_file(fi->name)) {
			if (!g_strcasecmp
			    (ext, tifiles_flash_app_file_ext()))
				tilp_calc_send_flash_app(fi->name);

			else if (!g_strcasecmp
				 (ext, tifiles_flash_os_file_ext()))
				tilp_calc_send_flash_os(fi->name);
		} else if (tifiles_is_a_regular_file(fi->name)) {
			options.confirm = FALSE;	// remove dirlist
			tilp_calc_send_var(0);
			options.confirm = last;
			return 0;
		} else if (tifiles_is_a_backup_file(fi->name)) {
			tilp_calc_send_backup(fi->name);
		} else {
			DISPLAY(_("Unknown file type.\n"));
		}
	} else {

		// More than one file
		if (clist_win.selection != NULL) {
			options.confirm = FALSE;
			tilp_calc_send_var(0);
			options.confirm = last;
			return 0;
		}
	}
	return 0;
}
int tilp_tifiles_ungroup(void)
{
	GList *sel;
	gchar *src_file, *dst_file;
	if (!tilp_clist_selection_ready())
		return -1;
	sel = clist_win.selection;
	while (sel != NULL) {
		gchar *dirname;
		TilpFileInfo *f = (TilpFileInfo *) sel->data;
		src_file =
		    g_strconcat(g_get_current_dir(), G_DIR_SEPARATOR_S,
				f->name, NULL);
		dirname =
		    gif->msg_entry(_("Create new directory"),
				   _
				   ("Directory where files will be ungrouped: "),
				   _("ungrouped"));
		if (dirname == NULL)
			return -1;
		tilp_file_mkdir(dirname);

		/*
		   if(mkdir(dirname))
		   {
		   gif->msg_box(_("Information"), 
		   _("Unable to create the directory.\n\n"));
		   g_free(dirname);
		   } */
		tilp_chdir(dirname);
		dst_file =
		    g_strconcat(g_get_current_dir(), G_DIR_SEPARATOR_S,
				f->name, NULL);
		tilp_file_copy(src_file, dst_file);
		tifiles_ungroup_file(dst_file);
		tilp_chdir("..");
		g_free(dirname);
		g_free(src_file);
		g_free(dst_file);
		sel = sel->next;
	}
	return 0;
}

int tilp_tifiles_group(void)
{
	GList *sel;
	char **array;
	gchar *grpname;
	gchar *dst_file;
	gint i = 0;

	if (!tilp_clist_selection_ready())
		return -1;
	if (g_list_length(clist_win.selection) < 2) {
		gif->msg_box(_("Error"),
			     _("You must select at least 2 files.\n\n"));
		return -1;
	}
	grpname =
	    gif->msg_entry(_("Group files"), _("Group name: "),
			   _("group"));
	if (grpname == NULL)
		return -1;
	array =
	    (char **) calloc(g_list_length(clist_win.selection) + 1,
			     sizeof(char *));
	sel = clist_win.selection;
	while (sel != NULL) {
		TilpFileInfo *f = (TilpFileInfo *) sel->data;
		array[i++] =
		    g_strconcat(g_get_current_dir(), G_DIR_SEPARATOR_S,
				f->name, NULL);
		array[i] = NULL;
		sel = sel->next;
	}
	dst_file =
	    g_strconcat(g_get_current_dir(), G_DIR_SEPARATOR_S, grpname,
			".", tifiles_group_file_ext(), NULL);
	g_free(grpname);
	tifiles_group_files(array, dst_file);
	g_strfreev(array);
	return 0;
}
