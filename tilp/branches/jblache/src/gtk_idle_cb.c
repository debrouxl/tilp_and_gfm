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
#include <string.h>

#include "includes.h"

/*
  This function is called when the gtk_main loop
  is idle and running.
  Used by TiLP for checking if a command from the TiFFEP is available.
 */
#ifdef HAVE_TIFFEP
gint listen_tiffep(gpointer data)
{
  Shm *s = (Shm *)data;
  TiffepMsg msg;
  gchar *backup_file;
  gchar tmp_filename[MAXCHARS];
  volatile TiffepMsg *m;
  gint cmd;

  m = (TiffepMsg *)(s->addr);
  if(tiffep_msg_is_available(*s))
    {
      //DISPLAY("   Message available. Processing...\n");
      cmd = m->cmd;
      switch(cmd)
	{
	case CMD_TI_RECV_BACKUP:
	  tiffep_msg_recv(*s, &msg);
	  DISPLAY("%3i: Receiving CMD_TI_RECV_BACKUP...\n", msg.cmd);
	  tiffep_cmd_send_ack(*s);
	  tiffep_cmd_recv_string(*s, &backup_file);
	  cb_receive_backup();
	  strcpy(tmp_filename, g_get_tmp_dir());
	  strcat(tmp_filename, "/tilp.backup");
	  if(move_file(tmp_filename, backup_file))
	    {
	      msg_box(_("Error"), _("Unable to move the temporary file.\n"));  
	    }
	  tiffep_cmd_send_ok(*s);
	  break;
	case CMD_TI_SEND_BACKUP:
	  tiffep_msg_recv(*s, &msg);
	  DISPLAY("%3i: Receiving CMD_TI_SEND_BACKUP...\n", msg.cmd);
	  tiffep_cmd_send_ack(*s);
	  tiffep_cmd_recv_string(*s, &backup_file);
	  cb_send_backup(backup_file);
	  tiffep_cmd_send_ok(*s);
	default:
	  //DISPLAY("Ignored.\n");
	  break;
	}
    }

  return TRUE;
}
#endif
