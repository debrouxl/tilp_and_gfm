#include <gtk/gtk.h>

enum {
  CTREE_NAME, CTREE_ATTR, CTREE_TYPE, CTREE_SIZE,
  CTREE_DATA, CTREE_FONT, CTREE_ICON,
  CTREE_NUMBER
};
#define CTREE_NCOLS CTREE_DATA

void
on_window1_destroy                     (GtkObject       *object,
                                        gpointer         user_data);
