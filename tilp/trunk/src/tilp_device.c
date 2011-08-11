/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_calcs.c 2270 2006-05-05 13:03:11Z roms $ */

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
	This file contains utility functions for hand-helds probing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tilibs.h"

#include "tilp_core.h"
#include "gtk_update.h"

#ifdef __WIN32__
# define strcasecmp _stricmp
#endif

#ifdef __WIN32__
#include <windows.h>
#define PAUSE(x) Sleep(x)
#else
#define PAUSE(x) usleep(1000*(x))
#endif

//----------------------------------------------------------------------------

/* 
	Note: TiLP internally uses all of the possible values of the 
	CalcModel enumeration but restricts it for the device box and the
	command line.
	The functions below allows to translate:
	- TI84+ USB <=> TI84+ w/ DirectLink
	- Titanium USB <=> Titanium w/ DirectLink
 */

// CABLE_USB & CALC_TIXX_USB -> CALC_TIXX
CalcModel tilp_remap_from_usb(CableModel cable, CalcModel calc)
{
        if(cable == CABLE_USB && calc == CALC_TI84P_USB)
		return CALC_TI84P;
	else if(cable == CABLE_USB && calc == CALC_TI89T_USB)
		return  CALC_TI89T;
	else if(cable == CABLE_DEV && calc == CALC_TI84P_USB)
	  return CALC_TI84P;
        else if(cable == CABLE_DEV && calc == CALC_TI89T_USB)
	  return  CALC_TI89T;
	else
		return calc;
}

// CABLE_USB & CALC_TIXX -> CALC_TIXX_USB
CalcModel tilp_remap_to_usb(CableModel cable, CalcModel calc)
{
	if((cable == CABLE_USB || cable == CABLE_DEV) && calc == CALC_TI84P)
		return CALC_TI84P_USB;
	else if((cable == CABLE_USB || cable ==CABLE_DEV) && calc== CALC_TI89T)
		return  CALC_TI89T_USB;
	else
		return calc;
}

//----------------------------------------------------------------------------

static int found_port(int *ports)
{
	int i;

	for(i = PORT_1; i <= PORT_4; i++)
		if(ports[i])
			return i;

	return 0;
}

/* Scan for USB devices only (fast, returns the first device found) */
int tilp_device_probe_usb(CableModel* cable_model, CablePort *port, CalcModel* calc_model)
{
	int err;
	int ret = -1;
	int **cables;
	CableHandle* handle;

	// search for all USB cables (faster)
	tilp_info("Searching for link cables...");
	err = ticables_probing_do(&cables, 5, PROBE_USB | PROBE_FIRST);
	if(err)
	{
		ticables_probing_finish(&cables);
		return -1;
	}

	// search for DirectLink devices
	*port = found_port(cables[CABLE_USB]);
	if(*port)
	{
		tilp_info("Searching for hand-helds on DirectLink...");
		handle = ticables_handle_new(CABLE_USB, *port);
		ticables_options_set_timeout(handle, 10);

		err = ticables_cable_open(handle);
		if(err)
		{
			ticables_handle_del(handle);
			goto step2;
		}

		err = ticalcs_probe_usb_calc(handle, calc_model);
		if(err)
		{
			ticables_cable_close(handle);
			ticables_handle_del(handle);
			goto step2;
		}

		ticables_cable_close(handle);
		ticables_handle_del(handle);

		*cable_model = CABLE_USB;
		ret = 0;
		goto step3;
	}
	
step2:
	// search for SilverLink devices
	*port = found_port(cables[CABLE_SLV]);
	if(*port)
	{
		tilp_info("Searching for hand-helds on SilverLink...");
		handle = ticables_handle_new(CABLE_SLV, *port);
		ticables_options_set_timeout(handle, 10);

		err = ticables_cable_open(handle);
		if(err)
		{
			ticables_handle_del(handle);
			goto step3;
		}

		err = ticalcs_probe_usb_calc(handle, calc_model);
		if(err)
		{
			ticables_cable_close(handle);
			ticables_handle_del(handle);
			goto step3;
		}

		ticables_cable_close(handle);
		ticables_handle_del(handle);

		*cable_model = CABLE_SLV;
		ret = 0;
		goto step3;
	}

step3:
	ticables_probing_finish(&cables);
	return ret;
}

/* 
   Scan for cables & devices.
   The current device is closed during scanning because some link cables
   (serial & paralle) can't be probed while open because already locked.
*/
int tilp_device_probe_all(int ***result)
{
	int **array;
	int i;
	CableModel cable;
	CablePort port;
	CalcModel calc;
	int found = 0;
	//CableHandle* handle;
	int err;
	gchar *s;

	// Close device
	err = tilp_device_close();
	if(err)
	  return err;

	// search for cables
	tilp_info("Searching for link cables...");
	ticables_probing_do(&array, 5, PROBE_ALL);
	*result = array;

	for(i = 1; i <= 5; i++)
		printf("%i: %i %i %i %i\n", i, array[i][1], array[i][2], array[i][3], array[i][4]);

	// found at least 1 cable ?
	for(cable = CABLE_GRY; cable <= CABLE_USB; cable++)
		for(port = PORT_1; port <= PORT_4; port++)
			if(array[cable][port])
				found = 1;
	if(!found)
		return -1;

	// search for devices on all cables
	for(cable = CABLE_GRY; cable <= CABLE_USB; cable++)
	{
		for(port = PORT_1; port <= PORT_4; port++)
		{
			if(!array[cable][port])
				continue;
			
			tilp_info("Searching for hand-helds on %i:%i...",
                                  cable, port);

#if 1
			err = ticalcs_probe(cable, port, &calc, !0);
			if(err)
			{
				array[cable][port] = CALC_NONE;
				continue;
			}
			array[cable][port] = calc;

			s = g_strdup_printf("Found: %s on %s:%s", 
				ticalcs_model_to_string(calc),
				ticables_model_to_string(cable),
				ticables_port_to_string(port));
			tilp_info(s);
			g_free(s);
#else
			handle = ticables_handle_new(cable, port);
			ticables_options_set_timeout(handle, 10);

			err = ticables_cable_open(handle);
			if(err)
			{
				ticables_handle_del(handle);
				array[cable][port] = CALC_NONE;
				continue;
			}

			if(cable != CABLE_USB)
			{
				err = ticalcs_probe_calc(handle, &calc);
				if(err)
				{
					array[cable][port] = CALC_NONE;
					goto reloop;
				}
				array[cable][port] = calc;
			}
			else
			{
				err = ticalcs_probe_usb_calc(handle, &calc);
				if(err)
				{
					array[cable][port] = CALC_NONE;
					goto reloop;
				}
				array[cable][port] = calc;
			}
			s = g_strdup_printf("Found: %s on %s:%s", 
				ticalcs_model_to_string(calc),
				ticables_model_to_string(cable),
				ticables_port_to_string(port));
			tilp_info(s);
			g_free(s);

reloop:
			ticables_cable_close(handle);
			ticables_handle_del(handle);
#endif
		}
	}

	// show list
	for(i = 1; i <= 5; i++) 
		printf("%i: %02i %02i %02i %02i\n", i, array[i][1], array[i][2], array[i][3], array[i][4]);

	// Re-open device
	err = tilp_device_open();
	if(err)
	  return err;

	return 0;
}

//----------------------------------------------------------------------------

static int lk_open = 0; /* keep status to avoid multiple error messages */

int tilp_device_open(void)
{
	int err = 0;
	const char *calc;
	const char *cable;

	// close cable before opening a new one
	if(lk_open)
		tilp_device_close();

	cable = ticables_model_to_string(options.cable_model);
	calc = ticalcs_model_to_string(options.calc_model);
	tilp_info("Opening cable %s on port #%d to communicate with calculator %s", cable, options.cable_port, calc);
	if (options.calc_model == CALC_NONE)
	{
		tilp_warning("Attempting to communicate with calculator \"none\" !");
	}

	cable_handle = ticables_handle_new(options.cable_model, options.cable_port);
	if(cable_handle == NULL)
		gif->msg_box1("Error", "Can't set cable");
	else
	{
		ticables_options_set_timeout(cable_handle, options.cable_timeout);
		ticables_options_set_delay(cable_handle, options.cable_delay);

		calc_handle = ticalcs_handle_new(options.calc_model);
		if(calc_handle == NULL)
			gif->msg_box1("Error", "Can't set cable");
		else
		{
			err = ticalcs_cable_attach(calc_handle, cable_handle);
			tilp_err(err);

#if 1
			if(options.cable_model != CABLE_USB)
			{
				// BlackLink & ParallelLink need a reset before use
				err = ticables_cable_reset(cable_handle);
				PAUSE(2000);
				tilp_err(err);
			}
#endif
		}

		// Initialize callbacks with default functions
		//tilp_update_set_default();
		tilp_update_set_gtk();
	}

	lk_open = err ? 0 : 1;
	return err;
}

int tilp_device_close(void)
{
	int err;

	// close cable unless already closed
	if(!lk_open)
		return 0;

	// detach cable (made by handle_del, too)
	if(calc_handle == NULL)
		return 0;
	err = ticalcs_cable_detach(calc_handle);
	tilp_err(err);

	// remove calc & cable
	ticalcs_handle_del(calc_handle); calc_handle = NULL;
	ticables_handle_del(cable_handle); cable_handle = NULL;

	lk_open = 0;
	return err;
}

int tilp_device_err(int err)
{
	char *s = NULL;	
	char *utf;
	gsize bw;
	
	if(!err) return 0;
	tilp_info("tilp_device_err catched error %i\n", err);

	err = ticables_error_get(err, &s);
	if (err) 
	{
		g_free(s);
		err = ticalcs_error_get(err, &s);
		if (err) 
			g_free(s);
	}

	if(s)
	{
		utf = g_locale_to_utf8(s, -1, NULL, &bw, NULL);
		gif->msg_box1(_("Error"), utf);
	}

	return err;
}

/*
  Note: SilverLink is still NACK'ed after error. This did not appear with 
  TiLP-1 because it always close/open the device before any transfer.
  It seems that an error (HALT condition) cannot be cleared by a simple
  slv_reset. We need to reopen the device. Why? I don't know!

  No call to tilp_err in this function to avoid recursivity with tilp_err which
  may call tilp_device_reset.
*/
int tilp_device_reset(void)
{
  if(!lk_open)
    return 0;

#if 0	// disabled because this is managed by ticables v1.2.0 now
    if(options.cable_model == CABLE_SLV || options.cable_model == CABLE_USB)
    {
		int err;

		gif->msg_box("Information", _("Connection is being reset... Please wait for 2 seconds."), !0);

		// detach cable (made by handle_del, too)
		PAUSE(500);
		err = ticalcs_cable_detach(calc_handle);
		tilp_device_err(err);

		// remove calc & cable
		ticalcs_handle_del(calc_handle);
		ticables_handle_del(cable_handle);

		// this pause is needed (let's the cable reset its internal state...)
		PAUSE(2000);

		// get cable & attach
		cable_handle = ticables_handle_new(options.cable_model, options.cable_port);
		if(cable_handle == NULL)
			gif->msg_box1(_("Error"), _("Can't set cable."));
		else
		{
			ticables_options_set_timeout(cable_handle, options.cable_timeout);
			ticables_options_set_delay(cable_handle, options.cable_delay);

			calc_handle = ticalcs_handle_new(options.calc_model);
			if(calc_handle == NULL)
				gif->msg_box1(_("Error"), _("Can't set cable."));
			else
			{
				err = ticalcs_cable_attach(calc_handle, cable_handle);
				tilp_device_err(err);
			}
		}

		gif->msg_box("", "", 0);
    }
    else
#endif
    {
        int err = ticables_cable_reset(cable_handle);
        tilp_device_err(err);
        PAUSE(1000);
    }

    return 0;
}
