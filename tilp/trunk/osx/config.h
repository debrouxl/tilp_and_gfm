/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2003 Julien BLACHE <jb@tilp.info>
 *
 *  $Id$
 *
 *  Cocoa GUI for Mac OS X
 *  Config header
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
 
#ifndef __CONFIG_H__
#define __CONFIG_H__

#define HAVE_UNISTD_H
#define HAVE_DIRENT_H

#define HAVE_TILP_TICABLES_H
#define HAVE_TILP_TIFILES_H

#define DIR_SEPARATOR "/"

#define ALLOW_EXIT_HOMEDIR

#define TILP_OSX_VERSION "0.6.3"

// the line below must be modified at each revision !
#define SVN_REV "$Rev$"

#define VERSION "6.62"

#endif /* !__CONFIG_H__ */
