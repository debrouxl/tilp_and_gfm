/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
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

/* This struct contains the general options to configure the program */
typedef struct 
{
	// device
	int		cable_model;
	int		cable_port;
	int		cable_timeout;
	int		cable_delay;
	int		calc_model;

	// gui
#ifndef __MACOSX__
    int		pane_x_size;
    int		pane_y_size;

	int		wnd_x_size1;
	int		wnd_y_size1;

	int		wnd_x_size2;
	int		wnd_y_size2;

    int		local_sort;
    int		local_sort_order;
#endif
    int		remote_sort;
    int		remote_sort_order;

	int		fs_type;
	int		full_gui;

	// options
	int		auto_detect;
    int		local_path;
    int		show_all;
	int		overwrite;
    int		recv_as_group;
	
	char*	working_dir;

	// screen
    int		screen_format;
    int		screen_scaling;
    int		screen_clipping;
    int		screen_blurry;

	// fonts
#ifndef __MACOSX__
    char*	remote_font_name;
    char*	local_font_name;
#endif

} TilpOptions;


/* Used by the local directory list function */
typedef struct 
{
	// used for entries
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

	// used for actions
	FileContent* content;	// file content to send
	int*		 selected;	// entry/entries is/are selected
} FileEntry;

/* Used to retrieve stats on the on-calc memory usage */
typedef struct 
{
	unsigned int n_folders;		// number of folders
    unsigned int n_vars;		// number of vars
	unsigned int n_apps;		// number of FLASH apps

	unsigned int ram_used;
	unsigned int flash_used;

    unsigned int ram_free;
	unsigned int flash_free;
} TilpMem;


/* This struct is used by the CList window */
typedef struct 
{
    GList* dirlist;			// linked list of files & directories
    gchar* cwdir;			// current active directory

    GList* selection;		// selection of files (data: FileEntry*)
	GList* selection2;		// selection of files (data: FileEntry*)
    GList* file_selection;	// selection of files (data: char*)

    int copy_cut;			// action type
} TilpLocal;


/* This struct is used by the CTree window */
typedef struct 
{
    TNode*	var_tree;		// future use: tree of vars
    TNode*	app_tree;		// future use: tree of apps

    TilpMem	memory;			// memory free or used by calc

    GList*	selection;		// selection of variables    (data: VarEntry)
    GList*	selection2;		// selection of applications (data: VarEntry)
} TilpRemote;

/* Global variables */

extern CableHandle* cable_handle;
extern CalcHandle*  calc_handle;

extern TilpOptions	options;
extern TilpLocal	local;
extern TilpRemote	remote;

extern int			working_mode;

#ifdef __cplusplus
}
#endif
#endif
