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
    IBOutlet id mainWindow;
    IBOutlet id dlgboxEntry;
    IBOutlet id pbar1Window;
    IBOutlet id pbar3Window;
    IBOutlet id pbar4Window;
    IBOutlet id pbar5Window;
    NSMutableDictionary *tilpConfig;
    NSUserDefaults *prefs;
    
    IBOutlet id alertPanel;
    
    // used for dlgbox_entry and userX_box
    char *dlgbox_data;
    int box_button;
 };

 
 
 #endif /* !__COCOA_STRUCTS_H__ */