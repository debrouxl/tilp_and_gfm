#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <gtk/gtk.h>
#include <fcntl.h> //open

#include "gtk_probeio_cb.h"
#include "gtk_probeio_dbox.h"
#include "support.h"

#include "includes.h"

#if defined(__LINUX__)
#elif defined(__WIN32__)
# define STDIN_FILENO  0//(fileno(CONIN$))
# define STDOUT_FILENO 1//(fileno(CONOUT$))
# define STDERR_FILENO 2//(fileno(CONOUT$))
#endif

static gint id = -1;
static gint pfd[2]; // pfd[0] is for reading, the other for writing
static gint old;

/*
  This function is called whenever a data is available for reading
  on the pipe output
 */
static void result(GtkWidget *widget, gint source, 
		   GdkInputCondition condition)
{
  gchar buf[MAXCHARS];
  gint lu;
  
  lu = read(source, buf, MAXCHARS);
  if(lu)
    {
      gtk_text_insert(GTK_TEXT(widget), NULL, NULL, NULL, buf, lu);
    }
}

void
probeio_ok_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar *os;
  PortInfo pi;
  GtkWidget *text = GTK_WIDGET(user_data);

  /* Backup stdout file descriptor */
  old = dup(STDOUT_FILENO);

  /* Open a pipe between stdout and the box */
  if(pipe(pfd) == -1)
    {
      g_warning("Unable to create an unnamed pipe.\n");
      return;
    }

  /* Redirect stdout to the pipe input */
  dup2(pfd[1], STDOUT_FILENO);
  //ticable_change_display(pfd[1]);
  ticable_detect_os(&os);
  ticable_detect_port(&pi);

  gtk_editable_delete_text(GTK_EDITABLE(text), 0, -1);
  id = gdk_input_add(pfd[0], GDK_INPUT_READ, 
		     (GdkInputFunction)result, text);
}


void
probeio_cancel_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_probeio_dbox_destroy                (GtkObject       *object,
                                        gpointer         user_data)
{
  gdk_input_remove(id);
  close(pfd[1]);
  dup2(old, STDOUT_FILENO);
  close(pfd[0]);
  id = -1;
}


/* */
