/*
 * TiLP Cocoa GUI for Mac OS X
 */
 
 #include "cocoa_msg_sheets.h"
 #include "cocoa_structs.h"
 
 extern struct cocoa_classes_ptr *classes_ptr;
 
 #import <Cocoa/Cocoa.h>
 
 /*
  * Common to msg_sheet, user1_box, pbar_type2
  * A private function, not to be used anywhere else.
  */

/*
 static int
 create_cocoa_msg_sheet_common(const char *title, char *msg, const char *button1, int type)
 {
    return 0;
 }
*/
 
 int
 create_cocoa_user1_sheet (const char *title, char *message, const char *button1)
 {
    return 0;
 }
                                                    
 void
 create_cocoa_pbar_type2_sheet(const char *title, char *message)
 {

 }

 void
 create_cocoa_msg_sheet(const char *title, char *message)
 {
    
 }
 
 /* user boxes */
 
 int
 create_cocoa_user2_sheet(const char *title, char *message, const char *button1, const char *button2)
 {
    return 0;
 }
 
 int
 create_cocoa_user3_sheet(const char *title, char *message, const char *button1, const char *button2, const char *button3)
 {
    return 0;
 }
 
 /* dialog box w/entry field */
 
 char *
 create_cocoa_dlgbox_entry(const char *title, const char *message, const char *content)
 {
    return NULL;
 }
 
 /* pbars */
 
 void
 create_cocoa_pbar_type1_sheet(const char *title)
 {
 
 }
 
 void
 create_cocoa_pbar_type3_sheet(const char *title)
 {
 
 }
 
 void
 create_cocoa_pbar_type4_sheet(const char *title, char *text)
 {
 
 }
 
 void
 create_cocoa_pbar_type5_sheet(const char *title, char *text)
 {
 
 }
 

/* destroy pbars */
 
 void
 destroy_pbar(void)
 {
 
 }
