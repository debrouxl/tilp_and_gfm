#include "../src/struct.h"
#include "../src/defs.h"

#import "PrefsController.h"

@implementation PrefsController

- (IBAction)prefsAdvanced:(id)sender
{
}

- (IBAction)prefsCalc:(id)sender
{
}

- (IBAction)prefsClose:(id)sender
{
    [NSApp stopModal];
}

- (IBAction)prefsGeneral:(id)sender
{
}

- (IBAction)prefsHardware:(id)sender
{
}

- (IBAction)prefsScreendump:(id)sender
{
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
            case SORT_BY_TYPE:
                [orderMatrix setState:NSOnState atRow:0 column:1];
                break;
            case SORT_BY_INFO:
                [orderMatrix setState:NSOnState atRow:1 column:0];
                break;
            case SORT_BY_SIZE:
                [orderMatrix setState:NSOnState atRow:1 column:1];
                break;
            default:
                [orderMatrix setState:NSOnState atRow:0 column:0];
                break;
        }
        
    if (options.ctree_sort_order == SORT_UP) // Ahem. FIXME OS X ?
        [sortByMatrix setState:NSOnState atRow:0 column:0];
    else
        [sortByMatrix setState:NSOnState atRow:0 column:1];

    switch(options.lp.link_type) // Ahem. Cable types etc... FIXME OS X ?
        {
            case LINK_TPU:
                [linkTypeMatrix setState:NSOnState atRow:0 column:1];
                break;
            case LINK_TIE:
                [linkTypeMatrix setState:NSOnState atRow:1 column:0];
                break;
            case LINK_VTI:
                [linkTypeMatrix setState:NSOnState atRow:1 column:1];
                break;
            default: // defaults to TIGL USB
                [linkTypeMatrix setState:NSOnState atRow:0 column:0];
                break;
        }

    switch(options.lp.calc_type)
        {
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
            default: // defaults to TI92P
                [calcTypeMatrix setState:NSOnState atRow:0 column:0];
                break;
        }
        
    if (options.auto_detect == TRUE)
        [calcTypeProbe setState:NSOnState];
    else
        [calcTypeProbe setState:NSOffState];
    
    switch(options.screen_format)
        {
            case XPM:
                [screenFormatMatrix setState:NSOnState atRow:1 column:0];
                break;
            //case TIFF:  // FIXME OS X
            //    [screenFormatMatrix setState:NSOnState atRow:2 column:0];
            //    break;
            default:
                [screenFormatMatrix setState:NSOnState atRow:0 column:0];
                break;
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
