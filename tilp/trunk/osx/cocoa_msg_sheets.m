/*
 * TiLP Cocoa GUI for Mac OS X
 */
 
 #include "cocoa_msg_sheets.h"
 #include "cocoa_structs.h"
 
 #include "../src/intl.h"
 #include "../src/defs.h"
 
 #define MSG_SHEET 1
 #define USER1_SHEET 2
 #define PBAR_TYPE2_SHEET 3
 
 extern struct cocoa_objects_ptr *objects_ptr;
 
 #import <Cocoa/Cocoa.h>
 
 // we could use NSbeep(); on some boxes (dlgboxEntry maybe ?)
 
 void
 create_cocoa_msg_sheet(const char *title, char *message)
 {
    NSBeginAlertSheet([NSString stringWithCString:title], @"Ok", nil, nil, objects_ptr->mainWindow,
                      nil, nil, nil, nil, [NSString stringWithCString:message]);
 }
 
 int
 create_cocoa_user1_sheet(const char *title, char *message, const char *button1)
 {
     NSBeginAlertSheet([NSString stringWithCString:title], [NSString stringWithCString:button1], nil,
                      nil, objects_ptr->mainWindow, nil, nil, nil, nil,
                      [NSString stringWithCString:message]);
                 
     return BUTTON1;
 }
                                                    
 void
 create_cocoa_pbar_type2_sheet(const char *title, char *message)
 {
    // FIXME OS X
    // we need to attach a method here... :-/
    NSBeginAlertSheet([NSString stringWithCString:title], [NSString stringWithCString:_("Abort")], nil,
                      nil, objects_ptr->mainWindow, nil, nil, nil, nil,
                      [NSString stringWithCString:message]);
 }
 
 /* user boxes */
 
 int
 create_cocoa_user2_sheet(const char *title, char *message, const char *button1, const char *button2)
 {
    int ret;
 
    id alertPanel;
    NSModalSession session;
    
    if (objects_ptr->alertPanel != nil)
        return -1;
    
    alertPanel = NSGetAlertPanel([NSString stringWithCString:title],
                                 [NSString stringWithCString:message],
                                 [NSString stringWithCString:button1],
                                 [NSString stringWithCString:button2],
                                 nil);
                                
    objects_ptr->alertPanel = alertPanel;
                                 
    session = [NSApp beginModalSessionForWindow:alertPanel];
    
    [alertPanel orderOut:nil];
    
    for (;;)
        {
            if ([NSApp runModalSession:session] != NSRunContinuesResponse)
                break;
        }
    
    [NSApp endModalSession:session];
    
    [alertPanel close];
    [alertPanel release];

    objects_ptr->alertPanel = nil;

    ret = objects_ptr->box_button;
    objects_ptr->box_button = -1;

    return ((ret > 0) ? ret : BUTTON1);
 }
 
 int
 create_cocoa_user3_sheet(const char *title, char *message, const char *button1, const char *button2, const char *button3)
 {
    int ret;
 
    id alertPanel;
    NSModalSession session;
    
    if (objects_ptr->alertPanel != nil)
        return -1;
    
    alertPanel = NSGetAlertPanel([NSString stringWithCString:title],
                                 [NSString stringWithCString:message],
                                 [NSString stringWithCString:button1],
                                 [NSString stringWithCString:button2],
                                 [NSString stringWithCString:button3]);
                                 
    objects_ptr->alertPanel = alertPanel;
                                
    session = [NSApp beginModalSessionForWindow:alertPanel];
    
    [alertPanel orderOut:nil];
    
    for (;;)
        {
            if ([NSApp runModalSession:session] != NSRunContinuesResponse)
                break;
        }
    
    [NSApp endModalSession:session];
    
    [alertPanel close];
    [alertPanel release];
    
    objects_ptr->alertPanel = nil;

    ret = objects_ptr->box_button;
    objects_ptr->box_button = -1;

    return ((ret > 0) ? ret : BUTTON1);
 }
 
 /* dialog box w/entry field */
 
 char *
 create_cocoa_dlgbox_entry(const char *title, const char *message, const char *content)
 {
    // called twice in cb_calc.c
    id mainWindow;
    id dlgboxEntry;
    
    NSModalSession session;
    
    // FIXME OS X : close the sheet in the button's attached method
    
    mainWindow = objects_ptr->mainWindow;
    dlgboxEntry = objects_ptr->dlgboxEntry;
 
    if ([dlgboxEntry isVisible])
        return NULL;
          
    [NSApp beginSheet:dlgboxEntry
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    session = [NSApp beginModalSessionForWindow:dlgboxEntry];
    
    [NSApp endSheet:dlgboxEntry];
    [dlgboxEntry orderOut:nil];
    
    for (;;)
        {
            if ([NSApp runModalSession:session] != NSRunContinuesResponse)
                break;
        }
    
    [NSApp endModalSession:session];
    
    while (objects_ptr->dlgbox_data == NULL);
                    
    return objects_ptr->dlgbox_data;
 }
 
 /* pbars */
 
 void
 create_cocoa_pbar_type1_sheet(const char *title)
 {
    id mainWindow;
    id pbar1Window;
    
    mainWindow = objects_ptr->mainWindow;
    pbar1Window= objects_ptr->pbar1Window;
    
    if ([pbar1Window isVisible])
        return;
    
    [NSApp beginSheet:pbar1Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    [NSApp runModalForWindow:pbar1Window];
    
    [NSApp endSheet:pbar1Window];
    [pbar1Window orderOut:nil]; 
 }
 
 void
 create_cocoa_pbar_type3_sheet(const char *title)
 {
    id mainWindow;
    id pbar3Window;
    
    mainWindow = objects_ptr->mainWindow;
    pbar3Window= objects_ptr->pbar3Window;

    if ([pbar3Window isVisible])
        return;
    
    [NSApp beginSheet:pbar3Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    [NSApp runModalForWindow:pbar3Window]; 
        
    [NSApp endSheet:pbar3Window];
    [pbar3Window orderOut:nil]; 
 }
 
 void
 create_cocoa_pbar_type4_sheet(const char *title, char *text)
 {
    id mainWindow;
    id pbar4Window;
    
    mainWindow = objects_ptr->mainWindow;
    pbar4Window= objects_ptr->pbar4Window;
    
    if ([pbar4Window isVisible])
        return;
    
    [NSApp beginSheet:pbar4Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    [NSApp runModalForWindow:pbar4Window]; 
        
    [NSApp endSheet:pbar4Window];
    [pbar4Window orderOut:nil]; 
 }
 
 void
 create_cocoa_pbar_type5_sheet(const char *title, char *text)
 {
    id mainWindow;
    id pbar5Window;
    
    mainWindow = objects_ptr->mainWindow;
    pbar5Window= objects_ptr->pbar5Window;
    
    if ([pbar5Window isVisible])
        return;
    
    [NSApp beginSheet:pbar5Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    [NSApp runModalForWindow:pbar5Window]; 
        
    [NSApp endSheet:pbar5Window];
    [pbar5Window orderOut:nil]; 
 }
 

/* destroy pbars */
 
 void
 destroy_pbar(void)
 {
    id pbar1Window;
    id pbar3Window;
    id pbar4Window;
    id pbar5Window;
    
    pbar1Window = objects_ptr->pbar1Window;
    pbar3Window = objects_ptr->pbar3Window;
    pbar4Window = objects_ptr->pbar4Window;
    pbar5Window = objects_ptr->pbar5Window;
 
    if ([pbar1Window isVisible])
        {
            [pbar1Window close];
            
            [NSApp stopModal];
        }
    else if ([pbar3Window isVisible])
        {
            [pbar3Window close];
            
            [NSApp stopModal];
        }
    else if ([pbar4Window isVisible])
        {
            [pbar4Window close];
            
            [NSApp stopModal];
        }
    else if ([pbar5Window isVisible])
        {
            [pbar5Window close];
            
            [NSApp stopModal];
        }
 }
