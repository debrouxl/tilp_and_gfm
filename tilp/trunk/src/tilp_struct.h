/* Hey EMACS -*- linux-c -*- */
/* tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2003  Romain Lievin
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

#ifndef __MACOSX__
# include <glib.h>
# include "tilibs.h"
#else
# include <glib/glib.h>
# include <libticables/cabl_int.h>
# include <libticalcs/calc_def.h>
#endif				/* !__MACOSX__ */

#include <sys/types.h>

#ifndef __WIN32__
# include <sys/stat.h>
#endif

#ifdef __WIN32__
# include "win32/grp.h"
# include "win32/pwd.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MAXCHARS 256

  extern TicableLinkCable link_cable;
  extern TicalcFncts ti_calc;
  extern TicalcInfoUpdate info_update;


#ifndef __MACOSX__
  typedef struct {
    gchar *base_dir;		// base directory
    gchar *locale_dir;		// locale
    gchar *manpage_dir;		// manpages
    gchar *help_dir;		// help files
    gchar *pixmap_dir;		// pixmaps
    gchar *icon_dir;		// icons
    gchar *plugin_dir;		// plug-ins
    gchar *glade_dir;		// directory of files for Glade
  } TilpInstPaths;
#endif


/* This struct contains the general options to configure the program */
  typedef struct {
#ifndef __MACOSX__
    int xsize;
    int ysize;

    int clist_sort;
    int clist_sort_order;
#endif /* !__MACOSX__ */

    int ctree_sort;
    int ctree_sort_order;

    int path_mode;
    int file_disp;

    int use_checksum;
    int single_or_group;
    int confirm;

    int screen_format;
    int screen_clipping;
    int screen_blurry;

    int clock_mode;
    int date_format;
    int time_format;

#ifndef __MACOSX__
    char *unzip_location;
    char *unzip_options;
    char *tar_location;
    char *tar_options;
    char *web_location;
    char *web_options;

    char *appsign_location;
    char *appsign_options;

    char left_font_name[MAXCHARS];
    char right_font_name[MAXCHARS];

    char locale[MAXCHARS];
#endif /* !__MACOSX__ */

    int console_mode;
    int auto_detect;
    int show_gui;

    char *working_dir;

    TicableLinkParam lp;
  } TilpOptions;


/* Used by the local directory list function */
  typedef struct {
    char *name;
    time_t date;
    off_t size;
    uid_t user;
    gid_t group;
    mode_t attrib;

    char **actions;		// Ticalc action associated w/ the file
  } TilpFileInfo;


/* Used to retrieve stats on the on-calc memory usage */
  typedef struct {
    int vars;			// number of vars
    int folders;		// number of folders
    int mem;			// memory used (not archive memory)
    int archivemem;		// archive memory used

    int flash;			// number of FLASH apps
    int flashmem;		// FLASH mem used

    int freemem;		// remaining memory
  } TilpCalcMemInfo;


/* This struct is used by the CList window */
  typedef struct {
    GList *dirlist;		// linked list of files & directories
    gchar *current_dir;		// current active directory
    GList *selection;		// selection of files (send, view, ...)
    GList *file_selection;	// selection of files (cut/copy/paste)
    int copy_cut;		// action type
  } TilpClistWin;


/* This struct is used by the CTree window */
  typedef struct {
    GNode *dirlist;		// linked list of variables & folders
    GNode *var_tree;		// future use: tree of vars
    GNode *app_tree;		// future use: tree of apps
    unsigned int memory;	// memory free or used by calc
    GList *selection;		// selection of variables
    GList *selection2;		// selection of applications
  } TilpCtreeWin;


/* Used by the screendump related boxes */
  typedef struct {
    uint8_t *bitmap;
    int width;
    int height;
  } TilpScreen;

  extern TilpOptions options;
  extern TilpClistWin clist_win;
  extern TilpCtreeWin ctree_win;
#ifndef __MACOSX__
  extern TilpInstPaths inst_paths;
#endif /* !__MACOSX__ */

#ifdef __cplusplus
}
#endif
#endif
