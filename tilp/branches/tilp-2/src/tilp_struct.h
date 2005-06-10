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
	Structure definitions.
*/

#ifndef __TILP_STRUCT__
#define __TILP_STRUCT__

#ifndef __MACOSX__
# include <glib.h>
# include "tilibs.h"
#else
# include <glib/glib.h>
# include <libticables/cabl_int.h>
# include <libticalcs/calc_def.h>
#endif				/* !__MACOSX__ */

#include <sys/types.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAXCHARS 256

extern CableHandle* cable_handle;
extern CalcHandle*  calc_handle;

/* This struct contains the general options to configure the program */
typedef struct 
{
	DeviceOptions	device;

#ifndef __MACOSX__
    int		xsize;
    int		ysize;

    int		clist_sort;
    int		clist_sort_order;
#endif /* !__MACOSX__ */
    int		ctree_sort;
    int		ctree_sort_order;

    int		path_mode;
    int		file_disp;
	int		confirm;
    int		single_or_group;

    int		screen_format;
    int		screen_scaling;
    int		screen_clipping;
    int		screen_blurry;

#ifndef __MACOSX__
    char	left_font_name[MAXCHARS];
    char	right_font_name[MAXCHARS];

    char locale[MAXCHARS];
#endif /* !__MACOSX__ */

    int		console_mode;
    int		auto_detect;
    int		show_gui;

    char*	working_dir;
} TilpOptions;


/* Used by the local directory list function */
typedef struct 
{
    char *name;
    time_t date;
    off_t size;
#ifdef __WIN32__
    int user;
    int group;
    int attrib;
#else
    uid_t user;
    gid_t group;
    mode_t attrib;
#endif

    char **actions;		// Ticalc action associated w/ the file
} TilpFileInfo;


/* Used to retrieve stats on the on-calc memory usage */
typedef struct 
{
    int vars;			// number of vars
    int folders;		// number of folders
    int mem;			// memory used (not archive memory)
    int archivemem;		// archive memory used

    int flash;			// number of FLASH apps
    int flashmem;		// FLASH mem used

    int freemem;		// remaining memory
} TilpCalcMemInfo;


/* This struct is used by the CList window */
typedef struct 
{
    GList *dirlist;			// linked list of files & directories
    gchar *current_dir;		// current active directory
    GList *selection;		// selection of files (send, view, ...)
    GList *file_selection;	// selection of files (cut/copy/paste)
    int copy_cut;			// action type
} TilpClistWin;


/* This struct is used by the CTree window */
typedef struct 
{
    TNode *dirlist;			// linked list of variables & folders
    TNode *var_tree;		// future use: tree of vars
    TNode *app_tree;		// future use: tree of apps
    unsigned int memory;	// memory free or used by calc
    GList *selection;		// selection of variables
    GList *selection2;		// selection of applications
} TilpCtreeWin;


/* Used by the screendump related boxes */
typedef struct 
{
    uint8_t*	bitmap;
    int			width;
    int			height;
} TilpScreen;

  extern TilpOptions	options;
  extern TilpClistWin	clist_win;
  extern TilpCtreeWin	ctree_win;

#ifdef __cplusplus
}
#endif
#endif
