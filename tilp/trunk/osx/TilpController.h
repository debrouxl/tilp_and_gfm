#import <Cocoa/Cocoa.h>
#import "SimpleTreeNode.h"

@interface TilpController : NSObject
{
    IBOutlet id BoxesController;
    IBOutlet id currentFolder;
    IBOutlet id dirlistTree;
    IBOutlet id mainWindow;
    IBOutlet id memoryUsed;
    IBOutlet id MenuController;
    IBOutlet id numberOfFolders;
    IBOutlet id numberOfVars;
    IBOutlet id PrefsController;

    SimpleTreeNode *dirlistData;

    NSMutableDictionary *tilpConfig;
    NSUserDefaults *prefs;
}

- (void)initiateOutlineReload;

@end
