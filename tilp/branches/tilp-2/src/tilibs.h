/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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

/*
  This file includes libtifiles, libticables & libticalcs headers and some
  other needed headers.
*/

#ifndef TILIBS_H
#define TILIBS_H

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#if !defined(__MACOSX__) && !defined(__WIN32__)
# include <tilp2/ticables.h>
#elif defined(__MACOSX__)
# include <libticables/ticables.h>
#else
# include "ticables.h"
#endif

#if !defined(__MACOSX__) && !defined(__WIN32__)
# include <tilp2/tifiles.h>
# include <tilp2/macros.h>
#elif defined(__MACOSX__)
# include <libtifiles2/tifiles.h>
# include <libtifiles2/macros.h>
#else
# include "tifiles.h"
# include "macros.h"
#endif

#if !defined(__MACOSX__) && !defined(__WIN32__)
# include <tilp2/ticalcs.h>
#elif defined(__MACOSX__)
# include <libticalcs2/ticalcs.h>
#else
# include "ticalcs.h"
#endif

#endif
