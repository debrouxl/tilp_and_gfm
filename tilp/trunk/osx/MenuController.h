#import <Cocoa/Cocoa.h>

@interface MenuController : NSObject
{
    IBOutlet id BoxesController;
    IBOutlet id PrefsController;
    IBOutlet id TilpController;

    IBOutlet id mainWindow;
    IBOutlet id screendumpWindow;
    IBOutlet id screendumpImage;
    IBOutlet id thanksPanel;
    IBOutlet id thanksPanelText;
    
    NSMutableDictionary *toolbarItems;
}

// toolbar

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag;    
- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar;
- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar;

// file

- (IBAction)saveConfig:(id)sender;
- (IBAction)defaultConfig:(id)sender;

// link

- (IBAction)probeLink:(id)sender;
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
- (IBAction)receiveFLASHApp:(id)sender;
- (IBAction)getIDList:(id)sender;
- (IBAction)romDump:(id)sender;
- (IBAction)romVersion:(id)sender;
- (IBAction)installShell:(id)sender;

// window

- (IBAction)newWindow:(id)sender;

// help

- (IBAction)showThanks:(id)sender;
@end
