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
  
#include <unistd.h>

#include <libticalcs/calc_def.h>
#include <libticalcs/ti92.h>

#include "../src/tilp_core.h"
#include "../src/tilp_struct.h"
#include "../src/tilp_indep.h"
#include "../src/tilp_defs.h"
#include "../src/intl.h"

#include "cocoa_structs.h"

#import "BoxesController.h"
#import "TransfersController.h"

extern struct cocoa_objects_ptr *objects_ptr;

@implementation BoxesController

- (void)awakeFromNib
{
#ifdef OSX_DEBUG
    fprintf(stderr, "boxes => got awakeFromNib\n");
#endif

    // Init the instance pointer
    objects_ptr->myBoxesController = self;
}


- (id)keyWindow
{
    if ([NSApp keyWindow] != nil)
        return [NSApp keyWindow];
    else
    {
        if ([mainWindow isVisible])
            return mainWindow;
        else
        {
            [mainWindow makeKeyAndOrderFront:self];

            return mainWindow;
        }
    }
}

// obsolete
- (void)user1ButtonPush:(id)sender
{
    objects_ptr->user1_return = BUTTON1;
    
    [NSApp stopModal];
}

- (void)user2ButtonPush:(id)sender
{
    if (sender == user2Button1)
        objects_ptr->user2_return = BUTTON1;
    else if (sender == user2Button2)
        objects_ptr->user2_return = BUTTON2;
        
    [NSApp stopModal];
}

- (void)user3ButtonPush:(id)sender
{
    if (sender == user3Button1)
        objects_ptr->user3_return = BUTTON1;
    else if (sender == user3Button2)
        objects_ptr->user3_return = BUTTON2;
    else if (sender == user3Button3)
        objects_ptr->user3_return = BUTTON3;
        
    [NSApp stopModal];
}

- (IBAction)dlgboxentryButton1Push:(id)sender
{
    id data;
    
    if (objects_ptr->dlgbox_data != nil)
        {
            data = objects_ptr->dlgbox_data;
            [data release];
        }

    data = [dlgboxentryEntry stringValue];
    [data retain];
    
    objects_ptr->dlgbox_data = data;
    
    [dlgboxentryEntry setStringValue:nil];
    
    [NSApp stopModal];
}

- (IBAction)dlgboxentryButton2Push:(id)sender
{
    if (objects_ptr->dlgbox_data != NULL)
        {
            free(objects_ptr->dlgbox_data);
            
            objects_ptr->dlgbox_data = NULL;
        }
    
    [dlgboxentryWindow close];
    
    [dlgboxentryEntry setStringValue:nil];
    
    [NSApp stopModal];
}

- (IBAction)pbarButtonPush:(id)sender
{
    // the sheet will be closed by calling gif->destroy_pbar();
#ifdef OSX_DEBUG
    fprintf(stderr, "*** ABORT BUTTON PUSHED !!! ***\n");
#endif
    info_update.cancel = 1;
    
    // but if it's a pbar type 2, ...
    if (sender == pbar2Button)
        [NSApp stopModal];
}

- (IBAction)screendumpSaveImage:(id)sender
{
    NSSavePanel *sp;
    NSString *proposedFile;

    sp = [NSSavePanel savePanel];

    switch (options.screen_format)
        {
            case TIFF:
                [sp setRequiredFileType:@"tiff"];
                [sp setTitle:@"Save screen as TIFF"];
                proposedFile = @"screendump.tiff";
                break;
            case PDF:
                [sp setRequiredFileType:@"pdf"];
                [sp setTitle:@"Save screen as PDF"];
                proposedFile = @"screendump.pdf";
                break;
            default: // just in case...
                return;
        }

    [sp setPrompt:@"Save"];
    
    [sp beginSheetForDirectory:NSHomeDirectory()
        file:proposedFile
        modalForWindow:screendumpWindow
        modalDelegate:self
        didEndSelector:@selector(screendumpSaveImageDidEnd:returnCode:contextInfo:)
        contextInfo:sp];
}


// NSOpenPanels callbacks

- (void)doRestoreDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSArray *files;
    
    [sheet orderOut:self];
    
    if (returnCode == NSOKButton)
        {
            files = [[NSArray arrayWithArray:[sheet filenames]] retain];
            
            [NSThread detachNewThreadSelector:@selector(doRestoreThreaded:)
                      toTarget:myTransfersController
                      withObject:files];
        }
}


- (void)sendFlashAppDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSArray *files;

    [sheet orderOut:self];

    if (returnCode == NSOKButton)
        {            
            files = [[NSArray arrayWithArray:[sheet filenames]] retain];
            
            [NSThread detachNewThreadSelector:@selector(sendFlashAppThreaded:)
                      toTarget:myTransfersController
                      withObject:files];
        }
}

- (void)sendAMSDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSArray *files;
    
    [sheet orderOut:self];
    
    if (returnCode == NSOKButton)
        {
            files = [[NSArray arrayWithArray:[sheet filenames]] retain];
            
            [NSThread detachNewThreadSelector:@selector(sendAMSThreaded:)
                      toTarget:myTransfersController
                      withObject:files];
        }
}

- (void)getVarsDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSArray *files;

    [sheet orderOut:self];

    if (returnCode == NSOKButton)
    {
        files = [[NSArray arrayWithArray:[sheet filenames]] retain];

        if (options.working_dir != NULL)
            free(options.working_dir);

        options.working_dir = strdup([[files objectAtIndex:0] fileSystemRepresentation]);
        tilp_chdir(options.working_dir);

        [NSThread detachNewThreadSelector:@selector(getVarsThreaded:)
                                 toTarget:myTransfersController
                               withObject:self];
    }
}


// NSSavePanels callbacks

- (void)screendumpSaveImageDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSData *imageData;
    NSSavePanel *sp; // sheet is an NSWindow, which does not sound very logical
                     // compared to the NSOpenPanel, so I'm passing sp as the contextInfo
    if (returnCode == NSOKButton)
        {
            sp = contextInfo;
              
            switch (options.screen_format)
                {
                    case TIFF:
                        imageData = [[screendumpImage image] TIFFRepresentation];
                        break;
                    case PDF: // Quartz roulaize (tm)
                        imageData = [screendumpImage dataWithPDFInsideRect:[screendumpImage visibleRect]];
                        break;
                    default:
                        break;
                }
            [imageData writeToFile:[sp filename] atomically:YES];
        }
}

- (void)getVarsGroupDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSSavePanel *sp;

    char *file;
    char *tmpfile;

    tmpfile = (char *)malloc(strlen(g_get_tmp_dir()) + strlen(TMPFILE_GROUP) + 2);

    strcpy(tmpfile, g_get_tmp_dir());
    strcat(tmpfile, G_DIR_SEPARATOR_S);
    strcat(tmpfile, TMPFILE_GROUP);

    if (returnCode == NSOKButton)
    {
        sp = contextInfo;

        file = strdup([[sp filename] fileSystemRepresentation]);

        if(tilp_file_move(tmpfile, file))
            gif->msg_box(_("Error"), _("Unable to move the temporary file.\n"));
    }
    else
        if(unlink(tmpfile))
            fprintf(stdout, _("Unable to remove the temporary file.\n"));
}

- (void)doBackupDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSSavePanel *sp;
    
    char *file;
    char *tmpfile;
    
    tmpfile = (char *)malloc(strlen(g_get_tmp_dir()) + strlen(TMPFILE_BACKUP) + 2);
            
    strcpy(tmpfile, g_get_tmp_dir());
    strcat(tmpfile, G_DIR_SEPARATOR_S);
    strcat(tmpfile, TMPFILE_BACKUP);
    
    if (returnCode == NSOKButton)
        {
            sp = contextInfo;
                              
            file = strdup([[sp filename] fileSystemRepresentation]);

            if(tilp_file_move(tmpfile, file))
                gif->msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
        }
    else
        if(unlink(tmpfile))
            fprintf(stdout, _("Unable to remove the temporary file.\n"));
}

- (void)romDumpDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSSavePanel *sp;
    
    char *file;
    char *tmpfile;
    
    tmpfile = (char *)malloc(strlen(g_get_tmp_dir()) + strlen(TMPFILE_ROMDUMP) + 2);
            
    strcpy(tmpfile, g_get_tmp_dir());
    strcat(tmpfile, G_DIR_SEPARATOR_S);
    strcat(tmpfile, TMPFILE_ROMDUMP);
    
    if (returnCode == NSOKButton)
        {
            sp = contextInfo;
                              
            file = strdup([[sp filename] fileSystemRepresentation]);

            if(tilp_file_move(tmpfile, file))
                gif->msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
        }
    else
        if(unlink(tmpfile))
            fprintf(stdout, _("Unable to remove the temporary file.\n"));
}

@end
