#ifndef __DBOXES_H__
#define __DBOXES_H__

#include <gtk/gtk.h>


void msg_box(const gchar * title, gchar * message);
gint msg_box2(const char *title, char *message);
gint msg_box3(const char *title, char *message,
	      const char *button1, const char *button2,
	      const char *button3);
gint msg_box4(const char *title, char *message);
char *msg_entry(const char *title,
		const char *message, const char *content);


#endif
