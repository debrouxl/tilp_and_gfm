/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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

/*
  This header contains the exported functions & definitions of the TiLP core.
  They can be used for developing a TiLP with a different GUI.
  You should use these functions with the name beginning by tilp_...
  You do not have to use any other function, please !

  Format: [tilp]_[group]_[name]
*/

#ifndef __TILP_CORE__
#define __TILP_CORE__

#ifdef __cplusplus
extern "C" {
#endif

  // GTK+ only (export callbacks for Glade linking at runtime)
#ifdef __WIN32__
# define GLADE_CB __declspec(dllexport)
#else
# define GLADE_CB
#endif

#include "tilibs.h"
#include "intl.h"

#include "tilp_calcs.h"
#include "tilp_cmdline.h"
#include "tilp_config.h"
#include "tilp_defs.h"
#include "tilp_files.h"
#include "tilp_indep.h"
#include "tilp_log.h"
#include "tilp_main.h"
#include "tilp_misc.h"
#include "tilp_struct.h"
#include "tilp_paths.h"
#include "tilp_screen.h"
#include "tilp_slct.h"
#include "tilp_struct.h"
#include "tilp_vars.h"
#include "tilp_version.h"

int tilp_error(int errcode);

#ifdef __cplusplus
}
#endif
#endif
