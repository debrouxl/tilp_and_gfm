#ifndef __DBOXES_H__
#define __DBOXES_H__

#include <gtk/gtk.h>

int msg_box1(const gchar * title, gchar * message);
int msg_box2(const char *title, char *message);
int msg_box3(const char *title, char *message, const char *button1, const char *button2, const char *button3);
int msg_box4(const char *title, char *message);

char *msg_entry(const char *title, const char *message, const char *content);

#endif
