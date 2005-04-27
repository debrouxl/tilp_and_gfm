/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2003 Julien BLACHE <jb@tilp.info>
 *
 *  $Id$
 *
 *  Cocoa GUI for Mac OS X
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

#ifndef __KEYS89_H__
#define __KEYS89_H__

#define TIKEY89_F1		1
#define TIKEY89_F2		2
#define TIKEY89_F3		3
#define TIKEY89_F4		4
#define TIKEY89_F5		5
#define TIKEY89_2ND		6
#define TIKEY89_SHIFT		7
#define TIKEY89_ESCAPE		8
#define TIKEY89_LEFT		12
#define TIKEY89_RIGHT		14
#define TIKEY89_UP		13
#define TIKEY89_DOWN		15
#define TIKEY89_DIAMOND		9
#define TIKEY89_ALPHA		10
#define TIKEY89_APPS		11
#define TIKEY89_HOME		16
#define TIKEY89_MODE		17
#define TIKEY89_CATALOG		18
#define TIKEY89_BACKSPACE	19
#define TIKEY89_CLEAR		20
#define TIKEY89_X		21
#define TIKEY89_Y		22
#define TIKEY89_Z		23
#define TIKEY89_T		24
#define TIKEY89_POWER		25
#define TIKEY89_EQUALS		26
#define TIKEY89_PALEFT		27
#define TIKEY89_PARIGHT		28
#define TIKEY89_COMMA		29
#define TIKEY89_DIVIDE		30
#define TIKEY89_PIPE		31
#define TIKEY89_7		32
#define TIKEY89_8		33
#define TIKEY89_9		34
#define TIKEY89_MULTIPLY	35
#define TIKEY89_EE		36
#define TIKEY89_4		37
#define TIKEY89_5		38
#define TIKEY89_6		39
#define TIKEY89_MINUS		40
#define TIKEY89_STORE		41
#define TIKEY89_1		42
#define TIKEY89_2		43
#define TIKEY89_3		44
#define TIKEY89_PLUS		45
#define TIKEY89_ON		46
#define TIKEY89_0		47
#define TIKEY89_PERIOD		48
#define TIKEY89_NEGATE		49
#define TIKEY89_ENTER1		50


struct ti89key
{
  uint16_t none;
  uint16_t shift;
  uint16_t second;
  uint16_t diamond;
  uint16_t alpha;
};


const struct ti89key TI89KEYS[] =
{
  { 0, 0, 0, 0, 0 }, /* bogus entry */
  { 268, 268, 273, 8460, 268 }, /* F1 */
  { 269, 269, 274, 8461, 269 }, /* F2 */
  { 270, 270, 275, 8462, 270 }, /* F3 */
  { 271, 271, 271, 8463, 271 }, /* F4 */
  { 272, 272, 272, 8464, 272 }, /* F5 */
  { 0, 0, 0, 12288, 0 }, /* 2nd */
  { 0, 0, 0, 24576, 0 }, /* Shift */
  { 264, 264, 4360, 8456, 264 }, /* ESC */
  { 0, 0, 0, 0, 0 }, /* Diamond */
  { 0, 0, 0, 0, 0 }, /* alpha */
  { 265, 265, 4361, 8457, 265 }, /* APPS */
  { 338, 16722, 4434, 8530, 33106 }, /* LEFT */
  { 337, 16721, 4433, 8529, 33105 }, /* UP */
  { 344, 16728, 4440, 8536, 33112 }, /* RIGHT */
  { 340, 16724, 4436, 8532, 33108 }, /* DOWN */
  { 277, 277, 4373, 277, 277 }, /* HOME */
  { 266, 266, 18, 95, 266 }, /* MODE */
  { 278, 278, 151, 190, 278 }, /* CATALOG */
  { 257, 257, 4353, 8449, 257 }, /* Backspace */
  { 263, 263, 263, 8455, 263 }, /* CLEAR */
  { 120, 88, 4184, 8280, 120 }, /* X */
  { 121, 89, 4185, 8281, 121 }, /* Y */
  { 122, 90, 4186, 8282, 122 }, /* Z */
  { 116, 84, 4180, 8276, 116 }, /* T */
  { 94, 94, 140, 136, 94 }, /* ^ */
  { 61, 65, 39, 157, 97 }, /* = */
  { 40, 66, 123, 0, 98 }, /* ( */
  { 41, 67, 125, 169, 99 }, /* ) */
  { 44, 68, 91, 8236, 100 }, /* , */
  { 47, 69, 93, 33, 101 }, /* / */
  { 124, 70, 176, 8316, 102 }, /* | */
  { 55, 71, 4151, 8247, 103 }, /* 7 */
  { 56, 72, 4152, 8248, 104 }, /* 8 */
  { 57, 73, 59, 8249, 105 }, /* 9 */
  { 42, 74, 4138, 38, 106 }, /* * */
  { 149, 75, 159, 8341, 107 }, /* EE */
  { 52, 76, 58, 8244, 108 }, /* 4 */
  { 53, 77, 4149, 8245, 109 }, /* 5 */
  { 54, 78, 4150, 8246, 110 }, /* 6 */
  { 45, 79, 4141, 0, 111 }, /* - */
  { 258, 80, 4354, 64, 112 }, /* STO=> */
  { 49, 81, 34, 8241, 113 }, /* 1 */
  { 50, 82, 92, 8242, 114 }, /* 2 */
  { 51, 83, 4147, 8243, 115 }, /* 3 */
  { 43, 85, 4139, 0, 117 }, /* + */
  { 0, 0, 0, 0, 0 }, /* ON */
  { 48, 86, 60, 156, 118 }, /* 0 */
  { 46, 87, 62, 158, 119 }, /* . */
  { 173, 32, 4372, 8365, 32 }, /* (-) */
  { 13, 13, 4109, 8205, 13 }  /* ENTER */
};

#endif /* !__KEYS89_H__ */

