#include <gtk/gtk.h>


GtkWidget *display_tilp_dbox();


void on_tilp_dbox_destroy(GtkObject * object, gpointer user_data);

void on_save_config1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on_reload_config1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on_default_config1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_quit1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_general1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on_external_programs1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on_communication1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on__amp_amp_clock1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_get_idlist1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on_terminal__amp_amp__remote1_activate(GtkMenuItem * menuitem,
				       gpointer user_data);

void on_rom_dump1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_upgrade_os1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_help2_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_manpage1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on_ti_s_web_site1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on_calculator_software1_activate(GtkMenuItem * menuitem,
				 gpointer user_data);

void on_ticalcorg1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_tinewsnet1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_ti_frorg1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_the_lpg1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on_tilp_s_web_site1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_about1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_tilp_button4_clicked(GtkButton * button, gpointer user_data);

void on_tilp_button5_clicked(GtkButton * button, gpointer user_data);

void on_tilp_button6_clicked(GtkButton * button, gpointer user_data);

void on_tilp_button7_clicked(GtkButton * button, gpointer user_data);

void on_tilp_button8_clicked(GtkButton * button, gpointer user_data);

void on_tilp_button9_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button9b_clicked(GtkButton * button, gpointer user_data);

void on_tilp_button10_clicked(GtkButton * button, gpointer user_data);

void on_tilp_button11_clicked(GtkButton * button, gpointer user_data);

void on_tilp_button12_clicked(GtkButton * button, gpointer user_data);

gboolean
on_ctree1_button_press_event(GtkWidget * widget,
			     GdkEventButton * event, gpointer user_data);

gboolean
on_tilp_clist1_button_press_event(GtkWidget * widget,
				  GdkEventButton * event,
				  gpointer user_data);

void on_clock1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_remote1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_manual1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on_ti_s_web_site1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_ti_frorg1_activate(GtkMenuItem * menuitem, gpointer user_data);

void
on_tilp_s_web_site1_activate(GtkMenuItem * menuitem, gpointer user_data);

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
