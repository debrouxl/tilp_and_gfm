#include "../src/cb_calc.h"
#include "../src/struct.h"

#include "cocoa_structs.h"

#import "BoxesController.h"

extern struct cocoa_objects_ptr *objects_ptr;
extern struct screenshot ti_screen;

@implementation BoxesController

- (void)awakeFromNib
{
    objects_ptr->pbar1Window = pbar1Window;
    objects_ptr->pbar3Window = pbar3Window;
    objects_ptr->pbar4Window = pbar4Window;
    objects_ptr->pbar5Window = pbar5Window;
}

- (IBAction)dlgboxentryButton1Push:(id)sender
{
}

- (IBAction)dlgboxentryButton2Push:(id)sender
{
}

- (IBAction)msgboxButtonPush:(id)sender
{
}

- (IBAction)pbarButtonPush:(id)sender
{
}

- (IBAction)remoteControlChangeMode:(id)sender
{
}

- (IBAction)remoteControlTextEntered:(id)sender
{
}

- (IBAction)screendumpLoadImage:(id)sender
{
    // FIXME OS X
    // pop-up a fileselection
    // then do the stuff in its OK button callback method
}

- (IBAction)screendumpRefresh:(id)sender
{
    NSData *bitmap;
    NSImage *screen;

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
    // FIXME OS X
    // pop-up a fileselection
    // then get the NSImage displayed
    // then test options.screen_format
    // for TIFF, call the appropriate method in the NSImage
}

@end
