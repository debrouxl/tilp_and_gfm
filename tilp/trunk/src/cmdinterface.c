/*  gtktiemu - a TI89/92/92+ emulator
 *  (c) Copyright 2000-2001, Romain Lievin and Thomas Corvazier
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

#include "intl.h"

#include <stdlib.h>
#include <stdio.h>
#ifndef __WIN32__
#include <dirent.h>
#endif
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include "includes.h"

char fname[64];
int linkType = 0;
int progBar = 0;
int totalSize = 0;
int cmdState = 0;
//tifile dirBuffer[64];
char currDir[128] = "";

int getOut = 0;

int do_command(unsigned char *cmd, unsigned char *arg1);
void prompt_commands(void);
void print_dir(void);

void display_dirlist(struct varinfo *varlist);

int do_command(unsigned char *cmd, unsigned char *arg1) 
{    
  if(cmdState) 
    {
      if(!strcmp(cmd, "quit"))
	{
	  cmdState = 0;
	  getOut = 1;
	}

      if(!strcmp(cmd, "exit"))
	{
	  cmdState = 0;
	  getOut = 1;
	}

      if(!(strcmp(cmd, "help"))) 
	{
	  DISPLAY(_("Currently recognized commands: ls, cd, help, quit, exit, ready, screen [filename], dirlist [filename], backup [filename], restore [filename], send [filename], receive [filename] and dump [filename]\n"));
	}
      
      if(!(strcmp(cmd, "ls"))) 
	{
	  char ext[4];
	  struct stat aStat;
	  struct dirent *dent;
	  DIR *dir = opendir(currDir);
	  
	  DISPLAY("%s\n", currDir);
	  while((dent = readdir(dir))) 
	    {
	      strcpy(ext, &dent->d_name[strlen(dent->d_name)-3]); 
	      ext[2] = toupper(ext[2]);
	      stat(dent->d_name, &aStat);
	      if(S_ISDIR(aStat.st_mode))
		DISPLAY("  [%s]\n", dent->d_name);
	      else
		if(!strcmp(ext, "92P") || !strcmp(ext, "92B"))
		  DISPLAY("  %-32s %d\n", dent->d_name, (int)(aStat.st_size));
	    }
	  closedir(dir);
	}

      if(!(strcmp(cmd, "cd"))) 
	{
	  if(arg1)  
	    {
	      if(chdir(arg1))
		  DISPLAY(_("\nIllegal directory!\n"));
	      else
		DISPLAY(_("\nCurrent directory changed to:\n%s\n"), 
			getcwd(currDir, sizeof(currDir)));
	    }
	  else
	      DISPLAY(_("\nCurrent directory is:\n%s\n"), currDir);
	}

      if(!(strcmp(cmd, "ready"))) 
	{
	  cb_calc_is_ready();
	  //DISPLAY("%s\n", cb_calc_is_ready() ? "ok" : "nok");
	}
      
      if(!(strcmp(cmd, "screen"))) 
	{
	  cb_screen_capture();
	  if(arg1)
	    {
	      cb_screen_save(arg1);
	    }
	}
	 
      if(!strcmp(cmd, "dirlist"))
	{
	  struct varinfo varlist;
	  int n;
	  
	  gif->create_pbar_type2(_("Directory list"), 
				 _("Reading variables"));
	  if(tilp_error(ti_calc.directorylist(&varlist, &n)))
	    {
	      varlist.next=NULL;
	      n=0;
	    }
	  display_dirlist(varlist.next);
	}
  
      if(!strcmp(cmd, "backup"))
	{
	  cb_recv_backup();
	  if(arg1)
	    {
	    }
	}

      if(!strcmp(cmd, "restore"))
	{
	  if(arg1)
	    cb_send_backup(arg1);
	}
      
      if(!strcmp(cmd, "send"))
	{
	  /*
	  if(arg1)
	    cb_send_var(arg1);
	  */	
	}
      
      if(!strcmp(cmd, "receive"))
	{
	  //cb_recv_var();
	  if(arg1)
	    { 
	    }
	}
      
      if(!strcmp(cmd, "dump"))
	{
	  cb_rom_dump();
	  if(arg1)
	    {
	    }
	}
    }
  
  return 0;  
}

void prompt_commands(void) 
{
  char *cmd, *arg1, *arg2;
  char line[80];
  
  getOut = 0;
  while(!getOut) 
    {   
      DISPLAY(_("\ncmd> "));
      fgets(line, 80, stdin);
      line[strlen(line)-1]='\0'; //strap LF
      cmd = strtok(line, " ");
      arg1 = strtok(NULL, " ");
      arg2 = strtok(NULL, " ");
      //fprintf(stdout, "<<%s %s %s>>\n", cmd, arg1, arg2);
      if(cmd) do_command(cmd, arg1);
    }
}

void enter_command(void) 
{
  if(!strlen(currDir))
    getcwd(currDir, sizeof(currDir));
  
  DISPLAY(_("Commandstate entered. Type \"quit\" or \"exit\" to quit.\n"));
  cmdState = 1;
  prompt_commands();
}








