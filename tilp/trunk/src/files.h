/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2002  Romain Lievin
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

#ifndef LFILES_H
#define LFILES_H

#include "struct.h"

#ifdef __cplusplus
extern "C" {
#endif

void process_buffer(gchar *buf);
void process_unix2dos(gchar *buf);
int copy_file(char *src, char *dst);
int move_file(char *src, char *dst);

int   get_home_path(char **path);
char* get_attributes(struct file_info f_info);
void  get_user_name(struct file_info f_info, char **name);
void  get_group_name(struct file_info f_info, char **name);
void  get_date(struct file_info f_info, char **s);

void varlist_to_glist(struct varinfo varlist);
struct varinfo *glist_to_varlist(GList *glist);
void generate_group_file_header(FILE *file, int mask_mode, 
				const char *id, struct varinfo *v, 
				int calc_type);

void l_directory_list();
#define local_directory_list l_directory_list

void sort_lfiles_by_name(GList *list);
void sort_lfiles_by_date(GList *list);
void sort_lfiles_by_size(GList *list);
void sort_lfiles_by_user(GList *list);
void sort_lfiles_by_group(GList *list);
void sort_lfiles_by_attrib(GList *list);

int c_directory_list(void);
#define remote_directory_list c_directory_list

void sort_cfiles_by_name(GList *list);
void sort_cfiles_by_info(GList *list);
void sort_cfiles_by_type(GList *list);
void sort_cfiles_by_size(GList *list);

char *file_extension(char *filename);

#ifdef __cplusplus
}
#endif

#endif





