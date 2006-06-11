/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_core.h 1125 2005-05-24 18:09:19Z julien $ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __TILP_CALCS__
#define __TILP_CALCS__

int tilp_calc_isready(void);
int tilp_calc_dirlist(void);

int tilp_calc_send_var(void);
int tilp_calc_recv_var(void);

int tilp_calc_send_backup(const char* filename);
int tilp_calc_recv_backup(void);

int tilp_calc_send_app(void);
int tilp_calc_recv_app(void);

int tilp_calc_send_os(char *filename);
int tilp_calc_idlist(int);

int tilp_calc_rom_dump(void);

int tilp_calc_del_var(void);
int tilp_calc_new_fld(void);

int tilp_calc_get_infos(CalcInfos*);

int tilp_calc_send_cert(char *filename);
int tilp_calc_recv_cert(void);

#endif
