#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h> //stderr
#include <fcntl.h>  // _O_BINARY for Win32 _pipe function

#include "gtk_shell_cb.h"
#include "gtk_shell_dbox.h"
#include "support.h"
#include "str.h"

#include "includes.h"

static GtkWidget *text;
static GtkWidget *entry;

static gint id1 = -1;
static gint id2 = -1;
static gint pfd[2];   // pfd[0] is for reading, the other for writing
static gint old;
static FILE *file;
static gchar *ext_cmd = NULL; // external command
static gint waiting = 0;      // processing in progress

#if defined(__LINUX__)
#elif defined(__WIN32__)
# define STDIN_FILENO  0//(fileno(CONIN$))
# define STDOUT_FILENO 1//(fileno(CONOUT$))
# define STDERR_FILENO 2//(fileno(CONOUT$))
#endif

/*
  Execute the command given by its command line and display the
  shell dialog box
 */
int execute_command(gchar *cmd_line)
{
  ext_cmd = g_strdup(cmd_line);
  fprintf(stderr, "Command to execute: <%s>\n", ext_cmd);
  gtk_widget_show_all(create_shell_dbox());               // display box
  gtk_signal_emit_by_name(GTK_OBJECT(entry), "activate"); // trigger cmd

  while(!waiting)
    {
      while( gtk_events_pending() ) { gtk_main_iteration(); }
    }
  
  return 0;
}

void
on_shell_dbox_show                      (GtkWidget       *widget,
                                        gpointer         user_data)
{
  text = GTK_WIDGET(user_data);
}


void
on_shell_dbox_show2                    (GtkWidget       *widget,
                                        gpointer         user_data)
{
  entry = GTK_WIDGET(user_data);
}

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
  else
    {
      gdk_input_remove(id1); // stop monitoring
      gdk_input_remove(id2);
      pclose(file);          // close shell
      id1 = id2 = -1;
      g_free(ext_cmd); ext_cmd = NULL;

      close(pfd[1]);			// close pipe
      dup2(old, STDERR_FILENO); // Restore stderr file descriptor
      close(pfd[0]);
    }
}

/*
  Function called whenever the user press the 'Enter' key
*/
void
on_shell_entry1_activate               (GtkEditable     *editable,
                                        gpointer         user_data)
{
  gchar *command;

  if((id1 == -1) || 
     (ext_cmd != NULL)) // if no command in progress or external command
    {  
      gchar *command_aff;
      
      /* Get commands from the entry box */
      if(ext_cmd == NULL)
	command = gtk_entry_get_text(GTK_ENTRY(entry)); //user command
      else
	command = ext_cmd;                              // external command

      /* Check for 'quit' command */
      if(!strcmp(command, "quit")) 
	{
	  gtk_widget_destroy(GTK_WIDGET(user_data));
	  return;
	}

      /* Display command */
      command_aff = g_strdup_printf("\n%s\n", command);
      gtk_text_insert(GTK_TEXT(text), NULL, NULL, NULL, 
		      command_aff, strlen(command_aff));
      g_free(command_aff);

      /* Backup stderr file descriptor */
      old = dup(STDERR_FILENO);
      
      /* Open a pipe between stderr and the box */
      if(pipe(pfd) == -1)
	{
	  g_warning("Unable to create an unnamed pipe.\n");
	  gtk_widget_destroy(GTK_WIDGET(user_data));
	  return;
	}
      
      /* Redirect stderr to the pipe input */
      dup2(pfd[1], STDERR_FILENO);
      
      /* Create a shell session */
      gtk_editable_delete_text(GTK_EDITABLE(entry), 0, -1);
      file = popen(command, "r");
      if(file == NULL)
	{
	  gtk_widget_destroy(GTK_WIDGET(user_data));
	  return;
	}

      /* Capture stdout/stderr activity */
      id1 = gdk_input_add(fileno(file), GDK_INPUT_READ, 
			  (GdkInputFunction)result, text);
      id2 = gdk_input_add(pfd[0], GDK_INPUT_READ, 
			  (GdkInputFunction)result, text);
    }
}

void
on_shell_dbox_destroy                  (GtkObject       *object,
                                        gpointer         user_data)
{
  g_free(ext_cmd);
  waiting = 1;
}

/* */
