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
  
#include <unistd.h>

#include <libticalcs/defs92.h>

#include "../src/cb_calc.h"
#include "../src/files.h"
#include "../src/struct.h"
#include "../src/gui_indep.h"
#include "../src/defs.h"
#include "../src/intl.h"

#include "cocoa_structs.h"

#import "BoxesController.h"
#import "Calc89KeyboardController.h"
#import "Calc92KeyboardController.h"

extern struct cocoa_objects_ptr *objects_ptr;

extern struct screenshot ti_screen;
extern struct ticalc_info_update info_update;

extern int is_active;

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
        {
            return [NSApp keyWindow];
        }
    else
        {
            if ([mainWindow isVisible])
                {
                    return mainWindow;
                }
            else
                {
                    [mainWindow makeKeyAndOrderFront:self];
                    
                    return mainWindow;
                }
        }
}

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
            case PCX:
                [sp setRequiredFileType:@"pcx"];
                [sp setTitle:@"Save screen as PCX"];
                proposedFile = @"screendump.pcx";
                break;
            case XPM:
                [sp setRequiredFileType:@"xpm"];
                [sp setTitle:@"Save screen as XPM"];
                proposedFile = @"screendump.xpm";
                break;
        }
        
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


// NSSavePanels callbacks

- (void)screendumpSaveImageDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSData *tiff;
    NSSavePanel *sp; // sheet is an NSWindow, which does not sound very logical
                     // compared to the NSOpenPanel, so I'm passing sp as the contextInfo

    char *file;

    if (returnCode == NSOKButton)
        {
            sp = contextInfo;
        
            file = strdup([[sp filename] fileSystemRepresentation]);
              
            switch (options.screen_format)
                {
                    case TIFF:
                        tiff = [[screendumpImage image] TIFFRepresentation];
                        [tiff writeToFile:[sp filename] atomically:YES];
                        break;
                    case PCX:
                        cb_screen_save(file);
                        break;
                    case XPM:
                        cb_screen_save(file);
                        break;
                }
            free(file);
        }
}

- (void)doBackupDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSSavePanel *sp;
    
    char *file;
    char *tmpfile;
    int ret;
    int skip = 0;
    
    gchar buffer[MAXCHARS];
    gchar *dirname;
    
    tmpfile = (char *)malloc(strlen(g_get_tmp_dir()) + strlen("/tilp.backup") + 1);
            
    strcpy(tmpfile, g_get_tmp_dir());
    strcat(tmpfile, "/tilp.backup");
    
    if (returnCode == NSOKButton)
        {
            sp = contextInfo;
                              
            file = strdup([[sp filename] fileSystemRepresentation]);

            if(options.confirm == CONFIRM_YES)
                {
                    if(access(file, F_OK) == 0)
                        {
                            sprintf(buffer, _("The file %s already exists.\n\n"),
                                            file);
                            
                            ret = gif->user3_box(_("Warning"), buffer,
                                                 _("Overwrite"), _("Rename"),
                                                 _("Skip"));
                            switch(ret)	
                                {
                                    case BUTTON2:
                                        dirname = gif->dlgbox_entry(_("Rename the file"),
                                                                    _("New name : "), file);
                                        if(dirname == NULL) return;
                                        free(file);
                                        file = (char *)malloc(strlen(dirname) + 1);
                                        strcpy(file, dirname);
                                        g_free(dirname);
                                        break;
                                    case BUTTON1:
                                        skip=0;
                                        break;
                                    case BUTTON3:
                                        skip=1;
                                        break;
                                    default:
                                        break;
                                }
                        }
                }
                
            if(skip == 0)
                {
                    if(move_file(tmpfile, file))
                        {	
                            gif->msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
                        }
                }
        }
    else
        {
            if(unlink(tmpfile))
                {
                    fprintf(stdout, _("Unable to remove the temporary file.\n"));
                }
        }
}

- (void)romDumpDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSSavePanel *sp;
    
    char *file;
    char *tmpfile;
    int ret;
    int skip = 0;
    
    gchar buffer[MAXCHARS];
    gchar *dirname;
    
    tmpfile = (char *)malloc(strlen(g_get_tmp_dir()) + strlen("/tilp.ROMdump") + 1);
            
    strcpy(tmpfile, g_get_tmp_dir());
    strcat(tmpfile, "/tilp.ROMdump");
    
    if (returnCode == NSOKButton)
        {
            sp = contextInfo;
                              
            file = strdup([[sp filename] fileSystemRepresentation]);

            if(options.confirm == CONFIRM_YES)
                {
                    if(access(file, F_OK) == 0)
                        {
                            sprintf(buffer, _("The file %s already exists.\n\n"),
                                            file);
                            
                            ret = gif->user3_box(_("Warning"), buffer,
                                                 _("Overwrite"), _("Rename"),
                                                 _("Skip"));
                            switch(ret)	
                                {
                                    case BUTTON2:
                                        dirname = gif->dlgbox_entry(_("Rename the file"),
                                                                    _("New name : "), file);
                                        if(dirname == NULL) return;
                                        free(file);
                                        file = (char *)malloc(strlen(dirname) + 1);
                                        strcpy(file, dirname);
                                        g_free(dirname);
                                        break;
                                    case BUTTON1:
                                        skip=0;
                                        break;
                                    case BUTTON3:
                                        skip=1;
                                        break;
                                    default:
                                        break;
                                }
                        }
                }
                
            if(skip == 0)
                {
                    if(move_file(tmpfile, file))
                        {	
                            gif->msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
                        }
                }
        }
    else
        {
            if(unlink(tmpfile))
                {
                    fprintf(stdout, _("Unable to remove the temporary file.\n"));
                }
        }
}

- (void)getSingleVarDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSSavePanel *sp;
    NSString *mytmpfile;
    NSMutableDictionary *context;
    
    char *file;
    char *tmpfile;
    int ret;
    int skip = 0;
    
    gchar buffer[MAXCHARS];
    gchar *dirname;
    
    context = contextInfo;
    
    mytmpfile = [context objectForKey:@"tmpfile"];
    
    tmpfile = (char *)malloc((strlen(g_get_tmp_dir()) + [mytmpfile cStringLength] + 2) * sizeof(char));
            
    strcpy(tmpfile, g_get_tmp_dir());
    strcat(tmpfile, "/");
    strcat(tmpfile, [mytmpfile cString]);
    
    if (returnCode == NSOKButton)
        {
            sp = [context objectForKey:@"savepanel"];
                              
            file = strdup([[sp filename] fileSystemRepresentation]);
 
            if(options.confirm == CONFIRM_YES)
                {
                    if(access(file, F_OK) == 0)
                        {
                            sprintf(buffer, _("The file %s already exists.\n\n"),
                                            file);
                            
                            ret = gif->user3_box(_("Warning"), buffer,
                                                 _("Overwrite"), _("Rename"),
                                                 _("Skip"));
                            switch(ret)	
                                {
                                    case BUTTON2:
                                        dirname = gif->dlgbox_entry(_("Rename the file"),
                                                                    _("New name : "), file);
                                        if (dirname == NULL)
                                            return;
                                        
                                        free(file);
                                        file = (char *)malloc(strlen(dirname) + 1);
                                        strcpy(file, dirname);
                                        g_free(dirname);
                                        break;
                                    case BUTTON1:
                                        skip=0;
                                        break;
                                    case BUTTON3:
                                        skip=1;
                                        break;
                                    default:
                                        break;
                                }
                        }
                }
                
            if(skip == 0)
                {
                    if(move_file(tmpfile, file))
                        {	
                            gif->msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
                        }
                }
        }
    else
        {
            if(unlink(tmpfile))
                {
                    fprintf(stdout, _("Unable to remove the temporary file.\n"));
                }
        }
}

- (void)getVarsDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSSavePanel *sp;
    NSMutableDictionary *context;
    
    char *file;
    char *tmpfile;
    int ret;
    int skip = 0;
    
    gchar buffer[MAXCHARS];
    gchar *dirname;
    
    context = contextInfo;

    tmpfile = (char *)malloc(strlen(g_get_tmp_dir()) + strlen("/tilp.PAK") + 1);
            
    strcpy(tmpfile, g_get_tmp_dir());
    strcat(tmpfile, "/tilp.PAK");
    
    if (returnCode == NSOKButton)
        {
            sp = [context objectForKey:@"savepanel"];
                              
            file = strdup([[sp filename] fileSystemRepresentation]);

            if(options.confirm == CONFIRM_YES)
                {
                    if(access(file, F_OK) == 0)
                        {
                            sprintf(buffer, _("The file %s already exists.\n\n"),
                                            file);
                            
                            ret = gif->user3_box(_("Warning"), buffer,
                                                 _("Overwrite"), _("Rename"),
                                                 _("Skip"));
                            switch(ret)	
                                {
                                    case BUTTON2:
                                        dirname = gif->dlgbox_entry(_("Rename the file"),
                                                                    _("New name : "), file);
                                        if (dirname == NULL)
                                            return;
                                            
                                        free(file);
                                        file = (char *)malloc(strlen(dirname) + 1);
                                        strcpy(file, dirname);
                                        g_free(dirname);
                                        break;
                                    case BUTTON1:
                                        skip=0;
                                        break;
                                    case BUTTON3:
                                        skip=1;
                                        break;
                                    default:
                                        break;
                                }
                        }
                }
                
            if(skip == 0)
                {
                    if(move_file(tmpfile, file))
                        {	
                            gif->msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
                        }
                }
        }
    else
        {
            if(unlink(tmpfile))
                {
                    fprintf(stdout, _("Unable to remove the temporary file.\n"));
                }
        }
}

@end
