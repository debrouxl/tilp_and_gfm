#include "../src/cb_calc.h"
#include "../src/struct.h"

#include "cocoa_structs.h"

#include "../src/defs.h"
#include "../src/cb_calc.h"

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

    // that's ugly :-/

    pbars_ptr->pbar1Window = pbar1Window;
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
    
    pbars_ptr->pbar4Text = pbar4Text;
    pbars_ptr->pbar5Text = pbar5Text;

    pbars_ptr->pbar1 = nil;
    pbars_ptr->pbar2 = nil;
    
    pbars_ptr->pbar_text = nil;
    pbars_ptr->pbar_rate = nil;
    
    pbars_ptr->finished = 0;
    
    objects_ptr->remoteControlWindow = remoteControlWindow;
    objects_ptr->remoteControlTextArea = remoteControlTextArea;
    objects_ptr->term_mode = REMOTE;
}

- (void)pbarType2DidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
    info_update.cancel = 1;
}

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
    
    [dlgboxentryWindow close];
    
    [NSApp stopModal];
}

- (IBAction)dlgboxentryButton2Push:(id)sender
{
    if (objects_ptr->dlgbox_data != NULL)
        {
            free(objects_ptr->dlgbox_data);
            
            objects_ptr->dlgbox_data = NULL;
        }
    
    [dlgboxentryEntry setStringValue:nil];
    
    [dlgboxentryWindow close];
    
    [NSApp stopModal];

}

- (IBAction)pbarButtonPush:(id)sender
{
    // the sheet will be closed by calling gif->destroy_pbar();

    info_update.cancel = 1;
    pbars_ptr->finished = 1;
}

- (IBAction)remoteControlChangeMode:(id)sender
{
    // FIXME OS X
    // set an 'int mode;' variable
    // then print the help text corresponding to the mode...
    // BEWARE OF THESE FSCINK RADIO BUTTONS !@# !!
    // see gtk_term_cb.c
}

- (IBAction)remoteControlTextEntered:(id)sender
{
    // FIXME OS X : fscking GTK-dependant code detected...
    // this is not a tricky one... hmm... maybe it is.
    // according to gtk_term_cb.c, we must send each key pressed
    // to the calc... I wonder how I'm going to reimplement this.
    // maybe it's tricky, maybe it's not...
    
    // this method would in fact be a delegate of the NSTextField
    // I fear I'll have to get a complete string
    // and then do a loop to send each byte to the calc
    // no, no, it's not ugly...
    // => textDidEndEditing...
    
    // Oh, I just remembered we also need to match some keys
    // to access other TI functions (Apps, etc...)
    // It's gonna be funny...
}

- (IBAction)screendumpRefresh:(id)sender
{
    NSData *bitmap;
    NSImage *screen;

    if (is_active)
        return;

    if (cb_screen_capture() != 0)
        return;
    
    [screendumpWindow makeKeyAndOrderFront:self];
    
    bitmap = [[NSData alloc] initWithBytes:ti_screen.img.bitmap length:strlen(ti_screen.img.bitmap)];
    [bitmap autorelease];
    
    screen = [[NSImage alloc] initWithData:bitmap];
    [screen autorelease];
    
    [screendumpImage setImage:screen];
}

- (IBAction)screendumpSaveImage:(id)sender
{
    NSSavePanel *sp;
    NSData *tiff;
    
    int result;
    char *filename;
    
    sp = [NSSavePanel savePanel];

    switch (options.screen_format)
        {
            case TIFF:
                [sp setRequiredFileType:@"tiff"];
                [sp setTitle:@"Save screen as TIFF"];
                break;
            case PCX:
                [sp setRequiredFileType:@"pcx"];
                [sp setTitle:@"Save screen as PCX"];
                break;
            case XPM:
                [sp setRequiredFileType:@"xpm"];
                [sp setTitle:@"Save screen as XPM"];
                break;
        }
        
    result = [sp runModalForDirectory:NSHomeDirectory() file:@""];
    
    if (result == NSOKButton)
        {
            filename = (char *)malloc([[sp filename] cStringLength] + 1);
            [[sp filename] getCString:filename];
            
            switch (options.screen_format)
                {
                    case TIFF: // FIXME OS X : dunno if it's the right way...
                        tiff = [[screendumpImage image] TIFFRepresentation];
                        [tiff writeToFile:[sp filename] atomically:YES];
                        break;
                    case PCX:
                        cb_screen_save(filename);
                        break;
                    case XPM:
                        cb_screen_save(filename);
                        break;
                }
            free(filename);
        }
}

@end
