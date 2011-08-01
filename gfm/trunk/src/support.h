/*
  Name: Group File Manager
  Copyright (C) 2006 Tyler Cassidy, Romain Lievin, Kevin Kofler
  29/05/06 17:29 - support.h
  
  This program is free software you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation either version 2 of the License, or
  (at your option) any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gtk/gtk.h>

/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif

#if defined(__WIN32__) && !defined(__MINGW32__)
# undef PACKAGE
# define PACKAGE   "gfm"
# define LOCALEDIR ""
#endif

/*
 * Public Functions.
 */

/*
 * This function returns a widget in a component created by Glade.
 * Call it with the toplevel widget in the component (i.e. a window/dialog),
 * or alternatively any widget in the component, and the name of the widget
 * you want returned.
 */
GtkWidget *lookup_widget(GtkWidget * widget, const gchar * widget_name);


/* Use this function to set the directory containing installed pixmaps. */
void add_pixmap_directory(const gchar * directory);


/*
 * Private Functions.
 */

/* This is used to create the pixmaps used in the interface. */
GtkWidget *create_pixmap(GtkWidget * widget, const gchar * filename);

/* This is used to create the pixbufs used in the interface. */
GdkPixbuf *create_pixbuf(const gchar * filename);

/* This is used to set ATK action descriptions. */
void glade_set_atk_action_description(AtkAction * action,
				      const gchar * action_name,
				      const gchar * description);

 // GTK+ only (export callbacks for Glade linking at runtime)
#if defined(__WIN32__) && !defined(HAVE_FVISIBILITY)
# define GLADE_CB __declspec(dllexport)
#elif defined(HAVE_FVISIBILITY)
# define GLADE_CB __attribute__ ((visibility("default")))
#else
# define GLADE_CB
#endif

/* Update GTK Interface in Froze Position */
#define GTK_REFRESH() { while(gtk_events_pending()) { gtk_main_iteration(); } }
