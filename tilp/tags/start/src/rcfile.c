/*  ti_link - link program for TI calculators
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
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "defs.h"
#include "gui_indep.h"
#include "intl.h"
#include "version.h"
#include "struct.h"

static char *rc_file; 
static char *cwd_file;

int check_access()
{
  FILE *in;
  char buffer[MAXCHARS];
  unsigned int addr;
  int found=0;

#ifdef __WIN32__
  return 0;
#endif

  if(options.lp.link_type == LINK_VTL)
    return 0;

  in=fopen(IO_FILE, "rt");
  if(in == NULL)
    {
#if defined(__UNIX__)
      gif->msg_box(_("Error"), _("Unable to open the tilp.conf file. Please contact your system administrator.\n"));
#elif defined(__WIN32__)
      gif->msg_box(_("Error"), _("Unable to open the tilp.conf file.  It must be in the same directory than tilp\n"));
#endif
      return 1;
    }
  while(!feof(in))
    {
      fgets(buffer, 256, in);
      //printf("%s", buffer);
      if(buffer[0] == '#') continue;
      else
	{
	  sscanf(buffer, "0x%03X\n", &addr);
	  //printf("%03X\n", addr);
	  if(options.lp.io_addr == addr)
	    {
	      found=1;
	      break;
	    }
	}
    }
  fclose(in);
  if(!found)
    {
      gif->msg_box(_("Error"), 
		   _("The /etc/tilp.conf file do not authorize you to use this address. Contact your system administrator.\n"));
      options.lp.io_addr = addr;
      return 1;
    }

  return 0;
}

int debug_options()
{
  fprintf(stdout, "******************************************************************\n");

  fprintf(stdout, "# Calculator type\n");
  fprintf(stdout, "calctype=");
  switch(options.lp.calc_type)
    {
    case CALC_TI92P:
      fprintf(stdout, "ti92+\n");
      break;
    case CALC_TI92:
      fprintf(stdout, "ti92\n");
      break;
    case CALC_TI89:
      fprintf(stdout, "ti89\n");
      break; 
    case CALC_TI86:
      fprintf(stdout, "ti86\n");
      break;
    case CALC_TI85:
      fprintf(stdout, "ti85\n");
      break;
    case CALC_TI83P:
      fprintf(stdout, "ti83+\n");
      break; 
    case CALC_TI83:
      fprintf(stdout, "ti83\n");
      break;
    case CALC_TI82:
      fprintf(stdout, "ti82\n");
      break;
    }
  fprintf(stdout, "\n");
  fprintf(stdout, "# Link cable type\n");
  fprintf(stdout, "linktype=");
  switch(options.lp.link_type)
    {
    case LINK_PAR:
      fprintf(stdout, "parallel\n");
      break;
    case LINK_SER:
      fprintf(stdout, "serial\n");
      break;
    case LINK_TGL:
      fprintf(stdout, "TIGraphLink\n");
      break;
    }
  fprintf(stdout, "\n");
  fprintf(stdout, "# Parallel/serial port address\n");
  fprintf(stdout, "io_addr=0x%03X\n", options.lp.io_addr);
  fprintf(stdout, "\n");
  fprintf(stdout, "# Serial device\n");
  fprintf(stdout, "device=%s\n", options.lp.device);
  fprintf(stdout, "\n");
  fprintf(stdout, "# Timeout value in 0.1 seconds\n");
  fprintf(stdout, "timeout=%i\n", options.lp.timeout);
  fprintf(stdout, "\n");
  fprintf(stdout, "# Baud rate\n");

  fprintf(stdout, "# Delay value\n");
  fprintf(stdout, "delay=%i\n", options.lp.delay);
  fprintf(stdout, "\n");
  fprintf(stdout, "# Window size\n");
  fprintf(stdout, "xsize=%i\n", options.xsize);
  fprintf(stdout, "ysize=%i\n", options.ysize);
  fprintf(stdout, "\n");
  fprintf(stdout, "# Right window sort order: name, date, size, user, group, attrib\n");
  fprintf(stdout, "clist_sort=");
  switch(options.clist_sort)
    {
    case SORT_BY_NAME: fprintf(stdout, "name\n");
      break;
    case SORT_BY_DATE: fprintf(stdout, "date\n");
      break;
    case SORT_BY_SIZE: fprintf(stdout, "size\n");
      break;
    case SORT_BY_USER: fprintf(stdout, "user\n");
      break;
    case SORT_BY_GROUP: fprintf(stdout, "group\n");
      break;
    case SORT_BY_ATTRB: fprintf(stdout, "attrib\n");
      break;
    }
  fprintf(stdout, "clist_order=");
  switch(options.clist_sort_order)
    {
    case SORT_UP: fprintf(stdout, "up\n");
      break;
    case SORT_DOWN: fprintf(stdout, "down\n");
      break;
    }
  fprintf(stdout, "\n");

  fprintf(stdout, "# Left window sort order: name, info, type, size\n");
  fprintf(stdout, "ctree_sort=");
  switch(options.ctree_sort)
    {
    case SORT_BY_NAME: fprintf(stdout, "name\n");
      break;
    case SORT_BY_INFO: fprintf(stdout, "info\n");
      break;
    case SORT_BY_TYPE: fprintf(stdout, "type\n");
      break;
    case SORT_BY_SIZE: fprintf(stdout, "size\n");
      break;
    }
  fprintf(stdout, "ctree_order=");
  switch(options.ctree_sort_order)
    {
    case SORT_UP: fprintf(stdout, "up\n");
      break;
    case SORT_DOWN: fprintf(stdout, "down\n");
      break;
    }
  fprintf(stdout, "\n");
  fprintf(stdout, "# Delete files\n");
  fprintf(stdout, "confirm=%s\n", options.confirm ? "yes" : "no");
  fprintf(stdout, "\n");
  fprintf(stdout, "# Full or local path for sending variables\n");
  fprintf(stdout, "path=%s\n", options.path_mode ? "local" : "full");
  fprintf(stdout, "\n");
  fprintf(stdout, "# Show hidden files\n");
  fprintf(stdout, "hidden_files=%s\n", options.show ? "hide" : "show");


  
  return 0;
}

int get_rcfile_path(char **path)
{
#if defined(__UNIX__)
  char *home_dir;
  
  get_home_path(&home_dir);
  *path = (char *)g_malloc((strlen(home_dir) + strlen(RC_FILE) + 1)
			    * sizeof(char));
  strcpy(*path, home_dir); g_free(home_dir);
  strcat(*path, RC_FILE);
  //fprintf(stdout, "Home path: %s\n", *path);
#elif defined(__WIN32__)
  *path = (char *)g_malloc((strlen(inst_paths.base_dir) + 
			     strlen(DIR_SEPARATOR) + 
			     strlen(RC_FILE) + 1) * sizeof(char));
  strcpy(*path, inst_paths.base_dir);
  strcat(*path, DIR_SEPARATOR);
  strcat(*path, RC_FILE);
#endif

  return 0;
}

/* Print an error msg */
void stop (int line)
{
  fprintf(stderr, gettext("Configuration file error at line %i.\n"), line);
}

char *find_str(char *s, const char *t)
{
  char *p=strstr(s, t);

  if(p==NULL) return NULL;
  else return p+strlen(t);
}

/* Chech whether a RC file exists */
int is_rcfile_exist(void)
{
  get_rcfile_path(&rc_file);
  
  return !access(rc_file, F_OK);
}


/* Read the RC file and configure the corresponding variables */
void read_rc_file(void)
{
  FILE *txt;
  char buffer[256];
  char *p;
  int l=0;
  
  get_rcfile_path(&rc_file);
  
  txt=fopen(rc_file, "rt");
  if(txt == NULL)
    {
      fprintf(stdout, _("Configuration file not found, use default values. You can create one by the 'File|Save config' command menu.\n"));
      gif->msg_box(_("Information"), _("Configuration file not found, use default values. You can create one by the 'File|Save config' command menu.\n"));
      return;
    }
  
  while(!feof(txt))
    {
      fgets(buffer, 256, txt);
      l++;
      buffer[strlen(buffer)-1]='\0';
      if(!strcmp(buffer, "RC_END")) 
	{
	  fclose(txt);
	  return;
	}
      if(buffer[0]=='#' || !strlen(buffer)) continue;
      //printf("<%s>\n", buffer);
      if( (p=find_str(buffer, "calctype=")) )
	{
	  if(!strcmp(p, "ti92+")) options.lp.calc_type=CALC_TI92P;
	  else if(!strcmp(p, "ti92")) options.lp.calc_type=CALC_TI92;
	  else if(!strcmp(p, "ti89")) options.lp.calc_type=CALC_TI89;
	  else if(!strcmp(p, "ti86")) options.lp.calc_type=CALC_TI86;
	  else if(!strcmp(p, "ti85")) options.lp.calc_type=CALC_TI85;
	  else if(!strcmp(p, "ti83+")) options.lp.calc_type=CALC_TI83P;
	  else if(!strcmp(p, "ti83")) options.lp.calc_type=CALC_TI83;
	  else if(!strcmp(p, "ti82")) options.lp.calc_type=CALC_TI82;
	  else stop(l);
	  continue;
	}
      
      if( (p=find_str(buffer, "linktype=")) )
	{
	  if(!strcmp(p, "parallel")) options.lp.link_type=LINK_PAR;
	  else if(!strcmp(p, "serial")) options.lp.link_type=LINK_SER;
	  else if(!strcmp(p, "TIGraphLink")) options.lp.link_type=LINK_TGL;
	  else if(!strcmp(p, "fastAVRlink")) options.lp.link_type=LINK_AVR;
	  else if(!strcmp(p, "VTi")) options.lp.link_type=LINK_VTI;
	  else if(!strcmp(p, "TiEmulator")) options.lp.link_type=LINK_TIE;
	  else if(!strcmp(p, "virtual")) options.lp.link_type=LINK_VTL;
	  else if(!strcmp(p, "TiPcUsbLink")) options.lp.link_type=LINK_TPU;
	  else if(!strcmp(p, "UsbGraphLink")) options.lp.link_type=LINK_UGL;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "io_addr=")) )
	{
	  sscanf(p, "0x%03X", &(options.lp.io_addr));
	  //check_access();
	  continue;
	}
      if( (p=find_str(buffer, "device=")) )
	{
	  strcpy(options.lp.device, p);
	}
      if( (p=find_str(buffer, "timeout=")) )
	{
	  sscanf(p, "%i", &(options.lp.timeout));
	  continue;
	}
      if( (p=find_str(buffer, "baudrate=")) )
	{
	  sscanf(p, "%i", &(options.lp.baud_rate));
	  continue;
	}
      if( (p=find_str(buffer, "delay=")) )
	{
	  sscanf(p, "%i", &(options.lp.delay));
	  continue;
	}
      if( (p=find_str(buffer, "xsize=")) )
	{
	  sscanf(p, "%i", &(options.xsize));
	  continue;
	}
      if( (p=find_str(buffer, "ysize=")) )
	{
	  sscanf(p, "%i", &(options.ysize));
	  continue;
	}
      if( (p=find_str(buffer, "clist_sort=")) )
	{
	  if(!strcmp(p, "name")) options.clist_sort=SORT_BY_NAME;
	  else if(!strcmp(p, "date")) options.clist_sort=SORT_BY_DATE;
	  else if(!strcmp(p, "size")) options.clist_sort=SORT_BY_SIZE;
	  else if(!strcmp(p, "user")) options.clist_sort=SORT_BY_USER;
	  else if(!strcmp(p, "group")) options.clist_sort=SORT_BY_GROUP;
	  else if(!strcmp(p, "attrib")) options.clist_sort=SORT_BY_ATTRB;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "clist_order=")) )
	{
	  if(!strcmp(p, "up")) options.clist_sort_order=SORT_UP;
	  else if(!strcmp(p, "down")) options.clist_sort_order=SORT_DOWN;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "ctree_sort=")) )
	{
	  if(!strcmp(p, "name")) options.ctree_sort=SORT_BY_NAME;
	  else if(!strcmp(p, "info")) options.ctree_sort=SORT_BY_INFO;
	  else if(!strcmp(p, "type")) options.ctree_sort=SORT_BY_TYPE;
	  else if(!strcmp(p, "size")) options.ctree_sort=SORT_BY_SIZE;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "ctree_order=")) )
	{
	  if(!strcmp(p, "up")) options.ctree_sort_order=SORT_UP;
	  else if(!strcmp(p, "down")) options.ctree_sort_order=SORT_DOWN;
	  else stop(l);
	  continue;
	}      
      if( (p=find_str(buffer, "confirm=")) )
	{
	  if(!strcmp(p, "yes")) options.confirm=CONFIRM_YES;
	  else if(!strcmp(p, "no")) options.confirm=CONFIRM_NO;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "path=")) )
	{
	  if(!strcmp(p, "full")) options.path_mode=FULL_PATH;
	  else if(!strcmp(p, "local")) options.path_mode=LOCAL_PATH;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "hidden_files=")) )
	{
	  if(!strcmp(p, "show")) options.show=SHOW;
	  else if(!strcmp(p, "hide")) options.show=HIDE;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "file_mode=")) )
	{
	  if(!strcmp(p, "extended")) options.file_mode=EXTENDED_FORMAT;
	  else if(!strcmp(p, "normal")) options.file_mode=NORMAL_FORMAT;
	  else stop(l);
	  continue;
	}
      /*
      if( (p=find_str(buffer, "use_tidev=")) )
	{
	  if(!strcmp(p, "yes")) options.lp.tidev=TIDEV_ENABLED;
	  else if(!strcmp(p, "no")) options.lp.tidev=TIDEV_DISABLED;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "use_dlportio=")) )
        {
          if(!strcmp(p, "yes")) options.lp.dlportio=DLPORTIO_ENABLED;
          else if(!strcmp(p, "no")) options.lp.dlportio=DLPORTIO_DISABLED;
          else stop(l);
          continue;
        }
      */
      if( (p=find_str(buffer, "screen_format=")) )
	{
	  if(!strcmp(p, "pcx")) options.screen_format=PCX;
	  else if(!strcmp(p, "xpm")) options.screen_format=XPM;
	  else if(!strcmp(p, "jpg")) options.screen_format=JPG;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "screen_mode=")) )
	{
	  if(!strcmp(p, "full")) options.screen_clipping=FULL_SCREEN;
	  else if(!strcmp(p, "clipped")) options.screen_format=CLIPPED_SCREEN;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "plugins_loading=")) )
	{
	  if(!strcmp(p, "auto")) options.plugins_loading=PLUGINS_AUTO;
	  else if(!strcmp(p, "manual")) options.plugins_loading=PLUGINS_MANUAL;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "unzip_location=")) )
	{
	  g_free(options.unzip_location);
	  options.unzip_location = (char *)g_malloc((strlen(p) + 1) * 
						     sizeof(char));
	  strcpy(options.unzip_location, p);
	  continue;
	}
      if( (p=find_str(buffer, "unzip_options=")) )
        {
          g_free(options.unzip_options);
          options.unzip_options = (char *)g_malloc((strlen(p) + 1) *
						    sizeof(char));
          strcpy(options.unzip_options, p);
          continue;
        }
      if( (p=find_str(buffer, "tar_location=")) )
	{
          g_free(options.tar_location);
          options.tar_location = (char *)g_malloc((strlen(p) + 1) *
						   sizeof(char));
          strcpy(options.tar_location, p);
          continue;
	}      
      if( (p=find_str(buffer, "tar_options=")) )
        {
          g_free(options.tar_options);
          options.tar_options = (char *)g_malloc((strlen(p) + 1) *
						  sizeof(char));
          strcpy(options.tar_options, p);
          continue;
        }
      
      /*
	if( (p=find_str(buffer, "unzip_filter=")) )
        {
	for (i=0;i<strlen(p);i++) options.unzip_filter[i] = p[i];
	continue;
	}
      */  
      if( (p=find_str(buffer, "right_font_name=")) )
	{
	  strcpy(options.right_font_name, p);
	  continue;
	}
      if( (p=find_str(buffer, "left_font_name=")) )
	{
	  strcpy(options.left_font_name, p);
	  continue;
	}
      if( (p=find_str(buffer, "locale=")) )
	{
	  strcpy(options.locale, p);
	  continue;
	}
      if( (p=find_str(buffer, "file_checking=")) )
        {
	  if(!strcmp(p, "restrictive")) 
	    options.file_checking = FILE_CHECKING_ON;
          else if(!strcmp(p, "none")) 
	    options.file_checking = FILE_CHECKING_OFF;
	  else if(!strcmp(p, "middle")) 
	    options.file_checking = FILE_CHECKING_MID;
          else stop(l);
          continue;
        }
      if( (p=find_str(buffer, "rts_cts=")) )
        {
	  if(!strcmp(p, "on")) 
	    options.lp.hfc = HFC_ON;
          else if(!strcmp(p, "off")) 
	    options.lp.hfc = HFC_OFF;
          else stop(l);
          continue;
        }
      if( (p=find_str(buffer, "probe_89_92_92+=")) )
	{
	  if(!strcmp(p, "no"))
	    options.auto_detect = FALSE;
	  else if(!strcmp(p, "yes"))
	    options.auto_detect = TRUE;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "console=")) )
        {
	  if(!strcmp(p, "yes")) 
	    options.console_mode = TRUE;
          else if(!strcmp(p, "no")) 
	    options.console_mode = FALSE;
          else stop(l);
          continue;
        }
      if( (p=find_str(buffer, "show_gui=")) )
	{
	  if(!strcmp(p, "yes")) 
	    options.show_gui = TRUE;
          else if(!strcmp(p, "no")) 
	    options.show_gui = FALSE;
          else stop(l);
          continue;
        }
      if( (p=find_str(buffer, "force_dirlist=")) )
	{
	  if(!strcmp(p, "yes")) 
	    options.force_dirlist = TRUE;
          else if(!strcmp(p, "no")) 
	    options.force_dirlist = FALSE;
          else stop(l);
          continue;
        }
      if( (p=find_str(buffer, "port=")) )
	{
	  if(!strcmp(p, "parallel port #1")) options.lp.port=PARALLEL_PORT_1;
	  else if(!strcmp(p, "parallel port #2")) options.lp.port=PARALLEL_PORT_2;
	  else if(!strcmp(p, "parallel port #3")) options.lp.port=PARALLEL_PORT_3;
	  else if(!strcmp(p, "serial port #1")) options.lp.port=SERIAL_PORT_1;
	  else if(!strcmp(p, "serial port #2")) options.lp.port=SERIAL_PORT_2;
	  else if(!strcmp(p, "serial port #3")) options.lp.port=SERIAL_PORT_3;
	  else if(!strcmp(p, "serial port #4")) options.lp.port=SERIAL_PORT_4;
	  else if(!strcmp(p, "virtual port #1")) options.lp.port=VIRTUAL_PORT_1;
	  else if(!strcmp(p, "virtual port #2")) options.lp.port=VIRTUAL_PORT_2;
	  else if(!strcmp(p, "USB port #1")) options.lp.port=USB_PORT_1;
	  else if(!strcmp(p, "USB port #2")) options.lp.port=USB_PORT_2;
	  else if(!strcmp(p, "USB port #3")) options.lp.port=USB_PORT_3;
	  else if(!strcmp(p, "USB port #4")) options.lp.port=USB_PORT_4;
	  else stop(l);
	  continue;
	}
      if( (p=find_str(buffer, "method=")) )
	{
	  if(!strcmp(p, "automatic")) options.lp.method=IOM_AUTO;
	  else if(!strcmp(p, "asm"))	    
	    options.lp.method=IOM_ASM;
	  else if(!strcmp(p, "dcb")) 
	    options.lp.method=IOM_DCB;
	  else if(!strcmp(p, "kernel driver"))
	    options.lp.method=IOM_DRV;
	  else stop(l);
	  continue;
	}
    }
  fclose(txt);

  fprintf(stderr, "rcfile, 0x%03x\n", options.lp.io_addr);

  return;
}

/* Write the contents of some variables to the RC file in a plain text format */
void write_rc_file(void)
{
  FILE *txt;

  get_rcfile_path(&rc_file);
  txt=fopen(rc_file, "wt");
  if(txt==NULL)
    {
      gif->msg_box(_("Error"), _("Unable to write the config file (~/.tilp or tilp.ini).\n"));
      return;
    }

  fprintf(txt, "# Config file for tilp\n");
  fprintf(txt, "# Copyright (C) 1999-2000 Romain Lievin <rlievin@mail.com>\n");
  fprintf(txt, "# Warning: any comments that you add to this file WILL be overwritten\n");
  fprintf(txt, "\n");
  fprintf(txt, "version=%s\n", TILP_VERSION);
  fprintf(txt, "\n");
  fprintf(txt, "#\n");
  fprintf(txt, "# HARDWARE SECTION\n");
  fprintf(txt, "#\n");
  fprintf(txt, "\n");
  fprintf(txt, "# Calculator type\n");
  fprintf(txt, "calctype=");
  switch(options.lp.calc_type)
    {
    case CALC_TI92P:
      fprintf(txt, "ti92+\n");
      break;
    case CALC_TI92:
      fprintf(txt, "ti92\n");
      break;
    case CALC_TI89:
      fprintf(txt, "ti89\n");
      break; 
    case CALC_TI86:
      fprintf(txt, "ti86\n");
      break;
    case CALC_TI85:
      fprintf(txt, "ti85\n");
      break;
    case CALC_TI83P:
      fprintf(txt, "ti83+\n");
      break; 
    case CALC_TI83:
      fprintf(txt, "ti83\n");
      break;
    case CALC_TI82:
      fprintf(txt, "ti82\n");
      break;
    }
  fprintf(txt, "\n");
  fprintf(txt, "# Link cable type\n");
  fprintf(txt, "linktype=");
  switch(options.lp.link_type)
    {
    case LINK_PAR:
      fprintf(txt, "parallel\n");
      break;
    case LINK_SER:
      fprintf(txt, "serial\n");
      break;
    case LINK_TGL:
      fprintf(txt, "TIGraphLink\n");
      break; 
    case LINK_AVR:
      fprintf(txt, "fastAVRlink\n");
      break;
    case LINK_VTL:
      fprintf(txt, "virtual\n");
      break;
    case LINK_TIE:
      fprintf(txt, "TiEmulator\n");
      break;
    case LINK_VTI:
      fprintf(txt, "VTi\n");
      break;
    case LINK_UGL:
      fprintf(txt, "UsbGraphLink\n");
      break;
    case LINK_TPU:
      fprintf(txt, "TiPcUsbLink\n");
      break;
    }
  fprintf(txt, "\n");
  fprintf(txt, "# Port to use (serial, parallel, ...\n");
  fprintf(txt, "port=");
  switch(options.lp.port)
    {
    case PARALLEL_PORT_1:
      fprintf(txt, "parallel port #1\n");
      break;
    case PARALLEL_PORT_2:
      fprintf(txt, "parallel port #2\n");
      break;
    case PARALLEL_PORT_3:
      fprintf(txt, "parallel port #3\n");
      break;
    case SERIAL_PORT_1:
      fprintf(txt, "serial port #1\n");
      break;
    case SERIAL_PORT_2:
      fprintf(txt, "serial port #2\n");
      break;
    case SERIAL_PORT_3:
      fprintf(txt, "serial port #3\n");
      break;
    case SERIAL_PORT_4:
      fprintf(txt, "serial port #4\n");
      break;
    case VIRTUAL_PORT_1:
      fprintf(txt, "virtual port #1\n");
      break;
    case VIRTUAL_PORT_2:
      fprintf(txt, "virtual port #2\n");
      break;
    case USB_PORT_1:
      fprintf(txt, "USB port #1\n");
      break;
    case USB_PORT_2:
      fprintf(txt, "USB port #2\n");
      break;
    case USB_PORT_3:
      fprintf(txt, "USB port #3\n");
      break;
    case USB_PORT_4:
      fprintf(txt, "USB port #4\n");
      break;
    }
  fprintf(txt, "\n");
  fprintf(txt, "# Method to use for I/O accesses\n");
  fprintf(txt, "method=");
  switch(options.lp.method)
    {
    case IOM_AUTO:
      fprintf(txt, "automatic\n");
      break;
    case IOM_ASM:
      fprintf(txt, "asm\n");
      break;
    case IOM_DCB:
      fprintf(txt, "dcb\n");
      break;
    case IOM_DRV:
      fprintf(txt, "kernel driver\n");
      break;
    }
  fprintf(txt, "\n");
  fprintf(txt, "# Parallel/serial/virtual port address (0=automatic)\n");
  fprintf(txt, "adr_port=0x%03X\n", options.lp.io_addr);
  fprintf(txt, "\n");
  fprintf(txt, "# Serial device or character device (empty=automatic)\n");
  fprintf(txt, "serial_device=%s\n", options.lp.device);
  fprintf(txt, "\n");
  fprintf(txt, "# Baud rate for the fastAVRlink\n");
  fprintf(txt, "baudrate=%i\n", options.lp.baud_rate);
  fprintf(txt, "\n");
  fprintf(txt, "# Timeout value in 0.1 seconds\n");
  fprintf(txt, "timeout=%i\n", options.lp.timeout);
  fprintf(txt, "\n");
  fprintf(txt, "# Delay value\n");
  fprintf(txt, "delay=%i\n", options.lp.delay);
  fprintf(txt, "\n");
  fprintf(txt, "# Hardware flow control for fastAVRlink.\n");
  fprintf(txt, "rts_cts=%s\n", (options.lp.hfc == HFC_ON) ? "on" : "off");
  fprintf(txt, "\n");
  /*
  fprintf(txt, "# Use or not the Linux 'tidev' kernel module ?\n");
  fprintf(txt, "use_tidev=%s\n", options.lp.tidev ? "yes" : "no");
  fprintf(txt, "\n");
  fprintf(txt, "# Use or not the Win32 'DLPortI/O' kernel module ?\n");
  fprintf(txt, "use_dlportio=%s\n", options.lp.dlportio ? "yes" : "no");
  fprintf(txt, "\n");
  */
  fprintf(txt, "#\n");
  fprintf(txt, "# GUI SECTION\n");
  fprintf(txt, "#\n");
  fprintf(txt, "\n");
  fprintf(txt, "# Window size\n");
  fprintf(txt, "xsize=%i\n", options.xsize);
  fprintf(txt, "ysize=%i\n", options.ysize);
  fprintf(txt, "\n");
  fprintf(txt, "# Right window sort order: name, date, size, user, group, attrib\n");
  fprintf(txt, "clist_sort=");
  switch(options.clist_sort)
    {
    case SORT_BY_NAME: fprintf(txt, "name\n");
      break;
    case SORT_BY_DATE: fprintf(txt, "date\n");
      break;
    case SORT_BY_SIZE: fprintf(txt, "size\n");
      break;
    case SORT_BY_USER: fprintf(txt, "user\n");
      break;
    case SORT_BY_GROUP: fprintf(txt, "group\n");
      break;
    case SORT_BY_ATTRB: fprintf(txt, "attrib\n");
      break;
    }
  fprintf(txt, "clist_order=");
  switch(options.clist_sort_order)
    {
    case SORT_UP: fprintf(txt, "up\n");
      break;
    case SORT_DOWN: fprintf(txt, "down\n");
      break;
    }
  fprintf(txt, "\n");

  fprintf(txt, "# Left window sort order: name, info, type, size\n");
  fprintf(txt, "ctree_sort=");
  switch(options.ctree_sort)
    {
    case SORT_BY_NAME: fprintf(txt, "name\n");
      break;
    case SORT_BY_INFO: fprintf(txt, "info\n");
      break;
    case SORT_BY_TYPE: fprintf(txt, "type\n");
      break;
    case SORT_BY_SIZE: fprintf(txt, "size\n");
      break;
    }
  fprintf(txt, "ctree_order=");
  switch(options.ctree_sort_order)
    {
    case SORT_UP: fprintf(txt, "up\n");
      break;
    case SORT_DOWN: fprintf(txt, "down\n");
      break;
    }
  fprintf(txt, "\n");
  fprintf(txt, "# Show hidden files\n");
  fprintf(txt, "hidden_files=%s\n", options.show ? "show" : "hide");
  fprintf(txt, "\n");
  fprintf(txt, "# Delete files\n");
  fprintf(txt, "confirm=%s\n", options.confirm ? "yes" : "no");
  fprintf(txt, "\n");
  fprintf(txt, "# Display console.\n");
  fprintf(txt, "console=%s\n", (options.console_mode) ? "yes" : "no");
  fprintf(txt, "\n");
  fprintf(txt, "# Show GUI in command line mode.\n");
  fprintf(txt, "show_gui=%s\n", (options.show_gui) ? "yes" : "no");
  fprintf(txt, "\n");
  fprintf(txt, "#\n");
  fprintf(txt, "# CALCULATOR SECTION\n");
  fprintf(txt, "#\n");
  fprintf(txt, "\n");
  fprintf(txt, "# Full or local path for sending variables\n");
  fprintf(txt, "path=%s\n", options.path_mode ? "local" : "full");
  fprintf(txt, "\n");
  fprintf(txt, "# Keep (extended file format) or not keep archive attribute (normal file format)\n");
  fprintf(txt, "file_mode=%s\n", options.file_mode ? "extended" : "normal");
  fprintf(txt, "\n");
  fprintf(txt, "# File checking: authorize (none, middle) or forbid (restrictive) the ability to transfer a file type different of the current calc type\n");
  fprintf(txt, "file_checking=");
  switch(options.file_checking)
    {
    case FILE_CHECKING_OFF: fprintf(txt, "none\n");
      break;
    case FILE_CHECKING_MID: fprintf(txt, "middle\n");
      break;
    case FILE_CHECKING_ON: fprintf(txt, "restrictive\n");
      break;
    }
  fprintf(txt, "\n");
  fprintf(txt, "# Auto-detection of TI89/92/92+ calculator.\n");
  fprintf(txt, "probe_89_92_92+=%s\n", (options.auto_detect) ? "yes" : "no");
  fprintf(txt, "\n");
  fprintf(txt, "# Force a dirlist before sending variables (same behaviour as TIGL software).\n");
  fprintf(txt, "force_dirlist=%s\n", (options.force_dirlist) ? "yes" : "no");
  fprintf(txt, "\n");
  fprintf(txt, "#\n");
  fprintf(txt, "# EXTERNAL PROGRAMS SECTION\n");
  fprintf(txt, "#\n");
  fprintf(txt, "\n");
  fprintf(txt, "# Unzip program location: 'unzip'/'wzunzip.exe' by default\n");
  fprintf(txt, "unzip_location=%s\n", options.unzip_location);
  fprintf(txt, "\n");
  fprintf(txt, "# Unzip program options: no option -> 'archivename/' directory\n");
  fprintf(txt, "unzip_options=%s\n", options.unzip_options);
  fprintf(txt, "\n");
  fprintf(txt, "# Tar program location: 'tar'/'wzunzip.exe' by default\n");
  fprintf(txt, "tar_location=%s\n", options.tar_location);
  fprintf(txt, "\n");
  fprintf(txt, "# Tar program options: no option -> 'xvzf' by default\n");
  fprintf(txt, "tar_options=%s\n", options.tar_options);
  fprintf(txt, "\n");
  
  /*
  fprintf(txt, "# Unzip filter : parameters [list] [-x list] [-d exdir] \n# eg. unzip_filter=*.89* -d tidir/  will unzip ti89 files into tidir/ directory.\n");
  fprintf(txt, "unzip_filter=%s\n", options.unzip_filter );
  fprintf(txt, "\n"); */
  fprintf(txt, "#\n");
  fprintf(txt, "# FONTS SECTION\n");
  fprintf(txt, "#\n");
  fprintf(txt, "\n");
  fprintf(txt, "# Font used in the leftt window.\n");
  fprintf(txt, "left_font_name=%s\n", options.left_font_name);
  fprintf(txt, "\n");
  fprintf(txt, "# Font used in the right window.\n");
  fprintf(txt, "right_font_name=%s\n", options.right_font_name);
  fprintf(txt, "\n");
  fprintf(txt, "#\n");
  fprintf(txt, "# SCREEN SECTION\n");
  fprintf(txt, "#\n");
  fprintf(txt, "\n");
  fprintf(txt, "# Full (full) or clipped (clipped) screen for screen captures\n");
  fprintf(txt, "screen_mode=%s\n", options.screen_clipping ? "clipped" : "full");
  fprintf(txt, "\n");
  fprintf(txt, "# Use the PCX (pcx), XPM (xpm) or JPEG (jpg) file format for images\n");
  fprintf(txt, "screen_format=");
  switch(options.screen_format)
    {
    case XPM: fprintf(txt, "xpm\n");
      break;
    case PCX: fprintf(txt, "pcx\n");
      break;
    case JPG: fprintf(txt, "jpg\n");
      break;
    }
  fprintf(txt, "\n");
  fprintf(txt, "#\n");
  fprintf(txt, "# MISC SECTION\n");
  fprintf(txt, "#\n");
  fprintf(txt, "\n");
  fprintf(txt, "# Load plugins at startup (auto) or manually (manual)\n");
  fprintf(txt, "plugins_loading=%s\n", options.plugins_loading ? "auto" : "manual");
  fprintf(txt, "\n");
  fprintf(txt, "# Language used.\n");
  fprintf(txt, "locale=%s\n", options.locale);
  fprintf(txt, "\n");
  
  fprintf(txt, "RC_END\n");
  fclose(txt);
}

/**/

int get_cwdfile_path(char **path)
{
#if defined(__UNIX__)
  char *home_dir;
  
  get_home_path(&home_dir);
  *path = (char *)g_malloc((strlen(home_dir) + strlen(CWD_FILE) + 1)
			    * sizeof(char));
  strcpy(*path, home_dir); g_free(home_dir);
  strcat(*path, CWD_FILE);
  //fprintf(stdout, "Home path: %s\n", *path);
#elif defined(__WIN32__)
  *path = (char *)g_malloc((strlen(inst_paths.base_dir) + 
			     strlen(DIR_SEPARATOR) + 
			     strlen(CWD_FILE) + 1) * sizeof(char));
  strcpy(*path, inst_paths.base_dir);
  strcat(*path, DIR_SEPARATOR);
  strcat(*path, CWD_FILE);
#endif

  return 0;
}


/* Chech whether a RC file exists */
int is_cwdfile_exist(void)
{
  int b=0;
  get_cwdfile_path(&cwd_file);
  b = !access(cwd_file, F_OK);
  g_free(cwd_file);
  return b;
}


/* Read the RC file and configure the corresponding variables */
char* read_cwd_file(void)
{
  FILE *txt;
  char *s;
  int l;

  get_cwdfile_path(&cwd_file);
  if(!is_cwdfile_exist())
  {
	  s = NULL;
	  return s;
  }

  txt=fopen(cwd_file, "rt");
  if(txt == NULL)
    {
      fprintf(stdout, _("'Current working directory' file can not be opened.\n"));
      gif->msg_box(_("Information"), _("CWD file not found.\n"));
      return NULL;
    }
	fseek(txt, 0, SEEK_END);
    l = ftell(txt);
    fseek(txt, 0, SEEK_SET);

	s = g_malloc(l*sizeof(gchar));
	fscanf(txt, "%s", s);
	//g_warning("Read: <%s>\n", s); 
	fclose(txt);
	//g_free(cwd_file);

	return s;
}


void write_cwd_file(void)
{
  FILE *txt;

  g_free(cwd_file); 
  get_cwdfile_path(&cwd_file);
  txt=fopen(cwd_file, "wt");
  if(txt==NULL)
    {
      gif->msg_box(_("Error"), _("Unable to write the CWD file (~/.tilp_cwd or tilp.cwd).\n"));
      return;
    }
	fprintf(txt, "%s\n", clist_win.cur_dir);
	fclose(txt);
	g_free(cwd_file);
}
