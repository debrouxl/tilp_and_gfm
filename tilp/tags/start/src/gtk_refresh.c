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

#include <stdio.h>
#include <gtk/gtk.h>

#include "includes.h"

void gt_start()
{
  info_update.prev_percentage = info_update.percentage = 0.0;
  info_update.start_time = clock();
}

void gt_stop()
{
  info_update.prev_percentage = info_update.percentage = 0.0;
}

static void refresh_pbar1()
{
  static gchar buffer[32];
  static gfloat rate;

  if(p_win.pbar != NULL) 
    {
      /* Refresh if necessary (for speeding up !) */
      if( (info_update.percentage - info_update.prev_percentage) < 0.05)
	{
	  if( (info_update.percentage - info_update.prev_percentage) < 0)
	    info_update.prev_percentage = info_update.percentage;
	  else
	    return;
	}
      else
	info_update.prev_percentage = info_update.percentage;

      rate = info_update.count / 
	((float)(clock() - info_update.start_time)/CLOCKS_PER_SEC);
      g_snprintf(buffer, 32, "Rate: %1.1f Kbytes/s", rate / 1000);
     
      /* Display label & pbar */
      gtk_label_set(GTK_LABEL (p_win.label_rate), buffer);
      gtk_progress_bar_update(GTK_PROGRESS_BAR (p_win.pbar), 
			      info_update.percentage);
      
      while( gtk_events_pending() ) { gtk_main_iteration(); }
    }
}

static void refresh_pbar2()
{
  if(p_win.pbar2 != NULL)
    {
      /* Refresh if necessary (for speeding up !) */
      if( (info_update.main_percentage - info_update.prev_main_percentage) < 0.05)
	return;
      else
	info_update.prev_main_percentage = info_update.main_percentage;
      
      gtk_progress_bar_update(GTK_PROGRESS_BAR (p_win.pbar2), 
			      info_update.main_percentage);
      while( gtk_events_pending() ) { gtk_main_iteration(); }
    }
}

void gt_pbar()
{
  refresh_pbar1();
  refresh_pbar2();
}

void gt_label()
{
  if(p_win.label == NULL) return;
  gtk_label_set(GTK_LABEL (p_win.label), info_update.label_text);
  while( gtk_events_pending() ) { gtk_main_iteration(); }
}

void gt_refresh()
{
  while( gtk_events_pending() ) { gtk_main_iteration(); }
}

int gt_choose(char *cur_varname, char *new_varname)
{
  int ret=0;
  int action = ACTION_NONE;
  gchar *s;
  
  strcpy(new_varname, "");
  ret = user3_box(_("Action"), 
		  _("The variable already exists..."), 
		  _("Skip"), _("Overwrite"), _("Rename"));
  switch(ret)
    {
    case BUTTON1:
      action = ACTION_SKIP;
      break;
    case BUTTON2:
      action = ACTION_OVERWRITE;
      break;
    case BUTTON3:
      action = ACTION_RENAME;
      s = gif->dlgbox_entry(_("Rename the variable"),
			    _("New name: "), cur_varname);
      if((s == NULL) || (strlen(s)>17)) { action=ACTION_SKIP; break; }
      strcpy(new_varname, s);
      g_free(s);
      break;
    default:
      break;
    }
    
  return action;
}

void gt_init_refresh_functions(void)
{
  ticalc_set_update(&info_update, 
		    gt_start,
		    gt_stop,
		    gt_refresh,
		    msg_box, 
		    gt_pbar, 
		    gt_label, 
		    gt_choose
		    );

  fprintf(stdout, _("Initialized in GTK+ mode.\n"));

  return;
}







