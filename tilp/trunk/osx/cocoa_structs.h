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
    
    // the main window
    id mainWindow;
    
    // the NSOutlineView
    id dirlistTree;
    // and its content
    SimpleTreeNode *dirlistData;
    
    // info labels
    id currentFolder;
    id numberOfFolders;
    id numberOfVars;
    id memoryUsed;
    
    // userX boxes and their return value...
    id user1Window;
    id user1Text;
    id user1Button;
    
    int user1_return;
    
    id user2Window;
    id user2Text;
    id user2Button1;
    id user2Button2;
    
    int user2_return;
    
    id user3Window;
    id user3Text;
    id user3Button1;
    id user3Button2;
    id user3Button3;
    
    int user3_return;
    
    // the dlgbox (for pbars, see the following struct)
    id dlgboxentryWindow;
    id dlgboxentryEntry;
    id dlgboxentryText;
    
    // the remote control/terminal window
    id remoteControlWindow;
    
    // and its textField
    id remoteControlTextArea;
    
    // the operating mode of the remote control/terminal stuff
    int term_mode;
    
    // used by the preferences system
    NSMutableDictionary *tilpConfig;
    NSUserDefaults *prefs;
    
    // keep track of which widget is being used
    id alertPanel;
    
    // used for dlgbox_entry and userX_box
    NSString *dlgbox_data;
    int box_button;
};
 
#endif /* !__COCOA_STRUCTS_H__ */