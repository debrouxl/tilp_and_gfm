/*
 * TiLP Cocoa GUI for Mac OS X
 */

#import <Cocoa/Cocoa.h>
#import "SimpleTreeNode.h"

@interface TilpController : NSObject
{
    IBOutlet id dirlistTree;
    IBOutlet id mainWindow;

    IBOutlet id currentFolder;
    IBOutlet id numberOfFolders;
    IBOutlet id numberOfVars;
    IBOutlet id memoryUsed;
 
    IBOutlet id myBoxesController;
    IBOutlet id myMenuController;
    IBOutlet id myPrefsController;
    IBOutlet id mySheetsController;
 
    SimpleTreeNode *dirlistData;
    
    NSDictionary *calcsProperties;
    
    NSMutableDictionary *tilpConfig;
    NSUserDefaults *prefs;
}

- (NSDictionary *)getCurrentCalcDict;

- (void)refreshOutline;
- (void)refreshInfos;

@end
