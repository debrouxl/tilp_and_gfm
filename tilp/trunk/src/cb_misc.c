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

#ifdef __MACOSX__
#include <glib/glib.h>
#include <libticables/cabl_int.h>
#include <libticalcs/calc_int.h>
#elif defined(__WIN32__)
#include <windows.h>
#include <process.h>
#endif

#include "defs.h"
#include "gui_indep.h"
#include "intl.h"
#include "error.h"
#ifndef __MACOSX__
#include "rcfile.h"
#endif
#include "struct.h"
#include "cb_calc.h"

#ifndef __MACOSX__ /* we use a general preferences system from Mac OS X */
/*
  Save the configuration file
*/
int cb_save_config_file(void)
{
  write_rc_file();
  gif->msg_box(_("Information"), 
	  _("Configuration file saved."));

  return 0;
}

/*
  Load the configuration file
*/
int cb_load_config_file(void)
{
  read_rc_file();
  gif->msg_box(_("Information"), 
	  _("Configuration file loaded."));

  return 0;
}
#endif /* !__MACOSX__ */

/*
  Fill the option structure with default values
*/
int cb_default_config(void)
{
#if defined(__UNIX__) || defined(__WIN32__)
  gchar *locale;
#endif

  options.xsize = 125;
  options.ysize = 90;
  options.clist_sort = SORT_BY_NAME;
  options.clist_sort_order = SORT_DOWN;
  options.ctree_sort = SORT_BY_NAME;
  options.ctree_sort_order = SORT_DOWN;
  options.confirm = CONFIRM_YES;
  options.path_mode = FULL_PATH;
  options.show = HIDE;
  options.file_mode = EXTENDED_FORMAT;
  options.plugins_loading = PLUGINS_AUTO;
  options.screen_format = PCX;
  options.screen_clipping = CLIPPED_SCREEN;

#if defined(__LINUX__)
  options.unzip_location = g_strdup("unzip");
  options.unzip_options = g_strdup("");
  options.tar_location = g_strdup("tar");
  options.tar_options = g_strdup("");
#elif defined(__WIN32__)
  options.unzip_location = g_strdup("\"C:\\Program Files\\WinZip\\wzunzip.exe\"");
  options.unzip_options = g_strdup("");
  options.tar_location = g_strdup("\"C:\\Program Files\\WinZip\\wzunzip.exe\"");
  options.tar_options = g_strdup("");
#else
options.unzip_location = NULL;
options.unzip_options = NULL;
options.tar_location = NULL;
options.tar_options = NULL;
#endif
  
  /* Fill lp struct with default values */
  ticable_get_default_param(&(options.lp));
  
#if defined(__LINUX__)
  strcpy(options.left_font_name, 
	 "");
  strcpy(options.right_font_name, 
	 "-adobe-courier-medium-r-*-*-*-125-*-*-*-*-*-*");
#elif defined(__WIN32__)
  strcpy(options.left_font_name,
	 "");
  strcpy(options.right_font_name, 
	 "-adobe-courier-medium-r-normal--12-120-75-75-p-70-iso8859-1");
#endif
  options.transfer_mode = SILENT_MODE;
  options.file_checking = FILE_CHECKING_MID;
#ifdef __WIN32__
  options.console_mode = 0;
#else
  options.console_mode = 1;
#endif
  options.auto_detect = 1;

  /* Query the locale */
#if defined(__WIN32__)
  locale = g_win32_getlocale();
  fprintf(stdout, "Current locale: <%s>\n", locale);
  g_free(locale);
#elif defined(__LINUX__)
  locale = setlocale(LC_ALL, NULL);
  fprintf(stdout, "Current locale: <%s>\n", locale);
  strcpy(options.locale, locale);
#else
  fprintf(stdout, "No locale.\n");
#endif

  options.show_gui = TRUE;
  options.single_or_group = RECV_AS_GROUP;
  options.use_checksum = USE_CHECKSUM;

  return 0;
}

/* Unused */
int cb_probe_port(void)
{
  gif->msg_box(_("Information"),
	       _("This function is not yet available."));

  return 0;
}

/* Unused */
int cb_probe_cable(void)
{
  gchar *os;
  PortInfo pi;
  
  gif->msg_box(_("Information"),
               _("Implemented but not activated yet (mouse hang-up)."));
  return 0;

  ticable_detect_os(&os);
  ticable_detect_port(&pi);
  ticable_detect_cable(&pi);

  return 0;
}

/*
  Try to detect the calculator type and display the result
*/
int cb_probe_calc(void)
{
  int type;
  char text[MAXCHARS];
  
  strcpy(text, _("Calculator detected: "));
  
  if(tilp_error(detect_calc(&type)))
    {
      strcpy(text, _("No calculator found. Check your port and/or cable"));
    }
  else
    {
      printf(_("Type: %i\n"), type);
      switch(type)
	{
	case CALC_TI92P:
	  strcat(text, "TI92+");
	  break;
	case CALC_TI92:
	  strcat(text, "TI92");
	  break;
	case CALC_TI89:
	  strcat(text, "TI89");
	  break;
	case CALC_TI86:
	  strcat(text, "TI86");
	  break;
	case CALC_TI85:
	  strcat(text, "TI85");
	  break;
	case CALC_TI83P:
	  strcat(text, "TI83+");
	  break;
	case CALC_TI83:
	  strcat(text, "TI83");
	  break;
	case CALC_TI82:
	  strcat(text, "TI82");
	  break;
	case CALC_TI73:
	  strcat(text, "TI73");
	  break;
	default:
	  strcpy(text, _("No calculator found. Check your port and/or cable"));
	  break;
	}
    }
  gif->msg_box(_("Probe results"), text);
  
  return 0;
}

#ifndef __MACOSX__
/*
  Register some file types for Windows.
  Requires an external file (tilp.reg).
*/
int cb_registry_register(void)
{
#if defined(__LINUX__)
  gif->msg_box(_("Information"), 
	  _("Available on Win32 platforms only."));
#elif defined(__WIN32__)
  int ret;
  ret = _spawnlp(_P_WAIT, "regedit.exe", "regedit.exe", "tilp.reg", NULL );
  if(ret == -1)
    DISPLAY_ERROR("Spawn error.\n");
#endif
  return 0;
}

/*
  Unregister previously registered files
*/
int cb_registry_unregister(void)
{
#if defined(__LINUX__)
  gif->msg_box(_("Information"), 
	  _("Available on Win32 platforms only."));
#elif defined(__WIN32__)
  gif->msg_box(_("Information"), 
	  _("Sorry, but this is impossible for the moment."));
#endif
  return 0;
}
#endif /* !__MACOSX__ */


#ifndef __MACOSX__
/*
  Called by TiLP at startup for initializing platform dependant paths.
*/
int initialize_paths(void)
{
  char *home_dir;
#ifdef __WIN32__
  HMODULE hModule;
  DWORD dWord;
  char *dirname;
  char *sBuffer;
#endif
  gchar *curdir = NULL;
  
  /* 
     Init the path for the Windows version by getting the executable
     location.
  */
#if defined(__WIN32__)
  /* Retrieve the directory of the executable */
  hModule = GetModuleHandle("tilp.exe");
  sBuffer = (char *)malloc(4096*sizeof(char));
  dWord = GetModuleFileName(hModule, sBuffer, 4096);
  dirname = g_dirname(sBuffer);
  DISPLAY_ERROR("Current path: <%s>\n", dirname);
  inst_paths.base_dir = g_strdup(dirname);
  g_free(dirname);
  free(sBuffer);
#else
  inst_paths.base_dir = g_strdup("");
#endif
  //DISPLAY_ERROR("inst_path.base_dir = <%s>\n", inst_paths.base_dir);

  /*
    Initialize share path
  */
#if defined(__UNIX__)
  inst_paths.share_dir = g_strconcat(inst_paths.base_dir, SHARE_DIR,
				   G_DIR_SEPARATOR_S, NULL);
#endif

  /*
    Initialize pixmaps path
  */
  
#ifdef __UNIX__
  inst_paths.pixmap_dir = g_strconcat(inst_paths.base_dir, SHARE_DIR,
				    "/pixmaps/", NULL);
#elif defined(__WIN32__)
  inst_paths.pixmap_dir = g_strconcat(inst_paths.base_dir, SHARE_DIR,
				    "\\pixmaps\\", NULL);
#else
  inst_paths.pixmap_dir = NULL;
#endif
  //DISPLAY("inst_paths.pixmap_dir = <%s>\n", inst_paths.pixmap_dir);

  /* 
     Init internationalization for Linux or Windows
     Some things about i18 paths:
     bintextdomain(PACKAGE, "/usr/share/locale"); ->
     '/usr/share/locale/fr/LC_MESSAGES/tilp.mo'
  */
#if defined(HAVE_LIBINTL_H)
#ifdef __LINUX__
  inst_paths.locale_dir = g_strconcat(inst_paths.base_dir, PACKAGE_LOCALE_DIR,
				    G_DIR_SEPARATOR_S, NULL);
#elif defined(__WIN32__)
  inst_paths.locale_dir = g_strconcat(inst_paths.base_dir, PACKAGE_LOCALE_DIR,
				    "\\locale\\", NULL);
#endif
  //DISPLAY_ERROR("inst_paths.locale_dir = <%s>\n", inst_paths.locale_dir);
#endif
  
  /*
    Initialize help path
  */
#ifdef __UNIX__
  inst_paths.help_dir = g_strconcat(inst_paths.base_dir, SHARE_DIR,
				  "/help/", NULL);
#elif defined(__WIN32__)
  inst_paths.help_dir = g_strconcat(inst_paths.base_dir, SHARE_DIR,
				  "\\help\\", NULL);
#else
  inst_paths.help_dir = NULL;
#endif
  //DISPLAY_ERROR("inst_paths.help_dir = <%s>\n", inst_paths.help_dir);
  
  /*
    Initialize manpage path
  */
#ifdef __UNIX__
  inst_paths.manpage_dir = g_strconcat(inst_paths.base_dir, SHARE_DIR,
				       "/", NULL);
#elif defined(__WIN32__)
  inst_paths.manpage_dir = g_strconcat(inst_paths.base_dir, SHARE_DIR,
				       "\\", NULL);
#else
  inst_paths.manpage_dir = NULL;
#endif
  //DISPLAY_ERROR("inst_paths.manpage_dir = <%s>\n", inst_paths.manpage_dir);

  /*
    Save startup path for command line args
  */
  
  curdir = g_get_current_dir();
  inst_paths.startup_dir = g_strconcat(curdir, G_DIR_SEPARATOR_S, NULL);
  
  // on LINUX systems, HOME directory by default for security reasons
#ifdef __LINUX__ 
  if(get_home_path(&home_dir))
    {
      chdir(home_dir);
      g_free(home_dir);
    }
  else
    {
      DISPLAY_ERROR("Can not get HOME directory.\n");
      exit(-1);
    }
#elif defined(__WIN32__)	// on WIN32 systems, the last used folder
    home_dir = read_cwd_file();
	if(home_dir != NULL)
    {
      chdir(home_dir);
      g_free(home_dir);
    }
#endif

  return 0;
}

/*
  Change the current drive (Win32 only)
*/
int cb_change_drive(char drive_letter)
{
#ifdef __WIN32__
  char buffer[MAXCHARS];
  gchar *s;
  
  snprintf(clist_win.cur_dir, 8, "%c:\\", (char)drive_letter);
  s = g_filename_from_utf8(clist_win.cur_dir, NULL);
  if(chdir(s) == -1)	//chdir(clist_win.cur_dir);
	  gif->msg_box(_("Error"), _("Unable to change directory."));
  g_free(s);
#else
  gif->msg_box(_("Information"),
	  _("This function is not available in the Win version."));
#endif

  return 0;
}
#endif /* !__MACOSX__ */

/* 
   Return the calc type corresponding to the file
   - filename [in]: a filename
   - int [out]: the calculator type
*/
#ifndef CALC_NONE
# define CALC_NONE 0
#endif
/*
static int which_calc_type_from_file(char *filename)
{
  gchar *ext;

  ext = strrchr(filename, '.');
  
  if(strstr(ext, "73") != NULL)      return CALC_TI73;
  else if(strstr(ext, "82") != NULL) return CALC_TI82;
  else if(strstr(ext, "83") != NULL) return CALC_TI83;
  else if(strstr(ext, "8x") != NULL) return CALC_TI83P;
  else if(strstr(ext, "85") != NULL) return CALC_TI85;
  else if(strstr(ext, "86") != NULL) return CALC_TI86;
  else if(strstr(ext, "89") != NULL) return CALC_TI89;
  else if(strstr(ext, "92") != NULL) return CALC_TI92;
  else if(strstr(ext, "9x") != NULL) return CALC_TI92P;
  else return CALC_NONE;
  
  return CALC_NONE;
}
*/

/*
  This function send files passed on the command line and place them in
  the clist_win.selection linked list.
  Manage file type, calculator detection and some other things.
*/
int cb_send_cmdline(void)
{
  gchar *e;
  struct file_info *fi;
  int last = options.confirm;

  if(clist_win.selection == NULL)
    return -1;

  /* Determine extension */
  fi = (struct file_info *)(g_list_first(clist_win.selection))->data;
  e = strrchr(fi->filename, '.');
  if(e == NULL)
    {
      DISPLAY_ERROR(_("Invalid filename. There is no extension.\n"));
      exit(-1);
    }
  e++; // skip the dot !
  
  /* Determine calculator type and override current settings */
  //options.lp.calc_type = which_calc_type_from_file(fi->filename);
  //ticalc_set_calc(options.lp.calc_type, &ti_calc, &link_cable);

  /* Send file(s) */
  if(g_list_length(clist_win.selection) == 1)
    {    
      // One file
      /* Determine file type */
      if(!g_strcasecmp(e, ticalc_backup_file_ext(options.lp.calc_type)))
	{ 
	  // backup file
	  cb_send_backup(fi->filename);
	}
      else if(!g_strcasecmp(e, 
			    ticalc_flash_app_file_ext(options.lp.calc_type)))
	{
	  // FLASH file (apps)
	  cb_send_flash_app(fi->filename);
	}
      else if(!g_strcasecmp(e, 
			    ticalc_flash_os_file_ext(options.lp.calc_type)))
	{
	  // FLASH file (ams)
	  cb_send_flash_os(fi->filename);
	}
      else
	{
	  // single/group file
	  options.confirm = FALSE; // remove dirlist
	  cb_send_var();
	  options.confirm = last;
	  exit(0);
	}
    }
  else
    {    
      // More than one file
      if(clist_win.selection != NULL)
	{
	  options.confirm = FALSE;
	  cb_send_var();
	  options.confirm = last;
	  exit(0);
	}
    }
  
  exit(0);
  return 0;
}

int cb_ungroup_files(void)
{
#ifdef HAVE_LIBTIFFEP
  TiffepFileInfo *fi_src = NULL;
  TiffepFileInfo *fi_dst = NULL;
  TiffepVarInfo  *vi_src = NULL;
  TiffepVarInfo  *vi_dst = NULL;
  
  if(clist_win.selection == NULL) 
    return 0;

  sel = clist_win.selection;
  while(sel != NULL)
    {
      f = (struct file_info *)sel->data;
      if(!tiffep_is_a_group_file(f->filename))
	{
	  gif->msg_box(_("Error"),
		       _("Ungroup: this is not a group file."));
	  sel = g_list_next(sel);
	  continue;
	}
      /**/
      if(tiffep_load_file_content(f->filename, &fi_src) != 0)
	gif->msg_box(_("Error"), _("Unable to load the file."));
      
      vl = FILEINFO_VARLIST(fi_src);
      while(vl != NULL)
	{
	  vi_src = (TiffepVarInfo *)(vl->data);
	  fi_dst = tiffep_alloc_fi_struct();	  
	  FILEINFO_FILETYPE(fi_dst) = FILE_SINGLE;
	  FILEINFO_CALCTYPE(fi_dst) = FILEINFO_CALCTYPE(fi_src);
	  FILEINFO_NUMVARS(fi_dst)  = 1; // single file
	  vi_dst = tiffep_dup_vi_struct(vi_src);
	  tiffep_print_vi_struct(vi_dst);
	  FILEINFO_VARLIST(fi_dst) = g_list_append(FILEINFO_VARLIST(fi_dst), 
						   vi_dst);
	  g_free(FILEINFO_COMMENT(fi_dst));
	  FILEINFO_COMMENT(fi_dst) = g_strdup("File ungrouped by TiLP");
	  filename = g_strdup(VARINFO_REALNAME(vi_src));	
          tiffep_save_file_content(filename, fi_dst);
	  tiffep_free_fi_struct(&fi_dst);
	  g_free(filename);

	  vl = g_list_next(vl);
	}
      tiffep_free_fi_struct(&fi_src); // vi is implicitely freed
      /**/
      sel = g_list_next(sel);
    }

  return 0;
#else
  gif->msg_box(_("Information"),
	  _("This function is not available: have you installed the TiFFEP library ?"));
  return 0;
#endif
}

int cb_group_files(void)
{
#ifdef HAVE_LIBTIFFEP
  TiffepFileInfo *fi_src = NULL;
  TiffepFileInfo *fi_dst = NULL;
  TiffepVarInfo  *vi_src = NULL;
  TiffepVarInfo  *vi_dst = NULL;
  
  if((sel = clist_win.selection) == NULL) 
    return 0;
  
  // Create a group file
  fi_dst = tiffep_alloc_fi_struct();	  
  FILEINFO_FILETYPE(fi_dst) = FILE_GROUP;
  switch(options.lp.calc_type)
    {
    case CALC_TI89:
      FILEINFO_CALCTYPE(fi_dst) = TYPE_TI89;
      break;
    case CALC_TI92:
      FILEINFO_CALCTYPE(fi_dst) = TYPE_TI92;
      break;
    case CALC_TI92P:
      FILEINFO_CALCTYPE(fi_dst) = TYPE_TI92P;
      break;
    default:
      FILEINFO_CALCTYPE(fi_dst) = TYPE_NONE;
      break;
    }
  FILEINFO_COMMENT(fi_dst)  = g_strdup("Group of files made by TiLP");

  // Parse any single file
  while(sel != NULL)
    {
      f = (struct file_info *)sel->data;
      printf("filename: <%s>\n", f->filename);
      if(tiffep_is_a_backup_file(f->filename) ||
	 tiffep_is_a_flash_file(f->filename))
	{
	  gif->msg_box(_("Error"),
		  _("Group: this is not a single/group file."));
	  sel = g_list_next(sel);
	  continue;
	}

      if(tiffep_load_file_content(f->filename, &fi_src) != 0)
	gif->msg_box(_("Error"), _("Unable to load the file."));
      vi_src = VARLIST_DATA(FILEINFO_VARLIST(fi_src));
      vi_dst = tiffep_dup_vi_struct(vi_src);
      tiffep_print_vi_struct(vi_dst);
      tiffep_add_vi_struct(fi_dst, vi_dst);
      tiffep_free_fi_struct(&fi_src);

      sel = g_list_next(sel);
    }

  filename = g_strdup("test");
  tiffep_update_vi_offset(fi_dst);
  tiffep_save_file_content(filename, fi_dst);
  tiffep_free_fi_struct(&fi_dst);
  g_free(filename);

  return 0;
#else
  gif->msg_box(_("Information"),
	  _("This function is not available: have you installed the TiFFEP library ?"));
  return 0;
#endif
}
