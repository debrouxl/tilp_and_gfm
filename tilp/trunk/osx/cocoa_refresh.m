/*
 * TiLP Cocoa GUI for Mac OS X
 */

#include <libticalcs/calc_int.h>

#include "../src/struct.h"
#include "../src/defs.h"
#include "../src/gui_indep.h"
#include "../src/intl.h"

#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;

extern struct ticalc_info_update info_update;

#import "cocoa_refresh.h"
#import "SheetsController.h"

#import <Cocoa/Cocoa.h>

// FIXME OS X
// find a mean to allow cocoa to process its events between pbar refresh...

void
gt_start(void)
{
    info_update.prev_percentage = info_update.percentage = 0.0;
    info_update.start_time = clock();
}

void
gt_stop(void)
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
gt_pbar(void)
{
    refresh_pbar1();
    refresh_pbar2();
}

void
gt_label(void)
{
    id mySheetsController;
    
    mySheetsController = objects_ptr->mySheetsController;
    
    [mySheetsController refreshLabel];
}

void
gt_refresh(void)
{
    // FIXME OS X
    // HERE WE JUST NEED TO PASS THE BALL TO COCOA TO PERFORM EVENTS !
}

int
gt_choose(char *cur_varname, char *new_varname)
{
    int ret=0;
    int action = ACTION_NONE;
    gchar *s;
    
    strcpy(new_varname, "");
    ret = gif->user3_box(_("Action"), 
                         _("The variable already exists..."), 
                         _("Skip"), _("Overwrite"), _("Rename"));
    switch(ret)
        {
            case BUTTON1:
                action = ACTION_SKIP;
                break;
            case BUTTON2:
                action = ACTION_OVERWRITE;
                break;
            case BUTTON3:
                action = ACTION_RENAME;
                s = gif->dlgbox_entry(_("Rename the variable"),
                                      _("New name: "), cur_varname);
                if((s == NULL) || (strlen(s)>17)) { action=ACTION_SKIP; break; }
                strcpy(new_varname, s);
                g_free(s);
                break;
            default:
                break;
        }

    return action;
}

void
gt_init_refresh_functions(void)
{
    ticalc_set_update(&info_update, 
                      gt_start,
		      gt_stop,
		      gt_refresh,
		      gif->msg_box, 
		      gt_pbar, 
		      gt_label, 
		      gt_choose);

    fprintf(stdout, _("Initialized in Cocoa mode.\n"));
}







