/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2003 Julien BLACHE <jb@tilp.info>
 *
 *  $Id$
 *
 *  Cocoa GUI for Mac OS X
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

#include <libticalcs/calc_int.h>
#include <libticables/cabl_int.h>
#include <libticables/cabl_def.h>

#include "../src/tilp_struct.h"
#include "../src/tilp_defs.h"
#include "../src/tilp_indep.h"
#include "../src/intl.h"

#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;

#import "cocoa_refresh.h"
#import "SheetsController.h"

#import <Cocoa/Cocoa.h>

TicableDataRate *dr;

void
cocoa_refresh_start(void)
{
    info_update.prev_percentage = info_update.percentage = 0.0;
    ticable_get_datarate(&dr);
}

void
cocoa_refresh_stop(void)
{
    info_update.prev_percentage = info_update.percentage = 0.0;
}

static void
refresh_pbar1(void)
{
    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    [mySheetsController refreshPbar1];
}

static void
refresh_pbar2(void)
{
    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;

    [mySheetsController refreshPbar2];
}

void
cocoa_refresh_pbar(void)
{
    refresh_pbar1();
    refresh_pbar2();
}

void
cocoa_refresh_label(void)
{
    id mySheetsController;
      
    mySheetsController = objects_ptr->mySheetsController;
    
    [mySheetsController refreshLabel];
}

void
cocoa_refresh_gui(void)
{
  // Nothing to do
}

void
cocoa_init_refresh_functions(void)
{
    ticalc_set_update(&info_update, 
                      cocoa_refresh_start,
		      cocoa_refresh_stop,
		      cocoa_refresh_gui,
		      cocoa_refresh_pbar,
                      cocoa_refresh_label);

    fprintf(stdout, _("Initialized in Cocoa mode.\n"));
}







