/*  tilp - link program for TI calculators
 *  Copyright (C) 1999-2001  Romain Lievin
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

#ifndef PAKFILE_H
#define PAKFILE_H

/* Specific PAK file functions*/
int is_pak_file(char *filename);
int number_of_files(char *filename);

/* General functions */
char *varname_in_file(FILE *f, char *varname);
int is_varname_in_ctree(char *varname);
void rename_variable(FILE *old, char *new_filename, char *varname);
int get_file_informations(char *filename, struct file_char *sfc);

#endif





