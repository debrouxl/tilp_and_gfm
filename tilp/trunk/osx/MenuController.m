#include "../src/cb_misc.h"

#include "cocoa_config.h"
#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;

#import "MenuController.h"

@implementation MenuController

- (IBAction)defaultConfig:(id)sender
{
    cb_default_config();
    
    rc_init_with_default();
    rc_fill_dictionary();
}

- (IBAction)doBackup:(id)sender
{
}

- (IBAction)doRestore:(id)sender
{
}

- (IBAction)getDirlist:(id)sender
{
}

- (IBAction)getIDList:(id)sender
{
}

- (IBAction)getScreen:(id)sender
{
}

- (IBAction)installShell:(id)sender
{
}

- (IBAction)isReady:(id)sender
{
}

- (IBAction)newWindow:(id)sender
{
}

- (IBAction)probeCalc:(id)sender
{
}

- (IBAction)probeLink:(id)sender
{
}

- (IBAction)receiveFLASHApp:(id)sender
{
}

- (IBAction)receiveVar:(id)sender
{
}

- (IBAction)remoteControl:(id)sender
{
}

- (IBAction)romDump:(id)sender
{
}

- (IBAction)romVersion:(id)sender
{
}

- (IBAction)saveConfig:(id)sender
{
    NSUserDefaults *myPrefs;

    rc_save_user_prefs();
    
    myPrefs = objects_ptr->prefs;
    
    [myPrefs synchronize];
}

- (IBAction)sendAMS:(id)sender
{
}

- (IBAction)sendFLASHApp:(id)sender
{
}

- (IBAction)sendVar:(id)sender
{
}

- (IBAction)showThanks:(id)sender
{
}

@end
