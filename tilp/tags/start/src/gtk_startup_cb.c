#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_startup_cb.h"
#include "gtk_startup_dbox.h"
#include "support.h"

#include "includes.h"
#include "version.h"

void display_startup_dbox(void)
{
  gchar str[MAXCHARS];
  FILE *f;
  gchar *buffer;
  char *home_dir;

  /* Display the startup box */
#if defined(__UNIX__)
  get_home_path(&home_dir);
  buffer = (char *)g_malloc((strlen(home_dir) + 
			     strlen(DIR_SEPARATOR) + strlen(ST_FILE) + 1)
			    * sizeof(char));
  strcpy(buffer, home_dir); g_free(home_dir);
  strcat(buffer, DIR_SEPARATOR);
  strcat(buffer, ST_FILE);
#elif defined(__WIN32__)
  buffer = (char *)g_malloc((strlen(inst_paths.base_dir) + 
				strlen(DIR_SEPARATOR) + strlen(ST_FILE) + 1) 
				* sizeof(char));
  strcpy(buffer, inst_paths.base_dir);
  strcat(buffer, DIR_SEPARATOR);
  strcat(buffer, ST_FILE);
#endif

  /* Try to access the file */
  if(access(buffer, F_OK) != 0 )
    {
      // file not found
      //fprintf(stderr, "File not found. Create it.\n");
      f = fopen(buffer, "wt");
      if(f == NULL)
	{
	  fprintf(stderr, 
		  "Unable to open/create this file: <%s>.\n", buffer);
	  
	  g_free(buffer);
	  return;
	}
      fprintf(f, "%s\n", TILP_VERSION);
      fclose(f);
      gtk_widget_show(create_startup_dbox());
    }
  else
    {
      // file found
      //fprintf(stderr, "File found.\n");
      f = fopen(buffer, "rt");
      if(f == NULL)
	{
	  fprintf(stderr, 
		  "Unable to open/create this file: <%s>.\n", buffer);
	  return;
	}
      fgets(str, MAXCHARS, f);
      //fprintf(stderr, "<%s>\n", str);
      if(strcmp(TILP_VERSION, str) > 0)
	{
	  fclose(f);
	  f = fopen(buffer, "wt");
	  if(f == NULL)
	    {
	      fprintf(stderr, 
		      "Unable to open/create this file: <%s>.\n", buffer);

	      g_free(buffer);
	      return;
	    }
	  fprintf(f, "%s\n", TILP_VERSION);	
	  gtk_widget_show(create_startup_dbox());
	}
      fclose(f);
    }

  g_free(buffer);
}

void
on_startup_dbox_show                   (GtkWidget       *widget,
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
  strcat(buffer, "ChangeLog");
#elif defined(__WIN32__)
  strcat(buffer, "ChangeLog.txt");
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
startup_ok_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

