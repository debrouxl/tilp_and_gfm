/*
 * TiLP Cocoa GUI for Mac OS X
 */
 
#ifndef __COCOA_STRUCTS_H__
#define __COCOA_STRUCTS_H__
 
#import <Cocoa/Cocoa.h>
#import <SimpleTreeNode.h>
 
struct cocoa_objects_ptr
{
    // our classes
    id myBoxesController;
    id myMenuController;
    id myPrefsController;
    id myTilpController;
    id mySheetsController;

    // return values for some dialog sheets
    // this is a quick hack to workaround the C way-of-life ;-)
    int user1_return;
    int user2_return;
    int user3_return;
    NSString *dlgbox_data;
      
    // used by the preferences system
    NSMutableDictionary *tilpConfig;
    NSUserDefaults *prefs;
};
 
#endif /* !__COCOA_STRUCTS_H__ */