/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  libtifiles - Ti File Format library, a part of the TiLP project
 *  Copyright (C) 1999-2004  Romain Lievin
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
  Logging system for the 4 domains:
  - ticables
  - tifiles
  - ticalcs 
  - tilp
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "intl.h"

#include "export.h"
#include "tilibs.h"
#include "tilp_printl.h"

/* 
   Print to stdout as default behaviour unless changed by tifiles_set_print 
   Level: such as "warning", "error", "information", etc. "" = nothing.
*/

#define DOMAIN_TICABLES         "ticables"
#define DOMAIN_TIFILES          "tifiles"
#define DOMAIN_TICALCS          "ticalcs"
#define DOMAIN_TILP             "tilp"

#define NO_STDOUT

/**************** printl muxer ************************/

#ifdef __WIN32__
static BOOL alloc_console_called = FALSE;
HANDLE hConsole;
#endif

int printl_muxer(const char *domain, int level, const char *format, va_list ap)
{
                char buffer[128];
                int cnt;
                DWORD nWritten;
/*
    	        if (alloc_console_called == FALSE) {
      		        AllocConsole();
      		        alloc_console_called = TRUE;
      		        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      		        //freopen("CONOUT$", "w", stdout);
    	        }

                va_start(ap, format);
                cnt = _vsnprintf(buffer, 128, format, ap);
                WriteConsole(hConsole, buffer, cnt, &nWritten, NULL);
                va_end(ap);
*/
	//return vfprintf(stdout, format, ap);
        return 0;
}

/**************** printl callbacks ********************/

int ticables_printl(int level, const char *format, ...)
{
        va_list ap;
	int ret = 0;
#ifndef NO_STDOUT
	fprintf(stdout, "cables ");
	if(level != 0)
		fprintf(stdout, "(%s)", 
			(level == 2) ? _("error") : _("warning"));
        fprintf(stdout, ": ");
#endif
	va_start(ap, format);
        ret = printl_muxer(DOMAIN_TICABLES, level, format, ap);
        va_end(ap);
 
	return ret;
}

int tifiles_printl(int level, const char *format, ...)
{
        va_list ap;
	int ret = 0;
#ifndef NO_STDOUT
	fprintf(stdout, "files ");
	if(level != 0)
		fprintf(stdout, "(%s)", 
			(level == 2) ? _("error") : _("warning"));
        fprintf(stdout, ": ");
#endif
	va_start(ap, format);
        ret = printl_muxer(DOMAIN_TIFILES, level, format, ap);
        va_end(ap);
 
	return ret;
}

int ticalcs_printl(int level, const char *format, ...)
{
        va_list ap;
	int ret = 0;
#ifndef NO_STDOUT
	fprintf(stdout, "calcs ");
	if(level != 0)
		fprintf(stdout, "(%s)", 
			(level == 2) ? _("error") : _("warning"));
        fprintf(stdout, ": ");
#endif
	va_start(ap, format);
        ret = printl_muxer(DOMAIN_TICALCS, level, format, ap);
        va_end(ap);
 
	return ret;
}

int default_printl(int level, const char *format, ...)
{
	va_list ap;
	int ret = 0;

	va_start(ap, format);
        ret = printl_muxer(DOMAIN_TILP, level, format, ap);
        va_end(ap);

	return ret;
}

TILP_PRINTL printl = default_printl;

/*
	Change print behaviour (callback).
*/
TILP_PRINTL tilp_set_printl(TILP_PRINTL new_printl)
{
  TILP_PRINTL old_printl = printl;

  //printf("printl = %p\n", printl);
  //printf("old_printl = %p\n", old_printl);
  //printf("new_printl = %p\n", new_printl);

  printl = new_printl;

  return old_printl;
}
