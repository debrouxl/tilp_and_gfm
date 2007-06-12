/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  29/05/06 17:51 - file.c

  This program is free software you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib/gstdio.h>
#include <gtk/gtk.h>
#include "tilibs.h"

#include "dialog.h"
#include "file.h"
#include "paths.h"

/* File Exist Function */
int file_exists(const char *filename)
{
    FILE *fpointer;

    // Does it exist?
    if ((fpointer = fopen(filename, "r")) == NULL)
        return 0;
    else
        fclose(fpointer);

    return 1;
}

/* Check to see if we have all of our Glade Files */
void glade_files_check(void)
{
    const char *glade_files[] = {
        "dialogs.glade",
        "gfm.glade",
    };
    short i, num_files;
    gchar *msg;
    num_files = sizeof(glade_files) / sizeof(char *);

    // Loop em all up!
    for (i=0; i<num_files; i++)
    {
        if (!file_exists((const char *)gfm_paths_build_glade(glade_files[i])))
        {
            msg = g_strconcat("Could not find: <b>",
                              glade_files[i],
                              "</b> GUI File in '",
                              inst_paths.glade_dir,
                              "' directory!", NULL);
            msgbox_error(msg);
            g_free(msg);
            exit(-1); // Exit
        }
    }

    // Return
    return;
}
