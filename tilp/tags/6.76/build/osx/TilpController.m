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

/*
 * The code for the toolbar is derived from Apple Sample Code (ToolbarSample)
 * Apple is not liable for anything regarding this code, according to
 * the Apple Sample Code License.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <libticalcs/calc_int.h>

#include "../src/tilp_core.h"
#include "../src/tilp_struct.h"
#include "../src/tilp_indep.h"
#include "../src/tilp_defs.h"

#include "cocoa_sheets.h"
#include "cocoa_structs.h"
#include "cocoa_refresh.h"

extern struct cocoa_objects_ptr *objects_ptr;

#import "TilpController.h"
#import "ImageAndTextCell.h"
#import "Varinfo.h"

#define NODE(n)			((SimpleTreeNode*)n)
#define NODE_DATA(n) 		((SimpleNodeData*)[NODE((n)) nodeData])
#define SAFENODE(n) 		((SimpleTreeNode*)((n)?(n):(dirlistData)))

@implementation TilpController

TilpGuiFncts gui_functions;

- (id)init
{
  NSMutableDictionary *tmpCalcProperties;
  NSMutableDictionary *tmpMutDict;
  NSArray *tmpArray;

  self = [super init];

  if (self == nil)
    return nil;

  tmpCalcProperties = [[NSMutableDictionary alloc] init];
  tmpMutDict = [[NSMutableDictionary alloc] init];

  // begin with the TI 73
  tmpArray = [NSArray arrayWithObjects:@"73c", @"73g", @"73i", @"73l",
    @"73n", @"73p", @"73t", @"73v",
    @"73w", @"73y", nil];
  [tmpMutDict setObject:tmpArray forKey:@"tiTypes"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extAMS"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extFLASHApp"];

  tmpArray = [NSArray arrayWithObjects:@"73g", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extBackup"];

  [tmpMutDict setObject:@"backup.73g" forKey:@"defaultBackupFilename"];
  [tmpMutDict setObject:@"group.73g" forKey:@"defaultGroupFilename"];

  [tmpCalcProperties setObject:[NSDictionary dictionaryWithDictionary:tmpMutDict]
                        forKey:[NSString stringWithFormat:@"CALC %i", CALC_TI73]];

  [tmpMutDict removeAllObjects];

  // TI 82
  tmpArray = [NSArray arrayWithObjects:@"82b", @"82d", @"82g", @"82i",
    @"82l", @"82m", @"82n", @"82p",
    @"82t", @"82w", @"82y", @"82z", nil];
  [tmpMutDict setObject:tmpArray forKey:@"tiTypes"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extAMS"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extFLASHApp"];

  tmpArray = [NSArray arrayWithObjects:@"82g", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extBackup"];

  [tmpMutDict setObject:@"backup.82g" forKey:@"defaultBackupFilename"];
  [tmpMutDict setObject:@"group.82g" forKey:@"defaultGroupFilename"];

  [tmpCalcProperties setObject:[NSDictionary dictionaryWithDictionary:tmpMutDict]
                        forKey:[NSString stringWithFormat:@"CALC %i", CALC_TI82]];

  [tmpMutDict removeAllObjects];

  // TI 83
  tmpArray = [NSArray arrayWithObjects:@"83b", @"83c", @"83d", @"83g",
    @"83i", @"83l", @"83m", @"83n",
    @"83p", @"83s", @"83t", @"83y",
    nil];
  [tmpMutDict setObject:tmpArray forKey:@"tiTypes"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extAMS"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extFLASHApp"];

  tmpArray = [NSArray arrayWithObjects:@"83g", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extBackup"];

  [tmpMutDict setObject:@"backup.83g" forKey:@"defaultBackupFilename"];
  [tmpMutDict setObject:@"group.83g" forKey:@"defaultGroupFilename"];

  [tmpCalcProperties setObject:[NSDictionary dictionaryWithDictionary:tmpMutDict]
                        forKey:[NSString stringWithFormat:@"CALC %i", CALC_TI83]];

  [tmpMutDict removeAllObjects];

  // TI 83+
  tmpArray = [NSArray arrayWithObjects:@"8xb", @"8xc", @"8xd", @"8xg",
    @"8xi", @"8xl", @"8xm", @"8xn",
    @"8xp", @"8xs", @"8xy", nil];
  [tmpMutDict setObject:tmpArray forKey:@"tiTypes"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extAMS"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extFLASHApp"];

  tmpArray = [NSArray arrayWithObjects:@"8xg", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extBackup"];

  [tmpMutDict setObject:@"backup.8xg" forKey:@"defaultBackupFilename"];
  [tmpMutDict setObject:@"group.8xg" forKey:@"defaultGroupFilename"];

  [tmpCalcProperties setObject:[NSDictionary dictionaryWithDictionary:tmpMutDict]
                        forKey:[NSString stringWithFormat:@"CALC %i", CALC_TI83P]];

  [tmpMutDict removeAllObjects];

  // TI 85
  tmpArray = [NSArray arrayWithObjects:@"85b", @"85c", @"85d", @"85e",
    @"85g", @"85i", @"85k", @"85l"
    @"85m", @"85n", @"85p", @"85r",
    @"85s", @"85v", nil];
  [tmpMutDict setObject:tmpArray forKey:@"tiTypes"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extAMS"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extFLASHApp"];

  tmpArray = [NSArray arrayWithObjects:@"85g", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extBackup"];

  [tmpMutDict setObject:@"backup.85g" forKey:@"defaultBackupFilename"];
  [tmpMutDict setObject:@"group.85g" forKey:@"defaultGroupFilename"];

  [tmpCalcProperties setObject:[NSDictionary dictionaryWithDictionary:tmpMutDict]
                        forKey:[NSString stringWithFormat:@"CALC %i", CALC_TI85]];

  [tmpMutDict removeAllObjects];

  // TI 86
  tmpArray = [NSArray arrayWithObjects:@"86c", @"86d", @"86e", @"86g",
    @"86i", @"86k", @"86l", @"86m",
    @"86n", @"86p", @"86r", @"86s",
    @"86v", @"86w", nil];
  [tmpMutDict setObject:tmpArray forKey:@"tiTypes"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extAMS"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extFLASHApp"];

  tmpArray = [NSArray arrayWithObjects:@"86g", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extBackup"];

  [tmpMutDict setObject:@"backup.86g" forKey:@"defaultBackupFilename"];
  [tmpMutDict setObject:@"group.86g" forKey:@"defaultGroupFilename"];

  [tmpCalcProperties setObject:[NSDictionary dictionaryWithDictionary:tmpMutDict]
                        forKey:[NSString stringWithFormat:@"CALC %i", CALC_TI86]];

  [tmpMutDict removeAllObjects];

  // TI 89
  tmpArray = [NSArray arrayWithObjects:@"89a", @"89b", @"89c", @"89d",
    @"89e", @"89f", @"89g", @"89i",
    @"89l", @"89m", @"89p", @"89s",
    @"89t", @"89x", @"89y", @"89z",
    @"89k", @"89u", nil];
  [tmpMutDict setObject:tmpArray forKey:@"tiTypes"];

  tmpArray = [NSArray arrayWithObjects:@"89u", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extAMS"];

  tmpArray = [NSArray arrayWithObjects:@"89k", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extFLASHApp"];

  tmpArray = [NSArray arrayWithObjects:@"89g", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extBackup"];

  [tmpMutDict setObject:@"backup.89g" forKey:@"defaultBackupFilename"];
  [tmpMutDict setObject:@"group.89g" forKey:@"defaultGroupFilename"];

  [tmpCalcProperties setObject:[NSDictionary dictionaryWithDictionary:tmpMutDict]
                        forKey:[NSString stringWithFormat:@"CALC %i", CALC_TI89]];

  [tmpMutDict removeAllObjects];

  // TI 92
  tmpArray = [NSArray arrayWithObjects:@"92a", @"92b", @"92c", @"92d",
    @"92e", @"92f", @"92g", @"92i",
    @"92l", @"92m", @"92p", @"92s",
    @"92t", @"92x", nil];
  [tmpMutDict setObject:tmpArray forKey:@"tiTypes"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extAMS"];

  tmpArray = [NSArray arrayWithObjects:@"NOT SUPPORTED", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extFLASHApp"];

  tmpArray = [NSArray arrayWithObjects:@"92g", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extBackup"];

  [tmpMutDict setObject:@"backup.92g" forKey:@"defaultBackupFilename"];
  [tmpMutDict setObject:@"group.92g" forKey:@"defaultGroupFilename"];

  [tmpCalcProperties setObject:[NSDictionary dictionaryWithDictionary:tmpMutDict]
                        forKey:[NSString stringWithFormat:@"CALC %i", CALC_TI92]];

  [tmpMutDict removeAllObjects];

  // TI 92+
  tmpArray = [NSArray arrayWithObjects:@"9xa", @"9xb", @"9xc", @"9xd",
    @"9xe", @"9xf", @"9xg", @"9xi",
    @"9xl", @"9xm", @"9xp", @"9xs",
    @"9xt", @"9xx", @"9xz", @"9xk",
    @"9xu", nil];
  [tmpMutDict setObject:tmpArray forKey:@"tiTypes"];

  tmpArray = [NSArray arrayWithObjects:@"9xu", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extAMS"];

  tmpArray = [NSArray arrayWithObjects:@"9xk", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extFLASHApp"];

  tmpArray = [NSArray arrayWithObjects:@"9xg", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extBackup"];

  [tmpMutDict setObject:@"backup.9xg" forKey:@"defaultBackupFilename"];
  [tmpMutDict setObject:@"group.9xg" forKey:@"defaultGroupFilename"];

  [tmpCalcProperties setObject:[NSDictionary dictionaryWithDictionary:tmpMutDict]
                        forKey:[NSString stringWithFormat:@"CALC %i", CALC_TI92P]];

  [tmpMutDict removeAllObjects];

  // TI V200
  tmpArray = [NSArray arrayWithObjects:@"v2a", @"v2c", @"v2d", @"v2e",
      @"v2f", @"v2g", @"v2i", @"v2k",
      @"v2l", @"v2m", @"v2p", @"v2q",
      @"v2r", @"v2s", @"v2t", @"v2u",
      @"v2w", @"v2x", @"v2y", @"v2z",
      nil];

  [tmpMutDict setObject:tmpArray forKey:@"tiTypes"];

  tmpArray = [NSArray arrayWithObjects:@"v2u", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extAMS"];

  tmpArray = [NSArray arrayWithObjects:@"v2k", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extFLASHApp"];

  tmpArray = [NSArray arrayWithObjects:@"v2g", nil];
  [tmpMutDict setObject:tmpArray forKey:@"extBackup"];

  [tmpMutDict setObject:@"backup.v2g" forKey:@"defaultBackupFilename"];
  [tmpMutDict setObject:@"group.v2g" forKey:@"defaultGroupFilename"];

  [tmpCalcProperties setObject:[NSDictionary dictionaryWithDictionary:tmpMutDict]
                        forKey:[NSString stringWithFormat:@"CALC %i", CALC_V200]];  
  
  [tmpMutDict release];

  calcsProperties = [NSDictionary dictionaryWithDictionary:tmpCalcProperties];

  [tmpCalcProperties release];
  [calcsProperties retain];

  return self;
}

- (void)dealloc
{
  NSUserDefaults *myPrefs;
  NSMutableDictionary *myTilpConfig;

  myPrefs = objects_ptr->prefs;
  myTilpConfig = objects_ptr->tilpConfig;

  [myPrefs synchronize];
  [myPrefs release];
  myPrefs = nil;
  objects_ptr->prefs = NULL;

  [myTilpConfig release];
  myTilpConfig = nil;
  objects_ptr->tilpConfig = NULL;

  if (dirlistData != nil)
    [dirlistData release];

  dirlistData = nil;

  // at this time, nobody uses this struct anymore (hopefully...)
  // if you get any segfault/sigbus problem on exiting, rank this #1 :)
  free(objects_ptr);

  [calcsProperties release];

  [super dealloc];
}

- (void)awakeFromNib
{
  NSTableColumn *column;
  ImageAndTextCell *imageAndTextCell;

#ifdef OSX_DEBUG
  fprintf(stderr, "tilp => got awakeFromNib\n");
#endif

  // Init the instance pointer
  objects_ptr->myTilpController = self;

  objects_ptr->dlgbox_data = NULL;

  // Init the GUI independant functions
  gui_functions.msg_box = create_cocoa_msg_sheet;
  gui_functions.msg_box2 = create_cocoa_msg2_sheet;
  gui_functions.msg_box3 = create_cocoa_msg3_sheet;
  gui_functions.msg_box4 = create_cocoa_msg4_sheet;
  gui_functions.msg_entry = create_cocoa_msg_entry;
  gui_functions.create_pbar_type1 = create_cocoa_pbar_type1_sheet;
  gui_functions.create_pbar_type2 = create_cocoa_pbar_type2_sheet;
  gui_functions.create_pbar_type3 = create_cocoa_pbar_type3_sheet;
  gui_functions.create_pbar_type4 = create_cocoa_pbar_type4_sheet;
  gui_functions.create_pbar_type5 = create_cocoa_pbar_type5_sheet;
  gui_functions.destroy_pbar = destroy_pbar;
  tilp_gui_set_fncts(&gui_functions);

  cocoa_init_refresh_functions();

  // set the title of the main window
  [mainWindow setTitle:[NSString stringWithFormat:@"TiLP v%s (%s)", VERSION, TILP_OSX_VERSION]];
  
  // init the outline view
  [dirlistTree setDelegate:self];

  column = [dirlistTree tableColumnWithIdentifier:@"Varname"];
  imageAndTextCell = [[[ImageAndTextCell alloc] init] autorelease];
  [imageAndTextCell setEditable:NO];
  [column setDataCell:imageAndTextCell];

  // we need to display an image
  column = [dirlistTree tableColumnWithIdentifier:@"Attributes"];
  [column setDataCell:imageAndTextCell];

  // init the content of the NSOutlineView
  [self refreshOutline];

  // register for dragging
  [dirlistTree registerForDraggedTypes:[NSArray arrayWithObjects:@"NSFilenamesPboardType", nil]];

  // register the ready callback
  tilp_calc_register(cocoa_set_link_status);
}

// calc properties

- (NSDictionary *)getCurrentCalcDict
{
  return [calcsProperties objectForKey:[NSString stringWithFormat:@"CALC %i", options.lp.calc_type]];
}

// link status

- (void)setLinkStatus:(int)status
{
    if (status != -1)
    {
        [calcState setTextColor:[NSColor greenColor]];
        [calcState setStringValue:[NSString stringWithFormat:@"OK - %s",
            tifiles_calctype_to_string(options.lp.calc_type)]];
    }
    else
    {
        [calcState setTextColor:[NSColor redColor]];
        [calcState setStringValue:@"Not connected"];
    }
}

// outline view and infos refresh

- (void)refreshOutline
{
  int folderPos = 0; // position in tiVarsArray
  int varPos = 0; // position in the array representing the folder
  int i, j;
  TilpCalcMemInfo cmi;

  memset(&cmi, 0, sizeof(TilpCalcMemInfo));
  
  TNode *vars;
  TNode *apps;
  TNode *p;
  TNode *q;
  
  TiVarEntry *v;
  
  NSMutableDictionary *content;
  NSMutableDictionary *tmpDict;
  NSMutableArray *mainEntries;
  NSMutableArray *tiVarsArray;
  NSMutableArray *tiAppsArray;
  NSMutableArray *tmpArray;
  Varinfo *varinfo;
  
  // init our big fscking dictionary of the d34th

  content = [[NSMutableDictionary alloc] init];

  [content setObject:@"OVRoot" forKey:@"Group"];

  mainEntries = [[NSMutableArray alloc] init];

  [content setObject:mainEntries forKey:@"Entries"];

  // now the real fun is about to begin

  tmpArray = nil; // GCC, please, just shut the f*ck up about this one.

  // FLASH APPS

  tiAppsArray = [[NSMutableArray alloc] init];

  tmpDict = [[NSMutableDictionary alloc] init];

  [mainEntries insertObject:tmpDict atIndex:0];

  [tmpDict setObject:@"FLASH Apps" forKey:@"Group"];
  [tmpDict setObject:tiAppsArray forKey:@"Entries"];

  // VARIABLES

  tiVarsArray = [[NSMutableArray alloc] init];

  tmpDict = [[NSMutableDictionary alloc] init];

  [mainEntries insertObject:tmpDict atIndex:1];

  [tmpDict setObject:@"TI Variables" forKey:@"Group"];
  [tmpDict setObject:tiVarsArray forKey:@"Entries"];
  
  // ok, we must now populate our big fscking dictionary with the
  // list of FLASH APPS and variables

  // ctree_win.dirlist is NULL when the app is launched
  if (ctree_win.dirlist != NULL)
  {
      // sort the dirlist
      switch(options.ctree_sort)
      {
          case SORT_BY_NAME:
              //sort_cfiles_by_name();
              break;
          case SORT_BY_INFO:
              tilp_sort_vars_by_info();
              break;
          case SORT_BY_TYPE:
              tilp_sort_vars_by_type();
              break;
          case SORT_BY_SIZE:
              tilp_sort_vars_by_size();
              break;
      }      

      // FLASH APPS

      apps = g_node_nth_child(ctree_win.dirlist, 1);

      for (i = 0; i < g_node_n_children(apps); i++)
      {
          p = g_node_nth_child(apps, i);
          v = (TiVarEntry *) (p->data);

          // dictionary that will hold this app
          tmpDict = [[NSMutableDictionary alloc] init];
          [tmpDict setObject:[NSImage imageNamed:@"doc.tiff"] forKey:@"Image"];
          [tmpDict setObject:[NSString stringWithUTF8String:v->trans] forKey:@"Varname"];
          [tmpDict setObject:[NSString stringWithCString:tifiles_vartype2string(v->type)] forKey:@"Vartype"];
          [tmpDict setObject:[NSString stringWithFormat:@"%u", v->size] forKey:@"Varsize"];

          varinfo = [[Varinfo alloc] initWithPointer:v];
          [tmpDict setObject:varinfo forKey:@"varinfo"];

          [tiAppsArray insertObject:tmpDict atIndex:varPos];
          varPos++;
          // keep some stats
          cmi.flash++;
          cmi.flashmem += v->size >> 10;
      }

      // Variables

      vars = g_node_nth_child(ctree_win.dirlist, 0);

      // folders first
      for (i = 0; i < g_node_n_children(vars); i++)
      {
          p = g_node_nth_child(vars, i);
          v = (TiVarEntry *) (p->data);

          if ((v != NULL) || ti_calc.has_folder)
          {
              // dictionary that will hold the stuff
              tmpDict = [[NSMutableDictionary alloc] init];

              [tiVarsArray insertObject:tmpDict atIndex:folderPos];
              folderPos++;

              // array that will hold all the vars for this folder
              tmpArray = [[NSMutableArray alloc] init];

              [tmpDict setObject:tmpArray forKey:@"Entries"];
              [tmpDict setObject:[NSString stringWithUTF8String:v->trans] forKey:@"Group"];

              // we're in a new folder, so...
              varPos = 0;
              cmi.folders++;
          }
          else
          {
              // the calc has no folder, the vars will go under the "TI Variables" item
              tmpArray = tiVarsArray;
              varPos = folderPos;
          }

          for (j = 0; j < g_node_n_children(p); j++)
          {
              q = g_node_nth_child(p, j);
              v = (TiVarEntry *) (q->data);

              // dictionary that will hold this var
              tmpDict = [[NSMutableDictionary alloc] init];

              switch (v->attr)
              {
                  case ATTRB_LOCKED:
                      [tmpDict setObject:[NSImage imageNamed:@"locked.tiff"] forKey:@"Attribute"];
                      break;
                  case ATTRB_ARCHIVED:
                      [tmpDict setObject:[NSImage imageNamed:@"archived.tiff"] forKey:@"Attribute"];
                      cmi.archivemem += v->size >> 10;
                      break;
                  default:
                      cmi.mem += v->size >> 10;
                      break;
              }

              [tmpDict setObject:[NSImage imageNamed:@"doc.tiff"] forKey:@"Image"];
              [tmpDict setObject:[NSString stringWithUTF8String:v->trans] forKey:@"Varname"];
              [tmpDict setObject:[NSString stringWithCString:tifiles_vartype2string(v->type)] forKey:@"Vartype"];
              [tmpDict setObject:[NSString stringWithFormat:@"%u", v->size] forKey:@"Varsize"];

              varinfo = [[Varinfo alloc] initWithPointer:v];
              [tmpDict setObject:varinfo forKey:@"varinfo"];

              [tmpArray insertObject:tmpDict atIndex:varPos];
              varPos++;
              cmi.vars++;
          }
      }
  }
  
  // get a tree from our big fscking dictionary...

  // release the preceding dirlistData if it exists
  if (dirlistData != nil)
  {
    [dirlistData release];
    dirlistData = nil;
  }

  dirlistData = [[SimpleTreeNode treeFromDictionary:content] retain];
  
  // release the big fscking dictionary. Feel better, eh ? :)
  [content release];
  content = nil;

  // ... then *HUMPFFF* pass the BAAAAAAALLLLLLLLLLLLLLLLLLLLLLL !!!
  [dirlistTree reloadData];

  // ball passed. blargh.

  // expand the "TI Variables" item if it has children
  if (ctree_win.dirlist != NULL)
    [dirlistTree expandItem:[dirlistTree itemAtRow:1]];
  else
    [dirlistTree collapseItem:[dirlistTree itemAtRow:1]];

  // Update the memory information
  [numberOfFolders setStringValue:[NSString stringWithFormat:@"Number of folders : %d", cmi.folders]];

  if (cmi.flash == 0)
    [varsStats setStringValue:[NSString stringWithFormat:@"Number of variables : %d", cmi.vars]];
  else
    [varsStats setStringValue:[NSString stringWithFormat:@"Number of variables : %d, FLASH Apps : %d", cmi.vars, cmi.flash]];

  [memoryStats setStringValue:[NSString stringWithFormat:@"Memory used : %d KB (archive %d KB, FLASH %d KB)", (cmi.mem + cmi.archivemem + cmi.flashmem), cmi.archivemem, cmi.flashmem]];
}


// required to be a valid dataSource for NSOutlineView
// more methods are available, see the docs...

- (int)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item
{
  return [SAFENODE(item) numberOfChildren];
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item
{
  return [NODE_DATA(item) isGroup];
}

- (id)outlineView:(NSOutlineView *)outlineView child:(int)index ofItem:(id)item
{
  return [SAFENODE(item) childAtIndex:index];
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item
{
  if ([[tableColumn identifier] isEqualToString:@"Varname"])
    return [NODE_DATA(item) name];
  else if ([[tableColumn identifier] isEqualToString:@"Attributes"])
    return nil; // there's no text to display (could be an option ?)
  else if ([[tableColumn identifier] isEqualToString:@"Type"])
    return [NODE_DATA(item) vartype];
  else if ([[tableColumn identifier] isEqualToString:@"Size"])
    return [NODE_DATA(item) varsize];

  return nil;
}


// delegate methods of NSOutlineView

- (void)outlineView:(NSOutlineView *)olv willDisplayCell:(NSCell *)cell forTableColumn:(NSTableColumn *)tableColumn item:(id)item
{
  if ([[tableColumn identifier] isEqualToString:@"Varname"])
  {
    // Make sure there is an image set. If not, it's a folder for sure
    // so set the image to what it should be
    if (item && ![NODE_DATA(item) iconRep])
      [NODE_DATA(item) setIconRep:[NSImage imageNamed:@"dir_c.tiff"]];
    // Set the image here since the value returned from outlineView:objectValueForTableColumn:...
    // didn't specify the image part...
    [(ImageAndTextCell *)cell setImage:[NODE_DATA(item) iconRep]];
  }
  else if ([[tableColumn identifier] isEqualToString:@"Attributes"])
  {
    [(ImageAndTextCell *)cell setImage:[NODE_DATA(item) attribute]];
  }
}

- (BOOL)outlineView:(NSOutlineView *)outlineView shouldExpandItem:(id)item
{
  [NODE_DATA(item) setIconRep:[NSImage imageNamed:@"dir_o.tiff"]];

  return YES;
}

- (BOOL)outlineView:(NSOutlineView *)outlineView shouldCollapseItem:(id)item
{
  [NODE_DATA(item) setIconRep:[NSImage imageNamed:@"dir_c.tiff"]];

  return YES;
}

// delegate methods of NSOutlineView, dragging-related

// This method validates whether or not the proposal is a valid one.
// Returns NO if the drop should not be allowed.
- (unsigned int)outlineView:(NSOutlineView*)olv validateDrop:(id <NSDraggingInfo>)info proposedItem:(id)item proposedChildIndex:(int)childIndex
{
  BOOL filenameIsValid = NO;

  NSPasteboard *pboard;
  NSArray *filenames;
  NSEnumerator *filesEnum;
  NSString *file;

  NSArray *tiTypes;
  NSString *tiType;
  NSEnumerator *tiTypesEnum;

  pboard = [info draggingPasteboard];

  if ([[pboard types] indexOfObject:@"NSFilenamesPboardType"] != NSNotFound)
  {
#ifdef OSX_DEBUG
    fprintf(stderr, "DEBUG: DRAG: NSFilenamesPboardType is AVAILABLE\n");
#endif
    filenames = [pboard propertyListForType:@"NSFilenamesPboardType"];

    if (filenames != nil)
    {
      filesEnum = [filenames objectEnumerator];

      tiTypes = [[self getCurrentCalcDict] objectForKey:@"tiTypes"];

      tiTypesEnum = [tiTypes objectEnumerator];

      while ((file = [filesEnum nextObject]) != nil)
      {
#ifdef OSX_DEBUG
        fprintf(stderr, "DEBUG: FILE : %s", [file cString]);
#endif
        while ((tiType = [tiTypesEnum nextObject]) != nil)
        {
          if ([[[file pathExtension] lowercaseString] isEqualToString:tiType])
          {
#ifdef OSX_DEBUG
            fprintf(stderr, " should be a TI file\n");
#endif
            filenameIsValid = YES;
            break;
          }
        }

        if (filenameIsValid == NO)
        {
#ifdef OSX_DEBUG
          fprintf(stderr, " is probably not a TI file, rejecting DROP\n");
#endif
          break;
        }
      }
    }
  }

  return filenameIsValid ? NSDragOperationGeneric : NO;
}

- (BOOL)outlineView:(NSOutlineView*)olv acceptDrop:(id <NSDraggingInfo>)info item:(id)targetItem childIndex:(int)childIndex
{
  GList *filelist = NULL;
  TilpFileInfo *fi = NULL;

  NSPasteboard *pboard;
  NSArray *filenames;
  NSEnumerator *filesEnum;
  NSString *file;

#ifdef OSX_DEBUG
  fprintf(stderr, "Building filelist...\n");
#endif

  pboard = [info draggingPasteboard];

  if ([[pboard types] indexOfObject:@"NSFilenamesPboardType"] != NSNotFound)
  {
    filenames = [pboard propertyListForType:@"NSFilenamesPboardType"];

    if (filenames != nil)
    {
      filesEnum = [filenames objectEnumerator];

      while ((file = [filesEnum nextObject]) != nil)
      {
        fi = (TilpFileInfo *)malloc(sizeof(TilpFileInfo));
        memset(fi, 0, sizeof(TilpFileInfo));

        if (fi == NULL)
        {
#ifdef OSX_DEBUG
          fprintf(stderr, "DEBUG: fi is NULL !!\n");
#endif
          return NO;
        }

        fi->name = strdup([file fileSystemRepresentation]);

        filelist = g_list_append(filelist, fi);
      }
    }
  }

  clist_win.selection = filelist;

  // FIXME OS X : thread it ?
  //cb_send_var();

  // FIXME OS X : need some tests !
  [NSThread detachNewThreadSelector:@selector(sendVarsThreaded:)
                           toTarget:myTransfersController
                         withObject:self];

  return YES;
}

@end
