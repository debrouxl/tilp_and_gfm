#ifndef __TILP_TILP_H__
#define __TILP_TILP_H__

#include <gtk/gtk.h>

extern GtkWidget *main_wnd;
extern GtkWidget *clist_wnd;
extern GtkWidget *ctree_wnd;

void show_right_view(int view);

GtkWidget *display_tilp_dbox(void);

void on_hpaned1_size_request(GtkPaned* paned, gpointer user_data);

void on_tilp_dbox_destroy(GtkWidget * object, gpointer user_data);

gboolean on_tilp_dbox_delete_event(GtkWidget* widget, GdkEvent* event, gpointer user_data);

void on_rom_dump1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_manpage1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_ti_s_web_site1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_calculator_software1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_ticalcorg1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_tiplanetorg1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_ti_frorg1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_the_lpg1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_tilp_s_web_site1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_bug_report1_activate (GtkMenuItem *menuitem, gpointer user_data);

void on_changelog1_activate(GtkMenuItem* menuitem, gpointer user_data);

void on_about1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_tilp_button1_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button2_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button3b_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button3_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button4_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button5_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button6_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button7_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button8_clicked(GtkButton * button, gpointer user_data);

void on_tilp_button10_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button11_clicked(GtkButton * button, gpointer user_data);
void on_tilp_button12_clicked(GtkButton * button, gpointer user_data);
void on_tilp_menuitem7_clicked(GtkButton * button, gpointer user_data);
void on_button14_clicked(GtkButton * button, gpointer user_data);
void on_tilp_menuitem9_clicked(GtkButton * button, gpointer user_data);
void on_tilp_menuitem10_clicked(GtkButton * button, gpointer user_data);
void on_tilp_menuitem12_clicked(GtkButton * button, gpointer user_data);
void on_tilp_viewmenu_active(GtkButton* button, gpointer user_data);

void on_manual1_activate(GtkMenuItem * menuitem, gpointer user_data);

void on_tilp_recv(void);
void on_tilp_send(const gchar *user_data);

#endif
