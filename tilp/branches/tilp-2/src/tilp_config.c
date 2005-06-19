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
#if defined(__LINUX__) || defined(__BSD__)
static void default_config_linux(void)	// linux specific options
{
	options.remote_font_name = g_strdup("");
	options.local_font_name = g_strdup("-adobe-courier-medium-r-*-*-*-120-*-*-*-*-*-*");
	options.working_dir = g_strdup(g_get_home_dir());
}
#endif				

#ifdef __WIN32__
static void default_config_win32(void)
{
	options.remote_font_name = g_strdup("");
	options.local_font_name = g_strdup("-adobe-courier-medium-r-normal--12-120-75-75-p-70-iso8859-1");
	options.working_dir = g_get_current_dir();
}
#endif

#ifndef __MACOSX__
int tilp_config_default(void)
{
	options.xsize = 640 / 2;
	options.ysize = 480 / 2;

	options.local_sort = SORT_BY_NAME;
	options.local_sort_order = SORT_DOWN;
	options.remote_sort = SORT_BY_NAME;
	options.remote_sort_order = SORT_DOWN;

	options.overwrite = CONFIRM_YES;
	options.full_path = PATH_FULL;
	options.show_hidden = SHOW_TIF;

	options.screen_format = PNG;
	options.screen_clipping = SCREEN_CLIPPED;
	options.screen_blurry = 0;

	options.auto_detect = !0;
	options.recv_as_group = RECV_AS_GROUP;

	options.cable_model = CABLE_NUL;
	options.cable_port = PORT_0;
	options.calc_model = CALC_NONE;
	options.cable_delay = DFLT_DELAY;
	options.cable_timeout = DFLT_TIMEOUT;

#if defined(__LINUX__) || defined(__BSD__)
	default_config_linux();
#elif defined(__WIN32__)
	default_config_win32();
#else				
	return 0;
#endif

	return 0;
}
#endif /* !__MACOSX__ */

static int get_config_path(char **path)
{
#if defined(__LINUX__) || defined(__BSD__)
	*path = g_strconcat(g_get_home_dir(), INI_FILE, NULL);
#elif defined(__WIN32__)
	*path = g_strconcat(inst_paths.base_dir, G_DIR_SEPARATOR_S, INI_FILE, NULL);
#endif				
	return 0;
}

/* Chech whether a RC file exists */
int tilp_config_exist(void)
{
	char* ini_file;

	get_config_path(&ini_file);

	return !access(ini_file, F_OK);
}


/* Delete the RC file */
int tilp_config_delete(void)
{
	char* ini_file;

	get_config_path(&ini_file);

	return unlink(ini_file);
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
	get_config_path(&ini_file);

	txt = fopen(ini_file, "rt");
	if (txt == NULL)
		return -1;

	for (i = 0; i < 5; i++)
		fgets(buffer, 256, txt);

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

	return 0;
}

int tilp_config_write(void)
{
	char* ini_file;
	GKeyFile* kf;
	GError* error = NULL;
	gchar *content;
	FILE* f;

	// get file location
	get_config_path(&ini_file);

	kf = g_key_file_new();

	g_key_file_set_comment(kf, NULL, NULL, 
		"# Config file for TiLP\n" \
		"# Copyright (C) 1999-2005 The TiLP Team <tilp-devel@lists.sf.net>\n" \
		"# Warning: any comments that you add to this file WILL be overwritten", &error);

	// Section [DEVICE]
	g_key_file_set_string (kf, SECTION_DEVICE, "calc_model", ticalcs_model_to_string(options.calc_model));
	g_key_file_set_comment(kf, SECTION_DEVICE, "calc_model", "Calculator model", &error);

	g_key_file_set_string (kf, SECTION_DEVICE, "cable_model", ticables_model_to_string(options.cable_model));
	g_key_file_set_comment(kf, SECTION_DEVICE, "cable_model", "Cable model", &error);

	g_key_file_set_string (kf, SECTION_DEVICE, "cable_port", ticables_port_to_string(options.cable_port));
	g_key_file_set_comment(kf, SECTION_DEVICE, "cable_port", "Port", &error);

	g_key_file_set_integer(kf, SECTION_DEVICE, "cable_timeout", options.cable_timeout);	
	g_key_file_set_comment(kf, SECTION_DEVICE, "cable_timeout", "Timeout in tenth of seconds", &error);

	g_key_file_set_integer(kf, SECTION_DEVICE, "cable_delay", options.cable_delay);	
	g_key_file_set_comment(kf, SECTION_DEVICE, "cable_delay", "Inter-bit delay in µs", &error);

	g_key_file_set_comment(kf, SECTION_DEVICE, NULL, "Device section", &error);

	// Section [GUI]

	g_key_file_set_integer(kf, SECTION_GUI, "xsize", options.xsize);
	g_key_file_set_comment(kf, SECTION_GUI, "xsize", "Size of window", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "ysize", options.ysize);
	g_key_file_set_comment(kf, SECTION_GUI, "ysize", "Size of window", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "local_sort", options.local_sort);
	g_key_file_set_comment(kf, SECTION_GUI, "local_sort", "Sorting mode for local view", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "local_sort_order", options.local_sort_order);
	g_key_file_set_comment(kf, SECTION_GUI, "local_sort_order", "Sorting order for local view", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "remote_sort", options.remote_sort);
	g_key_file_set_comment(kf, SECTION_GUI, "remote_sort", "Sorting mode for remote view", &error);

	g_key_file_set_integer(kf, SECTION_GUI, "remote_sort_order", options.remote_sort_order);
	g_key_file_set_comment(kf, SECTION_GUI, "remote_sort_order", "Sorting order for remote view", &error);

	g_key_file_set_comment(kf, SECTION_GUI, NULL, "GUI section", &error);

	// Section [OPTIONS]
	g_key_file_set_integer(kf, SECTION_OPTIONS, "auto_detect", options.auto_detect);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "auto_detect", "Auto-detect hand-held model", &error);

	g_key_file_set_integer(kf, SECTION_OPTIONS, "full_path", options.full_path);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "full_path", "Use full path when sending variables", &error);

	g_key_file_set_integer(kf, SECTION_OPTIONS, "show_hidden", options.show_hidden);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "show_hidden", "Show hidden files in local view", &error);

	g_key_file_set_integer(kf, SECTION_OPTIONS, "overwrite", options.overwrite);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "overwrite", "Ask for overwriting", &error);

	g_key_file_set_integer(kf, SECTION_OPTIONS, "recv_as_group", options.recv_as_group);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "recv_as_group", "Receive as group instead of single files", &error);

	g_key_file_set_string (kf, SECTION_OPTIONS, "working_dir", options.working_dir);
	g_key_file_set_comment(kf, SECTION_OPTIONS, "working_dir", "Working folder", &error);

	g_key_file_set_comment(kf, SECTION_OPTIONS, NULL, "GUI section", &error);

	// Section [FONTS]
	g_key_file_set_string (kf, SECTION_FONTS, "remote_font_name", options.remote_font_name);
	g_key_file_set_comment(kf, SECTION_FONTS, "remote_font_name", "Font to use for remote view", &error);

	g_key_file_set_string (kf, SECTION_FONTS, "local_font_name", options.local_font_name);
	g_key_file_set_comment(kf, SECTION_FONTS, "local_font_name", "Font to use for local view", &error);

	g_key_file_set_comment(kf, SECTION_FONTS, NULL, "Screenshot section", &error);

	// Section [SCREEN]
	g_key_file_set_integer(kf, SECTION_SCREEN, "screen_format", options.screen_format);
	g_key_file_set_comment(kf, SECTION_SCREEN, "screen_format", "Screen format", &error);

	g_key_file_set_integer(kf, SECTION_SCREEN, "screen_scaling", options.screen_scaling);
	g_key_file_set_comment(kf, SECTION_SCREEN, "screen_scaling", "Screen scaling", &error);

	g_key_file_set_integer(kf, SECTION_SCREEN, "screen_clipping", options.screen_clipping);
	g_key_file_set_comment(kf, SECTION_SCREEN, "screen_clipping", "Screen clipping", &error);

	g_key_file_set_integer(kf, SECTION_SCREEN, "screen_blurry", options.screen_blurry);
	g_key_file_set_comment(kf, SECTION_SCREEN, "screen_blurry", "Save as blurry image", &error);

	g_key_file_set_comment(kf, SECTION_SCREEN, NULL, "Screenshot section", &error);

	// export file as string
	content = g_key_file_to_data(kf, NULL, &error);
	if(error != NULL)
	{
		fprintf (stderr, "Unable to read file: %s\n", error->message);
		g_error_free(error);
		return -1;
	} 
	
	// write content
	f = fopen(ini_file, "wt");
	if (f == NULL) 
	{
		gif->msg_box1(_("Error"), _
			     ("Unable to write the config file (~/.tilp or tilp.ini).\n"));
		return -1;
	}
	fwrite(content, strlen(content), 1, f);
	fclose(f);

	// free structures
	g_free(content);
	g_key_file_free(kf);
	g_free(ini_file);

	return 0;
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
	get_config_path(&ini_file);

	// and read
	kf = g_key_file_new();
	result = g_key_file_load_from_file(kf, ini_file, G_KEY_FILE_NONE, &error);
	if(result == FALSE)
	{
		if(error != NULL)
		{
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
		options.calc_model = ticables_string_to_model(s);
	g_free(s);

	s = g_key_file_get_string(kf, SECTION_DEVICE, "cable_port", &error);
	if(s != NULL)
		options.calc_model = ticables_string_to_port(s);
	g_free(s);

	options.cable_timeout = 
		g_key_file_get_integer(kf, SECTION_DEVICE, "cable_timeout", &error);

	options.cable_delay = 
		g_key_file_get_integer(kf, SECTION_DEVICE, "cable_delay", &error);

	// Section GUI
	options.xsize = g_key_file_get_integer(kf, SECTION_GUI, "xsize", &error);
	options.ysize = g_key_file_get_integer(kf, SECTION_GUI, "ysize", &error);

	options.local_sort = 
		g_key_file_get_integer(kf, SECTION_GUI, "local_sort", &error);
	options.local_sort_order = 
		g_key_file_get_integer(kf, SECTION_GUI, "local_sort_order", &error);

	options.remote_sort = 
		g_key_file_get_integer(kf, SECTION_GUI, "remote_sort", &error);
	options.remote_sort_order = 
		g_key_file_get_integer(kf, SECTION_GUI, "remote_sort_order", &error);

	// Section [OPTIONS]
	options.auto_detect = 
		g_key_file_get_integer(kf, SECTION_OPTIONS, "auto_detect", &error);
	options.full_path = 
		g_key_file_get_integer(kf, SECTION_OPTIONS, "full_path", &error);
	options.show_hidden = 
		g_key_file_get_integer(kf, SECTION_OPTIONS, "show_hidden", &error);
	options.overwrite = 
		g_key_file_get_integer(kf, SECTION_OPTIONS, "overwrite", &error);
	options.recv_as_group = 
		g_key_file_get_integer(kf, SECTION_OPTIONS, "recv_as_group", &error);
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