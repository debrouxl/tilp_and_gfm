#import <Cocoa/Cocoa.h>

@interface PrefsController : NSObject
{
    IBOutlet id calcType73;
    IBOutlet id calcType82;
    IBOutlet id calcType83;
    IBOutlet id calcType83p;
    IBOutlet id calcType85;
    IBOutlet id calcType86;
    IBOutlet id calcType89;
    IBOutlet id calcType92;
    IBOutlet id calcType92p;
    IBOutlet id calcTypeAutoDetect;
    IBOutlet id linkCableTypeTIEMU;
    IBOutlet id linkCableTypeTIGLUSB;
    IBOutlet id linkCableTypeTPC;
    IBOutlet id linkCableTypeVTI;
    IBOutlet id linkTimeout;
    IBOutlet id orderDecreasing;
    IBOutlet id orderIncreasing;
    IBOutlet id pathModeFull;
    IBOutlet id pathModeLocal;
    IBOutlet id screendumpPCX;
    IBOutlet id screendumpXPM;
    IBOutlet id screenModeClipped;
    IBOutlet id screenModeFull;
    IBOutlet id sortByInfo;
    IBOutlet id sortByName;
    IBOutlet id sortBySize;
    IBOutlet id sortByType;
    IBOutlet id transferModeManual;
    IBOutlet id transferModeSilent;
}
- (IBAction)changeTimeout:(id)sender;
- (IBAction)closePrefs:(id)sender;
@end
