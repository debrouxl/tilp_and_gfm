/*
 * TiLP Cocoa GUI for Mac OS X
 */
 
#include <glib/glib.h>
 
#include "../src/defs.h"
#include "../src/struct.h"
#include "../src/files.h"
 
#include "cocoa_structs.h"
 
#import "cocoa_outline_refresh.h"

#import <Cocoa/Cocoa.h>
#import "SimpleTreeNode.h"

extern struct cocoa_objects_ptr *objects_ptr;

void
refresh_outline(void)
{
    // FIXME OS X
    // 1/ archived.tiff is for test only (ie replace with appropriate images)
    // 2/ check how pixmaps are set in a gtk_ctree, I'm unsure. I believe we
    // have 2 different pixmaps in this ctree in the GTK GUI
    // 3/ should release dirlistData if it already exists
    // 4/ ahem... bug :-/

    int folderPos = 0; // position in tiVarsArray
    int varPos = 0; // position in the array representing the folder

    struct varinfo *q;

    NSMutableDictionary *content;
    NSMutableDictionary *tmpDict;
    NSMutableArray *mainEntries;
    NSMutableArray *tiVarsArray;
    NSMutableArray *tmpArray;
    SimpleTreeNode *dirlistData;
    id TilpController;

    GList *p;
    
    switch(options.ctree_sort)
        {
            case SORT_BY_NAME:
                //sort_cfiles_by_name(ctree_win.varlist);
                break;
            case SORT_BY_INFO:
                sort_cfiles_by_info(ctree_win.varlist);
                break;
            case SORT_BY_TYPE:
                sort_cfiles_by_type(ctree_win.varlist);
                break;
            case SORT_BY_SIZE:
                sort_cfiles_by_size(ctree_win.varlist);
                break;
        }

    // init our big fscking dictionary of the d34th
    
    content = [[NSMutableDictionary alloc] init];
    
    [content setObject:@"OVRoot" forKey:@"Group"];
    
    mainEntries = [[NSMutableArray alloc] init];
    
    [content setObject:mainEntries forKey:@"Entries"];
    
    // general items => screen, memory, keyboard
    
    tmpDict = [[NSMutableDictionary alloc] init];
    
    [mainEntries insertObject:tmpDict atIndex:0];
    
    [tmpDict setObject:@"Screen" forKey:@"Label"];
    [tmpDict setObject:[NSImage imageNamed:@"archived.tiff"] forKey:@"Image"];
    
    tmpDict = [[NSMutableDictionary alloc] init];
    
    [mainEntries insertObject:tmpDict atIndex:1];
    
    [tmpDict setObject:@"Memory" forKey:@"Label"];
    [tmpDict setObject:[NSImage imageNamed:@"archived.tiff"] forKey:@"Image"];
    
    tmpDict = [[NSMutableDictionary alloc] init];
    
    [mainEntries insertObject:tmpDict atIndex:2];
    
    [tmpDict setObject:@"Keyboard" forKey:@"Label"];
    [tmpDict setObject:[NSImage imageNamed:@"archived.tiff"] forKey:@"Image"];
    
    // now the real fun is about to begin
    
    tiVarsArray = [[NSMutableArray alloc] init];
    
    tmpDict = [[NSMutableDictionary alloc] init];
    
    [mainEntries insertObject:tmpDict atIndex:3];
    
    [tmpDict setObject:@"TI Variables" forKey:@"Group"];
    [tmpDict setObject:tiVarsArray forKey:@"Entries"];
    
    // ok, we must now populate our big fscking dictionary with the
    // list of variables
    
    p = ctree_win.varlist;

    while (p != NULL)
        {
            q = (struct varinfo *)(p->data);
            
            if((options.lp.calc_type != CALC_TI83P) && ((q->vartype) ==  ti_calc.tixx_flash(options.lp.calc_type)))
                {
                    p = p->next;
                    continue;
                }
            
            if (q->is_folder)
                {
                    // dictionary that will hold the stuff
                    tmpDict = [[NSMutableDictionary alloc] init];
                    
                    [tiVarsArray insertObject:tmpDict atIndex:folderPos];
                    folderPos++;
                    
                    // array that will hold all the vars for this folder
                    tmpArray = [[NSMutableArray alloc] init];
                    
                    [tmpDict setObject:tmpArray forKey:@"Entries"];
                    [tmpDict setObject:[NSString stringWithCString:q->translate] forKey:@"Group"];
                    
                    // we're in a new folder, so...
                    varPos = 0;
                }
            else
                {
                    // dictionary that will hold this var
                    tmpDict = [[NSMutableDictionary alloc] init];
                
                    switch (q->varlocked)  // Uh, you'd better #define'd this type of things, Romain
                        {
                            case 1:
                                [tmpDict setObject:[NSImage imageNamed:@"locked.tiff"] forKey:@"Image"];
                                break;
                            case 3:
                                [tmpDict setObject:[NSImage imageNamed:@"archived.tiff"] forKey:@"Image"];
                                break;
                        }
                    
                    [tmpDict setObject:[NSString stringWithCString:q->translate] forKey:@"Label"];
                    [tmpDict setObject:[NSString stringWithCString:ti_calc.byte2type(q->vartype)] forKey:@"Vartype"];
                    [tmpDict setObject:[NSString stringWithFormat:@"%u", q->varsize] forKey:@"Varsize"];
        
                    [tmpArray insertObject:tmpDict atIndex:varPos];
                    varPos++;
                }
               
            // next one
            p = p->next;
        }
    
    // get a tree from our big fscking dictionary...
    
    dirlistData = [[SimpleTreeNode treeFromDictionary:content] retain];
    objects_ptr->dirlistData = dirlistData;
    
    // ... then *HUMPFFF* pass the BAAAAAAALLLLLLLLLLLLLLLLLLLLLLL !!!
    
    //dirlistTree = objects_ptr->dirlistTree;
    //[dirlistTree reloadData];
    
    TilpController = objects_ptr->TilpController;
    [TilpController initiateOutlineReload];
    
    // ball passed. blargh. Now modifying SimpleTree :P
}