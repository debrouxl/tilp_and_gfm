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

/*
  Plug-ins interface and definitions.
*/

#ifndef __TILP_PLUGIN__
#define __TILP_PLUGIN__

#include <glib.h>

/* Interface release */
#define PLUGIN_IFACE "1.0"
#define P_INT_VERSION  PLUGIN_IFACE

/* Plugin type */
#define PLUGIN_LIB 1
#define PLUGIN_EXE 2

/* Plugin informations */
typedef struct {
	gchar *name;
	gchar *version;
	gchar *author;
	gchar *extensions;

	gchar *path;
	gint type;
} TilpPluginInfo;

/* Typedefs */
typedef TilpPluginInfo *(*PLUGIN_QUERY) (void);
typedef int (*PLUGIN_RUN) (void);
typedef int (*PLUGIN_LOAD) (const char *);
typedef int (*PLUGIN_SAVE) (const char *);


/* 
   Returns plug-ins properties/capabilites
   - TilpPluginInfo [out] : plugin info or NULL
*/
TilpPluginInfo *plugin_query(void);

/* 
   Run plug-in 
   - int [out]     : an error code, 0 otherwise.
*/
int plugin_run(void);

/* 
   Load file 
   - filename [in] : the file to open
   - int [out]     : an error code, 0 otherwise.
*/
int plugin_load(const char *filename);

/* 
   Save file 
   - filename [in] : the file to save
   - int [out]     : an error code, 0 otherwise.
*/
int plugin_save(const char *filename);

#endif
