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
}

- (void)pbarType2DidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;

- (IBAction)dlgboxentryButton1Push:(id)sender;
- (IBAction)dlgboxentryButton2Push:(id)sender;
- (IBAction)pbarButtonPush:(id)sender;
- (IBAction)remoteControlChangeMode:(id)sender;
- (IBAction)remoteControlTextEntered:(id)sender;
- (IBAction)screendumpRefresh:(id)sender;
- (IBAction)screendumpSaveImage:(id)sender;

// NSOpenPanels callbacks
- (void)doRestoreDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
- (void)sendFlashAppDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
- (void)sendAMSDidEnd:(NSOpenPanel *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;

// NSSavePanels callbacks
- (void)screendumpSaveImageDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
- (void)doBackupDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
- (void)romDumpDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;

@end
