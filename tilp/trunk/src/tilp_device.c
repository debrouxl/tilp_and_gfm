/* Hey EMACS -*- linux-c -*- */
/* $Id: tilp_calcs.c 2270 2006-05-05 13:03:11Z roms $ */

/*  TiLP - Ti Linking Program
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
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*
	This file contains utility functions for hand-helds probing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef __MACOSX__
# include "tilibs.h"
#else				/*  */
# include <libticables/ticables.h>
# include <libticalcs/calc_int.h>
# include <libticalcs/calc_err.h>
# include <glib/glib.h>
# include <stdlib.h>
#endif				/*  */

#include "tilp_core.h"

#ifdef __WIN32__
# define strcasecmp _stricmp
#endif

CalcModel tilp_remap_from_usb(CableModel cable, CalcModel calc)
{
	if(cable == CABLE_USB && calc == CALC_TI84P_USB)
		return CALC_TI84P;
	else if(cable == CABLE_USB && calc == CALC_TI89T_USB)
		return  CALC_TI89T;
	else
		return calc;
}

CalcModel tilp_remap_to_usb(CableModel cable, CalcModel calc)
{
	if(cable == CABLE_USB && calc == CALC_TI84P)
		return CALC_TI84P_USB;
	else if(cable == CABLE_USB && calc == CALC_TI89T)
		return  CALC_TI89T_USB;
	else
		return calc;
}

static int found_port(int *ports)
{
	int i;

	for(i = PORT_1; i <= PORT_4; i++)
		if(ports[i])
			return i;

	return 0;
}

/* Scan for USB devices only (fast) */
int tilp_device_probe_usb(CableModel* cable_model, CablePort *port, CalcModel* calc_model)
{
	int err;
	int ret = -1;
	int **cables;
	CableHandle* handle;

	// search for all USB cables (faster)
	tilp_info("Searching for link cables...");
	err = ticables_probing_do(&cables, 5, PROBE_USB);
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

		err = ticalcs_probe_calc(handle, calc_model);
		if(err)
		{
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

/* Scan for cables & devices. Scan order is time increasing */
int tilp_device_probe_all(int ***result)
{
	int **array;
	int i;
	int cable, port, calc;
	int found;
	CableHandle* handle;
	int err;
	gchar *s;

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
			tilp_info("Searching for hand-helds on %i:%i...", 
				  cable, port);

			if(!array[cable][port])
				continue;
			
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
		}
	}

	// show list
	for(i = 1; i <= 5; i++) 
		printf("%i: %02i %02i %02i %02i\n", i, array[i][1], array[i][2], array[i][3], array[i][4]);

	return 0;
}

int tilp_device_open(void)
{
	int err = 0;

	cable_handle = ticables_handle_new(options.cable_model, options.cable_port);
	if(cable_handle == NULL)
	{
		gif->msg_box1("Error", "Can't set cable");
	}
	else
	{
		CalcModel cm = tilp_remap_to_usb(options.cable_model, options.calc_model);

		ticables_options_set_timeout(cable_handle, options.cable_timeout);
		ticables_options_set_delay(cable_handle, options.cable_delay);
		//ticables_cable_reset(cable_handle);

		calc_handle = ticalcs_handle_new(cm);
		if(calc_handle == NULL)
		{
			gif->msg_box1("Error", "Can't set cable");
		}
		else
		{
			err = ticalcs_cable_attach(calc_handle, cable_handle);
			tilp_err(err);
		}

		// Initialize callbacks with default functions
		tilp_update_set_default();
	}

	return err;
}

int tilp_device_close(void)
{
	int err = 0;

	// detach cable (made by handle_del, too)
	err = ticalcs_cable_detach(calc_handle);
	tilp_err(err);

	// remove calc & cable
	ticalcs_handle_del(calc_handle);
	ticables_handle_del(cable_handle);

	return err;
}

#if 0
int i, j;
	int **cables;
	CableHandle* handle;
	int err;
	gchar *s;

	// search for cables
	tilp_info("Searching for link cables...");
	gtk_label_set_text(GTK_LABEL(lbl), "Searching for cables...");
	GTK_REFRESH();
	ticables_probing_do(&cables, 5, PROBE_ALL);
	for(i = 1; i <= 5/*7*/; i++)
		printf("%i: %i %i %i %i\n", i, cables[i][1], cables[i][2], cables[i][3], cables[i][4]);

	cable_model = cable_port = calc_model = 0;
	for(i = CABLE_GRY; i <= CABLE_TIE; i++)
		for(j = PORT_1; j <= PORT_4; j++)
			if(cables[i][j])	// && ((i >= CABLE_VTI) && (j == PORT_2)))
			{
				cable_model = i;
				cable_port = j;
				goto finished;
			}
finished:
	ticables_probing_finish(&cables);

	if(!cable_model && !cable_port)
	{
		gtk_label_set_text(GTK_LABEL(lbl), "Not found !");
		return;
	}

	// search for devices
	tilp_info("Searching for hand-helds on %i:%i...", 
		  cable_model, cable_port);
	gtk_label_set_text(GTK_LABEL(lbl), "Searching for hand-helds...");
	GTK_REFRESH();
	
	handle = ticables_handle_new(cable_model, cable_port);
	ticables_options_set_timeout(handle, 10);

	err = ticables_cable_open(handle);
	if(err)
	{
		tilp_err(err);
		ticables_handle_del(handle);
		gtk_label_set_text(GTK_LABEL(lbl), "Not found !");
		return;
	}

	if(cable_model != CABLE_USB)
	{
		ticalcs_probe_calc(handle, &calc_model);
	}
	else
	{
		ticalcs_probe_usb_calc(handle, &calc_model);
	}
	s = g_strdup_printf("Found: %s %s %s", 
		ticalcs_model_to_string(calc_model),
		ticables_model_to_string(cable_model),
		ticables_port_to_string(cable_port));
	gtk_label_set_text(GTK_LABEL(lbl), s);
	GTK_REFRESH();
	g_free(s);

	ticables_cable_close(handle);
	ticables_handle_del(handle);

	calc_model = tilp_remap_from_usb(cable_model, calc_model);

	gtk_option_menu_set_history(GTK_OPTION_MENU(om_cable), cable_model);
	gtk_option_menu_set_history(GTK_OPTION_MENU(om_port), cable_port);
	gtk_option_menu_set_history(GTK_OPTION_MENU(om_calc), calc_model);
#endif