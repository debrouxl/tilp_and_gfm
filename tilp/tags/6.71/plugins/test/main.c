/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2002  Romain Lievin
 *
 * TiLP Plug-in for test/demo purposes.
 * Copyright (C) 2002 Romain Lievin <roms@tilp.info>
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

#include "tilp_plugin.h"

TilpPluginInfo infos = 
{
  "Test/Demo Plug-in",
  "1.0.0",
  "Romain Lievin <roms@tilp.info>",
  "89s"
};

/* 
   Returns plug-ins properties/capabilites 
   - name [out]    : the plug-in name
   - version [out] : the plug-in version
   - fext [out]    : an array of file extensions
*/
TilpPluginInfo* plugin_query(void)
{
  //printf(" plugin_query\n");
  return &infos;
}

/* Run plug-in */
int plugin_run(void)
{
  printf(" plugin_run\n");
  return 0;
}

/* Load file */
int plugin_load(const char *filename)
{
  printf(" plugin_load\n");
  return 0;
}

/* Save file */
int plugin_save(const char *filename)
{
  printf(" plugin_save\n");
  return 0;
}
