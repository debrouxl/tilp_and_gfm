/*
 * TiLP Cocoa GUI for Mac OS X
 */

#import <Cocoa/Cocoa.h>

@interface PrefsController : NSObject
{
    IBOutlet id BoxesController;
    IBOutlet id calcType73;
    IBOutlet id calcType82;
    IBOutlet id calcType83;
    IBOutlet id calcType83p;
    IBOutlet id calcType85;
    IBOutlet id calcType86;
    IBOutlet id calcType89;
    IBOutlet id calcType92;
    IBOutlet id calcType92p;
    IBOutlet id calcTypeProbe;
    IBOutlet id consoleModeMatrix;
    IBOutlet id consoleSilent;
    IBOutlet id consoleVerbose;
    IBOutlet id linkCableUGL;
    IBOutlet id linkCableTPU;
    IBOutlet id linkCableTIE;
    IBOutlet id linkCableVTI;
    IBOutlet id linkTimeoutField;
    IBOutlet id linkTimeoutValueStepper;
    IBOutlet id mainWindow;
    IBOutlet id MenuController;
    IBOutlet id orderDecreasing;
    IBOutlet id orderIncreasing;
    IBOutlet id pathModeFull;
    IBOutlet id pathModeLocal;
    IBOutlet id prefsWindow;
    IBOutlet id screenFormatPCX;
    IBOutlet id screenFormatTIFF;
    IBOutlet id screenFormatXPM;
    IBOutlet id screenModeClipped;
    IBOutlet id screenModeFull;
    IBOutlet id sortByInfo;
    IBOutlet id sortByName;
    IBOutlet id sortBySize;
    IBOutlet id sortByType;
    IBOutlet id TilpController;
    IBOutlet id transferModeManual;
    IBOutlet id transferModeSilent;
    
    IBOutlet id transferModeMatrix;
    IBOutlet id pathModeMatrix;
    IBOutlet id orderMatrix;
    IBOutlet id sortByMatrix;
    IBOutlet id linkTypeMatrix;
    IBOutlet id calcTypeMatrix;
    IBOutlet id screenFormatMatrix;
    IBOutlet id screenModeMatrix;
}
- (IBAction)prefsAdvanced:(id)sender;
- (IBAction)prefsClose:(id)sender;
- (IBAction)showPrefsSheet:(id)sender;
@end
