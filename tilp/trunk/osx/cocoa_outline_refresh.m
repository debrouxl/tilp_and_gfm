/*
 * TiLP Cocoa GUI for Mac OS X
 */
 
#include <glib/glib.h>
 
#include "../src/defs.h"
#include "../src/struct.h"
#include "../src/files.h"
#include "../src/info.h"
 
#include "cocoa_structs.h"
 
#import "cocoa_outline_refresh.h"

#import <Cocoa/Cocoa.h>
#import "SimpleTreeNode.h"
#import "TilpController.h"

extern struct cocoa_objects_ptr *objects_ptr;

void
refresh_outline(void)
{
    int folderPos = 0; // position in tiVarsArray
    int varPos = 0; // position in the array representing the folder

    struct varinfo *q;

    NSMutableDictionary *content;
    NSMutableDictionary *tmpDict;
    NSMutableArray *mainEntries;
    NSMutableArray *tiVarsArray;
    NSMutableArray *tmpArray;
    SimpleTreeNode *dirlistData;
    id dirlistTree;

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
    
    [tmpDict setObject:@"Screen" forKey:@"Varname"];
    [tmpDict setObject:[NSImage imageNamed:@"screen_mini.tiff"] forKey:@"Image"];
    
    tmpDict = [[NSMutableDictionary alloc] init];
    
    [mainEntries insertObject:tmpDict atIndex:1];
    
    [tmpDict setObject:@"Memory" forKey:@"Varname"];
    [tmpDict setObject:[NSImage imageNamed:@"archived.tiff"] forKey:@"Image"];
   
    tmpDict = [[NSMutableDictionary alloc] init];
    
    [mainEntries insertObject:tmpDict atIndex:2];
    
    [tmpDict setObject:@"Keyboard" forKey:@"Varname"];
    [tmpDict setObject:[NSImage imageNamed:@"keyboard_mini.tiff"] forKey:@"Image"];
    
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
                    fprintf(stderr, "DEBUG: Got a folder\n");
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
                    fprintf(stderr, "DEBUG: End of folder\n");
                }
            else
                {
                    fprintf(stderr, "DEBUG: Got a var\n");
                    // dictionary that will hold this var
                    tmpDict = [[NSMutableDictionary alloc] init];
                
                    switch (q->varlocked)  // Uh, you'd better #define'd this type of things, Romain
                        {
                            case 1:
                                [tmpDict setObject:[NSImage imageNamed:@"locked.tiff"] forKey:@"Attribute"];
                                break;
                            case 3:
                                [tmpDict setObject:[NSImage imageNamed:@"archived.tiff"] forKey:@"Attribute"];
                                break;
                        }
                    
                    [tmpDict setObject:[NSImage imageNamed:@"doc.tiff"] forKey:@"Image"];
                    [tmpDict setObject:[NSString stringWithCString:q->translate] forKey:@"Varname"];
                    [tmpDict setObject:[NSString stringWithCString:ti_calc.byte2type(q->vartype)] forKey:@"Vartype"];
                    
                    fprintf(stderr, "DEBUG: varsize ld : %ld u : %u i : %i\n", q->varsize, q->varsize, q->varsize);
                    
                    [tmpDict setObject:[NSString stringWithFormat:@"%u", q->varsize] forKey:@"Varsize"];
        
                    [tmpArray insertObject:tmpDict atIndex:varPos];
                    varPos++;
                    fprintf(stderr, "DEBUG: End of var\n");
                }
               
            // next one
            p = p->next;
        }
    
    fprintf(stderr, "DEBUG: Dirlist parsing finished\n");
    
    // get a tree from our big fscking dictionary...
    
    if (objects_ptr->dirlistData != nil)
        {
            fprintf(stderr, "DEBUG: releasing older dirlistData\n");
        
            dirlistData = objects_ptr->dirlistData;
            objects_ptr->dirlistData = nil;
            [dirlistData release];
            dirlistData = nil;
        }
    
    dirlistData = [[SimpleTreeNode treeFromDictionary:content] retain];
    objects_ptr->dirlistData = dirlistData;
    
    fprintf(stderr, "DEBUG: got a treeNode\n");
    
    // release the big fscking dictionary. Feel better, eh ? :)
    
    fprintf(stderr, "DEBUG: Releasing content\n");
    
    [content release];
    content = nil;
    
    // ... then *HUMPFFF* pass the BAAAAAAALLLLLLLLLLLLLLLLLLLLLLL !!!
    
    fprintf(stderr, "DEBUG: Reloading OutlineView\n");
    
    dirlistTree = objects_ptr->dirlistTree;
    [dirlistTree reloadData];
        
    // ball passed. blargh.
    fprintf(stderr, "DEBUG: refresh_outline() ended\n");
}

void
refresh_infos(void)
{
    NSString *strCurrentFolder;
    NSString *strNumberOfFolders;
    NSString *strNumberOfVars;
    NSString *strMemoryUsed;
    
    id currentFolder;
    id numberOfFolders;
    id numberOfVars;
    id memoryUsed;
    
    int vars = 0;
    int folders = 0;
    int mem = 0;

    fprintf(stderr, "DEBUG: IN REFRESH_INFOS()\n");

    number_of_folders_vars_and_mem(&folders, &vars, &mem);
    
    fprintf(stderr, "DEBUG: Got number of folders and vars\n");
    
    strNumberOfVars = [NSString stringWithFormat:@"%u", vars];
    
    fprintf(stderr, "DEBUG: Set number of vars string\n");
    
    strNumberOfFolders = [NSString stringWithFormat:@"%u", folders];
    
    fprintf(stderr, "DEBUG: Set number of folders string\n");
    
    strMemoryUsed = [NSString stringWithFormat:@"%u", mem];
    
    fprintf(stderr, "DEBUG: Set memory used string\n");
    
    strCurrentFolder = [NSString stringWithCString:ctree_win.cur_folder];

    fprintf(stderr, "DEBUG: Set current folder string\n");

    currentFolder = objects_ptr->currentFolder;
    numberOfFolders = objects_ptr->numberOfFolders;
    numberOfVars = objects_ptr->numberOfVars;
    memoryUsed = objects_ptr->memoryUsed;
    
    [currentFolder setStringValue:strCurrentFolder];
    
    fprintf(stderr, "DEBUG: Set current folder\n");
    
    [numberOfFolders setStringValue:strNumberOfFolders];
    
    fprintf(stderr, "DEBUG: Set number of folders\n");
    
    [numberOfVars setStringValue:strNumberOfVars];
    
    fprintf(stderr, "DEBUG: Set number of vars\n");
    
    [memoryUsed setStringValue:strMemoryUsed];
    
    fprintf(stderr, "DEBUG: Set memory used\n");
    
#if 0 // releasing or autoreleasing leads to a EXC_BAD_ACCESS signal to be raised   
    [strCurrentFolder autorelease];
    
    fprintf(stderr, "DEBUG: Autoreleased current folder\n");
    
    [strNumberOfFolders autorelease];
    
    fprintf(stderr, "DEBUG: Autoreleased number of folders\n");
    
    [strNumberOfVars autorelease];
    
    fprintf(stderr, "DEBUG: Autoreleased number of vars\n");
    
    [strMemoryUsed autorelease];
#endif    
    fprintf(stderr, "DEBUG: REFRESH_INFOS() ENDED\n");
}