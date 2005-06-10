/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
 *
 *  This program is free software you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __TILP_CORE__
#define __TILP_CORE__

/*
  This header contains the exported functions of the TiLP core.
  They can be used for developing a TiLP with a different GUI.
  You should use these functions with the name beginnig by tilp_...
  You do not have to use any other function, please !

  Format: [tilp]_[group]_[name]
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "tilp_defs.h"
#include "tilp_struct.h"
#include "tilp_paths.h"
#include "tilp_indep.h"
#include "tilp_version.h"
#include "tilp_printl.h"
#include "intl.h"

  /******************************/
  /* Use new dirlist management */
  /******************************/

  //#define DIRLIST_FORM1 // lib: 1, tilp: 1
  //#define DIRLIST_TRANS // lib: 1, tilp: 2
  #define DIRLIST_FORM2 // lib: 2, tilp: 2
  
  /**********************/
  /* Exported variables */
  /**********************/

  extern int working_mode;
  extern TilpScreen ti_screen;


  /**********************/
  /* Exported functions */
  /**********************/

  // tilp_indep.c
  void tilp_gui_set_default_fncts(void);
  void tilp_gui_set_fncts(TilpGuiFncts * gf);

  // tilp_refresh.c
  void tilp_cmdline_set_refresh(void);

  // tilp_main.c
  int tilp_main(int argc, const char *argv[], char **arge);

#ifndef __MACOSX__
  // tilp_paths.c
  int tilp_paths_init(void);
  const char *tilp_paths_build_glade(const char *name);
#endif /* !__MACOSX__ */
  
  // tilp_error.c
  int tilp_error(int err_num);

  // tilp_calc.c, tilp_screen.c
  typedef void (*READY_CALLBACK) (int status);
  READY_CALLBACK tilp_calc_register(READY_CALLBACK new_cb);
  int tilp_calc_isready(void);
  int tilp_calc_dirlist(void);
  int tilp_calc_send_backup(char *filename);
  int tilp_calc_recv_backup(void);
  int tilp_calc_send_var(int to_flash);
  int tilp_calc_recv_var(void);
  int tilp_calc_idlist(void);
  int tilp_calc_rom_dump(void);
  int tilp_calc_send_flash_app(char *filename);
  int tilp_calc_send_flash_os(char *filename);
  int tilp_calc_recv_app(void);
  int tilp_calc_ams2rom(char *filename);

  int tilp_screen_capture(void);
  uint8_t *tilp_screen_convert(void);
  uint8_t *tilp_screen_blurry(void);
  gboolean tilp_screen_write_eps(const gchar *filename, GError **error);
  gboolean tilp_screen_write_pdf(const gchar *filename, GError **error);

  // tilp_misc.c
#ifndef __MACOSX__
  int tilp_config_save(void);
  int tilp_config_load(void);
  int tilp_config_default(void);

  int tilp_drive_change(char drive_letter);

  int tilp_registry_register(void);
  int tilp_registry_unregister(void);
#endif /* !__MACOSX__ */

  int tilp_cmdline_send(void);

  int tilp_tifiles_group(void);
  int tilp_tifiles_ungroup(void);

#ifndef __MACOSX__
  // tilp_rcfile.c
  void tilp_rcfile_read(void);
  void tilp_rcfile_write(void);
  int tilp_rcfile_exist(void);

  int tilp_rcfile_get_version(char *version);
  int tilp_rcfile_delete(void);
#endif /* !__MACOSX__ */

  // tilp_slct.c
  void tilp_clist_selection_destroy(void);
  int tilp_clist_selection_ready(void);

  void tilp_ctree_selection_destroy(void);
  int tilp_ctree_selection_ready(void);
  int tilp_ctree_selection2_ready(void);

  void tilp_clist_file_selection_destroy(void);
  void tilp_add_file_to_file_selection(const char *filename);
#ifndef __MACOSX__
  void tilp_delete_selected_files();
  void tilp_rename_selected_files();
#endif /* !__MACOSX__ */
  
  // tilp_files.c
  void tilp_process_buffer(gchar * buf);
  void tilp_process_unix2dos(gchar * buf);
  char *tilp_file_underscorize(char *s);

  int tilp_file_copy(const char *src, const char *dst);
  int tilp_file_move(const char *src, const char *dst);
  int tilp_file_delete(const char *f);

  int tilp_file_mkdir(const char *pathname);

  int tilp_file_move_with_check(const char *src, const char *dst);
  int tilp_file_check(const char *src, char **dst);

  int tilp_chdir(const char *path);

#ifndef __MACOSX__
  const char *tilp_file_get_attributes(TilpFileInfo * fi);
  void tilp_file_get_user_name(TilpFileInfo * fi, char **name);
  void tilp_file_get_group_name(TilpFileInfo * fi, char **name);
  const char *tilp_file_get_date(TilpFileInfo * fi);
  const char *tilp_file_get_size(TilpFileInfo * fi);
  const char *tilp_file_get_type(TilpFileInfo * fi);

  int tilp_dirlist_local(void);

  void tilp_sort_files_by_name(void);
  void tilp_sort_files_by_date(void);
  void tilp_sort_files_by_size(void);
  void tilp_sort_files_by_user(void);
  void tilp_sort_files_by_group(void);
  void tilp_sort_files_by_attrib(void);
#endif /* !__MACOSX__ */

  // tilp_vars.c
  int tilp_dirlist_remote(void);
  void tilp_dirlist_display(void);

  void tilp_sort_vars_by_name(void);
  void tilp_sort_vars_by_info(void);
  void tilp_sort_vars_by_type(void);
  void tilp_sort_vars_by_size(void);

  void tilp_var_get_size(TiVarEntry * vi, char **buf);

#ifndef __MACOSX__
  // tilp_plugins.c
  int tilp_plugins_scan(void);
  int tilp_plugins_search_start(void);
  gchar *tilp_plugins_search_query(const gchar * extension);

  int tilp_plugins_open(const gchar * plugin_name);
  int tilp_plugins_close(void);

  int tilp_plugins_read(const char *filename);
  int tilp_plugins_write(const char *filename);
  int tilp_plugins_run(void);
#endif /* !__MACOSX__ */

  // tilp_printl.c
  int ticables_printl(int level, const char *format, ...);
  int tifiles_printl(int level, const char *format, ...);
  int ticalcs_printl(int level, const char *format, ...);
  int tilp_printl(int level, const char *format, ...);

  // GTK+ only (export callbacks for Glade linking at runtime)
#ifdef __WIN32__
# define GLADE_CB __declspec(dllexport)
#else
# define GLADE_CB
#endif

#ifdef __cplusplus
}
#endif
#endif
