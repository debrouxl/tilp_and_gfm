/*
 * TiLP Cocoa GUI for Mac OS X
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

extern struct cocoa_objects_ptr *objects_ptr;
extern struct cocoa_pbars_ptr *pbars_ptr;

extern struct screenshot ti_screen;
extern struct ticalc_info_update info_update;

extern int is_active;

@implementation BoxesController

- (void)awakeFromNib
{
    fprintf(stderr, "boxes => got awakeFromNib\n");

    objects_ptr->dlgboxentryWindow = dlgboxentryWindow;
    objects_ptr->dlgboxentryEntry = dlgboxentryEntry;
    objects_ptr->dlgboxentryText = dlgboxentryText;

    // that's ugly :-/

    pbars_ptr->pbar1Window = pbar1Window;
    pbars_ptr->pbar2Window = pbar2Window;
    pbars_ptr->pbar3Window = pbar3Window;
    pbars_ptr->pbar4Window = pbar4Window;
    pbars_ptr->pbar5Window = pbar5Window;
    
    pbars_ptr->pbar1PBar = pbar1PBar;
    pbars_ptr->pbar3PBar1 = pbar3PBar1;
    pbars_ptr->pbar3PBar2 = pbar3PBar2;
    pbars_ptr->pbar4PBar = pbar4PBar;
    pbars_ptr->pbar5PBar1 = pbar5PBar1;
    pbars_ptr->pbar5PBar2 = pbar5PBar2;
    
    pbars_ptr->pbar1Rate = pbar1Rate;
    pbars_ptr->pbar3Rate = pbar3Rate;
    pbars_ptr->pbar4Rate = pbar4Rate;
    pbars_ptr->pbar5Rate = pbar5Rate;
    
    pbars_ptr->pbar2Text = pbar2Text;
    pbars_ptr->pbar4Text = pbar4Text;
    pbars_ptr->pbar5Text = pbar5Text;

    pbars_ptr->pbar1 = nil;
    pbars_ptr->pbar2 = nil;
    
    pbars_ptr->pbar_text = nil;
    pbars_ptr->pbar_rate = nil;
        
    objects_ptr->user1Window = user1Window;
    objects_ptr->user1Text = user1Text;
    objects_ptr->user1Button = user1Button;
    
    objects_ptr->user2Window = user2Window;
    objects_ptr->user2Text = user2Text;
    objects_ptr->user2Button1 = user2Button1;
    objects_ptr->user2Button2 = user2Button2;

    objects_ptr->user3Window = user3Window;
    objects_ptr->user3Text = user3Text;
    objects_ptr->user3Button1 = user3Button1;
    objects_ptr->user3Button2 = user3Button2;
    objects_ptr->user3Button3 = user3Button3;
        
    objects_ptr->remoteControlWindow = remoteControlWindow;
    objects_ptr->remoteControlTextArea = remoteControlTextArea;
    objects_ptr->term_mode = REMOTE;
}

#if defined(USE_SHEETS)
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
#endif

- (IBAction)dlgboxentryButton1Push:(id)sender
{
    NSString *data;
    
    data = [dlgboxentryEntry stringValue];
    
    if (objects_ptr->dlgbox_data != NULL)
        {
            free(objects_ptr->dlgbox_data);
            
            objects_ptr->dlgbox_data = NULL;
        }
    
    objects_ptr->dlgbox_data = (char *)malloc([data cStringLength] + 1);
    
    [data getCString:objects_ptr->dlgbox_data];
    
    [data release];
    
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

    fprintf(stderr, "*** ABORT BUTTON PUSHED !!! ***\n");

    info_update.cancel = 1;
    
    // but if it's a pbar type 2, ...
    if (sender == pbar2Button)
        [NSApp stopModal];
}

- (IBAction)remoteControlChangeMode:(id)sender
{
    // FIXME OS X
    // fix the help text wrt the special key combos
      
    if ((sender == remoteControlRemoteMode) && (objects_ptr->term_mode != REMOTE))
        {
            // leaving terminal mode
            ti_calc.send_key(KEY92_F5);
            ti_calc.send_key(KEY92_CTRL);
            ti_calc.send_key(KEY92_LP);
            ti_calc.send_key(KEY92_r);
        
            [remoteControlTerminalMode setState:NSOffState];
            
            objects_ptr->term_mode = REMOTE;
            
            [remoteControlTextArea setStringValue:@"\nYou are in remote control mode.\nPress any key but for:\n- Shift, press the left Shift key\n- diamond, press the left Ctrl key\n- 2nd, press the right Alt key\n- APPS, press the F9 key\n- STO, press the F10 key\n- MODE, press the F11 key\n- CLEAR, press the F12 key\n- (-) negative, press the right enter key\nPlease click the text window to focus it.\n\n"];
        }
    else if ((sender == remoteControlTerminalMode) && (objects_ptr->term_mode != TERM))
        {
            [remoteControlRemoteMode setState:NSOffState];
            
            objects_ptr->term_mode = TERM;
            
            [remoteControlTextArea setStringValue:@"\nYou are in terminal mode.\nPress any key but for:\n- Shift, press the left Shift key\n- diamond, press the left Ctrl key\n- 2nd, press the right Alt key\n- APPS, press the F9 key\n- STO, press the F10 key\n- MODE, press the F11 key\n- CLEAR, press the F12 key\n- (-) negative, press the right enter key\nPlease click the text window to focus it.\n\n"];
            
            // entering terminal mode
            ti_calc.send_key(KEY92_F5);
            ti_calc.send_key(KEY92_CTRL);
            ti_calc.send_key(KEY92_LP);
            ti_calc.send_key(KEY92_r);
        }
}

- (IBAction)remoteControlTextEntered:(id)sender
{
    // FIXME OS X : fscking GTK-dependant code detected...
    // this is not a tricky one... hmm... maybe it is.
    // according to gtk_term_cb.c, we must send each key pressed
    // to the calc... I wonder how I'm going to reimplement this.
    // maybe it's tricky, maybe it's not...
    
    // this method would in fact be a delegate of the NSTextField
    // ==>> textDidChange I believe
    
    // Oh, I just remembered we also need to match some keys
    // to access other TI functions (Apps, etc...)
    // It's gonna be funny...
    // See NSEvent keyDown.
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
    NSString *nsfile;
    char *file;
    
    if (returnCode == NSOKButton)
        {
            nsfile = [[sheet filenames] objectAtIndex:0];
            
            file = (char *)malloc([nsfile cStringLength] + 1);
            
            [nsfile getCString:file];
            
            cb_send_backup(file);
                    
            [nsfile release];
            
            free(file);
        }
}


- (void)sendFlashAppDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSString *nsfile;
    char *file;

    if (returnCode == NSOKButton)
        {
            nsfile = [[sheet filenames] objectAtIndex:0];
            
            file = (char *)malloc([nsfile cStringLength] + 1);
            
            [nsfile getCString:file];
            
            cb_send_flash_app(file);
            
            [nsfile release];
            
            free(file);
        }
}

- (void)sendAMSDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    NSString *nsfile;
    char *file;

     if (returnCode == NSOKButton)
        {
            nsfile = [[sheet filenames] objectAtIndex:0];
            
            file = (char *)malloc([nsfile cStringLength] + 1);
            
            [nsfile getCString:file];
            
            cb_send_flash_os(file);
            
            [nsfile release];
            
            free(file);
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
        
            file = (char *)malloc([[sp filename] cStringLength] + 1);
            [[sp filename] getCString:file];
            
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
                              
            file = (char *)malloc([[sp filename] cStringLength] + 1);
            [[sp filename] getCString:file];

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
                              
            file = (char *)malloc([[sp filename] cStringLength] + 1);
            [[sp filename] getCString:file];

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

@end
