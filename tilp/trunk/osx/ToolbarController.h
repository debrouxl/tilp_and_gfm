#import <Cocoa/Cocoa.h>

@interface ToolbarController : NSObject
{
    NSMutableDictionary *toolbarItems;
    IBOutlet id mainWindow;
    IBOutlet id screendumpWindow;
    IBOutlet id screendumpImage;
    IBOutlet id BoxesController;
    IBOutlet id MenuController;
    IBOutlet id PrefsController;
    IBOutlet id TilpController;
}

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag;    
- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar;
- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar;

- (IBAction)doBackup:(id)sender;
- (IBAction)doRestore:(id)sender;
- (IBAction)getDirlist:(id)sender;
- (IBAction)getScreen:(id)sender;
- (IBAction)isReady:(id)sender;
@end
