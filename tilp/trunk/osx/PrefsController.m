#include "../src/struct.h"
#include "../src/defs.h"

#include "cocoa_config.h"

#import "PrefsController.h"

@implementation PrefsController

- (IBAction)prefsAdvanced:(id)sender
{
    if (sender == linkTimeoutValueStepper)
        {
            [linkTimeoutField takeIntValueFrom:linkTimeoutValueStepper];
            options.lp.timeout = [linkTimeoutField intValue];
        }
    else if (sender == linkTimeoutField)
        {
            [linkTimeoutValueStepper takeIntValueFrom:linkTimeoutField];
            options.lp.timeout = [linkTimeoutField intValue];
        }
}

- (IBAction)prefsClose:(id)sender
{
    // general
    
    if (NSOnState == [orderIncreasing state])
        options.ctree_sort_order = SORT_UP;
    else if (NSOnState == [orderDecreasing state])
        options.ctree_sort_order = SORT_DOWN;

    if (NSOnState == [sortByInfo state])
        options.ctree_sort = SORT_BY_INFO;
    else if (NSOnState == [sortByName state])
        options.ctree_sort = SORT_BY_NAME;
    else if (NSOnState == [sortBySize state])
        options.ctree_sort = SORT_BY_SIZE;
    else if (NSOnState == [sortByType state])
        options.ctree_sort = SORT_BY_TYPE;

    if (NSOnState == [pathModeFull state])
        options.path_mode = FULL_PATH;
    else if (NSOnState == [pathModeLocal state])
        options.path_mode = LOCAL_PATH;

    if (NSOnState == [transferModeManual state])
        options.transfer_mode = MANUAL_MODE;
    else if (NSOnState == [transferModeSilent state])
        options.transfer_mode = SILENT_MODE;

    // hardware // FIXME OS X : cable designation
    
    if (NSOnState == [linkCableTIGLUSB state])
        options.lp.link_type = LINK_UGL;
    else if (NSOnState == [linkCableTPC state])
        options.lp.link_type = LINK_TPU;
    else if (NSOnState == [linkCableVTE state])
        options.lp.link_type = LINK_TIE;
    else if (NSOnState == [linkCableVTI state])
        options.lp.link_type = LINK_VTI;

    // calculator

    if (NSOnState == [calcType92p state])
        options.lp.calc_type = CALC_TI92P;
    else if (NSOnState == [calcType92 state])
        options.lp.calc_type = CALC_TI92;
    else if (NSOnState == [calcType89 state])
        options.lp.calc_type = CALC_TI89;
    else if (NSOnState == [calcType86 state])
        options.lp.calc_type = CALC_TI86;
    else if (NSOnState == [calcType85 state])
        options.lp.calc_type = CALC_TI85;
    else if (NSOnState == [calcType83p state])
        options.lp.calc_type = CALC_TI83P;
    else if (NSOnState == [calcType83 state])
        options.lp.calc_type = CALC_TI83;
    else if (NSOnState == [calcType82 state])
        options.lp.calc_type = CALC_TI82;
    else if (NSOnState == [calcType73 state])
        options.lp.calc_type = CALC_TI73;
        
    options.auto_detect = [calcTypeProbe state];
    
    // screendump
    
    if (NSOnState == [screenFormatPCX state])
        options.screen_format = PCX;
    //else if (NSOnState == [screenFormatTIFF state]) // FIXME OS X
    //    options.screen_format == TIFF
    else if (NSOnState == [screenFormatXPM state])
        options.screen_format = XPM;

    if (NSOnState == [screenModeClipped state])
        options.screen_clipping = TRUE;
    else if (NSOnState == [screenModeFull state])
        options.screen_clipping = FALSE;
        
    rc_save_user_prefs();

    [NSApp stopModal];
}

- (IBAction)showPrefsSheet:(id)sender
{
    if (options.path_mode == FULL_PATH)
        [pathModeMatrix setState:NSOnState atRow:0 column:0];
    else
        [pathModeMatrix setState:NSOnState atRow:0 column:1];
    
    if (options.transfer_mode == SILENT_MODE)
        [transferModeMatrix setState:NSOnState atRow:0 column:0];
    else
        [transferModeMatrix setState:NSOnState atRow:0 column:1];
        
    switch(options.ctree_sort)
        {
            case SORT_BY_NAME:
                [sortByMatrix setState:NSOnState atRow:0 column:0];
                break;
            case SORT_BY_TYPE:
                [sortByMatrix setState:NSOnState atRow:0 column:1];
                break;
            case SORT_BY_INFO:
                [sortByMatrix setState:NSOnState atRow:1 column:0];
                break;
            case SORT_BY_SIZE:
                [sortByMatrix setState:NSOnState atRow:1 column:1];
                break;
        }
        
    if (options.ctree_sort_order == SORT_UP) // Ahem. FIXME OS X ?
        [orderMatrix setState:NSOnState atRow:0 column:0];
    else
        [orderMatrix setState:NSOnState atRow:0 column:1];

    switch(options.lp.link_type) // Ahem. Cable types etc... FIXME OS X ?
        {
            case LINK_UGL:
                [linkTypeMatrix setState:NSOnState atRow:0 column:0];
                break;
            case LINK_TPU:
                [linkTypeMatrix setState:NSOnState atRow:0 column:1];
                break;
            case LINK_TIE:
                [linkTypeMatrix setState:NSOnState atRow:1 column:0];
                break;
            case LINK_VTI:
                [linkTypeMatrix setState:NSOnState atRow:1 column:1];
                break;
        }

    switch(options.lp.calc_type)
        {
            case CALC_TI92P:
                [calcTypeMatrix setState:NSOnState atRow:0 column:0];
                break;
            case CALC_TI92:
                [calcTypeMatrix setState:NSOnState atRow:1 column:0];
                break;
            case CALC_TI89:
                [calcTypeMatrix setState:NSOnState atRow:2 column:0];
                break;
            case CALC_TI86:
                [calcTypeMatrix setState:NSOnState atRow:0 column:1];
                break;
            case CALC_TI85:
                [calcTypeMatrix setState:NSOnState atRow:1 column:1];
                break;
            case CALC_TI83P:
                [calcTypeMatrix setState:NSOnState atRow:2 column:1];
                break;
            case CALC_TI83:
                [calcTypeMatrix setState:NSOnState atRow:0 column:2];
                break;
            case CALC_TI82:
                [calcTypeMatrix setState:NSOnState atRow:1 column:2];
                break;
            case CALC_TI73:
                [calcTypeMatrix setState:NSOnState atRow:2 column:2];
                break;
        }
        
    if (options.auto_detect == TRUE)
        [calcTypeProbe setState:NSOnState];
    else
        [calcTypeProbe setState:NSOffState];
    
    switch(options.screen_format)
        {
            case PCX:
                [screenFormatMatrix setState:NSOnState atRow:0 column:0];
                break;
            case XPM:
                [screenFormatMatrix setState:NSOnState atRow:1 column:0];
                break;
            //case TIFF:  // FIXME OS X
            //    [screenFormatMatrix setState:NSOnState atRow:2 column:0];
            //    break;
        }
        
    if (options.screen_clipping == FULL_SCREEN)
        [screenModeMatrix setState:NSOnState atRow:0 column:0];
    else
        [screenModeMatrix setState:NSOnState atRow:1 column:0];
        
    if (options.lp.timeout > 0)
        [linkTimeoutField setIntValue:options.lp.timeout];
    else // defaults to 150
        [linkTimeoutField setIntValue:150];
        
    [NSApp beginSheet:prefsWindow
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    [NSApp runModalForWindow:prefsWindow];
    
    [NSApp endSheet:prefsWindow];
    [prefsWindow orderOut:self];
}
@end
