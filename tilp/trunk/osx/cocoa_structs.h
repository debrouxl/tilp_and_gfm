/*
 * TiLP Cocoa GUI for Mac OS X
 */
 
 #ifndef __COCOA_STRUCTS_H__
 #define __COCOA_STRUCTS_H__
 
 #import <Cocoa/Cocoa.h>
 
 struct cocoa_objects_ptr
 {
    IBOutlet id BoxesController;
    IBOutlet id MenuController;
    IBOutlet id PrefsController;
    IBOutlet id ToolbarController;
    IBOutlet id TilpController;
    NSMutableDictionary *tilpConfig;
    NSUserDefaults *prefs;
 };

 
 
 #endif /* !__COCOA_STRUCTS_H__ */