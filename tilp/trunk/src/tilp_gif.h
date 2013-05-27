/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Tilp Is a Linking Program
 *  Copyright (C) 1999-2006  Romain Lievin
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*

*/

#ifndef __TILP_GIF_H__
#define __TILP_GIF_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*PBAR_FNCT)	(const char*);

/*
  This structure holds the GUI independant functions
*/
typedef struct 
{
    int (*msg_box) (const char *title, const char *message, gint action);

    // Display a modal OK dialog box with a title and a message
    int (*msg_box1) (const char *title, const char *message);

    // Display a modal OK/Cancel dialog box
    int (*msg_box2) (const char *title, const char *message);

    // Display a modal dialog box with 3 buttons
    int (*msg_box3) (const char *title, const char *message,
                     const char *btn1, const char *btn2, const char *btn3);

    // Display a modal Next/Cancel dialog box
    int (*msg_box4) (const char *title, const char *message);

    // Display a modal entry dialog box with a title, a message and
    // a predefined content.
    // It returns NULL if the dbox has been cancelled else it 
    // returns an allocated string which contains the typed text.
    // Think to free the returned buffer when no longer needed...
    char *(*msg_entry) (const char *title,
                        const char *message, const char *content);

    // Display a dialog box with 1 progress bar and a 'Cancel' 
    // button. If the cancel button is pressed, you should have 
    // this in your callback: 'info_update.cancel = 1;'
    // 1 pbar
    void (*create_pbar_type1) (const char *title);
    // 1 label
    void (*create_pbar_type2) (const char *title);
    // 2 pbars
    void (*create_pbar_type3) (const char *title);
    // 1 pbar & 1 label
    void (*create_pbar_type4) (const char *title);
    // 2 pbars & 1 label
    void (*create_pbar_type5) (const char *title);

    void (*create_pbar)       (int type, const char *title);

    // Destroy one of the previous pbar dboxes.
    void (*destroy_pbar) (void);

} TilpGuiFncts;

#define create_pbar_(t,s)	create_pbar(tilp_pbar_type(t),(s))

extern const TilpGuiFncts *gif;

void tilp_gui_set_fncts(const TilpGuiFncts*);
void tilp_gif_set_default(void);
void tilp_update_set_default(void);

#ifdef __cplusplus
}
#endif
#endif
