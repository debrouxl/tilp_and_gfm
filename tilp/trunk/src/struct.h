/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2002  Romain Lievin
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

#ifndef STRUCT_H
#define STRUCT_H

#include <glib/glib.h>

#ifdef __MACOSX__
#include <libticables/cabl_int.h>
#include <libticalcs/calc_def.h>
#endif /* __MACOSX__ */

#include "img_fmt.h"

#ifdef __cplusplus
extern "C" {
#endif

extern LinkCable   link_cable;
extern TicalcFncts ti_calc;
extern InfoUpdate  info_update;

#ifdef HAVE_TIFFEP
extern Registry *plugin_registry;
extern gint registry_allowed;
#endif

#ifndef __MACOSX__
extern struct installation_paths
{
  gchar *base_dir;    // Windows directory (determined at startup)
  
  gchar *share_dir;   // shared directory
  gchar *locale_dir;  // locale
  gchar *manpage_dir; // manpages
  gchar *help_dir;    // help files
  gchar *pixmap_dir;  // pixmaps
  gchar *startup_dir; // directory where the program has been launched
} inst_paths;
#endif

/* This struct contains the general options to configure the program */
extern struct goptions
{
  int xsize;
  int ysize;
  int clist_sort;
  int clist_sort_order;
  int ctree_sort;
  int ctree_sort_order;
  int confirm;
  int path_mode;
  int show;
  int file_mode;
  int plugins_loading;
  int screen_format;
  int screen_clipping;
  char *unzip_location;
  char *unzip_options;
  char *tar_location;
  char *tar_options;
  char left_font_name[MAXCHARS];
  char right_font_name[MAXCHARS];
  int transfer_mode;
  char locale[MAXCHARS];
  int file_checking;
  int console_mode;
  int auto_detect;
  int show_gui;
  int force_dirlist;

  struct ticable_param lp;
} options;

/* Used by the local directory list function */
struct file_info
{
  char *filename;
  time_t date;
  off_t size;
  uid_t user;
  gid_t group;
  mode_t attrib;
};

/* Used to retrieve stats on the on-calc memory usage */
struct calc_mem_info
{
  int vars;        // number of vars
  int folders;     // number of folders
  int mem;         // memory used (not archive memory)
  int archivemem;  // archive memory used
  
  int flash;      // number of FLASH apps
  int flashmem;   // FLASH mem used
  
  int freemem;    // remaining memory (see libticalcs... dunno where this memory remains ;))
};

/* Used for the directory list of plugins */
struct plugin_info
{
  char *name;
  char *var_type;
  char *calc_type;
};

/* This struct is used by the CList window */
extern struct clist_window
{
  GList *dirlist;
  gchar *cur_dir;
  GList *selection;
  GList *file_selection;
  int copy_cut;
} clist_win;

/* This struct is used by the CTree window */
extern struct ctree_window
{
  GList *varlist;
  char cur_folder[9];
  int memory;			// memory free or used by calc
  GList *selection;  // selection of vars
  GList *selection2; // selection of apps
  gpointer node;     // parent node of vars tree
} ctree_win;

/* Used by the screendump related boxes */
struct screenshot
{
  Image img;
  ScrCoord sc;
};

#ifdef __cplusplus
}
#endif

#endif
