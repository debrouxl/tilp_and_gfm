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
 
void
create_cocoa_msg_sheet(const char *title, char *message)
{
    NSRunAlertPanel([NSString stringWithCString:title], [NSString stringWithCString:message], nil, nil, nil);
}
 
int
create_cocoa_user1_sheet(const char *title, char *message, const char *button1)
{
    NSRunAlertPanel([NSString stringWithCString:title], [NSString stringWithCString:message], [NSString stringWithCString:button1], nil, nil);
                 
    return BUTTON1;
}
                                                    
void
create_cocoa_pbar_type2_sheet(const char *title, char *message)
{
#if defined(USE_SHEETS)                      
    NSRunAlertPanel([NSString stringWithCString:title], [NSString stringWithCString:message], @"Abort", nil, nil);
    
    info_update.cancel = 1;
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
    int ret;
    
    ret = NSRunAlertPanel([NSString stringWithCString:title],
                          [NSString stringWithCString:message],
                          [NSString stringWithCString:button1],
                          [NSString stringWithCString:button2],
                          nil);
                                
    return ((ret == NSAlertDefaultReturn) ? BUTTON1 : BUTTON2);
}
 
int
create_cocoa_user3_sheet(const char *title, char *message, const char *button1, const char *button2, const char *button3)
{
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
}
 
/* dialog box w/entry field */
 
char *
create_cocoa_dlgbox_entry(const char *title, const char *message, const char *content)
{
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
  
    [NSApp runModalForWindow:pbar1Window];
    
    [NSApp endSheet:pbar1Window];
    [pbar1Window orderOut:nil];
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
           
    [NSApp runModalForWindow:pbar3Window]; 
        
    [NSApp endSheet:pbar3Window];
    [pbar3Window orderOut:nil]; 
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
           
    [NSApp runModalForWindow:pbar4Window]; 
        
    [NSApp endSheet:pbar4Window];
    [pbar4Window orderOut:nil]; 
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
           
    [NSApp runModalForWindow:pbar5Window]; 
        
    [NSApp endSheet:pbar5Window];
    [pbar5Window orderOut:nil]; 
#else
    [pbar5Window makeKeyAndOrderFront:nil];
#endif
}
 

// destroy pbars
 
void
destroy_pbar(void)
{
#if !defined(USE_SHEETS)
    id window;
#endif
    
#if defined(USE_SHEETS)
    [NSApp stopModal];
#else
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
#endif

    pbars_ptr->pbar1 = nil;
    pbars_ptr->pbar2 = nil;
    pbars_ptr->pbar_rate = nil;
    pbars_ptr->pbar_text = nil;
    
    pbars_ptr->finished = 0;
}
