/*  tilp - a linking program for TI graphing calculators
 *  Copyright (C) 1999-2002  Romain Lievin
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
#include <unistd.h>

#ifndef __MACOSX__
# include "platform.h"
# include "tilibs.h"
#else
# include <libticables/cabl_err.h>
# include <libticalcs/calc_err.h>
# include <libticalcs/calc_int.h>
# include <glib/glib.h>
# include <stdlib.h>
#endif

#include "sub_main.h"
#include "struct.h"
#include "defs.h"
#include "gui_indep.h"
#include "error.h"
#include "files.h"
#include "vars.h"
#include "select.h"

/* All functions returns -1 if error, 0 if OK (a file need to be saved). */


/*
  Check whether the calc is ready (with or without auto-detection)
*/
int cb_calc_is_ready(void)
{
  int err;
  int c = 0;
  
  ticalc_get_calc(&c);
  
  if(options.auto_detect && ((c == CALC_TI73) || (c == CALC_TI83P) || 
			     (c == CALC_TI89) || (c == CALC_TI92P)))
    {
      err = ticalc_73_83p_89_92p_isready(&(options.lp.calc_type));
      if(tilp_error(err))
	{  
	  return -1;
	}
      ticalc_set_calc(options.lp.calc_type, &ti_calc, &link_cable);
    }
  else
    {
      err = ti_calc.isready();
      if(err && (err != ERR_VOID_FUNCTION))
	{
	  tilp_error(err);
	  return -1;
	}
    }

  return 0;
}


/*
  Screendump: see cb_screen.c
*/


/*
  Do a directory listing
*/
TIEXPORT
int cb_dirlist(void)
{
  if(cb_calc_is_ready())
    return -1;
  
  if (remote_directory_list() != 0)
    return -1;

  return 0;
}



/*
  Send a backup from the specified filename
*/
int cb_send_backup(char *filename)
{
  int err, ret;
  FILE *bck;
  int file_mode = MODE_NORMAL;
  int file_check = MODE_NORMAL;
  
  ret = gif->user2_box(_("Warning"), 
		       _("You are going to restore the content of your calculator with a backup. The whole memory will be erased. Are you sure you want to do that ?"),
		       _("Next >"), 
		       _("Cancel"));
  if(ret != BUTTON1)
    return -1;

  if(cb_calc_is_ready())
    return -1;
     
  if(options.file_mode == EXTENDED_FORMAT)
    file_mode=MODE_KEEP_ARCH_ATTRIB;
  switch(options.file_checking)
    {
    case FILE_CHECKING_ON:
      file_check = MODE_FILE_CHK_ALL;
      break;
    case FILE_CHECKING_MID:
      file_check = MODE_FILE_CHK_MID;
      break;
    case FILE_CHECKING_OFF:
      file_check = MODE_FILE_CHK_NONE;
      break;
    default:
      file_check = MODE_FILE_CHK_MID;
      break;
    }

  switch(options.lp.calc_type)
    {
    case CALC_TI82:
    case CALC_TI85:
    case CALC_TI86:
      gif->create_pbar_type5(_("Backup"), 
			     _("Waiting for confirmation on calc..."));
      break;
	case CALC_TI73:
    case CALC_TI83:
    case CALC_TI83P:
    case CALC_TI92:
      gif->create_pbar_type3(_("Backup"));
      break;
    case CALC_TI89:
    case CALC_TI92P:
      gif->create_pbar_type5(_("Backup"), "");
      break;
      break;
    }

  err = ticalc_open_ti_file(filename, "rb", &bck);
  if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
  err=ti_calc.send_backup(bck, file_mode | file_check);
  ticalc_close_ti_file();
  gif->destroy_pbar();
  if(tilp_error(err)) 
    return -1;

  return 0;
}


/*
  Receive a backup
*/
int cb_recv_backup(void)
{
  FILE *bck;
  int err=0;
  longword version;
  char tmp_filename[MAXCHARS];
  int file_mode=MODE_NORMAL;

  if(cb_calc_is_ready())
    return -1;
  
  if(options.file_mode == EXTENDED_FORMAT)
    file_mode=MODE_KEEP_ARCH_ATTRIB;
  
  switch(options.lp.calc_type)
    {
    case CALC_TI82:
    case CALC_TI85:
    case CALC_TI86:
      gif->create_pbar_type5(_("Backup"), _("Waiting for backup from calc..."));
      break;
	  case CALC_TI73:
    case CALC_TI83:
    case CALC_TI83P:
      gif->create_pbar_type3(_("Backup"));
      break;
    case CALC_TI89:
    case CALC_TI92P:
      gif->create_pbar_type5(_("Backup"), "");
      break;
    case CALC_TI92:
      gif->create_pbar_type2(_("Backup"), _("Receiving blocks"));
      break;
    } 

  strcpy(tmp_filename, g_get_tmp_dir());
  strcat(tmp_filename, DIR_SEPARATOR);
  strcat(tmp_filename, TMPFILE_BACKUP);
  do
    {
      info_update.refresh();
      if(info_update.cancel) break;

      err=ticalc_open_ti_file(tmp_filename, "wb", &bck);
         if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
      err=ti_calc.recv_backup(bck, MODE_NORMAL | file_mode, &version);
      ticalc_close_ti_file(bck);
    }
  while( ((err == ERR_RCV_BYT_TIMEOUT) || (err == ERR_RCV_BIT_TIMEOUT)) && 
	 ((options.lp.calc_type == CALC_TI82) || 
	  (options.lp.calc_type == CALC_TI85) ||
	  (options.lp.calc_type == CALC_TI86)) );
  
  gif->destroy_pbar();
  if(tilp_error(err)) 
    return -1;

  return 0;
}

/*
  Receive the IDlist
*/
int cb_id_list(void)
{
  char buffer[MAXCHARS];
  char idlist[MAXCHARS];

  if(cb_calc_is_ready())
    return -1;

  if(tilp_error(ti_calc.get_idlist(idlist)))
    return -1;
  strcpy(buffer, _("IDlist: "));
  strcat(buffer, idlist+2);
  gif->msg_box(_("IDlist"), buffer);
  
  return 0;
}

/*
  Do a ROM dumping
*/
int cb_rom_dump(void)
{
  gint ret;
  FILE *dump;
  int err=0;
  gchar tmp_filename[MAXCHARS];
  
  ret = gif->user2_box(_("Warning"), 
		       _("An assembly program is about to be sent on your calculator. If you have not a backup yet, you should do one before proceeding with ROM dumping !"),
		       _("Next >"), 
		       _("Cancel"));
  if(ret != BUTTON1) return -1;
  
  switch(options.lp.calc_type)
    {
    case CALC_TI73:
    case CALC_TI83:
      ret = gif->user2_box(_("Information"), 
			   _("You must have AShell on your calculator in order to do a ROM dump.\nTiLP wil transfer the ROM dump program and it will wait until you launch it from the calculator."),
			   _("Next >"), 
			   _("Cancel"));
      switch(ret)
	{
	case BUTTON1: // OK/Next
	  gif->create_pbar_type5(_("ROM dump"), 
				 _("Receiving bytes"));
	  
	  strcpy(tmp_filename, g_get_tmp_dir());
	  strcat(tmp_filename, DIR_SEPARATOR);
	  strcat(tmp_filename, TMPFILE_ROMDUMP);
	  do
	    {
	      info_update.refresh();
	      if(info_update.cancel) break;
	      err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
              if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
	      err=ti_calc.dump_rom(dump, ret);
	      ticalc_close_ti_file(dump);
	    }
	  while( ((err == ERR_RCV_BIT_TIMEOUT) || 
		  (err == ERR_RCV_BYT_TIMEOUT)) );
	  
	  gif->destroy_pbar();
	  if(tilp_error(err)) return -1;	      
	  return 0;
	  break;
	default: // Cancel */
	  return -1; 
	  break;
	}
      break;
    case CALC_TI85:
      ret = gif->user2_box(_("Information"), 
			   _("You must have Zshell or Usgard on your calculator in order to do a ROM dump.\nTiLP wil transfer the ROM dump program and it will wait until you launch it from the calculator."),
			   _("Next >"), 
			   _("Cancel"));
      switch(ret)
	{
	case BUTTON1: // OK/Next
	  /* Ask for the shell type */
	  ret = gif->user3_box("Shell type", 
			       "Select a shell", 
			       "Zshell", "Usgard", "Cancel");
	  if(ret == 3) return -1;
	  else
	    {
	      gif->create_pbar_type5(_("ROM dump"), 
				     _("Receiving bytes"));
	      
	      strcpy(tmp_filename, g_get_tmp_dir());
	      strcat(tmp_filename, DIR_SEPARATOR);
	      strcat(tmp_filename, TMPFILE_ROMDUMP);
	      do
		{
		  info_update.refresh();
		  if(info_update.cancel) break;
		  err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
                  if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
		  err=ti_calc.dump_rom(dump, (ret == 1) ? 
				       SHELL_ZSHELL : SHELL_USGARD);
		  ticalc_close_ti_file(dump);
		}
	      while( ((err == ERR_RCV_BIT_TIMEOUT) || 
		      (err == ERR_RCV_BYT_TIMEOUT)) );
	      
	      gif->destroy_pbar();
	      if(tilp_error(err)) return -1;	      
	      return 0;
	    }
	  break;
	default: // Cancel */
	  return -1; 
	  break;
	}
      break;
	  case CALC_TI83P:
    case CALC_TI86:
      ret = gif->user2_box(_("Information"), 
			   _("You must have a shell (any) on your calculator in order to do a ROM dump.\nTiLP wil transfer the ROM dump program and it will wait until you launch it from the calculator."),
			   _("Next >"), 
			   _("Cancel"));
      switch(ret)
	{
	case BUTTON1: // OK/Next
	  gif->create_pbar_type5(_("ROM dump"), 
				 _("Receiving bytes"));
	  
	  strcpy(tmp_filename, g_get_tmp_dir());
	  strcat(tmp_filename, DIR_SEPARATOR);
	  strcat(tmp_filename, TMPFILE_ROMDUMP);
	  do
	    {
	      info_update.refresh();
	      if(info_update.cancel) break;
	      err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
              if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
	      err=ti_calc.dump_rom(dump, ret);
	      ticalc_close_ti_file(dump);
	    }
	  while( (err == ERR_RCV_BYT_TIMEOUT) || 
		 (err == ERR_RCV_BIT_TIMEOUT) );
	  
	  gif->destroy_pbar();
	  if(tilp_error(err)) return -1;	      
	  return 0;
	  break;
	default: // Cancel */
	  return -1; 
	  break;
	}
      break;
    case CALC_TI89:
    case CALC_TI92P:
      gif->create_pbar_type5(_("ROM dump"), _("Receiving bytes"));
      
      strcpy(tmp_filename, g_get_tmp_dir());
      strcat(tmp_filename, DIR_SEPARATOR);
      strcat(tmp_filename, TMPFILE_ROMDUMP);
      do
	{
	  info_update.refresh();
	  if(info_update.cancel) break;
	  err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
          if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
	  err=ti_calc.dump_rom(dump, ret);
	  ticalc_close_ti_file(dump);
	}
      while( (err == ERR_RCV_BYT_TIMEOUT) || 
	     (err == ERR_RCV_BIT_TIMEOUT) );
      
      gif->destroy_pbar();
      if(tilp_error(err)) return -1;	      
      return 0;
      break;
    case CALC_TI92:
      ret = gif->user2_box(_("Information"), 
			   _("You must have the FargoII shell on your calculator in order to do a ROM dump."),
			   _("Next >"), 
			   _("Cancel"));
      switch(ret)
	{
	case BUTTON1: // OK/Next
	  /* Ask for the ROM size */
	  ret = gif->user3_box("ROM size", 
			       "Select the size of your ROM or cancel", 
			       "1Mb", "2 Mb", "Cancel");
	  if(ret == 3)
	    return -1;
	  else
	    {
	      printf("ROM size: %i Mb\n", ret);
	      gif->create_pbar_type5(_("ROM dump"), 
				     _("Receiving bytes"));
	      
	      strcpy(tmp_filename, g_get_tmp_dir());
	      strcat(tmp_filename, DIR_SEPARATOR);
	      strcat(tmp_filename, TMPFILE_ROMDUMP);
	      do
		{
		  info_update.refresh();
		  if(info_update.cancel) break;
		  err = ticalc_open_ti_file(tmp_filename, "wb", &dump);
                  if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
		  err=ti_calc.dump_rom(dump, ret);
		  ticalc_close_ti_file(dump);
		}
	      while( (err == ERR_RCV_BYT_TIMEOUT) || 
		     (err == ERR_RCV_BIT_TIMEOUT) );
	      
	      gif->destroy_pbar();
	      if(tilp_error(err)) return -1;	      
	      return 0;
	    }	  
	  break;
	default: // Cancel */
	  return -1;
	  break;
	}
      break;
    default:
      DISPLAY("Unsupported ROM dump\n");
      break;
    }

  return 0;
}

/*
  Get the ROM version
*/
int cb_rom_version(void)
{
  char version[MAXCHARS];
  char buffer[MAXCHARS];

  if(cb_calc_is_ready())
    return -1;
 
  if(tilp_error(ti_calc.get_rom_version(version)))
    return -1;
  sprintf(buffer, _("ROM version %s\n"), version);
  gif->user1_box(_("ROM version"), buffer, _(" OK "));

  return 0;
}

/*
  Send a FLASH app
*/
TIEXPORT
int cb_send_flash_app(char *filename)
{
  int err, ret;
  FILE *bck;
  gint old_timeout;
  
  char *msg = _("You are going to send a FLASH application on your calculator.\nHe is strongly recommended for Windows users to close any application and eventually turn off your screen saver (this makes the transfer rate decrease !).");
  
  ret=gif->user2_box(_("Warning"), msg,
		     _("Continue"), _("Cancel"));
  if(ret == BUTTON2)
    return -1;

  if(cb_calc_is_ready())
    return -1;

  switch(options.lp.calc_type)
    {
    case CALC_TI73:
    case CALC_TI82:
    case CALC_TI83:
    case CALC_TI83P:
    case CALC_TI85:
    case CALC_TI92:
      gif->create_pbar_type3(_("Flash"));
      break;
    case CALC_TI89:
    case CALC_TI92P:
      gif->create_pbar_type3(_("Flash"));
      break;
      break;
    }

  err = ticalc_open_ti_file(filename, "rb", &bck);
  if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
  old_timeout = ticable_get_timeout();
  ticable_set_timeout(100); // 10 seconds
  err=ti_calc.send_flash(bck, MODE_APPS);
  ticable_set_timeout(old_timeout);
  ticalc_close_ti_file();
  gif->destroy_pbar();  
  if(tilp_error(err)) return -1;

  return 0;
}

/*
  Send a FLASH Operating System (AMS).
  Note: the timeout is increased to 10 seconds during the operation.
*/
int cb_send_flash_os(char *filename)
{
  int err, ret;
  FILE *bck;
  gint old_timeout;

  char *msg =_("You are going to upgrade the Operating System of your calculator.\nHe is strongly recommended for Windows users to close any application and to turn off your screen saver (this makes the transfer rate decrease !). If the transfer fails, wait until the TI89/TI92+ displays 'Waiting to receive' and try the transfer again. For TI73/83+ users, turns the calculator off and press a key.");
  
  ret=gif->user2_box(_("Warning"), msg,
		     _("Continue"), _("Cancel"));
  if(ret == BUTTON2)
    return -1;
  
  if(cb_calc_is_ready())
    return -1;

  switch(options.lp.calc_type)
    {
    case CALC_TI73:
    case CALC_TI82:
    case CALC_TI83:
    case CALC_TI83P:
    case CALC_TI85:
    case CALC_TI92:
      gif->create_pbar_type3(_("Flash"));
      break;
    case CALC_TI89:
    case CALC_TI92P:
      gif->create_pbar_type5(_("Flash"), "");
      break;
      break;
    }

  err = ticalc_open_ti_file(filename, "rb", &bck);
  if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
  old_timeout = ticable_get_timeout();
  ticable_set_timeout(100); // 10 seconds
  err=ti_calc.send_flash(bck, MODE_AMS);
  ticable_set_timeout(old_timeout);
  ticalc_close_ti_file();
  gif->destroy_pbar();
  if(tilp_error(err)) return -1;

  return 0;
}

/*
  Receive an FLASH application
*/
int cb_recv_app(void)
{
  int err=0;
  GList *ptr;
  FILE *txt;
  struct varinfo *v;
  char filename[MAXCHARS];
  int ret, skip=0;
  char buffer[MAXCHARS];
  char *dirname;

  if(ctree_win.selection2 == NULL) 
    return 0;

  if(cb_calc_is_ready())
    return -1;

  switch(options.lp.calc_type)
    {
    case CALC_TI73:
    case CALC_TI82:
    case CALC_TI83:
    case CALC_TI85:
    case CALC_TI86:
    case CALC_TI92:
      return -1;
      break;
    case CALC_TI83P:
    case CALC_TI89:
    case CALC_TI92P:
      gif->create_pbar_type5(_("Receiving application(s)"), "");
      break;
    }

  ptr=ctree_win.selection2;
  while(ptr != NULL)
    {
      v=(struct varinfo *)ptr->data;
      
      /* If the LAST element is just a folder, skip it */
      if( (v->is_folder == FOLDER) && (ptr->next == NULL) )
	break;

#ifndef __MACOSX__
      strcpy(filename, v->translate);
#else
      strcpy(filename, g_get_tmp_dir());
      strcat(filename, G_DIR_SEPARATOR_S);
      strcat(filename, v->translate);
#endif
      strcat(filename, ".");
      strcat(filename, ti_calc.byte2fext(v->vartype));
      
      if(options.confirm == CONFIRM_YES)
	{
	  if( access(filename, F_OK) == 0 )
	    {
	      sprintf(buffer, _("The file %s already exists. Overwrite ?"),
		      filename);
	      ret=gif->user3_box(_("Warning"), buffer,
				 _(" Overwrite "), _(" Rename "),
				 _(" Skip "));
	      switch(ret)
		{
		case BUTTON2:
		  dirname=gif->dlgbox_entry(_("Rename the file"),
					    _("New name: "), filename);
		  if(dirname == NULL) 
                    {
                      gif->destroy_pbar();
                      return -1;
                    }
		  strcpy(filename, dirname);
		  g_free(dirname);
		case BUTTON1:
		  skip=0;
		  break;
		case BUTTON3:
		  skip=1;
		  break;
		default:
		  break;
		}
	    }
	}
      if(skip == 0)
	{
	  err = ticalc_open_ti_file(filename, "wb", &txt);	
	  if(!err)
	    {
	      err = ti_calc.recv_flash(txt, MODE_NORMAL, 
				       v->translate, v->varsize);
	      ticalc_close_ti_file();
	    }
	  if(tilp_error(err))
	    {
	      gif->destroy_pbar();
	      return -1;
	    }
	}
      
      ptr=ptr->next;
    }
  gif->destroy_pbar();
  
  return 0;
}

/*
  Convert a FLASH OS (AMS) into a ROM image
*/
int cb_ams_to_rom(char *filename)
{
  FILE *file, *fo;
  byte data;
  char str[128];
  longword flash_size;
  int i, j;
  int num_blocks;
  word last_block;
  byte str_size;
  char date[5];
  char filename2[MAXCHARS];
  char *ext;
  char *signature = "Advanced Mathematics Software";
  int tib = 0;
  int calc_type;
  long offset;

  file = fopen(filename, "rb");
  if(file == NULL)
    {
      DISPLAY_ERROR("Unable to open this file: <%s>\n", filename);
      return -1;
    }
  
  ext = strrchr(filename, '.');
  if(ext != NULL)
    {
      strncpy(filename2, filename, strlen(filename)-strlen(ext));
      filename2[strlen(filename)-strlen(ext)] = '\0';
    }  
  else
    strcpy(filename2, filename);
  strcat(filename2, ".rom");

  fo = fopen(filename2, "wb");
  if(fo == NULL)
    {
      DISPLAY_ERROR("Unable to open this file: <%s>\n", filename2);
      return -1;
    }

  /* Check whether we have a .89u/.9xu or a .tib file */
  fgets(str, 128, file);
  if(strstr(str, "**TIFL**") == NULL) // is a .89u file
    {
      for(i=0, j=0; i<127; i++) // is a .tib file
	{
	  if(str[i] == signature[j])
	    {
	      j++;
	      if(j==strlen(signature))
		{
		  tib = 1;
		  break;
		}
	    }
	}
      if(j < strlen(signature))
	return -1; // not a FLASH file
    }

  /* Now, we convert it */
  rewind(file);
  if(!tib)
    {
      /* If a .89u/.9xu file, we skip the licence header */
      fgets(str, 9, file);
      if(strcmp(str, "**TIFL**")) 
	return -1;
      for(i=0; i<4; i++) 
	fgetc(file);
      
      for(i=0; i<4; i++)
	date[i] = fgetc(file);
      DISPLAY("Date of the FLASHapp or License: %02X/%02X/%02X%02X\n", 
	      date[0], date[1], date[2], 0xff & date[3]);
      str_size=fgetc(file);
      for(i=0; i<str_size; i++)
	str[i]=fgetc(file);
      str[i]='\0';
      for(i=16+str_size+1; i<0x4A; i++)
	fgetc(file);
      flash_size = fgetc(file);
      flash_size += (fgetc(file) << 8);
      flash_size += (fgetc(file) << 16);
      flash_size += (fgetc(file) << 24);

      if(!strcmp(str, "License"))
	{
	  DISPLAY("There is a license header: skipped.\n");
	  for(i=0; i<flash_size; i++)
	    fgetc(file);
	  
	  fgets(str, 9, file);
	  if(strcmp(str, "**TIFL**"))
	    return -1;
	  for(i=0; i<4; i++) fgetc(file);
	  for(i=0; i<4; i++)
	    date[i] = 0xff & fgetc(file);
	  DISPLAY("Date of the FLASHapp or License: %02X/%02X/%02X%02X\n", 
		  date[0], date[1], date[2], 0xff & date[3]);
	  str_size=fgetc(file);
	  for(i=0; i<str_size; i++)
	    str[i]=fgetc(file);
	  str[i]='\0';
	  for(i=16+str_size+1; i<0x4A; i++)
	    fgetc(file);
	  flash_size = fgetc(file);
	  flash_size += (fgetc(file) << 8);
	  flash_size += (fgetc(file) << 16);
	  flash_size += (fgetc(file) << 24);
	}
    }
  else
    {
      /* else, we can read it directly */
      fseek(file, 0, SEEK_END);
      flash_size = ftell(file);
      fseek(file, 0, SEEK_SET);
      strcpy(str, "basecode");
    }       
  
  DISPLAY("FLASH application name: \"%s\"\n", str);
  DISPLAY("FLASH application/Operating System size: %i bytes.\n", flash_size);

  /* Now, read data from the file and convert it */
  num_blocks = flash_size/65536;
  DISPLAY("Number of blocks: %i\n", num_blocks + 1);

  /* Boot block */
  for(i=0; i<0x05; i++)
    fputc(0xff, fo);

  offset = ftell(file);
  fseek(file, 0x8d, SEEK_CUR); // MSB of the PC reset vector
  data = fgetc(file);
  if((data&0x60)==0x20) // internal (0x200000)  or external (0x400000)
    calc_type=CALC_TI89; 
  else
    calc_type=CALC_TI92P;
  fseek(file, offset, SEEK_SET);

  if(calc_type == CALC_TI89)
    fputc(0x20, fo); // internal
  else
    fputc(0x40, fo); // external

  for(i=0x06; i<0x65; i++)
    fputc(0xff, fo);

  fputc(0xf0, fo); // FLASH ROM

  for(i=0x66; i<0x12000; i++)
    fputc(0xff, fo);
  
  gif->create_pbar_type1(_("Converting..."));

  /* FLASH upgrade */
  for(i=0; i<num_blocks; i++ )
    {

      info_update.percentage = (float)i/(num_blocks);
      info_update.pbar();
      if(info_update.cancel) 
	{
	  gif->destroy_pbar();
	  fclose(file);
	  fclose(fo);
	  return -1;
	}

      for(j=0; j<65536; j++)
 	{
	  data=fgetc(file);
	  fputc(data, fo);
	}
    }

  last_block=flash_size % 65536;
  for(j=0; j<last_block; j++)
    {
      data=fgetc(file);
      fputc(data, fo);
    }

  info_update.percentage = (float)i/(num_blocks);
  info_update.pbar();
  if(info_update.cancel) 
    {
      gif->destroy_pbar();
      fclose(file);
      fclose(fo);
      return -1;
    }

  for(j=0x12000+flash_size; j<2*1024*1024; j++)
    fputc(0xff, fo);

  gif->destroy_pbar();
  fclose(file);
  fclose(fo);

  return 0;
}

/*
  Send one or more selected variables
*/
int cb_send_var(void)
{
  GList *ptr;
  FILE *txt;
  struct file_info *f=NULL;
  gint i=0;
  gint l=0;
  int path_mode = MODE_NORMAL;
  int file_mode = MODE_NORMAL;
  int file_check = MODE_NORMAL;
  int err;

  if(clist_win.selection == NULL) 
    return 0;

  if(cb_calc_is_ready())
    return -1;

  if(options.path_mode == LOCAL_PATH)
    path_mode = MODE_LOCAL_PATH;
  if(options.file_mode == EXTENDED_FORMAT)
    file_mode = MODE_KEEP_ARCH_ATTRIB;
  switch(options.file_checking)
    {
    case FILE_CHECKING_ON:
      file_check = MODE_FILE_CHK_ALL;
      break;
    case FILE_CHECKING_MID:
      file_check = MODE_FILE_CHK_MID;
      break;
    case FILE_CHECKING_OFF:
      file_check = MODE_FILE_CHK_NONE;
      break;
    default:
      file_check = MODE_FILE_CHK_MID;
      break;
    }
  
  if(options.confirm == CONFIRM_YES)
    file_mode |= MODE_DIRLIST;

  ptr = clist_win.selection;
  l = g_list_length(clist_win.selection);
  
  /* Choose the appropriate dialog box */
  if(l == 1)
    { 
      // a single file (single var or group)
      f=(struct file_info *)ptr->data;
      if(strstr(f->filename, ticalc_group_file_ext(options.lp.calc_type)))
	gif->create_pbar_type5(_("Sending group file"), "");
      else
	gif->create_pbar_type4(_("Sending variable"), "");
    }
  else
    gif->create_pbar_type5(_("Sending variables"), "");
  
  /* Send the files */
  while(ptr != NULL)
    {
      f=(struct file_info *)ptr->data;
      
      if(strstr(f->filename, ticalc_group_file_ext(options.lp.calc_type)))
	{ 
	  /****************/
	  /* A group file */
	  /****************/

          err = tilp_error(ticalc_open_ti_file(f->filename, "rb", &txt));
          if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
	  
	  /* It is not the last file to send */
	  if( ((ptr->next) != NULL) && (l > 1) )
	    {
	      /* More than one file to send */
	      if(tilp_error(ti_calc.send_var(txt, MODE_SEND_VARS | 
					     path_mode | file_mode | 
					     file_check)))
		{
		  gif->destroy_pbar();
		  return -1;
		}
	    }
	  else
	    {
	      /* It is the last one */
	      if(tilp_error(ti_calc.send_var(txt, MODE_SEND_LAST_VAR | 
					     path_mode | file_mode |
					     file_check)))
		{
		  gif->destroy_pbar();
		  return -1;
		}
	    }
	  
	}
      else
	{ 
	  /*****************/
	  /* A single file */
	  /*****************/
	  
	  if(strstr(f->filename, ticalc_backup_file_ext(options.lp.calc_type)))
	    {/*
	      gif->destroy_pbar();
	      cb_send_backup(f->filename);
	      return 0;*/
	      gif->destroy_pbar();
	      gif->msg_box(_("Error"), 
			   _("Use the 'Restore' button instead."));
	      return -1;
	    }
	  else if(strstr(f->filename, ticalc_flash_app_file_ext(options.lp.calc_type)))
	    {
	      gif->destroy_pbar();
	      cb_send_flash_app(f->filename);
	      return 0;
	    }
	  else if(strstr(f->filename, ticalc_flash_os_file_ext(options.lp.calc_type)))
	    {
	      gif->destroy_pbar();
	      cb_send_flash_os(f->filename);
	      return 0;
	    }

          err = ticalc_open_ti_file(f->filename, "rb", &txt);
          if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
	  
	  /* It is not the last file to send */
	  if( ((ptr->next) != NULL) && (l > 1) )
	    {
	      /* More than one file to send */
	      if(tilp_error(ti_calc.send_var(txt, MODE_SEND_VARS | 
					     path_mode | file_mode |
					     file_check)))
		{
		  gif->destroy_pbar();
		  return -1;
		}
	    }
	  else
	    {
	      /* There is one */
	      if(tilp_error(ti_calc.send_var(txt, MODE_SEND_ONE_VAR |
					     path_mode | file_mode |
					     file_check)))
		{
		  gif->destroy_pbar();
		  return -1;
		}
	    }
	  ticalc_close_ti_file();
	}
      
      i++;
      if(l > 1)
	{
	  info_update.main_percentage=(float)i/l;
	  info_update.pbar();
	  info_update.refresh();
	}
      
      ptr=ptr->next;
    }
  gif->destroy_pbar();

  return 0;
}

/*
  Receive one or more selected variables.
  Returned value:
  - negative if error
  - zero if successful (single file)
  - positive if successful (group file name TMPFILE_GROUP)
*/
int cb_recv_var(void)
{
  int err=0;
  GList *ptr;
  FILE *txt;
  struct varinfo *v;
  char var_n[20]; /* 8+1+8 characters max */
#ifndef __MACOSX__
  char file_n[25];
#else
  char *file_n;
#endif
  int i,l;
  char str[16];
  char tmp_filename[MAXCHARS];
  int ret, skip=0;
  char buffer[MAXCHARS];
  char *dirname;
  char varname[9];
  int file_mode=MODE_NORMAL;

  if(cb_calc_is_ready())
    return -1;
  
  if(options.file_mode == EXTENDED_FORMAT)
    file_mode=MODE_KEEP_ARCH_ATTRIB;
  
  switch(options.lp.calc_type)
    {
    case CALC_TI73:
    case CALC_TI83:
    case CALC_TI83P:
    case CALC_TI86:
    case CALC_TI89:
    case CALC_TI92:
    case CALC_TI92P:
      if(ctree_win.selection==NULL) 
	return -1;

      if(g_list_length(ctree_win.selection)==1)
	{
	  /* Single file */
	  gif->create_pbar_type4(_("Receiving variable"), "");
	  v=(struct varinfo *)ctree_win.selection->data;
	  
	  if( (options.lp.calc_type != CALC_TI73) && 
	      (options.lp.calc_type != CALC_TI83) && 
	      (options.lp.calc_type != CALC_TI83P) && 
	      (options.lp.calc_type != CALC_TI86) )
	    {
	      strcpy(var_n, (v->folder)->varname);
	      strcat(var_n, "\\");
	      strcat(var_n, v->varname);
	    }
	  else
	    {
	      strncpy(var_n, v->varname, 9);
	    }
#ifdef __MACOSX__                  
          file_n = (char *)malloc((strlen(g_get_tmp_dir()) + strlen(v->translate) + 6) * sizeof(char));
            
          strcpy(file_n, g_get_tmp_dir());
          strcat(file_n, "/");
	  strcat(file_n, v->translate);
#else
	  strcpy(file_n, v->translate);
#endif
	  strcat(file_n, ".");
	  strcat(file_n, ti_calc.byte2fext(v->vartype));

	  if(file_n[0] < 0)
	  {
			dirname=gif->dlgbox_entry(_("Invalid file name, rename it"),
						_("New name: "), file_n);
		      if(dirname == NULL) 
			  {
				  gif->destroy_pbar();
			return -1;
			  }
		      strcpy(file_n, dirname);
		      g_free(dirname);
	  }
	  
	  if(options.confirm == CONFIRM_YES)
	    {
	      if( access(file_n, F_OK) == 0 )
		{
		  sprintf(buffer, _("The file %s already exists. Overwrite ?"), file_n);
		  ret=gif->user3_box(_("Warning"), buffer,
				     _(" Overwrite "), _(" Rename "),
				     _(" Skip "));
		  switch(ret)
		    {
		    case BUTTON2:
		      dirname=gif->dlgbox_entry(_("Rename the file"),
						_("New name: "), file_n);
		      if(dirname == NULL)
                        {
                          gif->destroy_pbar();
                          return -1;
                        }
		      strcpy(file_n, dirname);
		      g_free(dirname);
		    case BUTTON1:
		      skip=0;
		      break;
		    case BUTTON3:
		      skip=1;
		      break;
		    default:
		      break;
		    }
		}
	    }
	  if(skip == 0)
	    {
               err = tilp_error(ticalc_open_ti_file(file_n, "wb", &txt));
               if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
	     
	      /* This part generates the header for single files */
	      switch(options.lp.calc_type)
		{
		case CALC_TI89:
		  ti_calc.generate_single_file_header(txt, file_mode, 
						      "**TI92P*", 
						      v);
		  break;
		case CALC_TI92:
		  ti_calc.generate_single_file_header(txt, file_mode, 
						      "**TI92**", v);
		  break;
		case CALC_TI92P:
		  ti_calc.generate_single_file_header(txt, file_mode, 
						      "**TI92P*", v);
		  break;
		default:
		  break;
		}
	      err=ti_calc.recv_var(txt, MODE_RECEIVE_SINGLE_VAR | file_mode, 
				   var_n, v->vartype, v->varattr);
	      ticalc_close_ti_file();
	      if(tilp_error(err))
		{
		  gif->destroy_pbar();
		  return -1; 
		}
	    }
	  gif->destroy_pbar();
	}
      else
	{
	  /* Group file */
	  gif->create_pbar_type5(_("Receiving variables"), "");
	  strcpy(tmp_filename, g_get_tmp_dir());
	  strcat(tmp_filename, DIR_SEPARATOR);
	  strcat(tmp_filename, TMPFILE_GROUP);
          err = ticalc_open_ti_file(tmp_filename, "wb", &txt);
          if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
	  
	  switch(options.lp.calc_type)
	    {
	    case CALC_TI89:
	      generate_group_file_header(txt, file_mode, 
					 "**TI92P*", NULL,
					 options.lp.calc_type);
	      break;
	    case CALC_TI92:
	      generate_group_file_header(txt, file_mode, 
					 "**TI92**", NULL,
					 options.lp.calc_type);
	      break;
	    case CALC_TI92P:
	      generate_group_file_header(txt, file_mode, 
					 "**TI92P*", NULL,
					 options.lp.calc_type);
	      break;
	    }
	  
	  l=g_list_length(ctree_win.selection);
	  i=0;
	  ptr=ctree_win.selection;
	  while(ptr!=NULL)
	    {
	      v=(struct varinfo *)ptr->data;

	      /* If the LAST element is just a folder, skip it */
	      if( (v->is_folder == FOLDER) && (ptr->next == NULL) )
		break;
	      
	      if( (options.lp.calc_type != CALC_TI73) && 
		  (options.lp.calc_type != CALC_TI83) && 
		  (options.lp.calc_type != CALC_TI83P) && 
		  (options.lp.calc_type != CALC_TI86) )
		{
		  strcpy(var_n, (v->folder)->varname);
		  strcat(var_n, "\\");
		  strcat(var_n, v->varname);
		}
	      else
		{
		  strncpy(var_n, v->varname, 9);
		}
	      if(i == 0)
		err=ti_calc.recv_var(txt, MODE_RECEIVE_FIRST_VAR 
				     | file_mode, 
				     var_n, v->vartype, v->varattr);
	      else if( i == l-1)
		err=ti_calc.recv_var(txt, MODE_RECEIVE_LAST_VAR 
				     | file_mode, 
				     var_n, v->vartype, v->varattr);
	      else 
		err=ti_calc.recv_var(txt, MODE_RECEIVE_VARS | file_mode, 
				     var_n, v->vartype, v->varattr);
	      if(tilp_error(err)) 
		{
		  ticalc_close_ti_file();
		  gif->destroy_pbar();
		  return -1;
		}
	      i++;
	      info_update.main_percentage=(float)i/l;
	      info_update.pbar();
	      info_update.refresh();

	      ptr=ptr->next;
	    }
	  ticalc_close_ti_file();
	  gif->destroy_pbar();
          return 1;
 	}
      break;
    case CALC_TI82:
    case CALC_TI85:
      gif->create_pbar_type4(_("Receiving variable(s)"), _("Waiting..."));
      strcpy(tmp_filename, g_get_tmp_dir());
      strcat(tmp_filename, DIR_SEPARATOR);
      strcat(tmp_filename, TMPFILE_GROUP);
      do
	{
          err = ticalc_open_ti_file(tmp_filename, "wb", &txt);
          if(tilp_error(err)) { gif->destroy_pbar(); return -1; }

	
	  info_update.refresh();
	  if(info_update.cancel) break;
	  err=ti_calc.recv_var(txt, MODE_NORMAL | file_mode, varname, 0, 0);
	  ticalc_close_ti_file();
	}
      while((err == ERR_RCV_BYT_TIMEOUT) || (err == ERR_RCV_BIT_TIMEOUT));
      gif->destroy_pbar();
      if(tilp_error(err))
	{
	  return -1;
	}      
      
      if(varname[0] != '\0')
	{
	  /* Single file */
	  /* Some varnames should be translated */
	  if(options.lp.calc_type == CALC_TI82)
	    ti_calc.translate_varname(varname, str, 0);
	  else
	    strcpy(str, varname);
	  strcat(str, ".");
          err = ticalc_open_ti_file(tmp_filename, "wb", &txt);
          if(tilp_error(err)) { gif->destroy_pbar(); return -1; }
	
	  for(i=0; i<11; i++) fgetc(txt);
	  for(i=0; i<42; i++) fgetc(txt);
	  for(i=0; i<6; i++) fgetc(txt);
	  strcat(str, ti_calc.byte2fext((byte)fgetc(txt)));
	  ticalc_close_ti_file();
	  
	  if(options.confirm == CONFIRM_YES)
	    {
	      if( access(str, F_OK) == 0 )
		{
		  sprintf(buffer, _("The file %s already exists. Overwrite ?"),
			  str);
		  ret=gif->user3_box(_("Warning"), buffer,
				_(" Overwrite "), _(" Rename "),
				_(" Skip "));
		  switch(ret)
		    {
		    case BUTTON2:
		      dirname=gif->dlgbox_entry(_("Rename the file"),
					   _("New name: "), str);
		      if(dirname == NULL) 
                        {
                          gif->destroy_pbar();
                          return -1;
                        }
		      strcpy(str, dirname);
		      g_free(dirname);
		    case BUTTON1:
		      skip=0;
		      break;
		    case BUTTON3:
		      skip=1;
		      break;
		    default:
		      break;
		    }
		}
	    }	      
	  
	  if(skip == 0)
	    {
	      move_file(tmp_filename, str);  
	    }
	}
      else
	{
	  /* Group file */
          return 1;
	}
      break;
    }

  return 0;
}
