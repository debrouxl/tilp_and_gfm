/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tilp_core.h"

#define SECTION_DEVICE	"DEVICE"
#define SECTION_GUI		"GUI"
#define SECTION_OPTIONS	"OPTIONS"
#define SECTION_FONTS	"FONTS"
#define SECTION_SCREEN	"SCREEN"


/* Fill the option structure with default values */
#if defined(__LINUX__) || defined(__BSD__) || defined(__MACOSX__)
static void default_config_linux(void)	// linux specific options
{
	options.remote_font_name = g_strdup("");
	options.local_font_name = g_strdup("-adobe-courier-medium-r-*-*-*-120-*-*-*-*-*-*");
	options.working_dir = g_strdup(inst_paths.home_dir);
}
#endif				

#ifdef __WIN32__
static void default_config_win32(void)
{
	options.remote_font_name = g_strdup("");
	options.local_font_name = g_strdup("-adobe-courier-medium-r-normal--12-120-75-75-p-70-iso8859-1");
	options.working_dir = g_strdup(inst_paths.home_dir);
}
#endif

int tilp_config_default(void)
{
	options.pane_x_size = 640 / 2;
	options.pane_y_size = 480 / 2;

	options.wnd_x_size1 = 640;
	options.wnd_y_size1 = 480;

	options.wnd_x_size2 = 320;
	options.wnd_y_size2 = 320;

	options.local_sort = SORT_BY_NAME;
	options.local_sort_order = SORT_UP;
	options.remote_sort = SORT_BY_NAME;
	options.remote_sort_order = SORT_UP;

	options.filesel_type = 2;
	options.fs_type = 2;
	options.full_gui = !0;

	options.overwrite = CONFIRM_YES;
	options.show_all = 0;

	options.screen_format = PNG;
	options.screen_clipping = SCREEN_CLIPPED;
	options.screen_blurry = 0;

	options.auto_detect = 1;
	options.recv_as_group = (options.calc_model == CALC_NSPIRE) ? 0 : 1;
	options.backup_as_tigroup = 1;

	options.cable_model = CABLE_NUL;
	options.cable_port = PORT_0;
	options.calc_model = CALC_NONE;
	options.cable_delay = DFLT_DELAY;
	options.cable_timeout = DFLT_TIMEOUT;

	options.usb_avail = 0;

#if defined(__LINUX__) || defined(__BSD__) || defined(__MACOSX__)
	default_config_linux();
#elif defined(__WIN32__)
	default_config_win32();
#else

#endif

	return 0;
}

static char * get_config_path(void)
{
	return g_strconcat(g_get_home_dir(), G_DIR_SEPARATOR_S, INI_FILE, NULL);
}

/* Chech whether a RC file exists */
int tilp_config_exist(void)
{
#if defined(__LINUX__) || defined(__BSD__) || defined(__MACOSX__)
	char * ini_file;
	int retval;

	ini_file = get_config_path();

	retval = !access(ini_file, F_OK);
	g_free(ini_file);
	return retval;
#elif defined(__WIN32__)
	char* old_ini_file;
	char* ini_file;
	int result1, result2, retval;

	// On Windows, there can be two config files:
	// * in the install dir (deprecated, as it does not work well with the UAC);
	old_ini_file = g_strconcat(inst_paths.base_dir, G_DIR_SEPARATOR_S, INI_FILE, NULL);
	result1 = !access(old_ini_file, F_OK);
	// * per-user config files (which the *nix versions have been using for ages).
	ini_file = get_config_path();
	result2 = !access(ini_file, F_OK);

	if (result1)
	{
		// A config file exists at the old location
		if (!result2)
		{
			// No config file exists at the new location, bad.
			// Create it.
			FILE *in;
			FILE *out;

			in = fopen(old_ini_file, "rb");
			out = fopen(ini_file, "wb");
			if (in && out)
			{
				int c;

				while ((c = fgetc(in)) != EOF)
				{
					fputc(c, out);
				}
				fclose(out);
				fclose(in);
				// A config file now exists at the new location.
				// Delete the old file.
				unlink(old_ini_file);
				retval = 1;
			}
			else
			{
				// There's a problem...
				// Trigger failure in the callers.
				retval = 0;
			}
		}
		else
		{
			// A config file exists at the new location (even if a config file exists at the old location), good.
			retval = 1;
		}
	}
	else if (result2)
	{
		// A config file exists at the new location, good.
		retval = 1;
	}
	else
	{
		// No config file at either location.
		retval = 0;
	}
	g_free(old_ini_file);
	g_free(ini_file);
	return retval;
#endif
}


/* Delete the RC file */
int tilp_config_delete(void)
{
	char* ini_file;
	int result;

	ini_file = get_config_path();

	result = unlink(ini_file);
	g_free(ini_file);
	return result;
}

/* Return TiLP version number */
int tilp_config_get_version(char *version)
{
	char *ini_file;
	FILE *txt;
	char buffer[256];
	int i = 0;
	char *p;

	strcpy(version, "");
	if (tilp_config_exist() == 0) 
		return -1;
	ini_file = get_config_path();

	txt = fopen(ini_file, "rt");
	g_free(ini_file);
	if (txt == NULL)
		return -1;

	for (i = 0; i < 5; i++)
	{
		if (fgets(buffer, 256, txt) == NULL)
		{
			fclose(txt);
			return -1;
		}
	}

	p = strchr(buffer, '=');
	if (p == NULL)
		return -1;

	strcpy(version, ++p);
	p = strchr(version, '\r');
	if (p)
		*p = '\0';

	p = strchr(version, '\n');
	if (p)
		*p = '\0';

	fclose(txt);
	return 0;
}

int tilp_config_write(void)
{
	char* ini_file;
	GKeyFile* kf;
	GError* error = NULL;
	gchar *content;
	FILE* f;
	gint remap;
	int ret = 0;

	remap = ticalcs_remap_model_from_usb(options.cable_model, options.calc_model);

	// get file location
	ini_file = get_config_path();

	kf = g_key_file_new();

	g_key_file_set_comment(kf, NULL, NULL, 
		"# Config file for TiLP\n" \
		"# Copyright (C) 1999-2011 The TiLP Team <tilp-devel@lists.sf.net>\n" \
		"# Warning: any comments that you add to this file WILL be overwritten", &error);

	// Section [DEVICE]
	g_key_file_set_string (kf, SECTION_DEVICE, "calc_model", ticalcs_model_to_string(remap));
	g_key_file_set_comment(kf, SECTION_DEVICE, "calc_model", "Calculator model", &error);

	g_key_file_set_string (kf, SECTION_DEVICE, "cable_model", ticables_model_to_string(options.cable_model));
	g_key_file_set_comment(kf, SECTION_DEVICE, "cable_model", "Cable model", &error);

	g_key_file_set_string (kf, SECTION_DEVICE, "cable_port", ticables_port_to_string(options.cable_port));
	g_key_file_set_comment(kf, SECTION_DEVICE, "cable_port", "Port", &error);

	g_key_file_set_integer(kf, SECTION_DEVICE, "cable_timeout", options.cable_timeout);
	g_key_file_set_comment(kf, SECTION_DEVICE, "cable_timeout", "Timeout in tenth of seconds", &error);

	g_key_file_set_integer(kf, SECTION_DEVICE, "cable_delay", options.cable_delay);
	g_key_file_set_comment(kf, SECTION_DEVICE, "cable_delay", "Inter-bit delay in us", &error);

	// Section [GUI]

	g_key_file_set_integer(kf, SECTION_GUI, "pane_x_size", options.pane_x_size);
	g_key_file_set_comment(kf, SECTION_GUI, "pane_x_size", "Size of remote view", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "pane_y_size", options.pane_y_size);
	g_key_file_set_comment(kf, SECTION_GUI, "pane_y_size", "Size of remote view", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "wnd_x_size1", options.wnd_x_size1);
	g_key_file_set_comment(kf, SECTION_GUI, "wnd_x_size1", "Size of window (full)", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "wnd_y_size1", options.wnd_y_size1);
	g_key_file_set_comment(kf, SECTION_GUI, "wnd_y_size1", "Size of window (full)", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "wnd_x_size2", options.wnd_x_size2);
	g_key_file_set_comment(kf, SECTION_GUI, "wnd_x_size2", "Size of window (no local)", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "wnd_y_size2", options.wnd_y_size2);
	g_key_file_set_comment(kf, SECTION_GUI, "wnd_y_size2", "Size of window (no local)", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "local_sort", options.local_sort);
	g_key_file_set_comment(kf, SECTION_GUI, "local_sort", "Sorting mode for local view", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "local_sort_order", options.local_sort_order);
	g_key_file_set_comment(kf, SECTION_GUI, "local_sort_order", "Sorting order for local view", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "remote_sort", options.remote_sort);
	g_key_file_set_comment(kf, SECTION_GUI, "remote_sort", "Sorting mode for remote view", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "remote_sort_order", options.remote_sort_order);
	g_key_file_set_comment(kf, SECTION_GUI, "remote_sort_order", "Sorting order for remote view", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "fs_type", options.filesel_type);
	g_key_file_set_comment(kf, SECTION_GUI, "fs_type", "Obsolete, ignored by current TiLP", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "filesel_type", options.filesel_type);
	g_key_file_set_comment(kf, SECTION_GUI, "filesel_type", "File Selector type", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "full_gui", options.full_gui);
	g_key_file_set_comment(kf, SECTION_GUI, "full_gui", "Use full gui (TiLP-I) or just remote view", &error);

	// Section [OPTIONS]
	g_key_file_set_integer(kf, SECTION_OPTIONS, "auto_detect", options.auto_detect);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "auto_detect", "Auto-detect USB handheld model", &error);

	g_key_file_set_integer(kf, SECTION_OPTIONS, "show_all", options.show_all);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "show_all", "Show hidden files in local view", &error);

	g_key_file_set_integer(kf, SECTION_OPTIONS, "overwrite", options.overwrite);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "overwrite", "Ask for overwriting", &error);

	g_key_file_set_integer(kf, SECTION_OPTIONS, "recv_as_group", options.recv_as_group);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "recv_as_group", "Receive as group instead of single files", &error);

	g_key_file_set_integer(kf, SECTION_OPTIONS, "backup_as_tigroup", options.backup_as_tigroup);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "backup_as_tigroup", "Receive as TIGroup instead of backup/group files", &error);

	g_key_file_set_string (kf, SECTION_OPTIONS, "working_dir", options.working_dir);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "working_dir", "Working folder", &error);

	// Section [FONTS]
	g_key_file_set_string (kf, SECTION_FONTS, "remote_font_name", options.remote_font_name);
	g_key_file_set_comment(kf, SECTION_FONTS, "remote_font_name", "Font to use for remote view", &error);

	g_key_file_set_string (kf, SECTION_FONTS, "local_font_name", options.local_font_name);
	g_key_file_set_comment(kf, SECTION_FONTS, "local_font_name", "Font to use for local view", &error);

	// Section [SCREEN]
	g_key_file_set_integer(kf, SECTION_SCREEN, "screen_format", options.screen_format);
	g_key_file_set_comment(kf, SECTION_SCREEN, "screen_format", "Screen format", &error);

	g_key_file_set_integer(kf, SECTION_SCREEN, "screen_scaling", options.screen_scaling);
	g_key_file_set_comment(kf, SECTION_SCREEN, "screen_scaling", "Screen scaling", &error);

	g_key_file_set_integer(kf, SECTION_SCREEN, "screen_clipping", options.screen_clipping);
	g_key_file_set_comment(kf, SECTION_SCREEN, "screen_clipping", "Screen clipping", &error);

	g_key_file_set_integer(kf, SECTION_SCREEN, "screen_blurry", options.screen_blurry);
	g_key_file_set_comment(kf, SECTION_SCREEN, "screen_blurry", "Save as blurry image", &error);

	// export file as string
	content = g_key_file_to_data(kf, NULL, &error);
	if(error != NULL)
	{
		fprintf (stderr, "Unable to read file: %s\n", error->message);
		g_error_free(error);
		ret = -1;
		goto exit;
	} 
	
	// write content
	f = fopen(ini_file, "wt");
	if (f == NULL) 
	{
		gif->msg_box1(_("Error"), _("Unable to write the config file (~/.tilp or ~/tilp.ini).\n"));
		ret = -1;
		goto exit;
	}
	if (fwrite(content, strlen(content), 1, f) < 1)
	{
		ret = -1;
	}
	fclose(f);

exit:
	// free structures
	g_free(content);
	g_key_file_free(kf);
	g_free(ini_file);

	return ret;
}

int tilp_config_read(void)
{
	char* ini_file;
	gboolean result;
	GKeyFile* kf;
	GError* error = NULL;
	gchar* s;

	if(!tilp_config_exist())
		return -1;

	// get file location
	ini_file = get_config_path();

	// and read
	kf = g_key_file_new();
	result = g_key_file_load_from_file(kf, ini_file, G_KEY_FILE_NONE, &error);
	if (result == FALSE)
	{
		if (error != NULL)
		{
			g_key_file_free(kf);
			g_free(ini_file);
			fprintf (stderr, "Unable to read file: %s\n", error->message);
			g_error_free(error);
			return -1;
		}
	}

	// Section [DEVICE]
	s = g_key_file_get_string(kf, SECTION_DEVICE, "calc_model", &error);
	if(s != NULL)
		options.calc_model = ticalcs_string_to_model(s);
	g_free(s);

	s = g_key_file_get_string(kf, SECTION_DEVICE, "cable_model", &error);
	if(s != NULL)
		options.cable_model = ticables_string_to_model(s);
	g_free(s);
	
	options.calc_model = ticalcs_remap_model_to_usb(options.cable_model, options.calc_model);

	s = g_key_file_get_string(kf, SECTION_DEVICE, "cable_port", &error);
	if(s != NULL)
		options.cable_port = ticables_string_to_port(s);
	g_free(s);

	options.cable_timeout = 
		g_key_file_get_integer(kf, SECTION_DEVICE, "cable_timeout", &error);

	options.cable_delay = 
		g_key_file_get_integer(kf, SECTION_DEVICE, "cable_delay", &error);

	// Section GUI
	options.pane_x_size = g_key_file_get_integer(kf, SECTION_GUI, "pane_x_size", &error);
	options.pane_y_size = g_key_file_get_integer(kf, SECTION_GUI, "pane_y_size", &error);

	options.wnd_x_size1 = g_key_file_get_integer(kf, SECTION_GUI, "wnd_x_size1", &error);
	options.wnd_y_size2 = g_key_file_get_integer(kf, SECTION_GUI, "wnd_y_size2", &error);

	options.wnd_x_size1 = g_key_file_get_integer(kf, SECTION_GUI, "wnd_x_size1", &error);
	options.wnd_y_size2 = g_key_file_get_integer(kf, SECTION_GUI, "wnd_y_size2", &error);

	options.local_sort = 
		g_key_file_get_integer(kf, SECTION_GUI, "local_sort", &error);
	options.local_sort_order = 
		g_key_file_get_integer(kf, SECTION_GUI, "local_sort_order", &error);

	options.remote_sort = 
		g_key_file_get_integer(kf, SECTION_GUI, "remote_sort", &error);
	options.remote_sort_order = 
		g_key_file_get_integer(kf, SECTION_GUI, "remote_sort_order", &error);

	if (g_key_file_has_key(kf, SECTION_GUI, "filesel_type", &error))
		options.filesel_type = 
			g_key_file_get_integer(kf, SECTION_GUI, "filesel_type", &error);
	else
		options.filesel_type = 2;
	/* Copy filesel_type to fs_type. If fs_type is 2 (native), it will be changed to the
	   appropriate number based on the platform, whereas filesel_type stays at 2. */
	options.fs_type = options.filesel_type;
	options.full_gui = 
		g_key_file_get_integer(kf, SECTION_GUI, "full_gui", &error);

	// Section [OPTIONS]
	options.auto_detect = 
		g_key_file_get_integer(kf, SECTION_OPTIONS, "auto_detect", &error);
	options.show_all = 
		g_key_file_get_integer(kf, SECTION_OPTIONS, "show_all", &error);
	options.overwrite = 
		g_key_file_get_integer(kf, SECTION_OPTIONS, "overwrite", &error);
	options.recv_as_group = 
		g_key_file_get_integer(kf, SECTION_OPTIONS, "recv_as_group", &error);
	options.backup_as_tigroup = 
		g_key_file_get_integer(kf, SECTION_OPTIONS, "backup_as_tigroup", &error);
	s = 
		g_key_file_get_string(kf, SECTION_OPTIONS, "working_dir", &error);
	if(s != NULL)
	{
		g_free(options.working_dir);
		options.working_dir = s;
	}

	// Section FONTS
	s = g_key_file_get_string(kf, SECTION_FONTS, "local_font_name", &error);
	if(s != NULL)
	{
		g_free(options.local_font_name);
		options.local_font_name = s;
	}

	s = g_key_file_get_string(kf, SECTION_FONTS, "remote_font_name", &error);
	if(s != NULL)
	{
		g_free(options.remote_font_name);
		options.remote_font_name = s;
	}

	// Section [SCREEN]
	options.screen_format = 
		g_key_file_get_integer(kf, SECTION_SCREEN, "screen_format", &error);
	options.screen_scaling = 
		g_key_file_get_integer(kf, SECTION_SCREEN, "screen_scaling", &error);
	options.screen_clipping = 
		g_key_file_get_integer(kf, SECTION_SCREEN, "screen_clipping", &error);
	options.screen_blurry = 
		g_key_file_get_integer(kf, SECTION_SCREEN, "screen_blurry", &error);

	// free structures
	g_key_file_free(kf);
	g_free(ini_file);

	if(options.calc_model == CALC_NSPIRE)
		options.recv_as_group = 0;

	return 0;
}

/* GUI wrapper */

int tilp_config_save(void)
{
	tilp_config_write();
	gif->msg_box1(_("Information"), _("Configuration file saved."));

	return 0;
}

int tilp_config_load(void)
{
	tilp_config_read();
	gif->msg_box1(_("Information"), _("Configuration file loaded."));

	return 0;
}
