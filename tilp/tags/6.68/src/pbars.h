#include <gtk/gtk.h>

void create_pbar_type1(const gchar * title);
void create_pbar_type2(const gchar * title, gchar * text);
void create_pbar_type3(const gchar * title);
void create_pbar_type4(const gchar * title, gchar * text);
void create_pbar_type5(const gchar * title, gchar * text);
void destroy_pbar(void);

GLADE_CB void on_pbar_okbutton1_pressed(GtkButton * button,
					gpointer user_data);
