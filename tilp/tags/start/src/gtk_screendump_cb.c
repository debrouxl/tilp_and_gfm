#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_screendump_cb.h"
#include "gtk_screendump_dbox.h"
#include "support.h"

/*
  !!! A very important remark !!!
  If a block has been allocated with g_malloc,
  it must be freed with g_free, NOT with free else it will
  provoke a memory fault under Windows.
*/

#include "includes.h"

GtkWidget *tmp_window;
GtkWidget *tmp_pixmapwid;
extern struct screenshot ti_screen;

void
on_screendump_dbox_show1               (GtkWidget       *widget,
                                        gpointer         user_data)
{
  tmp_window = widget;
  tmp_pixmapwid = GTK_WIDGET(user_data);
}

/* Display pixmap on the first time */
void
on_screendump_dbox_show2               (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkStyle *style;
  GdkPixmap *pixmap;
  GdkBitmap *mask;

  if(is_active) return;

  /* Get a screen capture */
  if(cb_screen_capture() != 0) return;

  /* Convert it into a pixmap and displays it */
  convert_bitmap_to_pixmap(&(ti_screen.img));
  style = gtk_widget_get_style(widget);
  pixmap = gdk_pixmap_create_from_xpm_d(tmp_window->window, &mask, 
					&style->bg[GTK_STATE_NORMAL],
					(gchar **)(ti_screen.img.pixmap));
  gtk_pixmap_set(user_data, pixmap, mask);
}

/* Save pixmap */
void
on_sc_save1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_screendump_fileselection());
}

/* Load pixmap */
void
on_sc_load1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_screendump_fileselection2());
}

/* Capture again */
void
on_sc_recapture1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GdkPixmap *pixmap;
  GdkBitmap *mask;
  GtkStyle *style;

  if(is_active) return;

  /* Get a screen capture */
  if(cb_screen_capture() != 0) return;

  /* Redisplays the pixmap */
  convert_bitmap_to_pixmap(&(ti_screen.img));  
  style=gtk_widget_get_style(tmp_window);
  pixmap=gdk_pixmap_create_from_xpm_d(tmp_window->window, &mask,
                                      &style->bg[GTK_STATE_NORMAL],
                                      (gchar **)(ti_screen.img.pixmap));
  gtk_pixmap_set(user_data, pixmap, mask);
}

/* Screen capture options */
void
on_sc_options1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_scopt_dbox());
}


void
on_sc_help1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_help_dbox());
}


void
on_sc_about1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_about_dbox());
}


void
on_sc_quit1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_screendump_ok_button1_clicked                  (GtkButton       *button,
						   gpointer         user_data)
{
  char filename[MAXCHARS];
  gint ret;
  gint skip=0;
  gchar buffer[MAXCHARS];
  gchar *dirname;

  strcpy(filename,
         gtk_file_selection_get_filename(GTK_FILE_SELECTION (user_data)));
  
  if(options.confirm == CONFIRM_YES)
    {
      if(access(filename, F_OK) == 0)
        {
          sprintf(buffer, _("The file %s already exists.\n\n"),
                  filename);
          ret=user3_box(_("Warning"), buffer,
                        _(" Overwrite "), _(" Rename "),
                        _(" Skip "));
	  
	  switch(ret)
	    {
	    case BUTTON2:
	      dirname=dlgbox_entry(_("Rename the file"),
				   _("New name: "), filename);
	      if(dirname == NULL) return;
	      strcpy(filename, dirname);
	      g_free(dirname);
	    case BUTTON1:
	      skip=0;
	      break;
	    case BUTTON3:
	      skip=1;
	      break;
	    }
	}
    }
  if(skip == 0)
    {
      if(cb_screen_save(filename) != 0)
	return;
    }
  
  l_directory_list();
  refresh_clist(main_window);
  refresh_info(main_window);
  
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_screendump_cancel_button1_clicked              (GtkButton       *button,
						   gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_screendump_fileselection_show                 (GtkWidget       *widget,
						  gpointer         user_data)
{
  if(options.screen_format == XPM)
    gtk_file_selection_set_filename(GTK_FILE_SELECTION(user_data), 
				    "screendump.xpm");
  else if(options.screen_format == PCX)
    gtk_file_selection_set_filename(GTK_FILE_SELECTION(user_data), 
				    "screendump.pcx");
  else if(options.screen_format == JPG)
    gtk_file_selection_set_filename(GTK_FILE_SELECTION(user_data), 
				    "screendump.jpg");
  else 
    g_error("Unkwown file format. Report this bug !");
}

/* Toolbar button: refresh */
void
on_scdbox_button1_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
  on_sc_recapture1_activate(NULL, user_data);
}

/* Toolbar button: save */
void
on_scdbox_button2_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_screendump_fileselection());
}

/* Toolbar button: quit */
void
on_scdbox_button3_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

/* Toolbar button: help */
void
on_scdbox_button4_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_help_dbox());
}

/* */

void
on_screendump_fileselection2_show      (GtkWidget       *widget,
                                        gpointer         user_data)
{

}

#undef TEST
#define TEST

void
on_screendump_ok_button2_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
  GdkPixmap *pixmap;
  GdkBitmap *mask;
  GtkStyle *style;
  gchar *filename = "screendump.pcx";
  FILE *f;
  gint i;
  gchar *ext;

  filename = gtk_file_selection_get_filename(GTK_FILE_SELECTION (user_data));
  ext = (gchar *)strrchr(filename, '.');

  /* Open and load file */
#ifndef TEST
  f = fopen(filename, "rb");
  if(f == NULL)
  {
    g_warning("Unable to open file: <%s>.\n", filename);
	return ;
  }
  ti_screen.img.depth = 2;
  if(!strcasecmp(ext, ".pcx"))
    read_pcx_format(f, &(ti_screen.img));
  else if(!strcasecmp(ext, ".xpm"))
    read_xpm_format(f, &(ti_screen.img));
  else if(!strcasecmp(ext, ".jpg"))
    read_jpg_format(f, &(ti_screen.img));
  else
    {
      g_error("Invalid file\n");
      return;
    }
  fclose(f);
#else
  DISPLAY("!!! Test mode !!!\n");
  f = fopen(filename, "wb");
  if(f == NULL)
  {
    g_warning("Unable to open file: <%s>.\n", filename);
	return ;
  }
  delete_image(&(ti_screen.img));
  ti_screen.img.depth = 250;
  ti_screen.img.width = 160;
  ti_screen.img.height = 100;
  ti_screen.img.inverted = 0;
  ti_screen.img.bytemap = (byte *)malloc(ti_screen.img.width * 
					 ti_screen.img.height * 
					 sizeof(byte));
  ti_screen.img.colormap = (byte *)malloc(3 * 256 * sizeof(byte));
  
  for(i=0; i<ti_screen.img.depth; i++)
    {
      ti_screen.img.colormap[3*i+0] = i - i % 32;
      ti_screen.img.colormap[3*i+1] = (i / 32) * 4 + i - i % 32;
      ti_screen.img.colormap[3*i+2] = i - i % 64;
    }
  for(i=0; i<ti_screen.img.width * ti_screen.img.height; i++) 
    ti_screen.img.bytemap[i] = i % (ti_screen.img.depth);
  write_jpg_format(f, &(ti_screen.img));
  fclose(f);
#endif
  
  /* Redisplays the pixmap */
#ifndef TEST
  convert_bitmap_to_pixmap(&(ti_screen.img));
#else  
  convert_bytemap_to_pixmap(&(ti_screen.img));
#endif

  style=gtk_widget_get_style(tmp_window);
  pixmap=gdk_pixmap_create_from_xpm_d(tmp_window->window, &mask,
                                      &style->bg[GTK_STATE_NORMAL],
                                      (gchar **)(ti_screen.img.pixmap));
  gtk_pixmap_set(GTK_PIXMAP(tmp_pixmapwid), pixmap, mask);
  g_free(filename);
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_screendump_cancel_button2_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}
