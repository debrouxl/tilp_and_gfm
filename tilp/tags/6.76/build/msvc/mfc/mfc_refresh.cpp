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

/*
  libticalcs update functions in MFC mode
*/

#include "stdafx.h"
#include "TiLP.h"
#include "PbarDlg.h"

#include "../src/tilp_core.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CProgressCtrl	*mPbar2;
extern CProgressCtrl	*mPbar1;
extern CEdit			*mLabel;
extern CEdit			*mRate;

TicableDataRate *dr;

/*
	Refresh functions
*/
static void start()
{
	info_update.prev_percentage = info_update.percentage = 0.0;
	ticable_get_datarate(&dr);
}

static void stop()
{
	info_update.prev_percentage = info_update.percentage = 0.0;
}

static void refresh()
{
	return;
/*
	// Pump and process messages: refresh GUI (Abort button)
	static int i;
	if((i++ % 256)) return;
    MSG msg;
    while ( ::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) 
    { 
        if (!AfxGetApp()->PumpMessage( ) ) 
        { 
            ::PostQuitMessage(0); 
            break; 
        } 
    } 
    // let MFC do its idle processing
    LONG lIdle = 0;
    while ( AfxGetApp()->OnIdle(lIdle++ ) );  
    // Perform some background processing here 
    // using another call to OnIdle
*/	
}

static gfloat prev_rate;

static void refresh_pbar1()
{
	info_update.percentage = (float)info_update.count / info_update.total;

	if(mPbar2 != NULL)
	{
		if( (info_update.percentage - info_update.prev_percentage) < 0.05)
		{
			if( (info_update.percentage - info_update.prev_percentage) < 0)
			{
				info_update.prev_percentage = info_update.percentage;
			}
			else
				return;
		}
		else
			info_update.prev_percentage = info_update.percentage;

		mPbar2->SetPos((short)(100 * info_update.percentage));
		//mWnd->SendMessage(WM_USER_REFRESH_PBAR1, 0, 0);
    }
}

static void refresh_pbar2()
{
	if(mPbar1 != NULL)
	{
		if( (info_update.main_percentage - info_update.prev_main_percentage) < 0.05)
			return;
		else
			info_update.prev_main_percentage = info_update.main_percentage;
      
		mPbar1->SetPos((short)(100 * info_update.main_percentage));
		//mWnd->SendMessage(WM_USER_REFRESH_PBAR2, 0, 0);
    }
}

static void pbar()
{
	static gchar buffer[32];
	static gfloat rate;
	static gint i=0;

	refresh_pbar1();
	refresh_pbar2();	

	if(mRate != NULL)
	{
		i++;
		if(!(i % 512))
		{
			toCURRENT(dr->start);
			rate = dr->count / toCURRENT(dr->start);

			g_snprintf(buffer, 32, "%1.1f KB/s", rate / 1000);
			prev_rate = rate;
			mRate->SetWindowText(buffer);
		}
	}
}

static void label()
{
	if(mLabel != NULL)
	{
		mLabel->SetWindowText(info_update.label_text);
		//DISPLAY("info_update.label_text=%s\n", info_update.label_text);
		//mWnd->SendMessage(WM_USER_REFRESH_LABEL, 0, 0);
	}
}


void mfc_init_refresh_functions(void)
{
  ticalc_set_update(&info_update,
		    start,
		    stop,
		    refresh,
		    pbar,
		    label
		    );
  
  return;
}
