#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
*/
#include "gtk_lang_cb.h"
#include "gtk_lang_dbox.h"
#include "support.h"

#include "includes.h"

static gchar* tmp_locale;

void
lang_ok_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
  strcpy(options.locale, tmp_locale);
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
lang_cancel_button_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_lang_dbox_show                      (GtkWidget       *widget,
                                        gpointer         user_data)
{

}


void
on_lang_dbox_show2                     (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gtk_entry_set_text (GTK_ENTRY (user_data), options.locale);
}


void
on_lang_dbox_show3                     (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkWidget *combo = GTK_WIDGET(user_data);
  GList *items = NULL;

  DIR *dir;
  struct dirent *file;
  struct stat f_info;
  gchar *path;
  gchar *s = NULL;
  gchar *path2;

  items = g_list_append(items, "C");
  
  /* Get locale path for internationalization */
  path = (gchar *)g_malloc((strlen(inst_paths.locale_dir)
			   + 1) * sizeof(gchar));
	strcpy(path, inst_paths.locale_dir);
 
  if( (dir=opendir(path)) == NULL) 
    {
      fprintf(stderr, _("Opendir error\n"));
    }
  while( (file=readdir(dir)) != NULL) 
    {
      if(!strcmp(file->d_name, ".")) { continue; }
      if(!strcmp(file->d_name, "..")) { continue; }
      path2 = (gchar *)g_malloc((strlen(path) + 1 + 
				 strlen(file->d_name) + 1) *
				sizeof(gchar));
      strcpy(path2, path);
      strcat(path2, G_DIR_SEPARATOR_S);
      strcat(path2, file->d_name);
      if(stat(path2, &f_info) == 0)
	{
	  if(S_ISDIR(f_info.st_mode))
	    {
	      s = (gchar *)g_malloc((strlen(file->d_name) + 1) *
				    sizeof(gchar));
	      strcpy(s, file->d_name);
		  //fprintf(stderr, "scanned: <%s>\n", s);
	      items = g_list_append(items, s);
	    }
	}
      g_free(path2);
    }
  if(closedir(dir)==-1)
    {
      fprintf(stderr, _("Closedir error\n"));
    }

    gtk_combo_set_popdown_strings(GTK_COMBO(combo), items);
}


void
on_lang_combo_entry1_changed           (GtkEditable     *editable,
                                        gpointer         user_data)
{
  tmp_locale = gtk_editable_get_chars(editable, 0, -1);
}

/* */

