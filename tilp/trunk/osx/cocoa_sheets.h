/*
 * TiLP Cocoa GUI for Mac OS X
 */
 
#ifndef __COCOA_MSG_SHEETS_H__
#define __COCOA_MSG_SHEETS_H__

void
create_cocoa_msg_sheet		(const char *title,
                                 char *message);
 
int
create_cocoa_user1_sheet	(const char *title,
                                 char *message,
                                 const char *button1);
                                                    
void
create_cocoa_pbar_type2_sheet	(const char *title,
                                 char *message);
 
 
int
create_cocoa_user2_sheet	(const char *title,
                                 char *message,
                                 const char *button1,
                                 const char *button2);
 
int
create_cocoa_user3_sheet	(const char *title,
                                 char *message,
                                 const char *button1,
                                 const char *button2,
                                 const char *button3);

char *
create_cocoa_dlgbox_entry	(const char *title,
                                 const char *message,
                                 const char *content);
 
void
create_cocoa_pbar_type1_sheet	(const char *title);
 
void
create_cocoa_pbar_type3_sheet	(const char *title);
 
void
create_cocoa_pbar_type4_sheet	(const char *title,
                                 char *text);
 
void
create_cocoa_pbar_type5_sheet	(const char *title,
                                 char *text);

void
destroy_pbar			(void);

#endif /* !__COCOA_MSG_SHEETS_H__ */
 