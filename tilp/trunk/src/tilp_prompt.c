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
  TiLP in console mode (prompt)
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef __MACOSX__
# include <glib.h>
#else
# include <glib/glib.h>
#endif /* !__MACOSX__ */

#ifdef __WIN32__
# include "win32/dirent.h"
#endif

#include "tilp_core.h"

char fname[64];
int linkType = 0;
int progBar = 0;
int totalSize = 0;
int cmdState = 0;
char currDir[128] = "";
int getOut = 0;
int do_command(unsigned char *cmd, unsigned char *arg1);
static void prompt_commands(void);
int do_command(unsigned char *cmd, unsigned char *arg1)
{
	if (cmdState) {
		if (!strcmp(cmd, "quit")) {
			cmdState = 0;
			getOut = 1;
		}
		if (!strcmp(cmd, "exit")) {
			cmdState = 0;
			getOut = 1;
		}
		if (!(strcmp(cmd, "help"))) {
			printl(0, _
				("Currently recognized commands: ls, cd, help, quit, exit, ready, screen [filename], dirlist [filename], backup [filename], restore [filename], send [filename], receive [filename] and dump [filename]\n"));
		}
		if (!(strcmp(cmd, "ls"))) {
			char ext[4];
			struct stat aStat;
			GDir *dir;
			GError *error;
			G_CONST_RETURN gchar *dirname;
			dir = g_dir_open(currDir, 0, &error);
			if (dir == NULL) {
				DISPLAY_ERROR
				    ("Unable to open directory !");
			}
			printl(0, "%s\n", currDir);
			while ((dirname = g_dir_read_name(dir)) != NULL) {
				strcpy(ext, &dirname[strlen(dirname) - 3]);
				ext[2] = toupper(ext[2]);
				stat(dirname, &aStat);
				if (S_ISDIR(aStat.st_mode))
					printl(0, "  [%s]\n", dirname);

				else if (!strcmp(ext, "92P")
					 || !strcmp(ext, "92B"))
					printl(0, "  %-32s %d\n", dirname,
						(int) (aStat.st_size));
			} g_dir_close(dir);
		}
		if (!(strcmp(cmd, "cd"))) {
			if (arg1) {
				if (tilp_chdir(arg1))
					printl(0, _
						("\nIllegal directory!\n"));

				else
					printl(0, _
						("\nCurrent directory changed to:\n%s\n"),
						getcwd(currDir,
						       sizeof(currDir)));
			} else
				printl(0, _("\nCurrent directory is:\n%s\n"),
					currDir);
		}
		if (!(strcmp(cmd, "ready"))) {
			tilp_calc_isready();

			//printl(0, "%s\n", cb_calc_is_ready() ? "ok" : "nok");
		}
		if (!(strcmp(cmd, "screen"))) {
			tilp_screen_capture();
			if (arg1) {

				//tilp_screen_save(arg1);
			}
		}
		if (!strcmp(cmd, "dirlist")) {
			tilp_dirlist_remote();

			//tilp_dirlist_printl(0, );
		}
		if (!strcmp(cmd, "backup")) {
			tilp_calc_recv_backup();
			if (arg1) {
			}
		}
		if (!strcmp(cmd, "restore")) {
			if (arg1)
				tilp_calc_send_backup(arg1);
		}
		if (!strcmp(cmd, "send")) {

			/*
			   if(arg1)
			   tilp_calc_send_var(arg1);
			 */
		}
		if (!strcmp(cmd, "receive")) {

			//cb_recv_var();
			if (arg1) {
			}
		}
		if (!strcmp(cmd, "dump")) {
			tilp_calc_rom_dump();
			if (arg1) {
			}
		}
	}
	return 0;
}
static void prompt_commands(void)
{
	char *cmd, *arg1, *arg2;
	char line[80];
	getOut = 0;
	while (!getOut) {
		printl(0, _("\ncmd> "));
		fgets(line, 80, stdin);
		line[strlen(line) - 1] = '\0';	//strap LF
		cmd = strtok(line, " ");
		arg1 = strtok(NULL, " ");
		arg2 = strtok(NULL, " ");

		if (cmd)
			do_command(cmd, arg1);
	}
}
int tilp_prompt(void)
{
	if (!strlen(currDir))
		getcwd(currDir, sizeof(currDir));
	printl(0, _
		("Commandstate entered. Type \"quit\" or \"exit\" to quit.\n"));
	cmdState = 1;
	prompt_commands();
	return 0;
}
