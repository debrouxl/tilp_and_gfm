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

#ifndef CB_CALC_H
#define CB_CALC_H

int cb_calc_is_ready(void);
int cb_send_backup(char *filename);
int cb_receive_backup(void);
int cb_id_list(void);
int cb_rom_dump(void);
int cb_rom_version(void);
int cb_send_var(void);
int cb_receive_var(int *to_save);
int cb_dirlist(void);
int cb_send_flash_app(char *filename);
int cb_send_flash_os(char *filename);
int cb_receive_app(void);

extern struct screenshot ti_screen;

int cb_screen_capture(void);
int cb_screen_save(char *filename);
int cb_ams_to_rom(char *filename);

#endif




