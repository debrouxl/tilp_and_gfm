#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif				/*  */

#include <gtk/gtk.h>
#include <glade/glade.h>

#include "gstruct.h"
#include "tilp_core.h"
#include "pbars.h"

/* 
    For Win32 platforms, it is better to use discrete pbar 
    because they are faster. 
*/
#ifdef __WIN32__
#define PROGRESS_TYPE GTK_PROGRESS_CONTINUOUS
#else				/*  */
#define PROGRESS_TYPE GTK_PROGRESS_CONTINUOUS
#endif				/*  */

struct progress_window p_win = { 0 };
static GtkWidget *pbar_window = NULL;

/* Create a window with one progress bar */
void create_pbar_type1(const gchar * title)
{
	GladeXML *xml;

	info_update.prev_percentage = 0.0;
	info_update.percentage = 0.0;
	info_update.cancel = 0;

	xml = glade_xml_new
	    (tilp_paths_build_glade("pbars-2.glade"), "pbar1_dbox",
	     PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	pbar_window = glade_xml_get_widget(xml, "pbar1_dbox");
	gtk_window_set_title(GTK_WINDOW(pbar_window), title);

	p_win.pbar1 = glade_xml_get_widget(xml, "progressbar1");
	p_win.label_rate = glade_xml_get_widget(xml, "label20");

	gtk_widget_show_all(pbar_window);
}


/* Create a window with one label */
void create_pbar_type2(const gchar * title, gchar * text)
{
	GladeXML *xml;

	info_update.prev_percentage = 0.0;
	info_update.percentage = 0.0;
	info_update.cancel = 0;

	xml = glade_xml_new
	    (tilp_paths_build_glade("pbars-2.glade"), "pbar2_dbox",
	     PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	pbar_window = glade_xml_get_widget(xml, "pbar2_dbox");
	gtk_window_set_title(GTK_WINDOW(pbar_window), title);

	p_win.label = glade_xml_get_widget(xml, "label3");
	gtk_label_set_text(GTK_LABEL(p_win.label), text);

	gtk_widget_show_all(pbar_window);
}


/* Create a window with two progress bars */
void create_pbar_type3(const gchar * title)
{
	GladeXML *xml;

	info_update.prev_main_percentage = 0.0;
	info_update.main_percentage = 0.0;
	info_update.prev_percentage = 0.0;
	info_update.percentage = 0.0;
	info_update.cancel = 0;

	xml = glade_xml_new
	    (tilp_paths_build_glade("pbars-2.glade"), "pbar3_dbox",
	     PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	pbar_window = glade_xml_get_widget(xml, "pbar3_dbox");
	gtk_window_set_title(GTK_WINDOW(pbar_window), title);

	p_win.pbar1 = glade_xml_get_widget(xml, "progressbar3");
	p_win.pbar2 = glade_xml_get_widget(xml, "progressbar2");
	p_win.label_rate = glade_xml_get_widget(xml, "label21");

	gtk_widget_show_all(pbar_window);
}


/* Create a window with a one progress bar and one label */
void create_pbar_type4(const gchar * title, gchar * text)
{
	GladeXML *xml;

	info_update.percentage = 0.0;
	info_update.cancel = 0;

	xml = glade_xml_new
	    (tilp_paths_build_glade("pbars-2.glade"), "pbar4_dbox",
	     PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	pbar_window = glade_xml_get_widget(xml, "pbar4_dbox");
	gtk_window_set_title(GTK_WINDOW(pbar_window), title);

	p_win.label = glade_xml_get_widget(xml, "label15");
	gtk_label_set_text(GTK_LABEL(p_win.label), text);
	p_win.pbar1 = glade_xml_get_widget(xml, "progressbar4");
	p_win.label_rate = glade_xml_get_widget(xml, "label22");

	gtk_widget_show_all(pbar_window);
}


/* Create a window with two progress bars and one label */
void create_pbar_type5(const gchar * title, gchar * text)
{
	GladeXML *xml;

	info_update.prev_main_percentage = 0.0;
	info_update.main_percentage = 0.0;
	info_update.prev_percentage = 0.0;
	info_update.percentage = 0.0;
	info_update.cancel = 0;

	xml = glade_xml_new
	    (tilp_paths_build_glade("pbars-2.glade"), "pbar5_dbox",
	     PACKAGE);
	if (!xml)
		g_error("GUI loading failed !\n");
	glade_xml_signal_autoconnect(xml);

	pbar_window = glade_xml_get_widget(xml, "pbar5_dbox");
	gtk_window_set_title(GTK_WINDOW(pbar_window), title);

	p_win.label = glade_xml_get_widget(xml, "label19");
	gtk_label_set_text(GTK_LABEL(p_win.label), text);
	p_win.pbar1 = glade_xml_get_widget(xml, "progressbar6");
	p_win.pbar2 = glade_xml_get_widget(xml, "progressbar5");
	p_win.label_rate = glade_xml_get_widget(xml, "label23");

	gtk_widget_show_all(pbar_window);
}


/* 
   Destroy a pbar window
*/
void destroy_pbar(void)
{
	p_win.pbar1 = NULL;
	p_win.pbar2 = NULL;
	p_win.label = NULL;
	if (pbar_window)
		gtk_widget_destroy(pbar_window);
	pbar_window = NULL;
}


GLADE_CB void on_pbar_okbutton1_pressed(GtkButton * button,
					gpointer user_data)
{
	info_update.cancel = 1;
}
