/*
 * TiLP Cocoa GUI for Mac OS X
 */
 
 #include "cocoa_sheets.h"
 #include "cocoa_structs.h"
 
 #include "../src/intl.h"
 #include "../src/defs.h"
 
 extern struct cocoa_objects_ptr *objects_ptr;
 extern struct cocoa_pbars_ptr *pbars_ptr;
 
 #import <Cocoa/Cocoa.h>
 
 // we could use NSbeep(); on some boxes (dlgboxEntry maybe ?)
 
 // FIXME OS X : orderOut: closes the sheet !!! is it what we want ?
 
 void
 create_cocoa_msg_sheet(const char *title, char *message)
 {
    id BoxesController;
    
    BoxesController = objects_ptr->BoxesController;
 
    NSBeginAlertSheet([NSString stringWithCString:title], @"Ok", nil, nil, objects_ptr->mainWindow,
                      BoxesController, @selector(msgBoxOrUser2DidEnd:returnCode:contextInfo:),
                      nil, nil, [NSString stringWithCString:message]);
 }
 
 int
 create_cocoa_user1_sheet(const char *title, char *message, const char *button1)
 {
    id BoxesController;
    
    BoxesController = objects_ptr->BoxesController;
 
     NSBeginAlertSheet([NSString stringWithCString:title], [NSString stringWithCString:button1], nil,
                      nil, objects_ptr->mainWindow,
                      BoxesController, @selector(msgBoxOrUser2DidEnd:returnCode:contextInfo:),
                      nil, nil, [NSString stringWithCString:message]);
                 
     return BUTTON1;
 }
                                                    
 void
 create_cocoa_pbar_type2_sheet(const char *title, char *message)
 {
    id BoxesController;
    
    BoxesController = objects_ptr->BoxesController;
    
    NSBeginAlertSheet([NSString stringWithCString:title], [NSString stringWithCString:_("Abort")], nil,
                      nil, objects_ptr->mainWindow, BoxesController, nil,
                      @selector(pbarType2DidEnd:returnCode:contextInfo:),
                      nil, [NSString stringWithCString:message]);
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
                    
    return objects_ptr->dlgbox_data;
 }
 
 /* pbars */
 
 void
 create_cocoa_pbar_type1_sheet(const char *title)
 {
    id mainWindow;
    id pbar1Window;
    
    if (pbars_ptr->pbar1 != nil)
        return;
    
    mainWindow = objects_ptr->mainWindow;
    pbar1Window = pbars_ptr->pbar1Window;
    
    pbars_ptr->pbar1 = pbars_ptr->pbar1PBar;
    pbars_ptr->pbar_rate = pbars_ptr->pbar1Rate;
    
    [NSApp beginSheet:pbar1Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    // FIXME OS X : for each pbar
    // Use a modalsession here...
    // the loop would also be used in the refresh code
    // OR we could use a variable... and rely on it in the refresh code.    
    
    [NSApp runModalForWindow:pbar1Window];
    
    [NSApp endSheet:pbar1Window];
    [pbar1Window orderOut:nil]; 
 }
 
 void
 create_cocoa_pbar_type3_sheet(const char *title)
 {
    id mainWindow;
    id pbar3Window;

    if (pbars_ptr->pbar1 != nil)
        return;
    
    mainWindow = objects_ptr->mainWindow;
    pbar3Window = pbars_ptr->pbar3Window;
    
    pbars_ptr->pbar1 = pbars_ptr->pbar3PBar1;
    pbars_ptr->pbar2 = pbars_ptr->pbar3PBar2;
    pbars_ptr->pbar_rate = pbars_ptr->pbar3Rate;
    
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
    
    if (pbars_ptr->pbar1 != nil)
        return;
    
    mainWindow = objects_ptr->mainWindow;
    pbar4Window = pbars_ptr->pbar4Window;
    
    pbars_ptr->pbar1 = pbars_ptr->pbar4PBar;
    pbars_ptr->pbar_rate = pbars_ptr->pbar4Rate;
    pbars_ptr->pbar_text = pbars_ptr->pbar4Text;
    
    
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
    
    if (pbars_ptr->pbar1 != nil)
        return;
    
    mainWindow = objects_ptr->mainWindow;
    pbar5Window = pbars_ptr->pbar5Window;

    pbars_ptr->pbar1 = pbars_ptr->pbar5PBar1;
    pbars_ptr->pbar2 = pbars_ptr->pbar5PBar2;
    pbars_ptr->pbar_rate = pbars_ptr->pbar5Rate;
    pbars_ptr->pbar_text = pbars_ptr->pbar5Text;

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
    
    pbar1Window = pbars_ptr->pbar1Window;
    pbar3Window = pbars_ptr->pbar3Window;
    pbar4Window = pbars_ptr->pbar4Window;
    pbar5Window = pbars_ptr->pbar5Window;
 
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
    else
        return;
        
    pbars_ptr->pbar1 = nil;
    pbars_ptr->pbar2 = nil;
    pbars_ptr->pbar_rate = nil;
    pbars_ptr->pbar_text = nil;
    
    pbars_ptr->finished = 0;
 }
