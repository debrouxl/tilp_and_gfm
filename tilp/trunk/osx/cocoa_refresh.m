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
// find a mean to allow cocoa to process its events between pbar refresh...

void
gt_start(void)
{
    //fprintf(stderr, "DEBUG: GT_START() BEGINS\n");

    info_update.prev_percentage = info_update.percentage = 0.0;
    info_update.start_time = clock();

    //fprintf(stderr, "DEBUG: GT_START() ENDS\n");
}

void
gt_stop(void)
{
    //fprintf(stderr, "DEBUG: GT_STOP() BEGINS\n");

    info_update.prev_percentage = info_update.percentage = 0.0;
    
    //fprintf(stderr, "DEBUG: GT_STOP() ENDS\n");
}

static void
refresh_pbar1(void)
{
    NSRunLoop *myRunLoop;
    NSDate *limit;

    id pbar1;
    id pbar_rate;
    
    static gfloat rate;

    //fprintf(stderr, "DEBUG: REFRESH_PBAR1() BEGINS\n");

    if(pbars_ptr->pbar1 != nil) 
        {
            pbar1 = pbars_ptr->pbar1;
            pbar_rate = pbars_ptr->pbar_rate;

            // refresh only if necessary
            if((info_update.percentage - info_update.prev_percentage) < 0.01) // was 0.05 originally
                {
                    //fprintf(stderr, "DEBUG: refresh_pbar1 : delta < 0.05 : percentage = %2.2f, prev_percentage = %2.2f\n", info_update.percentage, info_update.prev_percentage);
                    
                    if((info_update.percentage - info_update.prev_percentage) < 0)
                        info_update.prev_percentage = info_update.percentage;
                    else
                        return;
                }
            else
                info_update.prev_percentage = info_update.percentage;

            //fprintf(stderr, "DEBUG: refresh_pbar1 : generating label\n");

            rate = info_update.count / ((float)(clock() - info_update.start_time)/CLOCKS_PER_SEC);
     
            // set pbar value and textField text
            
            //fprintf(stderr, "DEBUG: refresh_pbar1 : setting progress indicator value\n");
            
            [pbar1 setDoubleValue:(double)(info_update.percentage * 100)];
            [pbar_rate setStringValue:[NSString stringWithFormat:@"Rate : %3.2f KBytes/s", (rate / 1000)]];
            
            //fprintf(stderr, "DEBUG: refresh_pbar1 : calling displayIfNeeded\n");
            
            [pbar1 displayIfNeeded];
            [pbar_rate displayIfNeeded];
  
            // FIXME OS X
            // HERE WE NEED TO PASS THE BALL TO COCOA AGAIN TO PROCESS ITS EVENTS !!!
#if 0 /* Grmbl, can't get that to work, fsck ! */            
            fprintf(stderr, "DEBUG: running RunLoop\n");
            
            myRunLoop = [NSRunLoop currentRunLoop];
            
            limit = [[NSDate date] addTimeInterval:10];
            
            [myRunLoop runUntilDate:limit]; // must test this
            
            //[myRunLoop acceptInputForMode:NSDefaultRunLoopMode
            //           beforeDate:limit];
            
            fprintf(stderr, "DEBUG: RunLoop run\n");
#endif /* 0 */
        }
    //fprintf(stderr, "DEBUG: REFRESH_PBAR1 ENDS%s\n", (pbar1 == NULL) ? "(PBAR1 IS NULL)" : "");
}

static void
refresh_pbar2(void)
{
    id pbar2;

    //fprintf(stderr, "DEBUG: REFRESH_PBAR2() BEGINS\n");

    if(pbars_ptr->pbar2 != nil)
        {
            // refresh only if necessary, not too often (works well with 0.01, too, but consumes CPU I guess)
            if((info_update.main_percentage - info_update.prev_main_percentage) < 0.05)
                return;
            else
                info_update.prev_main_percentage = info_update.main_percentage;
      
            pbar2 = pbars_ptr->pbar2;
      
            [pbar2 setDoubleValue:(double)(info_update.main_percentage * 100)];
            [pbar2 displayIfNeeded];
      
            // FIXME OS X
            // HERE WE NEED TO PASS THE BALL TO COCOA, TOO.
        }
    //fprintf(stderr, "DEBUG: REFRESH_PBAR2() ENDS\n");
}

void
gt_pbar(void)
{
    //fprintf(stderr, "DEBUG: GT_PBAR() BEGINS\n");

    refresh_pbar1();
    refresh_pbar2();
    
    //fprintf(stderr, "DEBUG: GT_PBAR() ENDS\n");
}

void
gt_label(void)
{
    id pbar_text;

    //fprintf(stderr, "DEBUG: GT_LABEL() BEGINS\n");
    
    if (pbars_ptr->pbar_text == nil)
        return;

    pbar_text = pbars_ptr->pbar_text;
  
    [pbar_text setStringValue:[NSString stringWithCString:info_update.label_text]];
    [pbar_text displayIfNeeded];
  
    // FIXME OS X
    // HERE WE NEED TO PASS THE BALL TO COCOA, TOO.
          
    //fprintf(stderr, "DEBUG: GT_LABEL() ENDS\n");
}

void
gt_refresh(void)
{
    //fprintf(stderr, "DEBUG: GT_REFRESH()\n");

    // FIXME OS X
    // HERE WE JUST NEED TO PASS THE BALL TO COCOA TO PERFORM EVENTS !
}

int
gt_choose(char *cur_varname, char *new_varname)
{
    int ret=0;
    int action = ACTION_NONE;
    gchar *s;
  
    //fprintf(stderr, "DEBUG: GT_CHOOSE() BEGINS\n");
  
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
    
    //fprintf(stderr, "DEBUG: GT_CHOOSE() ENDS\n");
    
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







