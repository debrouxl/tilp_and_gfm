#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>

#include "gtk_about_cb.h"
#include "gtk_about_dbox.h"
#include "support.h"

#include "includes.h"
#include "version.h"

Image img = { NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0 };

void
on_about_dbox_show_text                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  FILE *fd;
  gchar buffer[MAXCHARS];
  GdkFont *fixed_font;
  GtkWidget *text;

  text = GTK_WIDGET(user_data);
  gtk_text_freeze(GTK_TEXT (text));
  gtk_editable_delete_text(GTK_EDITABLE(text), 0, -1);

  /* Create the base filename */
  strcpy(buffer, inst_paths.base_dir);  // retrieve base path
  strcat(buffer, SHARE_DIR);          //
  strcat(buffer, DIR_SEPARATOR);
#if defined(__UNIX__)
  strcat(buffer, "COPYING");
#elif defined(__WIN32__)
  strcat(buffer, "Copying.txt");
#endif

  /* Try to access the file */
  if(access(buffer, F_OK) == 0 )
    {
#if defined(__LINUX__)
      fixed_font = gdk_font_load ("-misc-clean-medium-r-*-*-*-140-*-*-*-*-*-*");
#elif defined(__WIN32__)
      fixed_font = gdk_font_load ("-adobe-courier-medium-r-normal--12-120-75-75-p-70-iso8859-1");
#endif
      if( (fd=fopen (buffer, "r")) != NULL)
	{
	  memset (buffer, 0, sizeof(buffer));
	  while(fread (buffer, 1, sizeof(buffer)-1, fd))
            {
              gtk_text_insert (GTK_TEXT (text), fixed_font, NULL, NULL, buffer, strlen (buffer));
              memset (buffer, 0, sizeof(buffer));
            }
	  fclose (fd);
	}
    }
  gtk_text_thaw(GTK_TEXT (text));
}


void
on_about_dbox_show_label               (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar tempstr[MAXCHARS];

  g_snprintf (tempstr, sizeof (tempstr), "TiLP v%s\n", TILP_VERSION);
  gtk_label_set_text(GTK_LABEL(user_data), tempstr);
}


void
about_ok_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  //delete_image(&img);
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_about_dbox_show_pixmap              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  return;
#if 0
  /* buggy code -- avoid segfault ... */
  GtkWidget *tmp_pixmapwid = GTK_WIDGET(user_data);
  GdkPixmap *pixmap;
  GdkBitmap *mask;
  GtkStyle *style;
  FILE *f;
  gchar buffer[MAXCHARS];

  return;

  /* Create the base filename */
  strcpy(buffer, inst_paths.base_dir);  // retrieve base path
  strcat(buffer, SHARE_DIR);          //
  strcat(buffer, DIR_SEPARATOR);
#if defined(__UNIX__)
  strcat(buffer, "logo.jpg");
#elif defined(__WIN32__)
  strcat(buffer, "logo.jpg");
#endif
  DISPLAY("logo: <%s>\n", buffer);
  /* Try to access the file */
  if(access(buffer, F_OK) == 0 )
    {
      /* Open and load file */
      f = fopen(buffer, "rb");
      if(f == NULL)
	g_error("Unable to open the logo (logo.jpg).\n");
      img.depth = 3; // > 2 colors
      read_jpg_format(f, &img);
      fclose(f);

      convert_bytemap_to_pixmap(&img);

      style = gtk_widget_get_style(widget);
      pixmap = gdk_pixmap_create_from_xpm_d(widget->window, &mask,
					    &style->bg[GTK_STATE_NORMAL],
					    (gchar **)(img.pixmap));
      gtk_pixmap_set(GTK_PIXMAP(tmp_pixmapwid), pixmap, mask);      
    }
  else 
    g_warning("Unable to open the logo (logo.jpg).\n");
#endif
}

