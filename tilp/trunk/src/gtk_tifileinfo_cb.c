#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_tifileinfo_cb.h"
#include "gtk_tifileinfo_dbox.h"
#include "support.h"

#include "includes.h"

static gchar *ti_filename = NULL;
#ifdef HAVE_TIFFEP
static FileInfo *fi = NULL;
static gint valid = FALSE;
#endif

int display_ti_file_info(gchar *filename)
{
  ti_filename = g_strdup(filename);

  gtk_widget_show_all(create_tifileinfo_dbox());
  return 0;
}

void
on_tifileinfo_dbox_show                (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  //fprintf(stdout, "filename: <%s>\n", ti_filename);
  if(tiffep_load_file_informations(ti_filename, &fi) != 0)
    valid = FALSE;
  else
    valid= TRUE;
#endif
}

/* entry */
void
on_tifileinfo_dbox_show1               (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  if(valid)
    gtk_entry_set_text(GTK_ENTRY(user_data), FILEINFO_COMMENT(fi));
  else
    gtk_entry_set_text(GTK_ENTRY(user_data), _("unavailable"));
#endif
}

/* label */
void
on_tifileinfo_dbox_show6               (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gchar *str;

  if(valid)
    {
      str = g_strconcat("File name: ", FILEINFO_NAME(fi), NULL);
      gtk_label_set_text(GTK_LABEL(user_data), str);
      g_free(str);
    }
  else
    gtk_label_set_text(GTK_LABEL(user_data), _("unavailable"));    
#endif
}


void
on_tifileinfo_dbox_show7               (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gchar *str;

  if(valid)
    {
      fprintf(stderr, "Binary varname: <<%s>>\n", 
	      VARINFO_CALCNAME(FILEINFO_VARINFO(fi)));
      fprintf(stderr, "Translated varname: <<%s>>\n",
	      VARINFO_REALNAME(FILEINFO_VARINFO(fi)));
      str = g_strconcat("Var name: ", VARINFO_REALNAME(FILEINFO_VARINFO(fi))
			/*fi->var_info->var_name_t*/, NULL);
      gtk_label_set_text(GTK_LABEL(user_data), str);
      g_free(str);     
    }
  else
    gtk_label_set_text(GTK_LABEL(user_data), _("unavailable"));
#endif
}


void
on_tifileinfo_dbox_show8               (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gchar *str;
  
  if(valid)
    {
      str = g_strconcat(_("Calc type: "), 
			calc_type_to_string(VARINFO_CALCTYPE(FILEINFO_VARINFO(fi))), NULL);
      gtk_label_set_text(GTK_LABEL(user_data), str);
      g_free(str);
    }
  else
    gtk_label_set_text(GTK_LABEL(user_data), _("unavailable"));
  
#endif
}


void
on_tifileinfo_dbox_show9               (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
gchar *str;

 if(valid)
   {
     str = g_strconcat("Var type: ", 
		       var_type_to_string(VARINFO_TYPE(FILEINFO_VARINFO(fi)))
		       /*fi->var_info->var_type)*/, NULL);
     gtk_label_set_text(GTK_LABEL(user_data), str);
     g_free(str);
   }
 else
   gtk_label_set_text(GTK_LABEL(user_data), _("unavailable"));
#endif
}


void
on_tifileinfo_dbox_show10              (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
    gchar *str;
    gchar buffer[MAXCHARS];
    
    g_snprintf(buffer, MAXCHARS, "%i", FILEINFO_FILESIZE(fi));
    str = g_strconcat("File size: ", buffer, " bytes", NULL);
    gtk_label_set_text(GTK_LABEL(user_data), str);
    g_free(str);
#endif
}


void
on_tifileinfo_dbox_show11              (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gchar *str;

  if(valid)
    {
      str = g_strconcat("Var path: ", VARINFO_PATH(FILEINFO_VARINFO(fi))
			/*fi->var_info->var_path*/, NULL);
      gtk_label_set_text(GTK_LABEL(user_data), str);
      g_free(str);
    }
  else
    gtk_label_set_text(GTK_LABEL(user_data), _("unavailable"));
#endif
}


void
on_tifileinfo_dbox_show12              (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gchar *str;
  gchar buffer[MAXCHARS];

  if(valid)
    {  
      g_snprintf(buffer, MAXCHARS, "%i", FILEINFO_DATASIZE(fi));
      str = g_strconcat("Data size: ", buffer, " bytes", NULL);
      gtk_label_set_text(GTK_LABEL(user_data), str);
      g_free(str);
    }
  else
    gtk_label_set_text(GTK_LABEL(user_data), _("unavailable"));
#endif
}


void
on_tifileinfo_dbox_show13              (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gchar *str;
  gchar buffer[MAXCHARS];

  if(valid)
    {  
      g_snprintf(buffer, MAXCHARS, "%i", VARINFO_SIZE(FILEINFO_VARINFO(fi))
		 /*fi->var_info->var_size*/);
      str = g_strconcat("Var size: ", buffer, " bytes", NULL);
      gtk_label_set_text(GTK_LABEL(user_data), str);
      g_free(str);
    }
  else
    gtk_label_set_text(GTK_LABEL(user_data), _("unavailable"));
#endif
}


void
on_tifileinfo_dbox_show14              (GtkWidget       *widget,
                                        gpointer         user_data)
{

}


void
on_tifileinfo_dbox_show15              (GtkWidget       *widget,
                                        gpointer         user_data)
{
#ifdef HAVE_TIFFEP
  gchar *str;
  gchar buffer[MAXCHARS];

  if(valid)
    {  
      g_snprintf(buffer, MAXCHARS, "%i", FILEINFO_NUMVARS(fi) 
		 /*fi->num_of_vars*/);
      str = g_strconcat("Number of vars: ", buffer, NULL);
      gtk_label_set_text(GTK_LABEL(user_data), str);
      g_free(str);
    }
  else
    gtk_label_set_text(GTK_LABEL(user_data), _("unavailable"));
#endif
}


void
on_tifileinfo_ok_button_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
  g_free(ti_filename);
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_tifileinfo_cancel_button_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
  g_free(ti_filename);
  gtk_widget_destroy(GTK_WIDGET(user_data));
}
