#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../src/gui_indep.h"
#include "../src/defs.h"
#include "../src/cb_misc.h"
#include "../src/main.h"

#include "cocoa_msg_sheets.h"
#include "cocoa_structs.h"

extern struct cocoa_objects_ptr *objects_ptr;

#import "TilpController.h"

@implementation TilpController

struct gui_fncts gui_functions;

- (void)awakeFromNib
{    
  /* Init the classes pointers */
  objects_ptr->BoxesController = BoxesController;
  objects_ptr->MenuController = MenuController;
  objects_ptr->PrefsController = PrefsController;
  objects_ptr->ToolbarController = ToolbarController;
  objects_ptr->TilpController = self;
    
  /* Init the GUI independant functions */
  gui_functions.msg_box = create_cocoa_msg_sheet;
  gui_functions.user1_box = create_cocoa_user1_sheet;
  gui_functions.user2_box = create_cocoa_user2_sheet;
  gui_functions.user3_box = create_cocoa_user3_sheet;
  gui_functions.dlgbox_entry = create_cocoa_dlgbox_entry;
  gui_functions.create_pbar_type1 = create_cocoa_pbar_type1_sheet;
  gui_functions.create_pbar_type2 = create_cocoa_pbar_type2_sheet;
  gui_functions.create_pbar_type3 = create_cocoa_pbar_type3_sheet;
  gui_functions.create_pbar_type4 = create_cocoa_pbar_type4_sheet;
  gui_functions.create_pbar_type5 = create_cocoa_pbar_type5_sheet;
  gui_functions.destroy_pbar = destroy_pbar;
  set_gui_fncts(&gui_functions);
  
  //gt_init_refresh_functions();  //depends on GTK, needs to be reimplemented.
    
  /* 
     If variables have been passed on the command line in GUI mode then
     send them 
  */
  if(working_mode == MODE_OSX)
    {
      cb_send_cmdline();
    }
}

@end
