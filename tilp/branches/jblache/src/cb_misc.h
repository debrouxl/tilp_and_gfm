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

#ifndef CB_MISC_H
#define CB_MISC_H

#ifndef __MACOSX__
int cb_save_config_file(void);

int cb_load_config_file(void);

int cb_change_drive(char drive_letter);
#endif

int cb_default_config(void);

int cb_probe_calc(void);

int cb_probe_cable(void);

int cb_probe_port(void);

int cb_registry_register(void);

int cb_registry_unregister(void);

int cb_send_cmdline(void);

#endif




