/*
 * TiLP Cocoa GUI for Mac OS X
 */

#import <Cocoa/Cocoa.h>

@interface MenuController : NSObject
{
    IBOutlet id mainWindow;
    IBOutlet id screendumpWindow;
    IBOutlet id screendumpImage;
    IBOutlet id thanksPanel;
    IBOutlet id thanksPanelText;
    IBOutlet id msgSheetText;
    IBOutlet id msgSheetWindow;
    IBOutlet id remoteControlTextArea;
    IBOutlet id remoteControlWindow;
 
    IBOutlet id myBoxesController;
    IBOutlet id myPrefsController;
    IBOutlet id myTilpController;
    IBOutlet id mySheetsController;

    NSMutableDictionary *toolbarItems;
}

// toolbar

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag;    
- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar;
- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar;

// Application menu
- (IBAction)showAbout:(id)sender;

// file

- (IBAction)saveConfig:(id)sender;
- (IBAction)defaultConfig:(id)sender;

// link

- (IBAction)probeCalc:(id)sender;

// functions 1

- (IBAction)isReady:(id)sender;
- (IBAction)remoteControl:(id)sender;
- (IBAction)getScreen:(id)sender;
- (IBAction)getDirlist:(id)sender;
- (IBAction)doRestore:(id)sender;
- (IBAction)doBackup:(id)sender;

// functions 2

- (IBAction)sendFLASHApp:(id)sender;
- (IBAction)sendAMS:(id)sender;
- (IBAction)getIDList:(id)sender;
- (IBAction)romDump:(id)sender;
- (IBAction)romVersion:(id)sender;
- (IBAction)installShell:(id)sender;

// window

- (IBAction)newWindow:(id)sender;
- (IBAction)closeWindow:(id)sender;

// help

- (IBAction)showThanks:(id)sender;
@end
