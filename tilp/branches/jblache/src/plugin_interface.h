/*  string_editor - a plug-in template for tilp
 *  Copyright (C) 2000  Romain Lievin
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

#ifndef PLUGIN_INT_H
#define PLUGIN_INT_H

#include "dep.h"

/********************/
/* Type definitions */
/********************/

/* The varinfo structure */
typedef struct varinfo VARINFO;

/* The tilp preferences/settings */
struct tilp_settings
{
  int calc_type; // Calculator type
  int link_type; // Link type
  unsigned int io_addr; // I/O port address
  char device[16]; // (Character) device
  int path_mode; // Full or local path (89/92/92+ only)
  int show; // Show or hide hidden files
  int file_mode; // Keep or not keep the archive attribute (89/92+ only)
  int screen_format; // PCX/XPM file format for screendumps
  int timeout; // Timeout value (link cable)
  int delay; // Delay value (link cable)
  int plugins_loading; // Load or not load plugins at startup
  int tidev; // Use the 'tidev' kernel module
};
typedef struct tilp_settings GTKTILINK_SETTINGS;

/* The structure for managing TI/PC transfers */
//typedef struct ti_calc TICALC_FNCTS;

/* The load & save functions */
typedef int (*PLUGIN_LOAD_FNCT) (char *, byte **, VARINFO **);
typedef int (*PLUGIN_SAVE_FNCT) (char *, byte *,  VARINFO *);

/* The plugin functions */
struct plugin_fncts
{
  char *filename;
  PLUGIN_LOAD_FNCT load_var_content;
  PLUGIN_SAVE_FNCT save_var_content;
};
typedef struct plugin_fncts PLUGIN_FNCTS;

/* The interface of the plugin */
//G_MODULE_EXPORT
const char *get_plugin_version();
//G_MODULE_EXPORT
const char **get_supp_calcs();
//G_MODULE_EXPORT
const char **get_supp_types();
//G_MODULE_EXPORT
int run_plugin(PLUGIN_FNCTS, GTKTILINK_SETTINGS, TICALC_FNCTS);

#endif



