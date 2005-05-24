
/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  tilp - Ti Linking Program
 *  Copyright (C) 1999-2004  Romain Lievin
 *  Copyright (C) 2005 Julien BLACHE <jb@jblache.org>
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
#include <time.h>

#include "tilp_core.h"
TilpScreen ti_screen = { 0 };


/*
  Do a screen capture
*/
int tilp_screen_capture(void)
{
	int err;
	TicalcScreenCoord sc;

	/* Place a progress bar */
	gif->create_pbar_type1(_("Screendump"));

	/* 
	   Get a screen capture
	 */
	err =
	    ti_calc.screendump(&(ti_screen.bitmap),
			       options.screen_clipping, &sc);
	if (options.screen_clipping == FULL_SCREEN) {
		ti_screen.width = sc.width;
		ti_screen.height = sc.height;
	} else {
		ti_screen.width = sc.clipped_width;
		ti_screen.height = sc.clipped_height;
	}
	gif->destroy_pbar();
	if (tilp_error(err))
		return -1;
	return 0;
}


/*
  Convert the bitmap into a B&W bytemap.
  The returned RRGGBB array must be freed when no longer used.
*/
uint8_t *tilp_screen_convert(void)
{
	guchar *bitmap, *bytemap, data, mask;
	gint w;
	gint h;
	int row, col, bit, pixel, pos;

	bitmap = ti_screen.bitmap;
	w = ti_screen.width;
	h = ti_screen.height;

	bytemap = g_malloc(3 * w * h);

	for (row = 0; row < h; row++) {
		for (col = 0; col < (w >> 3); col++) {
			data = bitmap[(w >> 3) * row + col];
			mask = 0x80;

			for (bit = 0; bit < 8; bit++) {
				pixel = data & mask;
				pos = row * w + 8 * col + bit;
				if (pixel) {
					bytemap[3 * pos + 0] = 0;
					bytemap[3 * pos + 1] = 0;
					bytemap[3 * pos + 2] = 0;
				} else {
					bytemap[3 * pos + 0] = 255;
					bytemap[3 * pos + 1] = 255;
					bytemap[3 * pos + 2] = 255;
				}
				mask >>= 1;
			}
		}
	}

	return bytemap;
}

/*
  Convert the bitmap into a 2-colors bytemap.
  The returned RRGGBB array must be freed when no longer used.
*/
uint8_t *tilp_screen_blurry(void)
{
	guchar *bitmap, *bytemap, data, mask;
	gint w;
	gint h;
	int row, col, bit, pixel, pos;

	bitmap = ti_screen.bitmap;
	w = ti_screen.width;
	h = ti_screen.height;

	bytemap = g_malloc(3 * w * h);

	for (row = 0; row < h; row++) {
		for (col = 0; col < (w >> 3); col++) {
			data = bitmap[(w >> 3) * row + col];
			mask = 0x80;

			for (bit = 0; bit < 8; bit++) {
				pixel = data & mask;
				pos = row * w + 8 * col + bit;
				if (pixel) {
					bytemap[3 * pos + 0] = 0x00;
					bytemap[3 * pos + 1] = 0x00;
					bytemap[3 * pos + 2] = 0x34;
				} else {
					bytemap[3 * pos + 0] = 0xa8;
					bytemap[3 * pos + 1] = 0xb4;
					bytemap[3 * pos + 2] = 0xa8;
				}
				mask >>= 1;
			}
		}
	}

	return bytemap;
}


/*
 * Write out an Encapsulated PostScript file.
 */
gboolean tilp_screen_write_eps(const gchar *filename, GError **error)
{
	int h, w;
	int i;
	int row, col, bit, pixel, pos;
	guchar data, mask;
	FILE *fp;
	GError e;
	time_t t;

	fp = fopen(filename, "wb");
	if (fp == NULL) {
		e.message = _("Couldn't open destination file for writing!");
		*error = &e;
		return FALSE;
	}

	h = ti_screen.height;
	w = ti_screen.width;
	time(&t);

	fprintf(fp, "%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(fp, "%%%%Creator: TiLP %s / PostScript output Copyright (C) 2005 Julien BLACHE\n", TILP_VERSION);
	fprintf(fp, "%%%%Title: TiLP %s screenshot\n",
		tifiles_calctype_to_string(options.lp.calc_type));
	fprintf(fp, "%%%%CreationDate: %s", ctime(&t));
	fprintf(fp, "%%%%LanguageLevel: 3\n");
	fprintf(fp, "%%%%BoundingBox: 0 0 %d %d\n", w, h);
	fprintf(fp, "\n");
	fprintf(fp, "/pix 4 string def\n");
	fprintf(fp, "%d %d scale\n", w, h);

	if (options.screen_blurry) {
		fprintf(fp, "%d %d 8 [%d 0 0 -%d 0 %d] {currentfile pix readhexstring pop} false 3 colorimage\n", w, h, w, h, h);
		for (row = 0; row < h; row++) {
			for (col = 0; col < (w >> 3); col++) {
				data = ti_screen.bitmap[(w >> 3) * row + col];
				mask = 0x80;

				for (bit = 0; bit < 8; bit++) {
					pixel = data & mask;
					pos = row * w + 8 * col + bit;
					if (pixel)
						fprintf(fp, "000034");
					else
						fprintf(fp, "a8b4a8");
					mask >>= 1;
				}
				fprintf(fp, "\n");
			}
			fprintf(fp, "\n");
		}
	}
	else {
		fprintf(fp, "%d %d 1 [%d 0 0 -%d 0 %d] {currentfile pix readhexstring pop} image", w, h, w, h, h);
		for (i = 0; (i * 8) < (w * h); i++) {
			if (i % 20 == 0)
				fprintf(fp, "\n");

			fprintf(fp, "%02x", (ti_screen.bitmap[i] ^ 0xff));
		}
	}

	fprintf(fp, "\n");
	fprintf(fp, "%%%%EOF\n");
	fclose(fp);

	return TRUE;
}

/*
 * Write out a PDF file.
 */
gboolean tilp_screen_write_pdf(const gchar *filename, GError **error)
{
	int h, w;
	int i;
	int row, col, bit, pixel, pos;
	guchar data, mask;
	FILE *fp;
	long obj5, obj6, obj7, xref, slen, slenp;
	struct tm *t;
	time_t tt;
	GError e;

	fp = fopen(filename, "wb");
	if (fp == NULL) {
		e.message = _("Couldn't open destination file for writing!");
		*error = &e;
		return FALSE;
	}

	h = ti_screen.height;
	w = ti_screen.width;

	tt = time(NULL);
	t = gmtime(&tt);

	fprintf(fp, "%%PDF-1.5\n");
	fprintf(fp, "\n");
	fprintf(fp, "1 0 obj\n");
	fprintf(fp, "   << /Type /Catalog\n");
	fprintf(fp, "      /Outlines 2 0 R\n");
	fprintf(fp, "      /Pages 3 0 R\n");
	fprintf(fp, "   >>\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");
	fprintf(fp, "2 0 obj\n");
	fprintf(fp, "   << /Type /Outlines\n");
	fprintf(fp, "      /Count 0\n");
	fprintf(fp, "   >>\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");
	fprintf(fp, "3 0 obj\n");
	fprintf(fp, "   << /Type /Pages\n");
	fprintf(fp, "      /Kids [4 0 R]\n");
	fprintf(fp, "      /Count 1\n");
	fprintf(fp, "   >>\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");
	fprintf(fp, "4 0 obj\n");
	fprintf(fp, "    << /Type /Page\n");
	fprintf(fp, "       /Parent 3 0 R\n");
	fprintf(fp, "       /MediaBox [0 0 %d %d]\n", w, h);
	fprintf(fp, "       /Contents 5 0 R\n");
	fprintf(fp, "       /Resources << /ProcSet 6 0 R >>\n");
	fprintf(fp, "    >>\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");

	/* Offset of object 5, for xref */
	obj5 = ftell(fp);

	fprintf(fp, "5 0 obj\n");
	fprintf(fp, "    << /Length          >>\n");

	/* Position of the stream length, to be written later on */
	slenp = ftell(fp) - 12;

	fprintf(fp, "stream\n");

	/* Start of the stream data */
	slen = ftell(fp);

	fprintf(fp, "q\n");
/* FIXME to be defined according to screen size and scaling */
	fprintf(fp, "%d 0 0 %d 0 0 cm\n", w, h);
	fprintf(fp, "BI\n");
	fprintf(fp, "  /W %d\n", w);
	fprintf(fp, "  /H %d\n", h);

	if (options.screen_blurry) {
		/* RGB, 8 bits per component, ASCIIHex encoding */
		fprintf(fp, "  /CS /RGB\n");
		fprintf(fp, "  /BPC 8\n");
		fprintf(fp, "  /F /AHx\n");
		fprintf(fp, "ID\n");
		for (row = 0; row < h; row++) {
			for (col = 0; col < (w >> 3); col++) {
				data = ti_screen.bitmap[(w >> 3) * row + col];
				mask = 0x80;

				for (bit = 0; bit < 8; bit++) {
					pixel = data & mask;
					pos = row * w + 8 * col + bit;
					if (pixel)
						fprintf(fp, "000034");
					else
						fprintf(fp, "a8b4a8");
					mask >>= 1;
				}
				fprintf(fp, "\n");
			}
			fprintf(fp, "\n");
		}
	}
	else {
		/* GrayLevel, 1 bit per component, ASCIIHex encoding */
		fprintf(fp, "  /CS /G\n");
		fprintf(fp, "  /BPC 1\n");
		fprintf(fp, "  /F /AHx\n");
		fprintf(fp, "ID");
		for (i = 0; (i * 8) < (w * h); i++) {
			if (i % 20 == 0)
				fprintf(fp, "\n");

			fprintf(fp, "%02x", (ti_screen.bitmap[i] ^ 0xff));
		}
	}

	fprintf(fp, "\n");
	fprintf(fp, "EI\n");
	fprintf(fp, "Q\n");

	/* Go back and write the length of the stream */
	slen = ftell(fp) - slen - 1;
	fseek(fp, slenp, SEEK_SET);
	fprintf(fp, "%lu", slen);
	fseek(fp, 0L, SEEK_END);

	fprintf(fp, "endstream\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");

	/* Offset of object 6, for xref */
	obj6 = ftell(fp);

	fprintf(fp, "6 0 obj\n");
	fprintf(fp, "    [/PDF]\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");

	/* Offset of object 7, for xref */
	obj7 = ftell(fp);

	fprintf(fp, "7 0 obj\n");
	fprintf(fp, "   << /Title (TiLP %s screenshot)\n",
		tifiles_calctype_to_string(options.lp.calc_type));
	fprintf(fp, "      /Creator (TiLP / PDF output Copyright (C) 2005 Julien BLACHE)\n");
	fprintf(fp, "      /Producer (TiLP %s)\n", TILP_VERSION);
	fprintf(fp, "      /CreationDate (D:%04d%02d%02d%02d%02d%02d+00'00')\n",
		1900 + t->tm_year, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	fprintf(fp, "   >>\n");
	fprintf(fp, "endobj\n");
	fprintf(fp, "\n");

	/* Offset of xref, for startxref below */
	xref = ftell(fp);

	fprintf(fp, "xref\n");
	fprintf(fp, "0 8\n");
	fprintf(fp, "0000000000 65535 f \n");
	fprintf(fp, "0000000010 00000 n \n");
	fprintf(fp, "0000000094 00000 n \n");
	fprintf(fp, "0000000153 00000 n \n");
	fprintf(fp, "0000000229 00000 n \n");
	fprintf(fp, "%010lu 00000 n \n", obj5);
	fprintf(fp, "%010lu 00000 n \n", obj6);
	fprintf(fp, "%010lu 00000 n \n", obj7);
	fprintf(fp, "\n");
	fprintf(fp, "trailer\n");
	fprintf(fp, "    << /Size 8\n");
	fprintf(fp, "       /Root 1 0 R\n");
	fprintf(fp, "       /Info 7 0 R\n");
	fprintf(fp, "    >>\n");
	fprintf(fp, "startxref\n");
	fprintf(fp, "%lu\n", xref);
	fprintf(fp, "%%%%EOF\n");

	fclose(fp);

	return TRUE;
}
