#import <Cocoa/Cocoa.h>

@interface ToolbarController : NSObject
{
    NSMutableDictionary *toolbarItems;
    IBOutlet id mainWindow;
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
