/*  tilp - linking program for TI calculators
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

/*
  This file contains a function for initializing the structure which
  contains the GUI independant functions
*/

#include "StdAfx.h"
#include "Tilp.h"

#include "tilp_core.h"

extern CTiLPApp theApp;

HWND getMainWnd()
{
	if(theApp.m_pMainWnd != NULL) 
		return theApp.m_pMainWnd->m_hWnd;
	else
		return NULL;
}

void mfc_msg_box(const char *title, char *message)
{
	MessageBox(getMainWnd(), message, title, 
		MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);
}

int mfc_user1_box(const char *title, char *message, 
						const char *b1)
{
	int ret = MessageBox(getMainWnd(), message, title, 
		MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);

	if(ret == IDOK)
		return 1;
	else
		return 0;
}

int mfc_user2_box(const char *title, char *message, 
						const char *b1, const char *b2)
{
  int ret = MessageBox(getMainWnd(), message, title, 
	  MB_YESNO | MB_ICONINFORMATION | MB_SYSTEMMODAL);

  switch(ret)
  {
  case IDYES: return 1;
  case IDNO: return 2;
  default: return 0;
  }
  return 0;
}

int mfc_user3_box(const char *title, char *message, 
		    const char *b1, const char *b2, const char *b3)
{
  int ret = MessageBox(getMainWnd(), message, title, 
	  MB_YESNOCANCEL | MB_ICONINFORMATION | MB_SYSTEMMODAL);

  switch(ret)
  {
  case IDYES: return 1;
  case IDNO: return 2;
  case IDCANCEL: return 3;
  default: return 0;
  }
  return 0;
}

/* Create a window with one progress bar */
void mfc_create_pbar_type1(const char *title)
{
	info_update.prev_main_percentage = 0.0;
	info_update.prev_percentage = 0.0;
	info_update.main_percentage = 0.0;
	info_update.percentage = 0.0;
	info_update.cancel = 0;

	AfxGetMainWnd()->SendMessage(WM_USER_CREATE_PBAR1, 
		(WPARAM)title, 0);
}

/* Create a window with one label */
void mfc_create_pbar_type2(const char *title, char *text)
{
	info_update.prev_main_percentage = 0.0;
	info_update.prev_percentage = 0.0;
	info_update.main_percentage = 0.0;
	info_update.percentage = 0.0;
	info_update.cancel = 0;

	AfxGetMainWnd()->SendMessage(WM_USER_CREATE_PBAR2, 
		(WPARAM)title, (LPARAM)text);
}

/* Create a window with two progress bars */
void mfc_create_pbar_type3(const char *title)
{
	info_update.prev_main_percentage = 0.0;
	info_update.prev_percentage = 0.0;
	info_update.main_percentage = 0.0;
	info_update.percentage = 0.0;
	info_update.cancel = 0;

	AfxGetMainWnd()->SendMessage(WM_USER_CREATE_PBAR3, 
		(WPARAM)title, (LPARAM)0);
}

/* Create a window with a one progress bar and one label */
void mfc_create_pbar_type4(const char *title, char *text)
{
	info_update.prev_main_percentage = 0.0;
	info_update.prev_percentage = 0.0;
	info_update.main_percentage = 0.0;
	info_update.percentage = 0.0;
	info_update.cancel = 0;

	AfxGetMainWnd()->SendMessage(WM_USER_CREATE_PBAR4, 
		(WPARAM)title, (LPARAM)text);
}

/* Create a window with two progress bars and one label */
void mfc_create_pbar_type5(const char *title, char *text)
{
	info_update.prev_main_percentage = 0.0;
	info_update.prev_percentage = 0.0;
	info_update.main_percentage = 0.0;
	info_update.percentage = 0.0;
	info_update.cancel = 0;

	AfxGetMainWnd()->SendMessage(WM_USER_CREATE_PBAR5, 
		(WPARAM)title, (LPARAM)text);
}

/* Destroy any pbar type */
void mfc_destroy_pbar(void)
{
	AfxGetMainWnd()->SendMessage(WM_USER_DESTROY_PBAR, 0, 0);
}