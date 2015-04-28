/* Hey EMACS -*- linux-c -*- */
/* $Id: print.h 522 2004-04-08 10:12:55Z roms $ */

/*  libtifiles - Ti File Format library, a part of the TiLP project
 *  Copyright (C) 1999-2006  Romain Lievin
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*
	Domain name logging.
*/

#ifndef __TILP_LOG_H__
#define __TILP_LOG_H__

#include <glib.h>

#define LOG_DOMAIN	"tilp"

void tilp_debug(const gchar *format, ...);
void tilp_info(const gchar *format, ...);
void tilp_message(const gchar *format, ...);
void tilp_warning(const gchar *format, ...);
void tilp_critical(const gchar *format, ...);
void tilp_error(const gchar *format, ...);

#define TRYC(x) { int aaa_; if((aaa_ = (x))) return aaa_; }

#endif
