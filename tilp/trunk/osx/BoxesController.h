#import <Cocoa/Cocoa.h>

@interface BoxesController : NSObject
{
    IBOutlet id dlgboxentryButton1;
    IBOutlet id dlgboxentryButton2;
    IBOutlet id dlgboxentryEntry;
    IBOutlet id dlgboxentryText;
    IBOutlet id dlgboxentryWindow;
    IBOutlet id MenuController;
    IBOutlet id pbar1PBar;
    IBOutlet id pbar1Rate;
    IBOutlet id pbar1Window;
    IBOutlet id pbar3PBar1;
    IBOutlet id pbar3PBar2;
    IBOutlet id pbar3Rate;
    IBOutlet id pbar3Window;
    IBOutlet id pbar4PBar;
    IBOutlet id pbar4Rate;
    IBOutlet id pbar4Text;
    IBOutlet id pbar4Window;
    IBOutlet id pbar5PBar1;
    IBOutlet id pbar5PBar2;
    IBOutlet id pbar5Rate;
    IBOutlet id pbar5Text;
    IBOutlet id pbar5Window;
    IBOutlet id PrefsController;
    IBOutlet id remoteControlRemoteMode;
    IBOutlet id remoteControlTerminalMode;
    IBOutlet id remoteControlTextArea;
    IBOutlet id remoteControlWindow;
    IBOutlet id screendumpImage;
    IBOutlet id screendumpWindow;
    IBOutlet id TilpController;
    IBOutlet id ToolbarController;
}
- (IBAction)dlgboxentryButton1Push:(id)sender;
- (IBAction)dlgboxentryButton2Push:(id)sender;
- (IBAction)msgboxButtonPush:(id)sender;
- (IBAction)pbarButtonPush:(id)sender;
- (IBAction)remoteControlChangeMode:(id)sender;
- (IBAction)remoteControlTextEntered:(id)sender;
- (IBAction)screendumpLoadImage:(id)sender;
- (IBAction)screendumpRefresh:(id)sender;
- (IBAction)screendumpSaveImage:(id)sender;
@end
