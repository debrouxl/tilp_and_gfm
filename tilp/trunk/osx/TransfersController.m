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

#include <glib/glib.h>
#include <libticalcs/calc_int.h>
#include <libticables/cabl_err.h>

#include "cocoa_structs.h"
#include "cocoa_sheets.h"

#include "../src/tilp_core.h"
#include "../src/tilp_indep.h"
#include "../src/tilp_defs.h"
#include "../src/intl.h"

extern struct cocoa_objects_ptr *objects_ptr;

#import "TilpController.h"
#import "SheetsController.h"
#import "TransfersController.h"

#define NODE(n)			((SimpleTreeNode*)n)
#define NODE_DATA(n) 		((SimpleNodeData*)[NODE((n)) nodeData])
#define SAFENODE(n) 		((SimpleTreeNode*)((n)?(n):(dirlistData)))

@implementation TransfersController

- (void)awakeFromNib
{
#ifdef OSX_DEBUG
    fprintf(stderr, "transfers => got awakeFromNib\n");
#endif

    objects_ptr->myTransfersController = self;
}


// THREADED

- (void)sendVarsThreaded:(id)sender
{
  NSAutoreleasePool *localPool;
  
  localPool = [[NSAutoreleasePool alloc] init];
  
  tilp_calc_send_var(0);
  
  [localPool release];
  [NSThread exit];
}


- (void)getVarsThreaded:(id)sender
{
    NSAutoreleasePool *localPool;

    NSMutableArray *items;
    NSEnumerator *itemsEnum;
    NSEnumerator *selectedRows;
    NSNumber *selRow;
    id item;
    id foldItem;
    
    GList *vars_list = NULL;
    GList *flash_list = NULL;
    
    TiVarEntry *v = NULL;
    
    int tiVarsRow;
    int i, j, row;
    int vars_indexes[128]; // I don't know if 128 vars can be fitted on the TI, but :-)
    int flash_indexes[64];

    localPool = [[NSAutoreleasePool alloc] init];
    
    items = [NSMutableArray array];
    
    selectedRows = [dirlistTree selectedRowEnumerator];
    selRow = nil;
    
    // If the FLASH Applications folder is expanded, then the TI Variables item is not at row 6
    if ([dirlistTree isItemExpanded:[dirlistTree itemAtRow:5]])
        {
            tiVarsRow = 5 + 1 + [myTilpController outlineView:dirlistTree numberOfChildrenOfItem:[dirlistTree itemAtRow:5]];
        }
    else
        tiVarsRow = 6;
    
    while ((selRow = [selectedRows nextObject]))
        {
            switch([selRow intValue])
                {
                    case 0: // do a screendump
                        [self getScreen:self];
                        break;
                    case 1: // do a romdump
                        [self romDump:self];
                        break;
                    case 2: // memory item => do... I don't know
                        fprintf(stderr, "DEBUG: GET VARS => MEMORY ITEM, UNUSED\n");
                        break;
                    case 3: // get ID list
                        tilp_calc_idlist();
                        break;
                    case 4: // keyboard item => do... I don't know
                        fprintf(stderr, "DEBUG: GET VARS => KEYBOARD ITEM, UNUSED\n");
                        break;
                    case 5: // FLASH Applications item => get each FLASH App
                        item = [dirlistTree itemAtRow:5];
                        
                        [dirlistTree expandItem:item];
                                          
                        foldItem = [dirlistTree itemAtRow:[dirlistTree rowForItem:item] + 1];
                  
                        while ([NODE_DATA(foldItem) isGroup] == NO)
                            {
                                v = (TiVarEntry *)malloc(sizeof(TiVarEntry));
                          
                                memcpy(v, [[NODE_DATA(foldItem) varinfo] varinfo], sizeof(TiVarEntry));
                        
                                flash_list = g_list_append(flash_list, v);
                                                        
                                foldItem = [dirlistTree itemAtRow:[dirlistTree rowForItem:foldItem] + 1];
                            }
                            
                            ctree_win.selection2 = flash_list;
                        break;
                    default:
                        if ([selRow intValue] == tiVarsRow)
                            {
                                // do a backup of all vars
                                [self doBackup:self];
                            }
                        else if (([selRow intValue] > 5) && ([dirlistTree itemAtRow:[selRow intValue]]))
                            [items addObject:[dirlistTree itemAtRow:[selRow intValue]]];
                }
        }

    itemsEnum = [items objectEnumerator];
    
    i = 0;
    
    while ((item = [itemsEnum nextObject]) != nil)
        {
            // if a folder is selected, select all vars in this folder
            if ([NODE_DATA(item) isGroup] == YES)
              {
                  [dirlistTree expandItem:item];
       
                  foldItem = [dirlistTree itemAtRow:[dirlistTree rowForItem:item] + 1];

                  while ([NODE_DATA(foldItem) isGroup] == NO)
                    {
                        v = (TiVarEntry *)malloc(sizeof(TiVarEntry));
                          
                        memcpy(v, [[NODE_DATA(foldItem) varinfo] varinfo], sizeof(TiVarEntry));
                        
                        row = [dirlistTree rowForItem:foldItem];

                        if (row > tiVarsRow)
                          {
                              vars_list = g_list_append(vars_list, v);
                              vars_indexes[i++] = [dirlistTree rowForItem:foldItem];
                          }
                        else
                          {
                              flash_list = g_list_append(flash_list, v);
                              flash_indexes[i++] = [dirlistTree rowForItem:foldItem];
                          }
                                                                                                                
                        foldItem = [dirlistTree itemAtRow:[dirlistTree rowForItem:foldItem] + 1];
                    }
              }
            else
              {
                  row = [dirlistTree rowForItem:item];

                  // make sure it is not already in the list
                  for (j = 0; j < g_list_length(vars_list); j++)
                    {
                        if (row == vars_indexes[j])
                          {
                              row = -1;
                              
                              break;
                          }
                    }
                    
                  for (j = 0; j < g_list_length(flash_list); j++)
                    {
                        if (row == flash_indexes[j])
                          {
                              row = -1;
                              
                              break;
                          }
                    }

                  if (row > 0)
                    {
                        v = (TiVarEntry *)malloc(sizeof(TiVarEntry));
                        
                        memcpy(v, [[NODE_DATA(item) varinfo] varinfo], sizeof(TiVarEntry));
                  
                        if (row > tiVarsRow)
                            {
                                vars_list = g_list_append(vars_list, v);
                                vars_indexes[i++] = [dirlistTree rowForItem:item];
                            }
                        else
                            {
                                flash_list = g_list_append(flash_list, v);
                                flash_indexes[i++] = [dirlistTree rowForItem:item];
                            }
                    }
              }
            
            v = NULL;
        }
        
    ctree_win.selection = vars_list; 
  
    // Retrieve vars
    if (ctree_win.selection != NULL)
    {
        tilp_calc_recv_var();

        ctree_win.selection = NULL;
        g_list_free(vars_list);
    }

    // FLASH APPS HERE !
        
    if (flash_list != NULL)
    {
        ctree_win.selection2 = flash_list;

        tilp_calc_recv_app();

        g_list_free(ctree_win.selection2);
        g_list_free(flash_list);
    }

    [localPool release];
    [NSThread exit];
}


- (void)sendFlashAppThreaded:(id)files
{
    NSAutoreleasePool *localPool;
    NSArray *nsfiles;
    NSEnumerator *filesEnum;
    NSString *nsfile;
    
    char *file = NULL;
    
    localPool = [[NSAutoreleasePool alloc] init];
        
    nsfiles = (NSArray *)files;
    
    filesEnum = [files objectEnumerator];
    
    while ((nsfile = [filesEnum nextObject]) != nil)
        {
            file = strdup([nsfile fileSystemRepresentation]);

            tilp_calc_send_flash_app(file);
            
            free(file);
        }
    
    [nsfiles release];
    
    [localPool release];
    [NSThread exit];
}

- (void)sendAMSThreaded:(id)files
{
    NSAutoreleasePool *localPool;
    NSArray *nsfiles;

    char *file;

    localPool = [[NSAutoreleasePool alloc] init];

    nsfiles = (NSArray *)files;
            
    file = strdup([[nsfiles lastObject] fileSystemRepresentation]);

    tilp_calc_send_flash_os(file);
            
    free(file);
    
    [nsfiles release];
    
    [localPool release];
    [NSThread exit];
}

- (void)doRestoreThreaded:(id)files
{
    NSAutoreleasePool *localPool;
    NSArray *nsfiles;

    char *file;

    localPool = [[NSAutoreleasePool alloc] init];

    nsfiles = (NSArray *)files;
            
    file = strdup([[nsfiles lastObject] fileSystemRepresentation]);
    
    tilp_calc_send_backup(file);
            
    free(file);
    
    [nsfiles release];
    
    [localPool release];
    [NSThread exit];
}

- (void)getScreenThreaded:(id)sender
{
    NSAutoreleasePool *localPool;
    
    localPool = [[NSAutoreleasePool alloc] init];
    
    [self getScreen:self];
    
    [localPool release];
    [NSThread exit];
}

- (void)romDumpThreaded:(id)sender
{
    NSAutoreleasePool *localPool;
    
    localPool = [[NSAutoreleasePool alloc] init];
    
    [self romDump:self];
    
    [localPool release];
    [NSThread exit];
}

- (void)doBackupThreaded:(id)sender
{
    NSAutoreleasePool *localPool;
    
    localPool = [[NSAutoreleasePool alloc] init];
    
    [self doBackup:self];
    
    [localPool release];
    [NSThread exit];
}

// NOT THREADED

static void
render_screen_bw(uint8_t *bitmap, unsigned char *pixels)
{
    int row;
    int col;
    uint8_t data;
    int mask;
    int bit;
    
    // speed things up : set a white width * height area (* 4 => 4 bytes per pixel)
    memset(pixels, 0xFF, (ti_screen.width * ti_screen.height * 4));

    for (row = 0; row < ti_screen.height; row++)
        for (col = 0; col < (ti_screen.width >> 3); col++)
        {
            data = bitmap[(ti_screen.width >> 3) * row + col];
            mask = 0x80;
            for (bit = 0; bit < 8; bit++)
            {
                if (data & mask) // black => set R/G/B/alpha to 0/0/0/0xFF
                {
                    *pixels++ = 0; // red
                    *pixels++ = 0; // blue
                    *pixels++ = 0; // green
                    pixels++; // alpha, but already set to 0xFF
                }
                else // white => increment the pixels pointer
                    pixels += 4;

                mask >>= 1;
            }
        }
}

static void
render_screen_blurry(uint8_t *bitmap, unsigned char *pixels)
{
    int row;
    int col;
    uint8_t data;
    int mask;
    int bit;

    for (row = 0; row < ti_screen.height; row++)
        for (col = 0; col < (ti_screen.width >> 3); col++)
        {
            data = bitmap[(ti_screen.width >> 3) * row + col];
            mask = 0x80;
            for (bit = 0; bit < 8; bit++)
            {
                if (data & mask) // black => set R/G/B to 0x00/0x00/0x34
                {
                    *pixels++ = 0x00; // red
                    *pixels++ = 0x00; // blue
                    *pixels++ = 0x34; // green
                }
                else // white => set R/G/B to 0xA8/0xB4/0xA8
                {
                    *pixels++ = 0xA8; // red
                    *pixels++ = 0xB4; // blue
                    *pixels++ = 0xA8; // green
                }
                *pixels++ = 0xFF; // alpha
                mask >>= 1;
            }
        }
}

- (void)getScreen:(id)sender
{
    // Ol, a big THANK YOU for this one

    NSImage *screen;
    NSBitmapImageRep *bitmap;
    NSSize size;
    NSRect viewFrame;
    NSSize newSize;
    
    if ((tilp_screen_capture() != 0) || (ti_screen.bitmap == NULL))
        return;
    
    bitmap = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:nil
                                       pixelsWide:ti_screen.width
                                       pixelsHigh:ti_screen.height
                                       bitsPerSample:8
                                       samplesPerPixel:4
                                       hasAlpha:YES
                                       isPlanar:NO
                                       colorSpaceName:NSDeviceRGBColorSpace
                                       bytesPerRow:0
                                       bitsPerPixel:0];

    // render the bitmap
    if (options.screen_blurry)
        render_screen_blurry(ti_screen.bitmap, [bitmap bitmapData]);
    else
        render_screen_bw(ti_screen.bitmap, [bitmap bitmapData]);

    size = NSMakeSize(ti_screen.width, ti_screen.height);
    
    screen = [[NSImage alloc] initWithSize:size];
    
    [screen addRepresentation:bitmap];

    [screendumpImage setImage:screen];

    if ([screendumpWindow isVisible] == NO)
    {
      // resize the window
      viewFrame = [screendumpImage frame];

      // resize the imageview
      viewFrame.size = size;
      viewFrame.origin.x = 53;
      viewFrame.origin.y = 60;
      
      newSize.width = viewFrame.size.width + 106;
      newSize.height = viewFrame.size.height + 80;

      [screendumpWindow setContentSize:newSize];
      [screendumpImage setFrame:viewFrame];
      
      // show and add to the Windows menu
      [screendumpWindow makeKeyAndOrderFront:self];
      [NSApp addWindowsItem:screendumpWindow title:@"Screendump" filename:NO];
    }

    // TODO : resize proportionally (10.2), displaying the scaling rate...
}

- (void)romDump:(id)sender
{
    NSSavePanel *sp;
    NSString *proposedFile;

    proposedFile = @"romdump.rom";

    if (tilp_calc_rom_dump() != 0)
        return;

    sp = [NSSavePanel savePanel];

    [sp setRequiredFileType:@"rom"];
    [sp setTitle:@"Save ROM dump as..."];

    [sp beginSheetForDirectory:NSHomeDirectory()
                          file:proposedFile
                modalForWindow:[myBoxesController keyWindow]
                 modalDelegate:myBoxesController
                didEndSelector:@selector(romDumpDidEnd:returnCode:contextInfo:)
                   contextInfo:sp];
}

- (void)doBackup:(id)sender
{
    NSSavePanel *sp;
    NSDictionary *calcDict;
    
    if (tilp_calc_recv_backup() != 0)
        return;
    
    sp = [NSSavePanel savePanel];
    
    calcDict = [myTilpController getCurrentCalcDict];
    
    [sp beginSheetForDirectory:NSHomeDirectory()
        file:[calcDict objectForKey:@"defaultBackupFilename"]
        modalForWindow:[myBoxesController keyWindow]
        modalDelegate:myBoxesController
        didEndSelector:@selector(doBackupDidEnd:returnCode:contextInfo:)
        contextInfo:sp];
}

- (int)sendChar:(uint16_t)tikey
{
#ifdef OSX_DEBUG
    fprintf(stderr, "DEBUG: sending '%c' (%d)\n", tikey, tikey);
#endif

    if (tilp_error(ti_calc.send_key(tikey)))
        return -1;
        
    return tikey;
}

@end
