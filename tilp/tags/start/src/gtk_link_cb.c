#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "gtk_link_cb.h"
#include "gtk_link_dbox.h"
#include "support.h"

#include "includes.h"

static gint link_type;
static gchar device[MAXCHARS];
static guint io_addr;
static gint port;
static gint method;

static gint already_loaded = 0;
static gint custom_toggled = 0;

gpointer wentry1 = NULL;
gpointer wentry2 = NULL;

static void s2v(void)
{
  port = options.lp.port;
  method = options.lp.method;
  link_type = options.lp.link_type;

  io_addr = options.lp.io_addr;
  strcpy(device, options.lp.device);
}

/************************************/
/* Called when the box is displayed */
/************************************/

void
on_linktype_dbox_show1                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(link_type == LINK_TGL)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_linktype_dbox_show2                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(link_type == LINK_PAR)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_linktype_dbox_show3                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(link_type == LINK_TIE)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_linktype_dbox_show4                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(link_type == LINK_TPU)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_linktype_dbox_show5                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(link_type == LINK_SER)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_linktype_dbox_show6                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(link_type == LINK_AVR)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_linktype_dbox_show7                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(link_type == LINK_VTI)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_linktype_dbox_show8                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(link_type == LINK_UGL)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
}


void
on_linktype_dbox_show10                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(method & IOM_DRV)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
  else
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), FALSE);
}


void
on_linktype_dbox_show11                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(method & IOM_DCB)
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), TRUE);
  else
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (user_data), FALSE);
}


void
on_linktype_dbox_show30                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar buffer[MAXCHARS];

  wentry1 = user_data;
  g_snprintf(buffer, MAXCHARS, "0x%03x", io_addr);

  gtk_entry_set_visibility(GTK_ENTRY(user_data), custom_toggled);
  gtk_entry_set_editable(GTK_ENTRY(user_data), custom_toggled ? TRUE : FALSE);
  gtk_entry_set_text(GTK_ENTRY(user_data), buffer);
}


void
on_linktype_dbox_show31                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar buffer[MAXCHARS];

  wentry2 = user_data;
  g_snprintf(buffer, MAXCHARS, "%s", device);

  gtk_entry_set_visibility(GTK_ENTRY(user_data), custom_toggled);
  gtk_entry_set_editable(GTK_ENTRY(user_data), custom_toggled ? TRUE : FALSE);
  gtk_entry_set_text(GTK_ENTRY(user_data), buffer);
}


void
on_linktype_dbox_show20                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  switch(link_type)
    {
    case LINK_PAR:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Parallel port #1");
      if(port == PARALLEL_PORT_1)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(GTK_WIDGET(GTK_BIN(user_data)->child));
      gtk_widget_show(user_data);
      break;
    case LINK_AVR:
    case LINK_TGL:
    case LINK_SER:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Serial port #1");
      if(port == SERIAL_PORT_1)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_TIE:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Virtual port #1 (emu)");
      if(port == VIRTUAL_PORT_1)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_VTI:
#ifdef __WIN32__
      gtk_widget_hide(user_data);
      break;
#endif
    case LINK_VTL:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Virtual port #1 (emu)");
      if(port == VIRTUAL_PORT_1)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_TPU:
      gtk_widget_hide(user_data);
      /*
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "'raw' mode");
      if(io_addr == TPU_RAW_MODE)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      */
      break;
    case LINK_UGL:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child),
                         "USB port #1");
      if(port == USB_PORT_1)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(GTK_WIDGET(GTK_BIN(user_data)->child));
      gtk_widget_show(user_data);
      break;
    }
}


void
on_linktype_dbox_show21                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  switch(link_type)
    {
    case LINK_PAR:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Parallel port #2");
      if(port == PARALLEL_PORT_2)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_AVR:
    case LINK_TGL:
    case LINK_SER:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Serial port #2");
      if(port == SERIAL_PORT_2)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_TIE:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Virtual port #2 (tilp)");
      if(port == VIRTUAL_PORT_2)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_VTI:
#ifdef __WIN32__
      gtk_widget_hide(user_data);
      break;
#endif
    case LINK_VTL:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Virtual port #2 (tilp)");
      if(port == VIRTUAL_PORT_2)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_TPU:
      gtk_widget_hide(user_data);
      /*
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "'cooked' mode");
      if(io_addr == TPU_COOKED_MODE)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      */
      break;
    case LINK_UGL:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child),
                         "USB port #2");
      if(port == USB_PORT_2)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(GTK_WIDGET(GTK_BIN(user_data)->child));
      gtk_widget_show(user_data);
      break;
    }
}


void
on_linktype_dbox_show22                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  switch(link_type)
    {
    case LINK_PAR:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Parallel port #3");
      if(port == PARALLEL_PORT_3)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_AVR:
    case LINK_TGL:
    case LINK_SER:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Serial port #3");
      if(port == SERIAL_PORT_3)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_TIE:
      gtk_widget_hide(user_data);
      break;
    case LINK_VTI:
      gtk_widget_hide(user_data);
      break;
    case LINK_VTL:
      gtk_widget_hide(user_data);
      break;
    case LINK_TPU:
      gtk_widget_hide(user_data);
      break;
    case LINK_UGL:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child),
                         "USB port #3");
      if(port == USB_PORT_3)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(GTK_WIDGET(GTK_BIN(user_data)->child));
      gtk_widget_show(user_data);
      break;
    }
}


void
on_linktype_dbox_show23                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  switch(link_type)
    {
    case LINK_PAR:
      gtk_widget_hide(user_data);
      break;
    case LINK_AVR:
    case LINK_TGL:
    case LINK_SER:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child), 
			 "Serial port #4");
      if(port == SERIAL_PORT_4)
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_TIE:
      gtk_widget_hide(user_data);
      break;
    case LINK_VTI:
      gtk_widget_hide(user_data);
      break;
    case LINK_VTL:
      gtk_widget_hide(user_data);
      break;
    case LINK_TPU:
      gtk_widget_hide(user_data);
      break;
    case LINK_UGL:
      gtk_label_set_text(GTK_LABEL(GTK_BIN(user_data)->child),
                         "USB port #4");
      if(port == USB_PORT_4)
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(GTK_WIDGET(GTK_BIN(user_data)->child));
      gtk_widget_show(user_data);
      break;
    }
}


void
on_linktype_dbox_show24                (GtkWidget       *widget,
                                        gpointer         user_data)
{
  switch(link_type)
    {
    case LINK_PAR:
      if( (port != PARALLEL_PORT_1) && (port != PARALLEL_PORT_2) && 
	  (port != PARALLEL_PORT_3) )
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_AVR:
    case LINK_TGL:
    case LINK_SER:
      if( (port != SERIAL_PORT_1) && (port != SERIAL_PORT_2) &&
	  (port != SERIAL_PORT_3) && (port != SERIAL_PORT_4) )
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    case LINK_TIE:
      gtk_widget_hide(user_data);
      break;
    case LINK_VTI:
      gtk_widget_hide(user_data);
      break;
    case LINK_VTL:
      gtk_widget_hide(user_data);
      break;
    case LINK_TPU:
      gtk_widget_hide(user_data);
      break;
    case LINK_UGL:
      if( (port != USB_PORT_1) && (port != USB_PORT_2) &&
          (port != USB_PORT_3) && (port != USB_PORT_4) )
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON (user_data), TRUE);
      gtk_widget_show(user_data);
      break;
    }
}

/***********************************/
/* Called whenever a char is typed */
/***********************************/

void
linktype_entry1_changed                (GtkEditable     *editable,
                                        gpointer         user_data)
{
  gchar *s;
  gint result;

  s = gtk_editable_get_chars(GTK_EDITABLE(user_data), 0, -1);
  result = sscanf(s, "0x%03x", &io_addr);
  if(result < 1)
    io_addr = AUTO_ADDR;
}


void
linktype_entry2_changed                (GtkEditable     *editable,
                                        gpointer         user_data)
{
  gchar *s;
  gint result;

  s = gtk_editable_get_chars(GTK_EDITABLE(user_data), 0, -1);
  result = sscanf(s, "%s", device);
  if(result < 1)
    strcpy(device, AUTO_NAME);
}


/***********/
/* Options */
/***********/

void
linktype_checkbutton1_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(gtk_toggle_button_get_active(togglebutton))
    method |=  IOM_DRV;
  else
    method &= ~IOM_DRV;
  
  gtk_signal_emit_by_name(GTK_OBJECT(user_data), "show");
}


void
linktype_checkbutton2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if(link_type != LINK_SER)
    return;

  if(gtk_toggle_button_get_active(togglebutton))
    method |=  IOM_DCB;
  else
    method &= ~IOM_DCB;

  gtk_signal_emit_by_name(GTK_OBJECT(user_data), "show");
}

void
linktype_checkbutton3_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  custom_toggled = gtk_toggle_button_get_active(togglebutton);

  if(custom_toggled)
    {
      io_addr= AUTO_ADDR;
      strcpy(device, AUTO_NAME);
    }

  gtk_entry_set_visibility(GTK_ENTRY(wentry1), custom_toggled);
  gtk_entry_set_editable(GTK_ENTRY(wentry1), custom_toggled ? TRUE : FALSE);
  gtk_entry_set_visibility(GTK_ENTRY(wentry2), custom_toggled);
  gtk_entry_set_editable(GTK_ENTRY(wentry2), custom_toggled ? TRUE : FALSE);
}

/*******************/
/* Link cable type */
/*******************/

void
linktype_radiobutton1_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  link_type = LINK_TGL;
  port = SERIAL_PORT_2;
  //printf("linktype_radiobutton1_toggled, %i\n", link_type);
  if(gtk_toggle_button_get_active(togglebutton))
    gtk_signal_emit_by_name(GTK_OBJECT(user_data), "show");
}

void
linktype_radiobutton2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  link_type = LINK_PAR;
  port = PARALLEL_PORT_1;
  //printf("linktype_radiobutton2_toggled, %i\n", link_type);
  if(gtk_toggle_button_get_active(togglebutton))
    gtk_signal_emit_by_name(GTK_OBJECT(user_data), "show");
}

void
linktype_radiobutton3_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  link_type = LINK_TIE;
  port = VIRTUAL_PORT_2;
  if(gtk_toggle_button_get_active(togglebutton))
    gtk_signal_emit_by_name(GTK_OBJECT(user_data), "show");
}

void
linktype_radiobutton4_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  link_type = LINK_TPU;

  if(gtk_toggle_button_get_active(togglebutton))
    gtk_signal_emit_by_name(GTK_OBJECT(user_data), "show");
}

void
linktype_radiobutton5_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  link_type = LINK_SER;
  port = SERIAL_PORT_2;
  if(gtk_toggle_button_get_active(togglebutton))
    gtk_signal_emit_by_name(GTK_OBJECT(user_data), "show");
}

void
linktype_radiobutton6_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  link_type = LINK_AVR;
  port = SERIAL_PORT_2;
  if(gtk_toggle_button_get_active(togglebutton))
    gtk_signal_emit_by_name(GTK_OBJECT(user_data), "show");
}

void
linktype_radiobutton7_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  link_type = LINK_VTI;
  port = VIRTUAL_PORT_2;
  if(gtk_toggle_button_get_active(togglebutton))
    gtk_signal_emit_by_name(GTK_OBJECT(user_data), "show");
}

void
linktype_radiobutton8_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  link_type = LINK_UGL;
  port = USB_PORT_1;
  if(gtk_toggle_button_get_active(togglebutton))
    gtk_signal_emit_by_name(GTK_OBJECT(user_data), "show");
}

/************/
/* I/O port */
/************/

void
linktype_radiobutton10_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  switch(link_type)
    {
    case LINK_PAR:
      port = PARALLEL_PORT_1;
      break;
    case LINK_SER:
    case LINK_AVR:
    case LINK_TGL:
      port = SERIAL_PORT_1;
      break;
    case LINK_VTL:
      port = VIRTUAL_PORT_1;
      break;
    case LINK_VTI:
      port = VIRTUAL_PORT_1;
      break;
    case LINK_TIE:
      port = VIRTUAL_PORT_1;
      break;
    case LINK_TPU:
      //io_addr = TPU_RAW_MODE;
      break;
    case LINK_UGL:
      port = USB_PORT_1;
      break;
    }
}


void
linktype_radiobutton11_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{ 
  switch(link_type)
    {
    case LINK_PAR:
      port = PARALLEL_PORT_2;
      break;
    case LINK_SER:
    case LINK_AVR:
    case LINK_TGL:
      port = SERIAL_PORT_2;
      break;
    case LINK_VTL:
      port = VIRTUAL_PORT_2;
      break;
    case LINK_VTI:
      port = VIRTUAL_PORT_2;
      break;
    case LINK_TIE:
      port = VIRTUAL_PORT_2;
      break;
    case LINK_TPU:
      //io_addr = TPU_COOKED_MODE;
      break;
    case LINK_UGL:
      port = USB_PORT_2;
      break;
    }
}


void
linktype_radiobutton12_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{  
  switch(link_type)
    {
    case LINK_PAR:
      port = PARALLEL_PORT_3;
      break;
    case LINK_AVR:
    case LINK_TGL:
    case LINK_SER:
      port = SERIAL_PORT_3;
      break;
    case LINK_VTL:
      break;
    case LINK_VTI:
      break;
    case LINK_TIE:
      break;
    case LINK_TPU:
      break;
    case LINK_UGL:
      port = USB_PORT_3;
      break;
    }
}


void
linktype_radiobutton13_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  switch(link_type)
    {
    case LINK_PAR:
      break;
    case LINK_SER:
    case LINK_AVR:
    case LINK_TGL:
      port = SERIAL_PORT_4;
      break;
    case LINK_VTL:
      break;
    case LINK_VTI:
      break;
    case LINK_TIE:
      break;
    case LINK_TPU:
      break;
    case LINK_UGL:
      port = USB_PORT_4;
      break;
    }
}


void
linktype_radiobutton14_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
}

/*************/
/* Ok/Cancel */
/*************/

void
linktype_ok_button_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));

  if( (tilp_error(link_cable.term_port())) ) 
    return;

  options.lp.method = method;
  options.lp.port = port;
  options.lp.link_type = link_type;
  options.lp.io_addr = io_addr;
  strcpy(options.lp.device, device);

  ticable_set_param(options.lp);
  ticable_set_cable(options.lp.link_type, &link_cable);
  ticalc_set_calc(options.lp.calc_type, &ti_calc, &link_cable);
  //check_access();
  if( (tilp_error(link_cable.init_port())) ) 
    return;
}


void
linktype_cancel_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}

void
on_linktype_dbox_show                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
  if(!already_loaded)
    {
      s2v();
      already_loaded = 1;
    }
}

void
on_linktype_button_fs_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_show(create_fileselection_device());
}


void
on_seldev_ok_button1_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar *s;

  s = gtk_file_selection_get_filename(GTK_FILE_SELECTION(user_data));
  gtk_entry_set_text(GTK_ENTRY(wentry2), s);

  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_seldev_cancel_button1_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_destroy(GTK_WIDGET(user_data));
}


void
on_fileselection_device_show           (GtkWidget       *widget,
                                        gpointer         user_data)
{
  gchar *s;

  s = gtk_editable_get_chars(GTK_EDITABLE(wentry2), 0, -1);
  gtk_file_selection_set_filename(GTK_FILE_SELECTION(user_data), s);
}

void
on_linktype_dbox_show40                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
#if defined(__WIN32__)
  gtk_label_set_text(GTK_LABEL(user_data), "DLPortIO NT\nkernel driver");
#elif defined(__LINUX__)
  gtk_label_set_text(GTK_LABEL(user_data), "tipar/tiser\nkernel module");
#else
  gtk_label_set_text(GTK_LABEL(user_data), "kernel driver");
#endif
}

/* */

