/*  tilp - link program for TI calculators
 *  Copyright (C) 1999-2001  Romain Lievin
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

#include "dep.h"
#include "img_fmt.h"

extern struct ticable_link        link_cable;
extern struct ticalc_fncts        ti_calc;
extern struct ticalc_info_update  info_update;

#ifdef HAVE_TIFFEP
extern Registry *plugin_registry;
extern gint registry_allowed;
#endif

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
  //  GtkWidget *widget;
  GList *dirlist;
  gchar *cur_dir;
  GList *selection;
  GList *file_selection;
  int copy_cut;
  //char win_dir[4*MAXCHARS];
} clist_win;

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

/* This struct is used by the CTree window */
extern struct ctree_window
{
  //GtkWidget *widget;
  GList *varlist;
  char cur_folder[9];
  GList *selection;
} ctree_win;

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
  //char unzip_filter[40];
  char left_font_name[MAXCHARS];
  char right_font_name[MAXCHARS];
  char transfer_mode;
  char locale[MAXCHARS];
  int file_checking;
  int console_mode;
  int auto_detect;
  int show_gui;
  int force_dirlist;

  struct ticable_param lp;
} options;

/* Not used yet */
struct file_char
{
  char *filename;	// Name of the file
  char *name;		// Name of the file without extension
  char *extension;	// and its extension
  int file_type;	// Type: single, group or backup
  int calc_type;	// Type: calculator (82, 83, ...)
  int nvars;		// Numbers of variables if group or PAK file
  // These fields are defined only if not a PAK or group file
  char local_varname[9];	// Name of the var (local path)
  char full_varname[18];	// Name of the var (full path)
  char parent_folder[9];	// Parent folder of the var
  char vartype[9];			// Type of the var
  byte varlocked;			// Var is locked/archived ?
  longword varsize;			// Size of the var
};

/* Used by the screendump related boxes */
struct screenshot
{
  Image img;
  //char **pixmap;
  //byte *bitmap;
  struct screen_coord sc;
};

#endif
