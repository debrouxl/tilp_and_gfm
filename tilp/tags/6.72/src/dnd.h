#ifndef __DND_H__
#define __DND_H__

#include <gtk/gtk.h>

void
on_treeview1_drag_begin(GtkWidget * widget,
			GdkDragContext * drag_context, gpointer user_data);

void
on_treeview1_drag_data_get(GtkWidget * widget,
			   GdkDragContext * drag_context,
			   GtkSelectionData * data,
			   guint info, guint time, gpointer user_data);

gboolean
on_treeview2_button_press_event(GtkWidget * widget,
				GdkEventButton * event,
				gpointer user_data);

void
on_treeview2_drag_begin(GtkWidget * widget,
			GdkDragContext * drag_context, gpointer user_data);

void
on_treeview2_drag_data_get(GtkWidget * widget,
			   GdkDragContext * drag_context,
			   GtkSelectionData * data,
			   guint info, guint time, gpointer user_data);

void
on_treeview2_drag_data_received(GtkWidget * widget,
				GdkDragContext * drag_context,
				gint x,
				gint y,
				GtkSelectionData * data,
				guint info,
				guint time, gpointer user_data);

#endif
