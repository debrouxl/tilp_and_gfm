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
  Plug-in management.
  The plug-in name is used as a unique key.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif				/*  */

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <gmodule.h>

#ifndef __MACOSX__
# include "tilp_core.h"
#else				/*  */
#include "../osx/cocoa_config.h"
#endif				/*  */

#include "tilp_plugin.h"

//#define DEBUG

// list of plug-ins
static GList *plugin_list = NULL;

// current plug-in (context)
static PLUGIN_QUERY module_query = NULL;
static PLUGIN_RUN module_run = NULL;
static PLUGIN_LOAD module_load = NULL;
static PLUGIN_SAVE module_save = NULL;
static TilpPluginInfo *module_infos = NULL;

/* 
   Copy/Free plugin info 
*/
static TilpPluginInfo *dup_plugin_info(TilpPluginInfo * src)
{
  TilpPluginInfo *dst = g_malloc0(sizeof(TilpPluginInfo));
  dst->name = g_strdup(src->name);
  dst->author = g_strdup(src->author);
  dst->version = g_strdup(src->version);
  dst->extensions = g_strdup(src->extensions);
  dst->path = g_strdup(src->path);
  dst->type = src->type;
  return dst;
}

static void free_plugin_info(TilpPluginInfo * src)
{
  g_free(src->name);
  g_free(src->author);
  g_free(src->version);
  g_free(src->extensions);
  g_free(src->path);
  g_free(src);
}

/* 
   Get plugin info structure 
*/
static TilpPluginInfo *query_plugin(const gchar * path,
				    const gchar * filename)
{
  GModule *module = NULL;
  gchar *fn = g_strconcat(path, "/", filename, NULL);
  PLUGIN_QUERY plugin_query = NULL;
  TilpPluginInfo *info = NULL;
  
  module = g_module_open(fn, 0);
  if (module == NULL) {
    g_warning("g_module_open failed: %s\n", g_module_error());
    return NULL;
  }
  
  if (g_module_symbol
      (module, "plugin_query", (gpointer) & plugin_query) == FALSE) {
    g_warning("g_module_symbol failed: %s\n",
	      g_module_error());
    return NULL;
  }
  
  info = dup_plugin_info(plugin_query());
  if (info == NULL) {
    g_warning("plugin_query failed !\n");
    return NULL;
  } else {
    info->path = g_strdup(fn);
    info->type = PLUGIN_LIB;
#ifdef DEBUG
    printl(0, "%s: %s | %s | %s | %s\n", info->path,
	    info->name, info->version, info->author,
	    info->extensions);
#endif				/*  */
  }
  
  if (g_module_close(module) == FALSE) {
    g_warning("g_module_close failed: %s\n", g_module_error());
    return NULL;
  }
  module = NULL;
  
  return info;
}


/* 
   Scan plugins directory and registry (usually at startup) 
*/
int tilp_plugins_scan(void)
{
	GDir *dir;
	GError *error;
	G_CONST_RETURN gchar *dirname;
	TilpPluginInfo *plugin_info;
	FILE *reg;
	char buffer[1024];
	gchar *reg_fn;
	gint end = 0;

	// Scan plug-ins directory
	if (g_module_supported() == FALSE) {
		gif->msg_box("Warning",
			     "Dynamic loading of modules (plug-ins) is not supported by the current platform !\n");
		return -1;
	}

	printl(0, _("scanning plug-ins... "));
	dir = g_dir_open(inst_paths.plugin_dir, 0, &error);
	if (dir == NULL) {
		g_error(_("tilp_plugins_scan: opendir error\n"));
		return -1;
	}

	while ((dirname = g_dir_read_name(dir)) != NULL) {
		if (!strcmp(dirname, "."))
			continue;
		if (!strcmp(dirname, ".."))
			continue;

		plugin_info = query_plugin(inst_paths.plugin_dir, dirname);
		if (plugin_info == NULL)
			return -1;

		plugin_list =
		    g_list_append(plugin_list, (gpointer) plugin_info);
	}
	g_dir_close(dir);
	printl(0, _("Done !\n"));

	// Scan registry 
	printl(0, _("scanning registry... "));
#ifdef __WIN32__
	reg_fn = g_strconcat(inst_paths.base_dir, REG_FILE, NULL);
#else				/*  */
	//reg_fn = g_strconcat(SYSCONFDIR "/tilp/", REG_FILE, NULL);
	reg_fn = g_strconcat(SHARE_DIR, G_DIR_SEPARATOR_S, REG_FILE, NULL);
#endif				/*  */
	//printf("<%s>\n", reg_fn);
	reg = fopen(reg_fn, "rt");
	if (reg == NULL) {
	  g_free(reg_fn);
	  gif->msg_box("Error", "The TiLP registry is missing !\n");
	  return -1;
	}
	g_free(reg_fn);

	while (!feof(reg) && !end) {
		char ext[256], name[256], path[256];
		char *s1, *s2;
		gint len;

		fgets(buffer, 256, reg);
		buffer[strlen(buffer) - 1] = '\0';
		if (!strcmp(buffer, "REG_END")) {
		  end = !0;
		  continue;
		}
		if (buffer[0] == '#' || !strlen(buffer))
			continue;
		plugin_info = g_malloc0(sizeof(TilpPluginInfo));

// to improve
		sscanf(buffer, "%s", ext);
		s1 = strchr(buffer, '\"');
		s1++;		// skip "
		s2 = strrchr(buffer, '\"');
		len = strlen(s1) - strlen(s2);
		strncpy(name, s1, len);
		name[len] = '\0';
		s2++;		// skip "
		sscanf(s2, " %s", path);

		//printf("<<%s|%s|%s>>\n", ext, name, path);
		plugin_info->name = g_strdup(name);
		plugin_info->author = g_strdup("");
		plugin_info->version = g_strdup("");
		plugin_info->extensions = g_strdup(ext);
		plugin_info->path = g_strdup(path);
		plugin_info->type = PLUGIN_EXE;
		plugin_list =
		    g_list_append(plugin_list, (gpointer) plugin_info);

#ifdef DEBUG
		printl(0, "%s: %s | %s | %s | %s\n", plugin_info->path,
			plugin_info->name, plugin_info->version,
			plugin_info->author, plugin_info->extensions);

#endif				/*  */
	}
	fclose(reg);
	printl(0, _("Done !\n"));

	return 0;
}

static GModule *module = NULL;
static gint counter = 0;
static gint type = 0;

/* 
   Start a new query:
   - int [out]: FALSE if no plugin available
*/
int tilp_plugins_search_start(void)
{
	counter = 0;
	return g_list_length(plugin_list);
}


/* 
   Search for a plug-in:
   - extension [in] : file extension to match
   - char* [out]    : the plug-in name or NULL if no more plugin
*/
gchar *tilp_plugins_search_query(const gchar * extension)
{
	GList *elt;
	TilpPluginInfo *info;

	if (counter == (int)g_list_length(plugin_list))
		return NULL;

	if (extension == NULL)
		return NULL;

	for (;;) {
		elt = g_list_nth(plugin_list, counter++);
		if (elt == NULL)
			break;
		info = (TilpPluginInfo *) elt->data;
		if (strstr(info->extensions, extension)) {
			//printl(0, "Plug-in found: <%s> <%s> <%s>\n", info->name, extension, info->extensions);
			return info->name;
		}
	}

	return NULL;
}


/* 
   Open a plug-in:
   - plugin_name [in] : the plug-in to load
   - int [out]        : an error code, 0 otherwise
*/
int tilp_plugins_open(const gchar * plugin_name)
{
	GList *ptr;
	TilpPluginInfo *info = NULL;

	if (module != NULL)
		tilp_plugins_close();

	ptr = plugin_list;
	while (ptr != NULL) {
		info = (TilpPluginInfo *) ptr->data;
		if (strstr(info->name, plugin_name))
			break;
		ptr = ptr->next;
	}

	module_infos = dup_plugin_info(info);

	type = info->type;
	if (info->type == PLUGIN_LIB) {
		module = g_module_open(info->path, 0);
		if (module == NULL) {
			g_warning("g_module_open failed: %s\n",
				  g_module_error());
			return -1;
		}
		if (g_module_symbol
		    (module, "plugin_query",
		     (gpointer) & module_query) == FALSE) {
			g_warning("g_module_symbol failed: %s\n",
				  g_module_error());
			return -1;
		}
		if (g_module_symbol
		    (module, "plugin_run",
		     (gpointer) & module_run) == FALSE) {
			g_warning("g_module_symbol failed: %s\n",
				  g_module_error());
			return -1;
		}
		if (g_module_symbol
		    (module, "plugin_load",
		     (gpointer) & module_load) == FALSE) {
			g_warning("g_module_symbol failed: %s\n",
				  g_module_error());
			return -1;
		}
		if (g_module_symbol
		    (module, "plugin_save",
		     (gpointer) & module_save) == FALSE) {
			g_warning("g_module_symbol failed: %s\n",
				  g_module_error());
			return -1;
		}
	} else if (info->type == PLUGIN_EXE)
	  return 0;
	else
	  return -1;

	return 0;
}


/* 
   Close a plug-in:
   - int [out]        : an error code, 0 otherwise
*/
int tilp_plugins_close()
{
	if (module == NULL)
		return -1;

	if ((type == PLUGIN_LIB) && (g_module_close(module) == FALSE)) {
		g_warning("g_module_close failed: %s\n", g_module_error());
		return -1;
	}

	module = NULL;
	module_query = NULL;
	module_run = NULL;
	module_load = NULL;
	module_save = NULL;

	free_plugin_info(module_infos);

	return 0;
}


/*
  Plugin wrappers
*/
TilpPluginInfo *tilp_plugins_query(void)
{
	if (module_infos->type == PLUGIN_LIB) {
		if (module_query == NULL)
			return NULL;
		else
			return module_query();
	} else if (module_infos->type == PLUGIN_EXE)
		return NULL;
	else
		return NULL;
}

int tilp_plugins_run(void)
{
	if (module_infos->type == PLUGIN_LIB) {
		if (module_run == NULL)
			return -1;
		else
			return module_run();
	} else if (module_infos->type == PLUGIN_EXE)
		return 0;
	else
		return -1;
}

int tilp_plugins_read(const char *filename)
{
	if (module_infos->type == PLUGIN_LIB) {
		if (module_load == NULL)
			return -1;
		else
			return module_load(filename);
	} else if (module_infos->type == PLUGIN_EXE) {
		gboolean result;
		gchar **argv = g_malloc0(3 * sizeof(gchar *));

		argv[0] = g_strdup(module_infos->path);
		argv[1] = g_strdup(filename);
		//printf("<%s %s>\n", argv[0], argv[1]);
		result = g_spawn_async(inst_paths.base_dir, argv, NULL, 0,
				       NULL, NULL, NULL, NULL);
		g_strfreev(argv);
		if (result == FALSE) {
			gif->msg_box("Error",
				     "Spawn error: unable to execute plug-in.");
			return -1;
		}
		return 0;
	} else
		return -1;
}

int tilp_plugins_write(const char *filename)
{
	if (module_infos->type == PLUGIN_LIB) {
		if (module_save == NULL)
			return -1;
		else
			return module_save(filename);
	}
	else if (module_infos->type == PLUGIN_EXE)
		return 0;
	else
		return -1;
}
