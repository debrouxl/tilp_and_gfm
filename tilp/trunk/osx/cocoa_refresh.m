/*
 * TiLP Cocoa GUI for Mac OS X
 */


#include <stdio.h>

#include <glib/glib.h>
#include <libticalcs/calc_def.h>
#include <libticalcs/calc_int.h>

#include "../src/intl.h"
#include "../src/defs.h"
#include "../src/struct.h"
#include "../src/gui_indep.h"

#include "cocoa_sheets.h"
#include "cocoa_structs.h"

extern struct ticalc_info_update info_update;

extern struct cocoa_pbars_ptr *pbars_ptr;

#import "cocoa_refresh.h"

#import <Cocoa/Cocoa.h>

// FIXME OS X
// unsure whether the refresh works...

// FIXME OS X
// see if we need to call displayIfNeeded when updating a progressIndicator

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
    id pbar1;
    id pbar_rate;

    static gchar buffer[32];
    static gfloat rate;

    if(pbars_ptr->pbar1 != nil) 
        {
            pbar1 = pbars_ptr->pbar1;
            pbar_rate = pbars_ptr->pbar_rate;

            // refresh only if necessary
            if((info_update.percentage - info_update.prev_percentage) < 0.5)
                {
                    if((info_update.percentage - info_update.prev_percentage) < 0)
                        info_update.prev_percentage = info_update.percentage;
                    else
                        return;
                }
            else
                info_update.prev_percentage = info_update.percentage;

            rate = info_update.count / ((float)(clock() - info_update.start_time)/CLOCKS_PER_SEC);
            g_snprintf(buffer, 32, "Rate: %1.1f Kbytes/s", rate / 1000);
     
            // set pbar value and textField text
            [pbar1 setDoubleValue:(double)info_update.percentage];
            [pbar_rate setStringValue:[NSString stringWithCString:buffer]];
      
            //while(!pbars_ptr->finished) { /* do nothing */ }
        }
}

static void
refresh_pbar2(void)
{
    id pbar2;

    if(pbars_ptr->pbar2 != nil)
        {
            // refresh only if necessary
            if((info_update.main_percentage - info_update.prev_main_percentage) < 0.5)
                return;
            else
                info_update.prev_main_percentage = info_update.main_percentage;
      
            [pbar2 setDoubleValue:(double)info_update.main_percentage];
      
            //while(!pbars_ptr->finished) { /* do nothing */ }
        }
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
    id pbar_text;

    if (pbars_ptr->pbar_text == nil)
        return;

    pbar_text = pbars_ptr->pbar_text;
  
    [pbar_text setStringValue:[NSString stringWithCString:info_update.label_text]];
  
    //while(!pbars_ptr->finished) { /* do nothing */ }
}

void
gt_refresh(void)
{
    //while(!pbars_ptr->finished) { /* do nothing */ }
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







