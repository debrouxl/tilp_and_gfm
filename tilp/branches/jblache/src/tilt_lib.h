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

#ifndef TILT_LIB_H
#define TILT_LIB_H

/*
  Below is the list of exported functions. You must use these functions with the
  name beginnig by tilp_...
  You do not have to use any other function please !
*/

#define tilp_set_gui_fncts		set_gui_fncts;
#define tilp_main_init			main_init;

#define tilp_error error;

#define tilp_calc_is_ready		cb_calc_is_ready;
#define tilp_send_backup		cb_send_backup;
#define tilp_receive_backup		cb_receive_backup;
#define tilp_id_list			cb_id_list;
#define tilp_rom_dump			cb_rom_dump;
#define tilp_rom_version		cb_rom_version;
#define tilp_send_var			cb_send_var;
#define tilp_receive_var		cb_receive_var;
#define tilp_dirlist			cb_dirlist;
#define tilp_send_flash_app		cb_send_flash_app;
#define tilp_send_flash_os		cb_send_flash_os;
#define tilp_screen_capture		cb_screen_capture;
#define tilp_screen_save		cb_screen_save;

#define tilp_save_config_file	cb_save_config_file;
#define tilp_load_config_file	cb_load_config_file;
#define tilp_probe_calc			cb_probe_calc;
#define tilp_probe_port			cb_probe_port;
#define tilp_change_drive		cb_change_drive;

#define tilp_check_access		check_access;
#define tilp_read_rc_file		read_rc_file;
#define tilp_write_rc_file		write_rc_file;
#define tilp_is_rcfile_exist	is_rcfile_exist;

#define tilp_clist_selection_destroy clist_selection_destroy;
#define tilp_ctree_selection_destroy clist_selection_destroy;

#endif


