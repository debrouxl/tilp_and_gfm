/*  tilp - link program for TI calculators
 *  Copyright (C) 1999-2001  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gtk/gtk.h>

#include "includes.h"


/* Put sensitive some buttons of the toolbar according to some options */
void refresh_sensitive_toolbar_buttons()
{
  switch(options.lp.calc_type)
    {
    case CALC_TI82:
    case CALC_TI85:
    case CALC_TI83:
    case CALC_TI83P:
    case CALC_TI86:
      gtk_widget_set_sensitive(toolbar_win.button1, FALSE);
      break;
    default:
      gtk_widget_set_sensitive(toolbar_win.button1, TRUE);
      break;
    }  

  switch(options.lp.calc_type)
    {
    case CALC_TI82:
    case CALC_TI85:
      gtk_widget_set_sensitive(toolbar_win.button4, FALSE);
      break;
    default:
      gtk_widget_set_sensitive(toolbar_win.button4, TRUE);
      break;
    } 

  if(options.lp.calc_type == CALC_TI86) 
    gtk_widget_set_sensitive(toolbar_win.button5, TRUE);
  else
    gtk_widget_set_sensitive(toolbar_win.button5, TRUE);

  if(options.lp.calc_type == CALC_TI86) 
    gtk_widget_set_sensitive(toolbar_win.button6, TRUE);
  else
    gtk_widget_set_sensitive(toolbar_win.button6, TRUE);

  return;
}



