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

static void
add_item_to_selection_list(GList **list, id item)
{
    TiVarEntry *v;
    
    v = (TiVarEntry *)malloc(sizeof(TiVarEntry));

    memcpy(v, [[NODE_DATA(item) varinfo] varinfo], sizeof(TiVarEntry));

    *list = g_list_append(*list, v);    
}

- (void)getVarsThreaded:(id)sender
{
    NSAutoreleasePool *localPool;

    NSEnumerator *selectedRows;
    NSEnumerator *varsEnum;
    NSNumber *selRow;
    NSMutableArray *vars;
    id item;
    id foldItem;

    BOOL expanded;
    
    GList *vars_list = NULL;
    GList *flash_list = NULL;
    
    int tiVarsRow;
    int row;
    int didBackup = 0;

    localPool = [[NSAutoreleasePool alloc] init];
    
    vars = [NSMutableArray array];
    
    selectedRows = [dirlistTree selectedRowEnumerator];
    selRow = nil;
    
    // If the FLASH Applications folder is expanded, then the TI Variables item is not at row 6
    if ([dirlistTree isItemExpanded:[dirlistTree itemAtRow:0]])
        {
            tiVarsRow = 1 + [myTilpController outlineView:dirlistTree numberOfChildrenOfItem:[dirlistTree itemAtRow:0]];
        }
    else
        tiVarsRow = 1;
    
    while ((selRow = [selectedRows nextObject]))
    {
        row = [selRow intValue];
        // FLASH Applications item => get each FLASH App
        if (row == 0)
        {
            item = [dirlistTree itemAtRow:0];
            expanded = [dirlistTree isItemExpanded:item];
            [dirlistTree expandItem:item];

            foldItem = [dirlistTree itemAtRow:[dirlistTree rowForItem:item] + 1];
            while ([NODE_DATA(foldItem) isGroup] == NO)
            {
                add_item_to_selection_list(&flash_list, foldItem);
                foldItem = [dirlistTree itemAtRow:[dirlistTree rowForItem:foldItem] + 1];
            }

            ctree_win.selection2 = flash_list;

            if (expanded != YES)
                [dirlistTree collapseItem:item];
        }
        else if (row == tiVarsRow)
        {
            [self doBackup:nil];
            didBackup = 1;
        }
        else
        {
            if ((flash_list == NULL) && (row < tiVarsRow))
            {
                // add to the flash_list
                add_item_to_selection_list(&flash_list, [dirlistTree itemAtRow:row]);
            }
            else if (didBackup == 0)
            {
                // add to the vars_list
                item = [dirlistTree itemAtRow:row];
                if ([NODE_DATA(item) isGroup] == YES)
                {
                    // add every var in the folder to the array
                    expanded = [dirlistTree isItemExpanded:item];
                    [dirlistTree expandItem:item];

                    foldItem = [dirlistTree itemAtRow:[dirlistTree rowForItem:item] + 1];
                    while ([NODE_DATA(foldItem) isGroup] == NO)
                    {
                        [vars addObject:foldItem];
                        foldItem = [dirlistTree itemAtRow:[dirlistTree rowForItem:foldItem] + 1];
                    }

                    if (expanded != YES)
                        [dirlistTree collapseItem:item];
                }
                else
                {
                    // add the var to the array if it's not alreay in
                    if ([vars containsObject:item] == NO)
                        [vars addObject:item];
                }
            }
        }
    }

    varsEnum = [vars objectEnumerator];

    while ((item = [varsEnum nextObject]) != nil)
        add_item_to_selection_list(&vars_list, item);
        
    ctree_win.selection = vars_list; 
  
    // Retrieve vars
    if (vars_list != NULL)
    {
        tilp_calc_recv_var();

        ctree_win.selection = NULL;
        g_list_free(vars_list);
    }

    // Retrieve FLASH Apps
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
render_screen_bw(uint8_t *bitmap, unsigned char *pixels, int scale)
{
    int row;
    int col;
    uint8_t data;
    int mask;
    int bit;
    int rs, cs;
    
    // speed things up : set a white (width *scale) * (height * scale) area (* 4 => 4 bytes per pixel)
    memset(pixels, 0xFF, (ti_screen.width * scale * ti_screen.height * scale * 4));

    for (row = 0; row < ti_screen.height; row++)
        for (rs = 0; rs < scale; rs++) // scaling for rows
            for (col = 0; col < (ti_screen.width >> 3); col++)
            {
                data = bitmap[(ti_screen.width >> 3) * row + col];
                mask = 0x80;
                for (bit = 0; bit < 8; bit++)
                {
                    if (data & mask) // black => set R/G/B/alpha to 0/0/0/0xFF
                    {
                        for (cs = 0; cs < scale; cs++) // scaling for columns
                        {
                            *pixels++ = 0; // red
                            *pixels++ = 0; // blue
                            *pixels++ = 0; // green
                            pixels++; // alpha, but already set to 0xFF
                        }
                    }
                    else // white => increment the pixels pointer
                        pixels += 4 * scale; // scaling for columns

                    mask >>= 1;
                }
            }
}

static void
render_screen_blurry(uint8_t *bitmap, unsigned char *pixels, int scale)
{
    int row;
    int col;
    uint8_t data;
    int mask;
    int bit;
    int rs, cs;

    for (row = 0; row < ti_screen.height; row++)
        for (rs = 0; rs < scale; rs++) // scaling for rows
            for (col = 0; col < (ti_screen.width >> 3); col++)
            {
                data = bitmap[(ti_screen.width >> 3) * row + col];
                mask = 0x80;
                for (bit = 0; bit < 8; bit++)
                {
                    if (data & mask) // black => set R/G/B to 0x00/0x00/0x34
                    {
                        for (cs = 0; cs < scale; cs++) // scaling for columns
                        {
                            *pixels++ = 0x00; // red
                            *pixels++ = 0x00; // blue
                            *pixels++ = 0x34; // green
                            *pixels++ = 0xFF; // alpha
                        }
                    }
                    else // white => set R/G/B to 0xA8/0xB4/0xA8
                    {
                        for (cs = 0; cs < scale; cs++) // scaling for columns
                        {
                            *pixels++ = 0xA8; // red
                            *pixels++ = 0xB4; // blue
                            *pixels++ = 0xA8; // green
                            *pixels++ = 0xFF; // alpha
                        }
                    }
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
                                       pixelsWide:(ti_screen.width * options.screen_scaling)
                                       pixelsHigh:(ti_screen.height * options.screen_scaling)
                                       bitsPerSample:8
                                       samplesPerPixel:4
                                       hasAlpha:YES
                                       isPlanar:NO
                                       colorSpaceName:NSDeviceRGBColorSpace
                                       bytesPerRow:0
                                       bitsPerPixel:0];

    // render the bitmap
    if (options.screen_blurry)
        render_screen_blurry(ti_screen.bitmap, [bitmap bitmapData], options.screen_scaling);
    else
        render_screen_bw(ti_screen.bitmap, [bitmap bitmapData], options.screen_scaling);

    size = NSMakeSize((ti_screen.width * options.screen_scaling), (ti_screen.height * options.screen_scaling));
    
    screen = [[NSImage alloc] initWithSize:size];
    
    [screen addRepresentation:bitmap];

    [screendumpImage setImage:screen];

// For now, always resize the window, until the resizing is handled
// by the NSImageView -- if it happens one day.

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

      if (options.screen_scaling > 1)
          [screendumpScale setStringValue:[NSString stringWithFormat:@"Screen scale : %d00%%", options.screen_scaling]];
      else
          [screendumpScale setStringValue:@""];

    if ([screendumpWindow isVisible] == NO)
    {
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

    // getVarsThreaded can call us with sender == nil
    // in which case we should open this dialog in the current directory
    if (sender != nil)
    {
        [sp beginSheetForDirectory:NSHomeDirectory()
                              file:[calcDict objectForKey:@"defaultBackupFilename"]
                    modalForWindow:[myBoxesController keyWindow]
                     modalDelegate:myBoxesController
                    didEndSelector:@selector(doBackupDidEnd:returnCode:contextInfo:)
                       contextInfo:sp];
    }
    else
    {
        [sp beginSheetForDirectory:[NSString stringWithCString:g_get_current_dir()]
                              file:[calcDict objectForKey:@"defaultBackupFilename"]
                    modalForWindow:[myBoxesController keyWindow]
                     modalDelegate:myBoxesController
                    didEndSelector:@selector(doBackupDidEnd:returnCode:contextInfo:)
                       contextInfo:sp];        
    }
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
