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
	Initialization of portable paths
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

#include "tilp_core.h"

#ifndef __MACOSX__
TilpInstPaths inst_paths = 
{
	"", "\\locale", "\\manpages", "\\help", "\\pixmaps"
};
#endif

#ifndef __MACOSX__
/*
  Called by TiLP at startup for initializing platform dependant paths.
*/
#if defined(__LINUX__) || defined(__BSD__)
static void init_linux_paths(void)
{
	inst_paths.base_dir =
	    g_strconcat(SHARE_DIR, G_DIR_SEPARATOR_S, NULL);
	inst_paths.pixmap_dir =
	    g_strconcat(inst_paths.base_dir, "pixmaps/", NULL);
	inst_paths.icon_dir =
	    g_strconcat(inst_paths.base_dir, "icons/", NULL);
	inst_paths.help_dir =
	    g_strconcat(inst_paths.base_dir, "help/", NULL);
	inst_paths.manpage_dir = 
            g_strconcat(inst_paths.base_dir, "", NULL);
	inst_paths.glade_dir =
	    g_strconcat(inst_paths.base_dir, "glade/", NULL);
	inst_paths.home_dir =
		g_strdup(g_get_home_dir());

	/* bintextdomain(PACKAGE, "/usr/share/locale"); ->
	   '/usr/share/locale/  fr/LC_MESSAGES/tilp.mo' */
#ifdef ENABLE_NLS
	inst_paths.locale_dir = g_strconcat(LOCALEDIR, "/", NULL);
#endif				/*  */

	// on LINUX systems, HOME directory by default for security reasons
	tilp_chdir(inst_paths.home_dir);
}
#endif				/*  */

#ifdef __WIN32__
static void init_win32_paths(void)
{
	char *home_dir = NULL;
	HMODULE hModule;
	DWORD dWord;
	char *dirname;
	char *sBuffer;

	// Init the path for the Windows version by getting the 
	// executable location.
	hModule = GetModuleHandle("tilp.exe");
	sBuffer = (char *) malloc(4096 * sizeof(char));
	dWord = GetModuleFileName(hModule, sBuffer, 4096);

	dirname = g_dirname(sBuffer);
	inst_paths.base_dir = g_strconcat(dirname, "\\", NULL);
	g_free(dirname);
	free(sBuffer);

	inst_paths.pixmap_dir =
	    g_strconcat(inst_paths.base_dir, "pixmaps\\", NULL);
	inst_paths.icon_dir =
	    g_strconcat(inst_paths.base_dir, "icons\\", NULL);
	inst_paths.help_dir =
	    g_strconcat(inst_paths.base_dir, "help\\", NULL);
	inst_paths.manpage_dir =
	    g_strconcat(inst_paths.base_dir, "", NULL);
	inst_paths.glade_dir =
	    g_strconcat(inst_paths.base_dir, "glade\\", NULL);
	inst_paths.home_dir = 
	    g_strconcat(inst_paths.base_dir, "My TI files\\", NULL);

	/* bintextdomain(PACKAGE, "/usr/share/locale"); ->
	   '/usr/share/locale/  fr/LC_MESSAGES/tilp.mo' */
#ifdef ENABLE_NLS
	inst_paths.locale_dir =
	    g_strconcat(inst_paths.base_dir, "locale\\", NULL);
#endif				/*  */

	// on WIN32 systems, 'My TI Files' by default
	_chdir(inst_paths.home_dir);
}
#endif				/*  */

int tilp_paths_init(void)
{

#if defined(__LINUX__) || defined(__BSD__)
	init_linux_paths();

#elif defined(__WIN32__)
	init_win32_paths();

#endif				/*  */
	return 0;
}
#endif				/*  */

const char *tilp_paths_build_glade(const char *name)
{
	static char *path = NULL;

	g_free(path);
	path = g_strconcat(inst_paths.glade_dir, name, NULL);

	return path;
}
