/*
 * TiLP Cocoa GUI for Mac OS X
 */

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
    
    NSArray *tiTypes73;
    NSArray *tiTypes82;
    NSArray *tiTypes83;
    NSArray *tiTypes8x;
    NSArray *tiTypes85;
    NSArray *tiTypes86;
    NSArray *tiTypes89;
    NSArray *tiTypes92;
    NSArray *tiTypes9x;
     
    NSMutableDictionary *tilpConfig;
    NSUserDefaults *prefs;
}

@end
