#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_term_cb.h"
#include "gtk_term_dbox.h"
#include "support.h"

#include <gdk/gdkkeysyms.h>
#include "includes.h"

#define REMOTE 1
#define TERM 2

static GtkWidget *term_window;
static GdkColormap *cmap;
static GdkColor colour;
static GdkFont *fixed_font;
static GtkWidget *text;
static gint mode=REMOTE;

void
on_term_dbox_show_text                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  text = GTK_WIDGET(user_data);
  
  /* Get the system colour map and allocate the colour red */
  cmap = gdk_colormap_get_system();
  colour.red = 0xffff;
  colour.green = 0;
  colour.blue = 0;
  if(!gdk_color_alloc(cmap, &colour)) 
    {
      fprintf(stderr, "couldn't allocate colour");
    }

  /* Load a fixed font */
  //fixed_font = gdk_font_load ("-misc-fixed-medium-r-*-*-*-140-*-*-*-*-*-*");
  fixed_font = gdk_font_load("-rli-ti92-calc-r-expanded--10-100-75-75-m-80-iso8859-1");

  /* Init */
  on_term_remote_control1_activate(NULL, NULL);
}


void
on_term_dbox_show_dbox                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  term_window = GTK_WIDGET(user_data);
}


void
on_term_quit1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_destroy(term_window);
}


void
on_term_remote_control1_activate       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  mode=REMOTE;
  gtk_text_freeze (GTK_TEXT (text));
  gtk_text_insert (GTK_TEXT (text), fixed_font, &colour, NULL,
		   "\nYou are in remote control mode.\nPress any key but for:\n- Shift, press the left Shift key\n- diamond, press the left Ctrl key\n- 2nd, press the right Alt key\n- APPS, press the F9 key\n- STO, press the F10 key\n- MODE, press the F11 key\n- CLEAR, press the F12 key\n- (-) negative, press the right enter key\nPlease click the text window to focus it.\n\n", -1);
  gtk_text_thaw (GTK_TEXT (text));
}


void
on_term_terminal1_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  mode=TERM;
  gtk_text_freeze (GTK_TEXT (text));
  gtk_text_insert (GTK_TEXT (text), fixed_font, &colour, NULL,
		   "\nYou are in terminal mode.\nPress any key but for:\n- Shift, press the left Shift key\n- diamond, press the left Ctrl key\n- 2nd, press the right Alt key\n- APPS, press the F9 key\n- STO, press the F10 key\n- MODE, press the F11 key\n- CLEAR, press the F12 key\n- (-) negative, press the right enter key\nPlease click the text window to focus it.\n\n", -1);
  gtk_text_thaw (GTK_TEXT (text));
  
  ti_calc.send_key(KEY92_F5);
  ti_calc.send_key(KEY92_CTRL);
  ti_calc.send_key(KEY92_LP);
  ti_calc.send_key(KEY92_r);
}


void
on_term_leave1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_text_freeze (GTK_TEXT (text));
  gtk_text_insert (GTK_TEXT (text), fixed_font, &colour, NULL,
		   "\nYou are not in terminal mode any longer.\n\n", -1);
  gtk_text_thaw (GTK_TEXT (text));
  
  ti_calc.send_key(KEY92_F5);
  ti_calc.send_key(KEY92_CTRL);
  ti_calc.send_key(KEY92_LP);
  ti_calc.send_key(KEY92_r);
}


void
on_term_help3_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_help_dbox());
}


void
on_term_manpage1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_manpage_dbox());
}


void
on_term_about1_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gtk_widget_show_all(create_about_dbox());
}

static void key_pressed89(GtkWidget *widget, 
			  GdkEventKey *event, 
			  gpointer user_data);
static void key_pressed92(GtkWidget *widget, 
			  GdkEventKey *event, 
			  gpointer user_data);

gboolean
on_text1_key_press_event               (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
  if( (options.lp.calc_type == CALC_TI92P) || 
      (options.lp.calc_type == CALC_TI92) )
      key_pressed92(widget, event, user_data);
  else
    key_pressed89(widget, event, user_data);
  
  return FALSE;
}

/*****************/

#if defined(__WIN32__) && !defined(__CYGWIN__)
#include "keys89.h"
#include "keys92.h"
#endif
extern const struct ti_key TI89_KEYS[];

static void key_pressed89(GtkWidget *widget, 
			  GdkEventKey *event, 
			  gpointer user_data)
{
  GdkEventKey *key_event;
  static guint key=0;
  static guint subkey;
  static gint b=0;
  int err;

  gtk_text_freeze (GTK_TEXT (text));
  key_event=(GdkEventKey *) event;
  key=key_event->keyval;
  //printf("Key value: %8s %04X\n", gdk_keyval_name(key), key);

  switch(key)
    {
    case GDK_Shift_L:
      b=1;
      break;
    case GDK_Control_L:
      b=3;
      break;
    case GDK_Alt_L:
      b=2;
      break;
    default:
      break;
    }

  if(key & 0xFF00)
    {
      switch(key)
	{
	case GDK_BackSpace:
	  subkey=key & 0x00FF;
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   TI89_KEYS[subkey].key1, -1);
	  if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	  b=0;
	  break;
	case GDK_Return:
	  subkey=key & 0x00FF;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key((word)subkey))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_F1:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F1", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY89_F1))) return;
	  b=0;
	  break;
	case GDK_F2:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F2", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY89_F2))) return;
	  b=0;
	  break;
	case GDK_F3:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F3", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY89_F3))) return;
	  b=0;
	  break;
	case GDK_F4:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F4", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY89_F4))) return;
	  b=0;
	  break;
	case GDK_F5:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F5", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY89_F5))) return;
	  b=0;
	  break;
	case GDK_F6:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F6", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY89_F6))) return;
	  b=0;
	  break;
	case GDK_F7:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F7", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY89_F7))) return;
	  b=0;
	  break;
	case GDK_F8:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F8", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY89_F8))) return;
	  b=0;
	  break;
	case GDK_F9:
	  subkey=0x83;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY89_APPS))) return;
	      break;
	    }
	  b=0;
	  break;
	case GDK_F10:
	  subkey=0x87;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY89_STO))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_F11:
	  subkey=0x80;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY89_MODE))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_F12:
	  subkey=0x81;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY89_CLEAR))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_Escape:
	  subkey=key & 0x00FF;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key((word)subkey))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_Up:
	  subkey=0x90;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY89_UP))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_Down:
	subkey=0x91;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY89_DOWN))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_Left:
	  subkey=0x89;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY89_LEFT))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_Right:
	  subkey=0x93;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY89_RIGHT))) return;
	      break;
	    } 
	  b=0;
	  break;
	default:
	  break;
	}
      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
		       " ", -1);      
      switch(key)
	{
	case GDK_KP_Decimal:
	  key=GDK_period;
	  break;
	case GDK_KP_Divide:
	  key=GDK_slash;
	  break;
	case GDK_KP_Multiply:
	  key=GDK_asterisk;
	  break;
	case GDK_KP_Subtract:
	  key=GDK_minus;
	  break;
	case GDK_KP_Add:
	  key=GDK_plus;
	  break;
	case GDK_KP_0:
	  key=GDK_0;
	  break;
	case GDK_KP_1:
	  key=GDK_1;
	  break;
	case GDK_KP_2:
	  key=GDK_2;
	  break;
	case GDK_KP_3:
	  key=GDK_3;
	  break;
	case GDK_KP_4:
	  key=GDK_4;
	  break;
	case GDK_KP_5:
	  key=GDK_5;
	  break;
	case GDK_KP_6:
	  key=GDK_6;
	  break;
	case GDK_KP_7:
	  key=GDK_7;
	  break;
	case GDK_KP_8:
	  key=GDK_8;
	  break;
	case GDK_KP_9:
	  key=GDK_9;
	  break;
	case GDK_KP_Enter:
	  subkey=0x89;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI89_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY89_NEG))) return;
	      break;
	    } 
	  b=0;
	  break;
	default:
	  break;
	}
    }
  if(!(key & 0xFF00))
    {
      if(key>=0x80) return;
      subkey=key & 0x00FF;
      switch(b)
	{
	case 1:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   TI89_KEYS[subkey].key1, -1);
	  if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].shift))) return;
	  break;
	case 2: 
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   TI89_KEYS[subkey].key2, -1);
	  if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].second))) return;
	  break;
	case 3: 
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   TI89_KEYS[subkey].key3, -1);
	  if(tilp_error(err=ti_calc.send_key(TI89_KEYS[subkey].diamond))) return;
	  break;
	default:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   TI89_KEYS[subkey].key_name, -1);
	  if(tilp_error(err=ti_calc.send_key((word)subkey))) return;
	 break;
       } 
      b=0;
    }
  
  gtk_text_thaw (GTK_TEXT (text));
  return; 
}

extern const struct ti_key TI92_KEYS[];

static void key_pressed92(GtkWidget *widget, 
			  GdkEventKey *event, 
			  gpointer user_data)
{
  GdkEventKey *key_event;
  static guint key=0;
  static guint subkey;
  static gint b=0;
  int err;

  gtk_text_freeze (GTK_TEXT (text));
  key_event=(GdkEventKey *) event;
  key=key_event->keyval;
  //printf("Key value: %8s %04X\n", gdk_keyval_name(key), key);

  switch(key)
    {
    case GDK_Shift_L:
      b=1;
      break;
    case GDK_Control_L:
      b=3;
      break;
    case GDK_Alt_L:
      b=2;
      break;
    default:
      break;
    }

  if(key & 0xFF00)
    {
      switch(key)
	{
	case GDK_BackSpace:
	  subkey=key & 0x00FF;
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   TI92_KEYS[subkey].key1, -1);
	  if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	  b=0;
	  break;
	case GDK_Return:
	  subkey=key & 0x00FF;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key((word)subkey))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_F1:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F1", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY92_F1))) return;
	  b=0;
	  break;
	case GDK_F2:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F2", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY92_F2))) return;
	  b=0;
	  break;
	case GDK_F3:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F3", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY92_F3))) return;
	  b=0;
	  break;
	case GDK_F4:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F4", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY92_F4))) return;
	  b=0;
	  break;
	case GDK_F5:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F5", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY92_F5))) return;
	  b=0;
	  break;
	case GDK_F6:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F6", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY92_F6))) return;
	  b=0;
	  break;
	case GDK_F7:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F7", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY92_F7))) return;
	  b=0;
	  break;
	case GDK_F8:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   "F8", -1);
	  if(tilp_error(err=ti_calc.send_key(KEY92_F8))) return;
	  b=0;
	  break;
	case GDK_F9:
	  subkey=0x83;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY92_APPS))) return;
	      break;
	    }
	  b=0;
	  break;
	case GDK_F10:
	  subkey=0x87;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY92_STO))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_F11:
	  subkey=0x80;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY92_MODE))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_F12:
	  subkey=0x81;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY92_CLEAR))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_Escape:
	  subkey=key & 0x00FF;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key((word)subkey))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_Up:
	  subkey=0x90;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY92_UP))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_Down:
	subkey=0x91;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY92_DOWN))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_Left:
	  subkey=0x92;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY92_LEFT))) return;
	      break;
	    } 
	  b=0;
	  break;
	case GDK_Right:
	  subkey=0x93;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY92_RIGHT))) return;
	      break;
	    } 
	  b=0;
	  break;
	default:
	  break;
	}
      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
		       " ", -1);      
      switch(key)
	{
	case GDK_KP_Decimal:
	  key=GDK_period;
	  break;
	case GDK_KP_Divide:
	  key=GDK_slash;
	  break;
	case GDK_KP_Multiply:
	  key=GDK_asterisk;
	  break;
	case GDK_KP_Subtract:
	  key=GDK_minus;
	  break;
	case GDK_KP_Add:
	  key=GDK_plus;
	  break;
	case GDK_KP_0:
	  key=GDK_0;
	  break;
	case GDK_KP_1:
	  key=GDK_1;
	  break;
	case GDK_KP_2:
	  key=GDK_2;
	  break;
	case GDK_KP_3:
	  key=GDK_3;
	  break;
	case GDK_KP_4:
	  key=GDK_4;
	  break;
	case GDK_KP_5:
	  key=GDK_5;
	  break;
	case GDK_KP_6:
	  key=GDK_6;
	  break;
	case GDK_KP_7:
	  key=GDK_7;
	  break;
	case GDK_KP_8:
	  key=GDK_8;
	  break;
	case GDK_KP_9:
	  key=GDK_9;
	  break;
	case GDK_KP_Enter:
	  subkey=0x89;
	  switch(b)
	    {
	    case 1:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key1, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	      break;
	    case 2: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key2, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	      break;
	    case 3: 
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key3, -1);
	      if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	      break;
	    default:
	      gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			       TI92_KEYS[subkey].key_name, -1);
	      if(tilp_error(err=ti_calc.send_key(KEY92_NEG))) return;
	      break;
	    } 
	  b=0;
	  break;
	default:
	  break;
	}
    }
  if(!(key & 0xFF00))
    {
      if(key>=0x80) return;
      subkey=key & 0x00FF;
      switch(b)
	{
	case 1:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   TI92_KEYS[subkey].key1, -1);
	  if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].shift))) return;
	  break;
	case 2: 
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   TI92_KEYS[subkey].key2, -1);
	  if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].second))) return;
	  break;
	case 3: 
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   TI92_KEYS[subkey].key3, -1);
	  if(tilp_error(err=ti_calc.send_key(TI92_KEYS[subkey].diamond))) return;
	  break;
	default:
	  gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL,
			   TI92_KEYS[subkey].key_name, -1);
	  if(tilp_error(err=ti_calc.send_key((word)subkey))) return;
	 break;
       } 
      b=0;
    }
  
  gtk_text_thaw (GTK_TEXT (text));
  return;
}

/* */

