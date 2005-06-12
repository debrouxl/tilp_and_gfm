/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  TiLP - Ti Linking Program
 *  Copyright (C) 1999-2005  Romain Lievin
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
#include <unistd.h>

#include "tilp_core.h"

#if 0
#ifndef __MACOSX__		/* we use a general preferences system from Mac OS X */
/*
  Save the configuration file
*/
int tilp_config_save(void)
{
	tilp_rcfile_write();
	gif->msg_box(_("Information"), _("Configuration file saved."));
	return 0;
}


/*
  Load the configuration file
*/
int tilp_config_load(void)
{
	tilp_rcfile_read();
	gif->msg_box(_("Information"), _("Configuration file loaded."));
	return 0;
}
#endif				/* !__MACOSX__ */

/*
  Fill the option structure with default values
*/
#if defined(__LINUX__) || defined(__BSD__)
static void default_config_linux(void)	// linux specific options
{
	gchar *locale;
	options.unzip_location = g_strdup("unzip");
	options.unzip_options = g_strdup("");
	options.tar_location = g_strdup("tar");
	options.tar_options = g_strdup("");
	options.appsign_location = g_strdup("/usr/bin/appsign");
	options.appsign_options = g_strdup("-k /usr/bin/0104.key");
	options.web_location = g_strdup("/usr/bin/mozilla");
	options.web_options = g_strdup("");
	strcpy(options.left_font_name, "");
	strcpy(options.right_font_name,
	       "-adobe-courier-medium-r-*-*-*-120-*-*-*-*-*-*");
	options.console_mode = !0;
	locale = setlocale(LC_ALL, NULL);
	strcpy(options.locale, locale);
	options.working_dir = g_strdup(g_get_home_dir());
}
#endif				/*  */

#ifdef __WIN32__
static void default_config_win32(void)
{
	gchar *locale;
	options.unzip_location =
	    g_strdup("\"C:\\Program Files\\WinZip\\wzunzip.exe\"");
	options.unzip_options = g_strdup("");
	options.tar_location =
	    g_strdup("\"C:\\Program Files\\WinZip\\wzunzip.exe\"");
	options.tar_options = g_strdup("");
	options.appsign_location = g_strdup("");
	options.appsign_options = g_strdup("");
	options.web_location =
	    g_strdup("C:\\Program Files\\Internet Explorer\\IExplore.exe");
	options.web_options = g_strdup("");
	strcpy(options.left_font_name, "");
	strcpy(options.right_font_name,
	       "-adobe-courier-medium-r-normal--12-120-75-75-p-70-iso8859-1");
	options.console_mode = 0;
	locale = g_win32_getlocale();
	
	printl(0, "current locale: <%s>\n", locale);
	
	g_free(locale);
	options.working_dir = g_get_current_dir();
}
#endif				/*  */
#ifndef __MACOSX__
int tilp_config_default(void)
{
	options.xsize = 640 / 2;
	options.ysize = 480 / 2;
	options.clist_sort = SORT_BY_NAME;
	options.clist_sort_order = SORT_DOWN;
	options.ctree_sort = SORT_BY_NAME;
	options.ctree_sort_order = SORT_DOWN;
	options.confirm = CONFIRM_YES;
	options.path_mode = FULL_PATH;
	options.file_disp = SHOW_TIF;
	options.screen_format = PNG;
	options.screen_clipping = CLIPPED_SCREEN;
	options.screen_blurry = 0;
	ticable_get_default_param(&options.lp);
	options.auto_detect = !0;
	options.show_gui = TRUE;
	options.single_or_group = RECV_AS_GROUP;

#if defined(__LINUX__) || defined(__BSD__)
	default_config_linux();

#elif defined(__WIN32__)
	default_config_win32();

#else				/*  */
	return 0;

#endif				/*  */
	return 0;
}
#endif /* !__MACOSX__ */
#endif

#if 0

static char *rc_file;
static int get_rcfile_path(char **path)
{

#if defined(__LINUX__) || defined(__BSD__)
	*path = g_strconcat(g_get_home_dir(), INI_FILE, NULL);

#elif defined(__WIN32__)
	*path =
	    g_strconcat(inst_paths.base_dir, DIR_SEPARATOR, INI_FILE,
			NULL);

#endif				/*  */
	return 0;
}


/* Print an error msg */
static void stop(int line)
{
	char buffer[256];

	sprintf(buffer, _("Configuration file error at line %i.\n"), line);
	gif->msg_box(_("Error"), buffer);
} 

static char *find_str(char *s, const char *t)
{
	char *p = strstr(s, t);
	if (p == NULL)
		return NULL;

	else
		return p + strlen(t);
}


/* Chech whether a RC file exists */
int tilp_rcfile_exist(void)
{
	get_rcfile_path(&rc_file);
	return !access(rc_file, F_OK);
}


/* Delete the RC file */
int tilp_rcfile_delete(void)
{
	get_rcfile_path(&rc_file);
	return unlink(rc_file);
}


/* Return TiLP version number */
int tilp_rcfile_get_version(char *version)
{
	FILE *txt;
	char buffer[256];
	int i = 0;
	char *p;
	strcpy(version, "");
	if (tilp_rcfile_exist() == 0) {
		return -1;
	}
	get_rcfile_path(&rc_file);
	txt = fopen(rc_file, "rt");
	if (txt == NULL)
		return -1;
	for (i = 0; i < 5; i++)
		fgets(buffer, 256, txt);
	p = strchr(buffer, '=');
	if (p == NULL)
		return -1;
	strcpy(version, ++p);
	p = strchr(version, '\r');
	if (p)
		*p = '\0';
	p = strchr(version, '\n');
	if (p)
		*p = '\0';
	return 0;
}


/* Read the RC file and set up variables */
void tilp_rcfile_read(void)
{
	FILE *txt;
	char buffer[256];
	char *p;
	int l = 0;

	get_rcfile_path(&rc_file);
	txt = fopen(rc_file, "rt");
	if (txt == NULL) {
		printl(0, _("Configuration file not found, use default values. You can create one by the 'File|Save config' command menu.\n"));
		gif->msg_box(_("Information"), _
			     ("Configuration file not found, use default values. You can create one by the 'File|Save config' command menu.\n"));
		return;
	}

	while (!feof(txt)) {
		fgets(buffer, 256, txt);
		l++;

		if(feof(txt))
			break;

		buffer[strlen(buffer) - 1] = '\0';
		if (!strcmp(buffer, "RC_END")) {
			fclose(txt);
			return;
		}
		if (buffer[0] == '#' || !strlen(buffer))
			continue;

		//printf("<%s>\n", buffer);
		/* Hardware section */
		if ((p = find_str(buffer, "calctype="))) {
			if (!strcmp(p, "v200"))
				options.lp.calc_type = CALC_V200;

			else if (!strcmp(p, "ti92+"))
				options.lp.calc_type = CALC_TI92P;

			else if (!strcmp(p, "ti92"))
				options.lp.calc_type = CALC_TI92;

			else if (!strcmp(p, "ti89t"))
				options.lp.calc_type = CALC_TI89T;

			else if (!strcmp(p, "ti89"))
				options.lp.calc_type = CALC_TI89;

			else if (!strcmp(p, "ti86"))
				options.lp.calc_type = CALC_TI86;

			else if (!strcmp(p, "ti85"))
				options.lp.calc_type = CALC_TI85;

			else if (!strcmp(p, "ti84+"))
				options.lp.calc_type = CALC_TI84P;

			else if (!strcmp(p, "ti83+"))
				options.lp.calc_type = CALC_TI83P;

			else if (!strcmp(p, "ti83"))
				options.lp.calc_type = CALC_TI83;

			else if (!strcmp(p, "ti82"))
				options.lp.calc_type = CALC_TI82;

			else if (!strcmp(p, "ti73"))
				options.lp.calc_type = CALC_TI73;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "linktype="))) {
			if (!strcmp(p, "parallel"))
				options.lp.link_type = LINK_PAR;

			else if (!strcmp(p, "serial"))
				options.lp.link_type = LINK_SER;

			else if (!strcmp(p, "TIGraphLink"))
				options.lp.link_type = LINK_TGL;

			else if (!strcmp(p, "fastAVRlink"))
				options.lp.link_type = LINK_AVR;

			else if (!strcmp(p, "VTi"))
				options.lp.link_type = LINK_VTI;

			else if (!strcmp(p, "TiEmulator"))
				options.lp.link_type = LINK_TIE;

			else if (!strcmp(p, "virtual"))
				options.lp.link_type = LINK_VTL;

			else if (!strcmp(p, "UsbGraphLink"))
				options.lp.link_type = LINK_UGL;

            else if (!strcmp(p, "null"))
				options.lp.link_type = LINK_NUL;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "adr_port="))) {
			sscanf(p, "0x%03X", &(options.lp.io_addr));

			//check_access();
			continue;
		}
		if ((p = find_str(buffer, "device="))) {
			strcpy(options.lp.device, p);
		}
		if ((p = find_str(buffer, "timeout="))) {
			sscanf(p, "%i", &(options.lp.timeout));
			continue;
		}
		if ((p = find_str(buffer, "baudrate="))) {
			sscanf(p, "%i", (int *) &(options.lp.baud_rate));
			continue;
		}
		if ((p = find_str(buffer, "delay="))) {
			sscanf(p, "%i", &(options.lp.delay));
			continue;
		}
		if ((p = find_str(buffer, "rts_cts="))) {
			if (!strcmp(p, "on"))
				options.lp.hfc = HFC_ON;

			else if (!strcmp(p, "off"))
				options.lp.hfc = HFC_OFF;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "port="))) {
			if (!strcmp(p, "user"))
				options.lp.port = USER_PORT;

			else if (!strcmp(p, "parallel port #1"))
				options.lp.port = PARALLEL_PORT_1;

			else if (!strcmp(p, "parallel port #2"))
				options.lp.port = PARALLEL_PORT_2;

			else if (!strcmp(p, "parallel port #3"))
				options.lp.port = PARALLEL_PORT_3;

			else if (!strcmp(p, "serial port #1"))
				options.lp.port = SERIAL_PORT_1;

			else if (!strcmp(p, "serial port #2"))
				options.lp.port = SERIAL_PORT_2;

			else if (!strcmp(p, "serial port #3"))
				options.lp.port = SERIAL_PORT_3;

			else if (!strcmp(p, "serial port #4"))
				options.lp.port = SERIAL_PORT_4;

			else if (!strcmp(p, "virtual port #1"))
				options.lp.port = VIRTUAL_PORT_1;

			else if (!strcmp(p, "virtual port #2"))
				options.lp.port = VIRTUAL_PORT_2;

			else if (!strcmp(p, "USB port #1"))
				options.lp.port = USB_PORT_1;

			else if (!strcmp(p, "USB port #2"))
				options.lp.port = USB_PORT_2;

			else if (!strcmp(p, "USB port #3"))
				options.lp.port = USB_PORT_3;

			else if (!strcmp(p, "USB port #4"))
				options.lp.port = USB_PORT_4;

            else if (!strcmp(p, "null port"))
				options.lp.port = NULL_PORT;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "method="))) {
			if (!strcmp(p, "automatic"))
				options.lp.method = IOM_AUTO;

			else if (!strcmp(p, "asm"))
				options.lp.method = IOM_ASM;

			else if (!strcmp(p, "api"))
				options.lp.method = IOM_API;

			else if (!strcmp(p, "driver"))
				options.lp.method = IOM_DRV;

			else
				stop(l);
			continue;
		}

		/* */
		if ((p = find_str(buffer, "xsize="))) {
			sscanf(p, "%i", &(options.xsize));
			continue;
		}
		if ((p = find_str(buffer, "ysize="))) {
			sscanf(p, "%i", &(options.ysize));
			continue;
		}
		if ((p = find_str(buffer, "clist_sort="))) {
			if (!strcmp(p, "name"))
				options.clist_sort = SORT_BY_NAME;

			else if (!strcmp(p, "date"))
				options.clist_sort = SORT_BY_DATE;

			else if (!strcmp(p, "size"))
				options.clist_sort = SORT_BY_SIZE;

			else if (!strcmp(p, "user"))
				options.clist_sort = SORT_BY_USER;

			else if (!strcmp(p, "group"))
				options.clist_sort = SORT_BY_GROUP;

			else if (!strcmp(p, "attrib"))
				options.clist_sort = SORT_BY_ATTRB;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "clist_order="))) {
			if (!strcmp(p, "up"))
				options.clist_sort_order = SORT_UP;

			else if (!strcmp(p, "down"))
				options.clist_sort_order = SORT_DOWN;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "ctree_sort="))) {
			if (!strcmp(p, "name"))
				options.ctree_sort = SORT_BY_NAME;

			else if (!strcmp(p, "info"))
				options.ctree_sort = SORT_BY_INFO;

			else if (!strcmp(p, "type"))
				options.ctree_sort = SORT_BY_TYPE;

			else if (!strcmp(p, "size"))
				options.ctree_sort = SORT_BY_SIZE;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "ctree_order="))) {
			if (!strcmp(p, "up"))
				options.ctree_sort_order = SORT_UP;

			else if (!strcmp(p, "down"))
				options.ctree_sort_order = SORT_DOWN;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "confirm="))) {
			if (!strcmp(p, "yes"))
				options.confirm = CONFIRM_YES;

			else if (!strcmp(p, "no"))
				options.confirm = CONFIRM_NO;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "path="))) {
			if (!strcmp(p, "full"))
				options.path_mode = FULL_PATH;

			else if (!strcmp(p, "local"))
				options.path_mode = LOCAL_PATH;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "file_display="))) {
			if (!strcmp(p, "all"))
				options.file_disp = SHOW_ALL;

			else if (!strcmp(p, "ti"))
				options.file_disp = SHOW_TIF;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "screen_format="))) {
			if (!strcmp(p, "pcx"))
				options.screen_format = PCX;

			else if (!strcmp(p, "xpm"))
				options.screen_format = XPM;

			else if (!strcmp(p, "jpg"))
				options.screen_format = JPG;

			else if (!strcmp(p, "bmp"))
				options.screen_format = BMP;

			else if (!strcmp(p, "png"))
				options.screen_format = PNG;

			else if (!strcmp(p, "pdf"))
				options.screen_format = PDF;

			else if (!strcmp(p, "eps"))
				options.screen_format = EPS;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "screen_mode="))) {
			if (!strcmp(p, "full"))
				options.screen_clipping = FULL_SCREEN;

			else if (!strcmp(p, "clipped"))
				options.screen_format = CLIPPED_SCREEN;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "screen_blurry="))) {
			if (!strcmp(p, "yes"))
				options.screen_blurry = 1;

			else if (!strcmp(p, "no"))
				options.screen_blurry = 0;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "unzip_location="))) {
			g_free(options.unzip_location);
			options.unzip_location = g_strdup(p);
			continue;
		}
		if ((p = find_str(buffer, "unzip_options="))) {
			g_free(options.unzip_options);
			options.unzip_options = g_strdup(p);
			continue;
		}
		if ((p = find_str(buffer, "tar_location="))) {
			g_free(options.tar_location);
			options.tar_location = g_strdup(p);
			continue;
		}
		if ((p = find_str(buffer, "tar_options="))) {
			g_free(options.tar_options);
			options.tar_options = g_strdup(p);
			continue;
		}
		if ((p = find_str(buffer, "appsign_location="))) {
			g_free(options.appsign_location);
			options.appsign_location = g_strdup(p);
			continue;
		}
		if ((p = find_str(buffer, "appsign_options="))) {
			g_free(options.appsign_options);
			options.appsign_options = g_strdup(p);
			continue;
		}
		if ((p = find_str(buffer, "web_location="))) {
			g_free(options.web_location);
			options.web_location = g_strdup(p);
			continue;
		}
		if ((p = find_str(buffer, "web_options="))) {
			g_free(options.web_options);
			options.web_options = g_strdup(p);
			continue;
		}
		if ((p = find_str(buffer, "right_font_name="))) {
			strcpy(options.right_font_name, p);
			continue;
		}
		if ((p = find_str(buffer, "left_font_name="))) {
			strcpy(options.left_font_name, p);
			continue;
		}
		if ((p = find_str(buffer, "locale="))) {
			strcpy(options.locale, p);
			continue;
		}
		if ((p = find_str(buffer, "probe_89_92_92+=")) ||
		    (p = find_str(buffer, "probe_ti="))) {
			if (!strcmp(p, "no"))
				options.auto_detect = FALSE;

			else if (!strcmp(p, "yes"))
				options.auto_detect = TRUE;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "console="))) {
			if (!strcmp(p, "yes"))
				options.console_mode = TRUE;

			else if (!strcmp(p, "no"))
				options.console_mode = FALSE;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "show_gui="))) {
			if (!strcmp(p, "yes"))
				options.show_gui = TRUE;

			else if (!strcmp(p, "no"))
				options.show_gui = FALSE;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "single_or_group="))) {
			if (!strcmp(p, "single"))
				options.single_or_group = RECV_AS_SINGLE;

			else if (!strcmp(p, "group"))
				options.single_or_group = RECV_AS_GROUP;

			else
				stop(l);
			continue;
		}
		if ((p = find_str(buffer, "working_dir="))) {
			g_free(options.working_dir);
			options.working_dir = g_strdup(p);
			continue;
		}
	}
	fclose(txt);
	printl(2, "rcfile, 0x%03x\n", options.lp.io_addr);
	return;
}
void tilp_rcfile_write(void)
{
	FILE *txt;
	get_rcfile_path(&rc_file);
	txt = fopen(rc_file, "wt");
	if (txt == NULL) {
		gif->msg_box(_("Error"), _
			     ("Unable to write the config file (~/.tilp or tilp.ini).\n"));
		return;
	}
	fprintf(txt, "# Config file for TiLP\n");
	fprintf(txt,
		"# Copyright (C) 1999-2003 Romain Lievin <rlievin@mail.com>\n");
	fprintf(txt,
		"# Warning: any comments that you add to this file WILL be overwritten\n");
	fprintf(txt, "\n");
	fprintf(txt, "version=%s\n", TILP_VERSION);
	fprintf(txt, "\n");
	fprintf(txt, "#\n");
	fprintf(txt, "# HARDWARE SECTION\n");
	fprintf(txt, "#\n");
	fprintf(txt, "\n");
	fprintf(txt, "# Calculator type\n");
	fprintf(txt, "calctype=");
	switch (options.lp.calc_type) {
	case CALC_V200:
		fprintf(txt, "v200\n");
		break;
	case CALC_TI92P:
		fprintf(txt, "ti92+\n");
		break;
	case CALC_TI92:
		fprintf(txt, "ti92\n");
		break;
	case CALC_TI89T:
		fprintf(txt, "ti89t\n");
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
	case CALC_TI84P:
		fprintf(txt, "ti84+\n");
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
	case CALC_TI73:
		fprintf(txt, "ti73\n");
		break;
	}
	fprintf(txt, "\n");
	fprintf(txt, "# Link cable type\n");
	fprintf(txt, "linktype=");
	switch (options.lp.link_type) {
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
    case LINK_NUL:
        fprintf(txt, "null\n");
		break;
	default:
		fprintf(txt, "invalid\n");
		break;
	}
	fprintf(txt, "\n");
	fprintf(txt, "# Port to use (serial, parallel, ...\n");
	fprintf(txt, "port=");
	switch (options.lp.port) {
	case USER_PORT:
		fprintf(txt, "user\n");
		break;
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
    case NULL_PORT:
        fprintf(txt, "null port\n");
		break;
	default:
		fprintf(txt, "invalid\n");
		break;
	}
	fprintf(txt, "\n");
	fprintf(txt, "# Method to use for I/O accesses\n");
	fprintf(txt, "method=");
	if (options.lp.method & IOM_AUTO)
		fprintf(txt, "automatic\n");

	else if (options.lp.method & IOM_ASM)
		fprintf(txt, "asm\n");

	else if (options.lp.method & IOM_API)
		fprintf(txt, "api\n");

	else if (options.lp.method & IOM_DRV)
		fprintf(txt, "driver\n");

	else
		fprintf(txt, "automatic\n");
	fprintf(txt, "\n");
	fprintf(txt,
		"# Parallel/serial/virtual port address (0=automatic)\n");
	fprintf(txt, "adr_port=0x%03X\n", options.lp.io_addr);
	fprintf(txt, "\n");
	fprintf(txt,
		"# Serial device or character device (empty=automatic)\n");
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
	fprintf(txt, "rts_cts=%s\n",
		(options.lp.hfc == HFC_ON) ? "on" : "off");
	fprintf(txt, "\n");
	fprintf(txt, "#\n");
	fprintf(txt, "# GUI SECTION\n");
	fprintf(txt, "#\n");
	fprintf(txt, "\n");
	fprintf(txt, "# Window size\n");
	fprintf(txt, "xsize=%i\n", options.xsize);
	fprintf(txt, "ysize=%i\n", options.ysize);
	fprintf(txt, "\n");
	fprintf(txt,
		"# Right window sort order: name, date, size, user, group, attrib\n");
	fprintf(txt, "clist_sort=");
	switch (options.clist_sort) {
	case SORT_BY_NAME:
		fprintf(txt, "name\n");
		break;
	case SORT_BY_DATE:
		fprintf(txt, "date\n");
		break;
	case SORT_BY_SIZE:
		fprintf(txt, "size\n");
		break;
	case SORT_BY_USER:
		fprintf(txt, "user\n");
		break;
	case SORT_BY_GROUP:
		fprintf(txt, "group\n");
		break;
	case SORT_BY_ATTRB:
		fprintf(txt, "attrib\n");
		break;
	}
	fprintf(txt, "clist_order=");
	switch (options.clist_sort_order) {
	case SORT_UP:
		fprintf(txt, "up\n");
		break;
	case SORT_DOWN:
		fprintf(txt, "down\n");
		break;
	}
	fprintf(txt, "\n");
	fprintf(txt, "# Left window sort order: name, info, type, size\n");
	fprintf(txt, "ctree_sort=");
	switch (options.ctree_sort) {
	case SORT_BY_NAME:
		fprintf(txt, "name\n");
		break;
	case SORT_BY_INFO:
		fprintf(txt, "info\n");
		break;
	case SORT_BY_TYPE:
		fprintf(txt, "type\n");
		break;
	case SORT_BY_SIZE:
		fprintf(txt, "size\n");
		break;
	}
	fprintf(txt, "ctree_order=");
	switch (options.ctree_sort_order) {
	case SORT_UP:
		fprintf(txt, "up\n");
		break;
	case SORT_DOWN:
		fprintf(txt, "down\n");
		break;
	}
	fprintf(txt, "\n");
	fprintf(txt, "# Show all/TI files\n");
	fprintf(txt, "file_display=%s\n",
		options.file_disp ? "all" : "ti");
	fprintf(txt, "\n");
	fprintf(txt, "# Delete files\n");
	fprintf(txt, "confirm=%s\n", options.confirm ? "yes" : "no");
	fprintf(txt, "\n");
	fprintf(txt, "# Display console.\n");
	fprintf(txt, "console=%s\n",
		(options.console_mode) ? "yes" : "no");
	fprintf(txt, "\n");
	fprintf(txt, "# Show GUI in command line mode.\n");
	fprintf(txt, "show_gui=%s\n", (options.show_gui) ? "yes" : "no");
	fprintf(txt, "\n");
	fprintf(txt,
		"# Receive multiple file as single files or group file\n");
	fprintf(txt, "single_or_group=");
	switch (options.single_or_group) {
	case RECV_AS_SINGLE:
		fprintf(txt, "single\n");
		break;
	case RECV_AS_GROUP:
		fprintf(txt, "group\n");
		break;
	}
	fprintf(txt, "\n");
	fprintf(txt, "#\n");
	fprintf(txt, "# CALCULATOR SECTION\n");
	fprintf(txt, "#\n");
	fprintf(txt, "\n");
	fprintf(txt, "# Full or local path for sending variables\n");
	fprintf(txt, "path=%s\n", options.path_mode ? "local" : "full");
	fprintf(txt, "\n");
	fprintf(txt,
		"# Auto-detection of FLASH calculator (73/83+/89/92+).\n");
	fprintf(txt, "probe_ti=%s\n",
		(options.auto_detect) ? "yes" : "no");
	fprintf(txt, "\n");
	fprintf(txt, "#\n");
	fprintf(txt, "# EXTERNAL PROGRAMS SECTION\n");
	fprintf(txt, "#\n");
	fprintf(txt, "\n");
	fprintf(txt,
		"# Unzip program location: 'unzip'/'wzunzip.exe' by default\n");
	fprintf(txt, "unzip_location=%s\n", options.unzip_location);
	fprintf(txt, "\n");
	fprintf(txt,
		"# Unzip program options: no option -> 'archivename/' directory\n");
	fprintf(txt, "unzip_options=%s\n", options.unzip_options);
	fprintf(txt, "\n");
	fprintf(txt,
		"# Tar program location: 'tar'/'wzunzip.exe' by default\n");
	fprintf(txt, "tar_location=%s\n", options.tar_location);
	fprintf(txt, "\n");
	fprintf(txt,
		"# Tar program options: no option -> 'xvzf' by default\n");
	fprintf(txt, "tar_options=%s\n", options.tar_options);
	fprintf(txt, "\n");
	fprintf(txt,
		"# AppSign 83+ program location: appsign by default\n");
	fprintf(txt, "appsign_location=%s\n", options.appsign_location);
	fprintf(txt, "\n");
	fprintf(txt,
		"# AppSign 83+ program options: no option by default\n");
	fprintf(txt, "appsign_options=%s\n", options.appsign_options);
	fprintf(txt, "\n");
	fprintf(txt,
		"# Web browser location: '/usr/bin/mozilla' by default\n");
	fprintf(txt, "web_location=%s\n", options.web_location);
	fprintf(txt, "\n");
	fprintf(txt, "# Web browser options: no option by default\n");
	fprintf(txt, "web_options=%s\n", options.web_options);
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
	fprintf(txt,
		"# Full (full) or clipped (clipped) screen for screen captures\n");
	fprintf(txt, "screen_mode=%s\n",
		options.screen_clipping ? "clipped" : "full");
	fprintf(txt, "\n");
	fprintf(txt,
		"# Use the PNG (png) or JPEG (jpg) file format for images\n");
	fprintf(txt, "screen_format=");
	switch (options.screen_format) {
	case XPM:
		fprintf(txt, "xpm\n");
		break;
	case PCX:
		fprintf(txt, "pcx\n");
		break;
	case JPG:
		fprintf(txt, "jpg\n");
		break;
	case BMP:
		fprintf(txt, "bmp\n");
		break;
	case PNG:
		fprintf(txt, "png\n");
		break;
	case PDF:
		fprintf(txt, "pdf\n");
		break;
	case EPS:
		fprintf(txt, "eps\n");
		break;
	}
	fprintf(txt, "\n");
	fprintf(txt, "# Save screnshot in B&W or pseudo-grayscales ?\n");
	fprintf(txt, "screen_blurry=%s\n",
		options.screen_blurry ? "yes" : "no");
	fprintf(txt, "\n");
	fprintf(txt, "#\n");
	fprintf(txt, "# MISC SECTION\n");
	fprintf(txt, "#\n");
	fprintf(txt, "\n");
	fprintf(txt, "# Language used.\n");
	fprintf(txt, "locale=%s\n", options.locale);
	fprintf(txt, "\n");
	fprintf(txt, "# Working directory.\n");
	fprintf(txt, "working_dir=%s\n", options.working_dir);
	fprintf(txt, "\n");
	fprintf(txt, "RC_END\n");
	fclose(txt);
}

#endif