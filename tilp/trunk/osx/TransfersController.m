/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2002 Julien BLACHE <jb@technologeek.org>
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

#include "../src/cb_calc.h"
#include "../src/gui_indep.h"
#include "../src/intl.h"
#include "../src/defs.h"
#include "../src/cb_misc.h"
#include "../src/cb_calc.h"
#include "../src/error.h"

extern struct cocoa_objects_ptr *objects_ptr;

extern int is_active;

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
  
  cb_send_var();
  
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
    NSDictionary *calcDict;
    NSMutableDictionary *context;
    NSString *tmpfile;
    NSSavePanel *sp;
    id item;
    id foldItem;
    
    GList *vars_list = NULL;
    GList *flash_list = NULL;
    GList *l = NULL;
    
    struct varinfo *v = NULL;
    
    int result = -1;
    int tiVarsRow;
    int i, j, row;
    int vars_indexes[1024]; // I don't know if 1024 vars can be fitted on the TI, but :-)
    int flash_indexes[256];

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
                        cb_id_list();
                        break;
                    case 4: // keyboard item => do... I don't know
                        fprintf(stderr, "DEBUG: GET VARS => KEYBOARD ITEM, UNUSED\n");
                        break;
                    case 5: // FLASH Applications item => get each FLASH App
#if 0 // problems with savepanel and transfer
                        item = [dirlistTree itemAtRow:5];
                        
                        [dirlistTree expandItem:item];
                                          
                        foldItem = [dirlistTree itemAtRow:[dirlistTree rowForItem:item] + 1];
                  
                        while ([NODE_DATA(foldItem) isGroup] == NO)
                            {
                                v = (struct varinfo *)malloc(sizeof(struct varinfo));
                          
                                memcpy(v, [[NODE_DATA(foldItem) varinfo] varinfo], sizeof(struct varinfo));
                        
                                flash_list = g_list_append(flash_list, v);
                                                        
                                foldItem = [dirlistTree itemAtRow:[dirlistTree rowForItem:foldItem] + 1];
                            }
                            
                            ctree_win.selection2 = flash_list;
#endif
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
                        v = (struct varinfo *)malloc(sizeof(struct varinfo));
                          
                        memcpy(v, [[NODE_DATA(foldItem) varinfo] varinfo], sizeof(struct varinfo));
                        
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
                        v = (struct varinfo *)malloc(sizeof(struct varinfo));
                        
                        memcpy(v, [[NODE_DATA(item) varinfo] varinfo], sizeof(struct varinfo));
                  
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
        result = cb_recv_var();
  
    if (result >= 0)
        {
            calcDict = [myTilpController getCurrentCalcDict];

            sp = [NSSavePanel savePanel];

            if (result == 0)
                {
                    v = (struct varinfo *)ctree_win.selection->data;

                    [sp setRequiredFileType:[NSString stringWithCString:ti_calc.byte2fext(v->vartype)]];
                    [sp setTitle:@"Save variable as..."];

                    tmpfile = [NSString stringWithFormat:@"%s.%s", v->translate, ti_calc.byte2fext(v->vartype)];
                
                    context = [[NSMutableDictionary alloc] init];
                
                    [context setObject:sp forKey:@"savepanel"];
                    [context setObject:tmpfile forKey:@"tmpfile"];
                
                    [sp beginSheetForDirectory:NSHomeDirectory()
                        file:tmpfile 
                        modalForWindow:[myBoxesController keyWindow]
                        modalDelegate:myBoxesController
                        didEndSelector:@selector(getSingleVarDidEnd:returnCode:contextInfo:)
                        contextInfo:context];
                }
            else if (result > 0)
                {
                    [sp setRequiredFileType:[[calcDict objectForKey:@"extBackup"] lastObject]];
                    [sp setTitle:@"Save group file as..."];
                
                    context = [[NSMutableDictionary alloc] init];
                
                    [context setObject:sp forKey:@"savepanel"];
                
                    [sp beginSheetForDirectory:NSHomeDirectory()
                        file:[calcDict objectForKey:@"defaultGroupFilename"]
                        modalForWindow:[myBoxesController keyWindow]
                        modalDelegate:myBoxesController
                        didEndSelector:@selector(getVarsDidEnd:returnCode:contextInfo:)
                        contextInfo:context];
                }
        }
    ctree_win.selection = NULL;
    g_list_free(vars_list);
    
    // FLASH APPS HERE !
        
    if (flash_list != NULL)
        {
            l = flash_list;
        
            while (l != NULL)
                {
                    ctree_win.selection2 = g_list_alloc();
                    
                    ctree_win.selection2->data = l->data;
                    
                    if (cb_recv_app() == 0)
                        {
                            calcDict = [myTilpController getCurrentCalcDict];
        
                            sp = [NSSavePanel savePanel];
                        
                            v = (struct varinfo *)ctree_win.selection2->data;
                
                            [sp setRequiredFileType:[NSString stringWithCString:ti_calc.byte2fext(v->vartype)]];
                            [sp setTitle:@"Save FLASH Application as..."];
                
                            tmpfile = [NSString stringWithFormat:@"%s.%s", v->translate, ti_calc.byte2fext(v->vartype)];
                
                            context = [[NSMutableDictionary alloc] init];
                
                            [context setObject:sp forKey:@"savepanel"];
                            [context setObject:tmpfile forKey:@"tmpfile"];
                
                            [sp beginSheetForDirectory:NSHomeDirectory()
                                file:tmpfile 
                                modalForWindow:[myBoxesController keyWindow]
                                modalDelegate:myBoxesController
                                didEndSelector:@selector(getFlashAppDidEnd:returnCode:contextInfo:)
                                contextInfo:context];

                            l = l->next;
                        }
                }
                
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

            cb_send_flash_app(file);
            
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

    cb_send_flash_os(file);
            
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
    
    cb_send_backup(file);
            
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
- (void)getScreen:(id)sender
{
    // Ol, a big THANK YOU for this one

    NSImage *screen;
    NSBitmapImageRep *bitmap;
    NSSize size;
    
    int row;
    int col;

    unsigned char *pixels;
    byte *data;
    
    if ((is_active) || (cb_screen_capture() != 0) || (ti_screen.img.bitmap == NULL))
        return;

    if ([screendumpWindow isVisible] == NO)
        {
            [screendumpWindow makeKeyAndOrderFront:self];
            [NSApp addWindowsItem:screendumpWindow title:@"Screendump" filename:NO];
        }
        
    convert_bitmap_to_bytemap(&(ti_screen.img));
    
    bitmap = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:nil
                                       pixelsWide:ti_screen.img.width
                                       pixelsHigh:ti_screen.img.height
                                       bitsPerSample:8
                                       samplesPerPixel:4
                                       hasAlpha:YES
                                       isPlanar:NO
                                       colorSpaceName:NSDeviceRGBColorSpace
                                       bytesPerRow:0
                                       bitsPerPixel:0];
    
    pixels = [bitmap bitmapData];
    
    data = ti_screen.img.bytemap;

    // speed-up things : set a white width * height area (* 4 => 4 bytes per pixel)
    memset(pixels, 0xFF, (ti_screen.img.width * ti_screen.img.height * 4)); 

    for(row = 0; row < ti_screen.img.height; row++)
        {
            for(col = 0; col < ti_screen.img.width; col++)
                {
                    if (*data == 0xFF) // black => set R/G/B to 0
                        {
                            *pixels++ = 0; // red
                            *pixels++ = 0; // blue
                            *pixels++ = 0; // green
                            pixels++; // alpha, but already set to 0xFF
                        }
                    else // white, increment the pixels pointer
                        {
                            pixels += 4;
                        }
                    data++;
                }
        }

    size = NSMakeSize(ti_screen.img.width, ti_screen.img.height);
    
    screen = [[NSImage alloc] initWithSize:size];
    
    [screen addRepresentation:bitmap];
    
    [screendumpImage setImageFrameStyle:NSImageFrameGroove];

    [screendumpImage setImage:screen];
}

- (void)romDump:(id)sender
{
    NSSavePanel *sp;
    NSString *proposedFile;
    
    int ret;
    int err = 0;
    char *tmp_filename = NULL;
    
    FILE *dump = NULL;
    
    if (is_active)
        return;
 
    proposedFile = @"romdump.rom";
 
    tmp_filename = (char *)malloc(strlen(g_get_tmp_dir()) + strlen(TMPFILE_ROMDUMP) + 2);
 
    strcpy(tmp_filename, g_get_tmp_dir());
    strcat(tmp_filename, G_DIR_SEPARATOR_S);
    strcat(tmp_filename, TMPFILE_ROMDUMP);
 
    ret = gif->user2_box(_("Warning"), 
                         _("An assembly program will be sent to your calc if you decide to continue. Consider doing a backup before."),
                         _("Proceed"), 
                         _("Cancel"));
    if(ret != BUTTON1)
        return;
  
    switch(options.lp.calc_type)
        {
            case CALC_TI83:
            case CALC_TI83P:
                ret = gif->user2_box(_("Information"), 
                                     _("An assembly program is needed to perform a ROM dump. You must AShell installed on your calc to run this program.\nTiLP will transfer the ROM dump program on your calc, then wait until you run it on your calc."),
                                     _("Proceed"), 
                                     _("Cancel"));
                switch(ret)
                    {
                        case BUTTON1:
                            gif->create_pbar_type5(_("ROM dump"), 
                                                   _("Receiving bytes"));
                                                   
                            do
                                {
                                    if(info_update.cancel)
                                        break;
                                        
                                    err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
                                    
                                    if(tilp_error(err))
                                        return;
                                    
                                    err = ti_calc.dump_rom(dump, ret);
                                    fclose(dump);
                                }
                            while((err == ERR_RCV_BYT_TIMEOUT) || (err == ERR_RCV_BIT_TIMEOUT));
                                                   
                            destroy_pbar();
                            if(tilp_error(err))
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
                                    
                            break;
                        default:
                            return; 
                    }
                break;
            case CALC_TI85:
                ret = gif->user2_box(_("Information"), 
                                     _("An assembly program is needed to perform a ROM dump. You must have ZShell or Usgard installed on your calc to run this program.\nTiLP will transfer the ROM dump program on your calc, then wait until you run this program."),
                                     _("Proceed"), 
                                     _("Cancel"));
                switch(ret)
                    {	
                        case BUTTON1:
                            ret = gif->user3_box(_("Shell type"), 
                                                 _("Select a shell"), 
                                                 _("ZShell"), _("Usgard"), _("Cancel"));
                            if(ret == 3)
                                return;
                            else	
                                {
                                    gif->create_pbar_type5(_("ROM dump"), 
                                                           _("Receiving bytes"));
                                                           
                                    do
                                        {
                                            if(info_update.cancel)
                                                break;
                                            
                                            err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
                                            
                                            if(tilp_error(err))
                                                return;
                                            
                                            err = ti_calc.dump_rom(dump, (ret == 1) ? SHELL_ZSHELL : SHELL_USGARD);
                                            fclose(dump);
                                        }
                                    while((err == ERR_RCV_BYT_TIMEOUT) || (err == ERR_RCV_BIT_TIMEOUT));
	      
                                    destroy_pbar();
                                    if(tilp_error(err))
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
                            break;	
                        default:
                            return; 
                    }
                break;
            case CALC_TI86:
                ret = gif->user2_box(_("Information"), 
                                     _("An assembly program is required to perform a ROM dump. You must have a shell installed on your calculator to run this program.\nTiLP will transfer this program on your calc, then wait until you run it."),
                                     _("Procced"), 
                                     _("Cancel"));
                switch(ret)
                    {
                        case BUTTON1:
                            gif->create_pbar_type5(_("ROM dump"), 
                                                   _("Receiving bytes"));
                                                   
                            do
                                {
                                    if(info_update.cancel)
                                        break;
                                        
                                    err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
                                    
                                    if(tilp_error(err))
                                        return;
                                    
                                    err = ti_calc.dump_rom(dump, ret);
                                    
                                    fclose(dump);
                                }
                            while((err == ERR_RCV_BYT_TIMEOUT) || (err == ERR_RCV_BIT_TIMEOUT));

                            destroy_pbar();
                            if(tilp_error(err))
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

                            break;
                        default:
                            return; 
                    }
                break;
            case CALC_TI89:
            case CALC_TI92P:
                gif->create_pbar_type5(_("ROM dump"), 
                                       _("Receiving bytes"));
                                       
                do
                    {
                        if(info_update.cancel)
                            break;
                            
                        err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
                        
                        if(tilp_error(err))
                            return;
                            
                        err = ti_calc.dump_rom(dump, ret);
                        
                        fclose(dump);
                    }
                while( ((err == ERR_RCV_BYT_TIMEOUT) || (err == ERR_RCV_BIT_TIMEOUT)) );

                destroy_pbar();
                if(tilp_error(err))
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

                break;
            case CALC_TI92:
                ret = gif->user2_box(_("Information"), 
                                     _("The FargoII shell must be installed on your calc to perform a ROM dump."),
                                     _("Proceed"), 
                                     _("Cancel"));
                switch(ret)
                    {
                        case BUTTON1:
                            ret = gif->user3_box(_("ROM size"), 
                                                 _("Select the size of your ROM or cancel"), 
                                                 _("1Mb"), _("2 Mb"), _("Cancel"));
                        if(ret == 3)
                            return;
                        else
                            {
                                printf(_("ROM size: %i Mb\n"), ret);
                                gif->create_pbar_type5(_("ROM dump"), 
                                                       _("Receiving bytes"));
                                                    
                                do
                                    {
                                        if(info_update.cancel)
                                            break;
                                        
                                        err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
                                        
                                        if(tilp_error(err))
                                            return;
                                            
                                        err=ti_calc.dump_rom(dump, ret);
                                        
                                        fclose(dump);
                                    }
                                while((err == ERR_RCV_BYT_TIMEOUT) || (err == ERR_RCV_BIT_TIMEOUT));

                                destroy_pbar();
                                if(tilp_error(err))
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
                        break;
                    default: 
                        return;
                    }
                break;
            default:
                DISPLAY(_("Unsupported ROM dump\n"));
                break;
        }
}

- (void)doBackup:(id)sender
{
    NSSavePanel *sp;
    NSDictionary *calcDict;
    
    if (is_active)
        return;
    
    if (cb_recv_backup() != 0)
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

- (int)sendChar:(unsigned int)tikey
{
#ifdef OSX_DEBUG
    fprintf(stderr, "DEBUG: sending '%c' (%d)\n", tikey, tikey);
#endif

    if (tilp_error(ti_calc.send_key(tikey)))
        return -1;
        
    return tikey;
}

@end
