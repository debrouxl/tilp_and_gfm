#import <Cocoa/Cocoa.h>

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

    NSMutableDictionary *tilpConfig;
    NSUserDefaults *prefs;
}
@end
