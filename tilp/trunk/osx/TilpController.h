#import <Cocoa/Cocoa.h>
#import "SimpleTreeNode.h"

@interface TilpController : NSObject
{
    IBOutlet id BoxesController;
    IBOutlet id MenuController;
    IBOutlet id PrefsController;

    IBOutlet id dirlistTree;
    IBOutlet id mainWindow;

    IBOutlet id currentFolder;
    IBOutlet id numberOfFolders;
    IBOutlet id numberOfVars;
    IBOutlet id memoryUsed;

    SimpleTreeNode *dirlistData;
     
    NSMutableDictionary *tilpConfig;
    NSUserDefaults *prefs;
}

@end
