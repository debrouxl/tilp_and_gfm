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

#ifndef CB_CALC_H
#define CB_CALC_H

#include "dep.h"

DLLEXPORT
int cb_calc_is_ready(void);
DLLEXPORT
int cb_send_backup(char *filename);
DLLEXPORT
int cb_receive_backup(void);
DLLEXPORT
int cb_id_list(void);
DLLEXPORT
int cb_rom_dump(void);
DLLEXPORT
int cb_rom_version(void);
DLLEXPORT
int cb_send_var(void);
DLLEXPORT
int cb_receive_var(int *to_save);
DLLEXPORT
int cb_dirlist(void);
DLLEXPORT
int cb_send_flash_app(char *filename);
DLLEXPORT
int cb_send_flash_os(char *filename);

extern struct screenshot ti_screen;

DLLEXPORT
int cb_screen_capture(void);
DLLEXPORT
int cb_screen_save(char *filename);
DLLEXPORT
int cb_ams_to_rom(char *filename);

#endif




