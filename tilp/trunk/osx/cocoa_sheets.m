/*
 * TiLP Cocoa GUI for Mac OS X
 */
 
#include "cocoa_sheets.h"
#include "cocoa_structs.h"
 
#include "../src/struct.h"
#include "../src/intl.h"
#include "../src/defs.h"
 
extern struct cocoa_objects_ptr *objects_ptr;
extern struct cocoa_pbars_ptr *pbars_ptr;
 
extern struct ticalc_info_update info_update;
 
#import <Cocoa/Cocoa.h>
 
// we could use NSbeep(); on some boxes (dlgboxEntry maybe ?)
// and also request the user attention (ie. the app's icon will jump on the screen)
// see requestUserAttention()

// FIXME OS X
// do we need to wait until userX sheets are closed to open a new one ?
// (ieis it possible to spawn a new one if one is already active ? (think modal...)
 
void
create_cocoa_msg_sheet(const char *title, char *message)
{
#ifdef USE_SHEETS
    // No delegate for this one, we don't care.
    // keep NSBeginAlertSheet here for the moment ; I think we'll have to use a modal sheet, too.

    id mainWindow;
    
    mainWindow = objects_ptr->mainWindow;
    
    NSBeginAlertSheet([NSString stringWithCString:title], nil, nil, nil, mainWindow, nil, nil, nil, nil,
                      [NSString stringWithCString:message]);
#else
    NSRunAlertPanel([NSString stringWithCString:title], [NSString stringWithCString:message], nil, nil, nil);
#endif
}
 
int
create_cocoa_user1_sheet(const char *title, char *message, const char *button1)
{
#ifdef USE_SHEETS
    id mainWindow;
    id user1Window;
    id user1Text;
    id user1Button;
    
    mainWindow = objects_ptr->mainWindow;
    user1Window = objects_ptr->user1Window;
    user1Text = objects_ptr->user1Text;
    user1Button = objects_ptr->user1Button;

    // FIXME OS X
    // should allow cocoa to catch and process events
    while ([user1Window isVisible]) { /* WAIT ! */ }
    
    [user1Text setStringValue:[NSString stringWithCString:message]];
    [user1Button setTitle:[NSString stringWithCString:button1]];
    
    [NSApp beginSheet:user1Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
    
    [NSApp runModalForWindow:user1Window];
    
    [NSApp endSheet:user1Window];
    [user1Window orderOut:nil];

    return objects_ptr->user1_return;
#else
    NSRunAlertPanel([NSString stringWithCString:title], [NSString stringWithCString:message], [NSString stringWithCString:button1], nil, nil);
    
    return BUTTON1;
#endif
}
                                                    
void
create_cocoa_pbar_type2_sheet(const char *title, char *message)
{
#if defined(USE_SHEETS)
    id mainWindow;
    id pbar2Window;
    id pbar2Text;

    mainWindow = objects_ptr->mainWindow;
    pbar2Window = pbars_ptr->pbar2Window;
    pbar2Text = pbars_ptr->pbar2Text;

    // FIXME OS X
    // should allow cocoa to catch and process events
    while ([pbar2Window isVisible]) { /* WAIT ! */ }

    [pbar2Window setTitle:[NSString stringWithCString:title]];
    [pbar2Text setStringValue:[NSString stringWithCString:message]];

    [NSApp beginSheet:pbar2Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
   
    [NSApp endSheet:pbar2Window];
#else
    id pbar2Window;
    id pbar2Text;

    pbar2Window = pbars_ptr->pbar2Window;
    pbar2Text = pbars_ptr->pbar2Text;

    [pbar2Window setTitle:[NSString stringWithCString:title]];
    [pbar2Text setStringValue:[NSString stringWithCString:message]];
    
    [pbar2Window makeKeyAndOrderFront:nil];
#endif
}
 
/* user boxes */
 
int
create_cocoa_user2_sheet(const char *title, char *message, const char *button1, const char *button2)
{
#ifdef USE_SHEETS
    id mainWindow;
    id user2Window;
    id user2Text;
    id user2Button1;
    id user2Button2;
    
    mainWindow = objects_ptr->mainWindow;
    user2Window = objects_ptr->user2Window;
    user2Text = objects_ptr->user2Text;
    user2Button1 = objects_ptr->user2Button1;
    user2Button2 = objects_ptr->user2Button2;
    
    // FIXME OS X
    // should allow cocoa to catch and process events
    while ([user2Window isVisible]) { /* WAIT ! */ }
    
    [user2Text setStringValue:[NSString stringWithCString:message]];
    [user2Button1 setTitle:[NSString stringWithCString:button1]];
    [user2Button2 setTitle:[NSString stringWithCString:button2]];
    
    [NSApp beginSheet:user2Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
    
    [NSApp runModalForWindow:user2Window];
    
    [NSApp endSheet:user2Window];
    [user2Window orderOut:nil];

    return objects_ptr->user2_return;
#else
    int ret;
    
    ret = NSRunAlertPanel([NSString stringWithCString:title],
                          [NSString stringWithCString:message],
                          [NSString stringWithCString:button1],
                          [NSString stringWithCString:button2],
                          nil);
                                
    return ((ret == NSAlertDefaultReturn) ? BUTTON1 : BUTTON2);
#endif
}
 
int
create_cocoa_user3_sheet(const char *title, char *message, const char *button1, const char *button2, const char *button3)
{
#ifdef USE_SHEETS
    id mainWindow;
    id user3Window;
    id user3Text;
    id user3Button1;
    id user3Button2;
    id user3Button3;
    
    mainWindow = objects_ptr->mainWindow;
    user3Window = objects_ptr->user3Window;
    user3Text = objects_ptr->user3Text;
    user3Button1 = objects_ptr->user3Button1;
    user3Button2 = objects_ptr->user3Button2;
    user3Button3 = objects_ptr->user3Button3;
    
    // FIXME OS X
    // should allow cocoa to catch and process events
    while ([user3Window isVisible]) { /* WAIT ! */}
    
    [user3Text setStringValue:[NSString stringWithCString:message]];
    [user3Button1 setTitle:[NSString stringWithCString:button1]];
    [user3Button2 setTitle:[NSString stringWithCString:button2]];
    [user3Button3 setTitle:[NSString stringWithCString:button3]];
    
    [NSApp beginSheet:user3Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
    
    [NSApp runModalForWindow:user3Window];
    
    [NSApp endSheet:user3Window];
    [user3Window orderOut:nil];

    return objects_ptr->user3_return;
#else
    int ret;
 
    ret = NSRunAlertPanel([NSString stringWithCString:title],
                          [NSString stringWithCString:message],
                          [NSString stringWithCString:button1],
                          [NSString stringWithCString:button2],
                          [NSString stringWithCString:button3]);
    
    switch (ret)
        {
            case NSAlertDefaultReturn:
                ret = BUTTON1;
                break;
            case NSAlertAlternateReturn:
                ret = BUTTON2;
                break;
            case NSAlertOtherReturn:
                ret = BUTTON3;
                break;
        }

    return ret;
#endif
}
 
/* dialog box w/entry field */
 
char *
create_cocoa_dlgbox_entry(const char *title, const char *message, const char *content)
{
    // This sheet is modal for the main window
    
    id mainWindow;
    id dlgboxentryWindow;
    id dlgboxentryEntry;
    id dlgboxentryText;
    
    mainWindow = objects_ptr->mainWindow;
    dlgboxentryWindow = objects_ptr->dlgboxentryWindow;
    dlgboxentryEntry = objects_ptr->dlgboxentryEntry;
    dlgboxentryText = objects_ptr->dlgboxentryText;
 
    if ([dlgboxentryWindow isVisible])
        return NULL;
          
    [dlgboxentryEntry setStringValue:[NSString stringWithCString:content]];
    [dlgboxentryEntry selectText:nil];
    [dlgboxentryText setStringValue:[NSString stringWithCString:message]];
          
    [NSApp beginSheet:dlgboxentryWindow
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
    
    [NSApp runModalForWindow:dlgboxentryWindow];
            
    [NSApp endSheet:dlgboxentryWindow];
    [dlgboxentryWindow orderOut:nil];
    
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

#if defined(USE_SHEETS)    
    [NSApp beginSheet:pbar1Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
    
    [NSApp endSheet:pbar1Window];
#else
    [pbar1Window makeKeyAndOrderFront:nil];
#endif
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

#if defined(USE_SHEETS)
    [NSApp beginSheet:pbar3Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];

    [NSApp endSheet:pbar3Window];
#else
    [pbar3Window makeKeyAndOrderFront:nil];
#endif
}
 
void
create_cocoa_pbar_type4_sheet(const char *title, char *text)
{
    id mainWindow;
    id pbar4Window;
    id pbar4Text;
    
    if (pbars_ptr->pbar1 != nil)
        return;
    
    mainWindow = objects_ptr->mainWindow;
    pbar4Window = pbars_ptr->pbar4Window;
    pbar4Text = pbars_ptr->pbar4Text;
    
    pbars_ptr->pbar1 = pbars_ptr->pbar4PBar;
    pbars_ptr->pbar_rate = pbars_ptr->pbar4Rate;
    pbars_ptr->pbar_text = pbars_ptr->pbar4Text;
    
    [pbar4Text setStringValue:[NSString stringWithCString:text]];

#if defined(USE_SHEETS)    
    [NSApp beginSheet:pbar4Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];

    [NSApp endSheet:pbar4Window];
#else
    [pbar4Window makeKeyAndOrderFront:nil];
#endif
}
 
void
create_cocoa_pbar_type5_sheet(const char *title, char *text)
{
    id mainWindow;
    id pbar5Window;
    id pbar5Text;
    
    if (pbars_ptr->pbar1 != nil)
        return;
    
    mainWindow = objects_ptr->mainWindow;
    pbar5Window = pbars_ptr->pbar5Window;
    pbar5Text = pbars_ptr->pbar5Text;

    pbars_ptr->pbar1 = pbars_ptr->pbar5PBar1;
    pbars_ptr->pbar2 = pbars_ptr->pbar5PBar2;
    pbars_ptr->pbar_rate = pbars_ptr->pbar5Rate;
    pbars_ptr->pbar_text = pbars_ptr->pbar5Text;

    [pbar5Text setStringValue:[NSString stringWithCString:text]];

#if defined(USE_SHEETS)
    [NSApp beginSheet:pbar5Window
           modalForWindow:mainWindow
           modalDelegate:nil
           didEndSelector:nil
           contextInfo:nil];
           
    [NSApp endSheet:pbar5Window]; 
#else
    [pbar5Window makeKeyAndOrderFront:nil];
#endif
}
 

// destroy pbars
 
void
destroy_pbar(void)
{
    id window;
    id pbar1;
    id pbar2;

    window = pbars_ptr->pbar1Window;
    if ([window isVisible])
        [window orderOut:nil];
        
    window = pbars_ptr->pbar2Window;
    if ([window isVisible])
        [window orderOut:nil];
    
    window = pbars_ptr->pbar3Window;
    if ([window isVisible])
        [window orderOut:nil];
        
    window = pbars_ptr->pbar4Window;
    if ([window isVisible])
        [window orderOut:nil];
        
    window = pbars_ptr->pbar5Window;
    if ([window isVisible])
        [window orderOut:nil];
            
    window = nil;

    // reset the pbars, in case the transfer has crashed
    if (pbars_ptr->pbar1 != nil)
        {
            pbar1 = pbars_ptr->pbar1;
            [pbar1 setDoubleValue:0.0];
            [pbar1 displayIfNeeded];
        }

    if (pbars_ptr->pbar2 != nil)
        {
            pbar2 = pbars_ptr->pbar2;
            [pbar2 setDoubleValue:0.0];
            [pbar2 displayIfNeeded];
        }

    pbars_ptr->pbar1 = nil;
    pbars_ptr->pbar2 = nil;
    pbars_ptr->pbar_rate = nil;
    pbars_ptr->pbar_text = nil;
    
    // reset, in case the transfer has crashed
    info_update.percentage = 0.0;
    info_update.prev_percentage = 0.0;
}
