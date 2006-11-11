/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  12/10/06 20:39 - group_file.c

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
#include <glib.h>

#include "dialog.h"
#include "drag_drop.h"
#include "file.h"
#include "group_file.h"
#include "group_tree.h"
#include "gui.h"
#include "labels.h"
#include "tilibs.h"

// Group File Structure
GFileStruct GFile;

/* Create Group File Routine */
int tigfile_create(gboolean globaltize)
{
  gchar *name, *locale_utf8, *utf8_file;
  gchar *filepath;
  int result, calc_model;
  gsize br, bw;
  TigContent *content;
  int ret;
  
  // Lets ask for a filename and Calculator Model
  name = msgbox_input("File Name", NULL, "Please enter a name for the new TI Group File.");
  if (name == NULL)
    return -1; // Error, no name entered/canceled
  result = msgbox_three("TI73 - TI86", "TI89 - TI92+, V200", "What calculator model(s) would you like the TI Group File to be for?");
  if (result == MSGBOX_NO)
    return -2; // Error, No Type chosen
  
  // Parse
  locale_utf8 = g_locale_to_utf8(name, -1, &br, &bw, NULL);
  utf8_file = g_filename_from_utf8(locale_utf8, -1, &br, &bw, NULL);
  g_free(locale_utf8);
  
  if (result == MSGBOX_BUTTON1)
    calc_model = CALC_TI73; // TI73 - TI86
  if (result == MSGBOX_BUTTON2)
    calc_model = CALC_TI89; // TI89 - V200
  
  // Generate File Path
  filepath = g_strconcat(settings.cur_dir, G_DIR_SEPARATOR_S, utf8_file, ".tig", NULL);
  
  // Does file exist?
  if (file_exists(filepath))
  {
    locale_utf8 = g_strconcat("The file '", filepath, "' already exists!", NULL);
    msgbox_error(locale_utf8);
    g_free(locale_utf8);
    g_free(utf8_file);
    return -3;
  }
  
  // Create the TI Group File
  ret = 0;
  content = tifiles_content_create_tigroup(calc_model, 0);
  if (tifiles_file_write_tigroup(filepath, content))
  {
    msgbox_error("Could not create TI Group File!");
    ret = -4;
  }
  tifiles_content_delete_tigroup(content);
  
  if (globaltize && !ret)
    DNDInfo.file_path = g_strdup(filepath);
  
  // Free stuff
  g_free(utf8_file);
  g_free(filepath);
  
  // Return
  return ret;
}

/* Open TI Group File */
int tigfile_open(const char *filename)
{
  int i, k;
  #define j GFile.num_entries

  // Clear Group Tree
  group_tree_clear();
  
  // Allocate TigContent Structure
  GFile.raw.TigFile = tifiles_content_create_tigroup(CALC_NONE, 1);
  
  // Load TI Group File into tig_data
  if (tifiles_file_read_tigroup(filename, GFile.raw.TigFile))
  {
    msgbox_error("Failed to Open TI Group File!");
    tifiles_content_delete_tigroup(GFile.raw.TigFile);
    return -1;
  }
  
  // Allocate GFM Compatible List
  GFile.list = g_malloc0(sizeof(tigfview) * GFile.raw.TigFile->num_entries);
  
  GFile.num_entries = 0; // Number of Files in List
  GFile.file_size = 0; // Size of files in list
  
  // Lets make the GFM compatible list
  for(i=0; i<GFile.raw.TigFile->num_entries; i++)
  {
    // Apps only
    if (GFile.raw.TigFile->entries[i]->type == TIFILE_FLASH)
    {
      GFile.list[j].name = ticonv_varname_to_utf8(GFile.raw.TigFile->entries[i]->content.flash->model,
                                                  GFile.raw.TigFile->entries[i]->content.flash->name); // Filename in UTF8
      GFile.list[j].type = GFile.raw.TigFile->entries[i]->type; // File Type, which would be APP
      
      // Get size, tricky with APPS
      GFile.list[j].size = 0;
      for(k=0; k<GFile.raw.TigFile->entries[i]->content.flash->num_pages; k++)
      {
        GFile.list[j].size += GFile.raw.TigFile->entries[i]->content.flash->pages[k]->size; // APP Size
      }
      GFile.file_size += GFile.list[j].size;
      
      GFile.list[j].loc_top = i;
      GFile.list[j].model = GFile.raw.TigFile->entries[i]->content.flash->model; // Calculator Model
      
      GFile.num_entries++; // Increment for GFM List
    }
    
    // Regular files
    if (GFile.raw.TigFile->entries[i]->type == TIFILE_REGULAR)
    {
      for(k=0; k<GFile.raw.TigFile->entries[i]->content.regular->num_entries; k++)
      {
        GFile.list[j].name = ticonv_varname_to_utf8(GFile.raw.TigFile->entries[i]->content.regular->model,
                                                    GFile.raw.TigFile->entries[i]->content.regular->entries[k]->name); // Filename in UTF8
        GFile.list[j].type = GFile.raw.TigFile->entries[i]->type; // File Type
        GFile.list[j].size = GFile.raw.TigFile->entries[i]->content.regular->entries[k]->size; // File Size
        GFile.list[j].loc_top = i;
        GFile.list[j].loc_bot = k;
        GFile.list[j].model = GFile.raw.TigFile->entries[i]->content.regular->model; // Calculator Model
        
        GFile.file_size += GFile.list[j].size;
        GFile.num_entries++;
      }
    }
  }
  
  // Set the settings structure data
  settings.cur_file = g_strdup(filename);
  settings.cur_filetype = TIFILE_TIGROUP;
  
  // Update the labels
  gtree_labels_refresh();
  
  // refresh group tree
  /// code group tree refresh
  
  // Return
  return 0;
}

/* Open Group File */
int gfile_open(const char *filename)
{
  int i;
  #define j GFile.num_entries
  
  // Clear Group Tree
  group_tree_clear();
  
  // Allocate FileContent Strucutre
  GFile.raw.GFile = tifiles_content_create_group(1);
  
  // Load Group FIle into GFile.GFile
  if (tifiles_file_read_regular(filename, GFile.raw.GFile))
  {
    msgbox_error("Failed to Open Group File!");
    tifiles_content_delete_group(GFile.raw.GFile);
    return -1;
  }
  
  // Allocate GFM Compatible List
  GFile.list = g_malloc0(sizeof(tigfview) * GFile.raw.GFile->num_entries);
  
  GFile.num_entries = 0; // Number of Files in List
  GFile.file_size = 0; // Size of files in list
  
  // Lets make the GFM compatible list
  for(i=0; i<GFile.raw.GFile->num_entries; i++)
  {
    GFile.list[j].name = ticonv_varname_to_utf8(GFile.raw.GFile->model, GFile.raw.GFile->entries[i]->name); // Filename in UTF-8
    GFile.list[j].type = TIFILE_REGULAR;
    GFile.list[j].size = GFile.raw.GFile->entries[i]->size;
    GFile.list[j].loc_top = i;
    GFile.list[j].model = GFile.raw.GFile->model;
    
    GFile.file_size += GFile.list[j].size;
    GFile.num_entries++;
  }
  
  // Set the settings structure data
  settings.cur_file = g_strdup(filename);
  settings.cur_filetype = TIFILE_GROUP;
  settings.cur_filemodel = GFile.raw.GFile->model;
  
  // Update the labels
  gtree_labels_refresh();
  
  // refresh group tree
  /// code group tree refresh
  
  // Return
  return 0;
  
}

/* Close the Group File */
int group_file_close(void)
{
  // Clear Group Tree
  group_tree_clear();
  
  // Reset the Group Tree Labels
  gtk_label_set_text(GTK_LABEL(gfm_widget.group_filesize), "File Size: 0 bytes");
  gtk_label_set_text(GTK_LABEL(gfm_widget.group_files), "Files: 0");
  
  // Free the Group File Data
  group_file_free();
  
  // More Stuff
  settings.cur_file = NULL;
  
  // Return
  return 0;
}

/* Free the Group File */
int group_file_free(void)
{
  // Free Structures, of a file is open.
  if (settings.cur_file)
  {
    if (settings.cur_filetype == TIFILE_TIGROUP)
      tifiles_content_delete_tigroup(GFile.raw.TigFile);
    if (settings.cur_filetype == TIFILE_GROUP)
      tifiles_content_delete_group(GFile.raw.GFile);
    
    g_free(GFile.list);
  }
  
  // Return
  return 0;
}
