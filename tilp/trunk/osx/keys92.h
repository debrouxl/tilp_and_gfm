/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2002 Julien BLACHE <jb@technologeek.org>
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


#define TIKEY92_GRAB		1
#define TIKEY92_F1		2
#define TIKEY92_F2		3
#define TIKEY92_F3		4
#define TIKEY92_F4		5
#define TIKEY92_F5		6
#define TIKEY92_F6		7
#define TIKEY92_F7		8
#define TIKEY92_F8		9
#define TIKEY92_Q		44
#define TIKEY92_W		45
#define TIKEY92_E		46
#define TIKEY92_R		47
#define TIKEY92_T		48
#define TIKEY92_Y		49
#define TIKEY92_U		50
#define TIKEY92_I		51
#define TIKEY92_O		52
#define TIKEY92_P		53
#define TIKEY92_A		54
#define TIKEY92_S		55
#define TIKEY92_D		56
#define TIKEY92_F		57
#define TIKEY92_G		58
#define TIKEY92_H		59
#define TIKEY92_J		60
#define TIKEY92_K		61
#define TIKEY92_L		62
#define TIKEY92_Z		64
#define TIKEY92_X		65
#define TIKEY92_C		66
#define TIKEY92_V		67
#define TIKEY92_B		68
#define TIKEY92_N		69
#define TIKEY92_M		70
#define TIKEY92_THETA		71
#define TIKEY92_SHIFT		63
#define TIKEY92_ON		72
#define TIKEY92_DIAMOND		73
#define TIKEY92_2ND		10
#define TIKEY92_STORE		74
#define TIKEY92_SPACE		75
#define TIKEY92_EQUALS		76
#define TIKEY92_BACKSPACE	77
#define TIKEY92_ENTER1		20
#define TIKEY92_ESCAPE		14
#define TIKEY92_MODE		11
#define TIKEY92_CLEAR		12
#define TIKEY92_LN		13
#define TIKEY92_APPS		15
#define TIKEY92_ENTER2		20
#define TIKEY92_LEFT		16
#define TIKEY92_RIGHT		19
#define TIKEY92_UP		17
#define TIKEY92_DOWN		18
#define TIKEY92_SIN		21
#define TIKEY92_COS		22
#define TIKEY92_TAN		23
#define TIKEY92_POWER		24
#define TIKEY92_PALEFT		25
#define TIKEY92_PARIGHT		26
#define TIKEY92_COMMA		27
#define TIKEY92_DIVIDE		28
#define TIKEY92_7		29
#define TIKEY92_8		30
#define TIKEY92_9		31
#define TIKEY92_MULTIPLY	32
#define TIKEY92_4		33
#define TIKEY92_5		34
#define TIKEY92_6		35
#define TIKEY92_MINUS		36
#define TIKEY92_1		37
#define TIKEY92_2		38
#define TIKEY92_3		39
#define TIKEY92_PLUS		40
#define TIKEY92_0		41
#define TIKEY92_DOT		42
#define TIKEY92_NEGATE		43


struct ti92key
{
  unsigned int none;
  unsigned int shift;
  unsigned int second;
  unsigned int diamond;
  unsigned int grab;
};


const struct ti92key TI92KEYS[] =
{
  { 0, 0, 0, 0, 0 }, /* bogus entry */
  { 0, 0, 0, 0, 0 }, /* GRAB */
  { 268, 268, 268, 8460, 0 }, /* F1 */
  { 269, 269, 269, 8461, 0 }, /* F2 */
  { 270, 270, 270, 8462, 0 }, /* F3 */
  { 271, 271, 271, 8463, 0 }, /* F4 */
  { 272, 272, 272, 8464, 0 }, /* F5 */
  { 273, 273, 273, 8465, 0 }, /* F6 */
  { 274, 274, 274, 8466, 0 }, /* F7 */
  { 275, 275, 275, 8467, 0 }, /* F8 */
  { 0, 0, 0, 0, 0 }, /* Second */
  { 266, 266, 266, 8458, 0 }, /* Mode */
  { 263, 263, 263, 8455, 0 }, /* CLEAR */
  { 262, 262, 4358, 8454, 0 }, /* LN */
  { 264, 264, 4360, 8456, 0 }, /* Escape */
  { 265, 265, 4361, 8457, 0 }, /* APPS */
  { 337, 16721, 4433, 8259, 33105 }, /* LEFT */ /* Arrow keys might need to be swapped */
  { 338, 16722, 4434, 8530, 33106 }, /* UP */
  { 344, 16728, 4440, 8536, 33112 }, /* DOWN */
  { 340, 16724, 4436, 8532, 33108 }, /* RIGHT */
  { 13, 13, 4109, 8305, 0 }, /* Enter */
  { 259, 259, 4355, 8451, 0 }, /* Sin */
  { 260, 260, 4356, 8452, 0 }, /* Cos */
  { 261, 261, 4357, 8453, 0 }, /* Tan */
  { 94, 94, 140, 8286, 0 }, /* ^ */
  { 40, 40, 123, 8232, 0 }, /* ( */
  { 41, 41, 125, 8233, 0 }, /* ) */
  { 44, 44, 91, 8236, 0 }, /* , */
  { 47, 47, 93, 8239, 0 }, /* / */
  { 55, 55, 4151, 8247, 0 }, /* 7 */
  { 56, 56, 4152, 8248, 0 }, /* 8 */
  { 57, 57, 4153, 8248, 0 }, /* 9 */
  { 42, 42, 4138, 8234, 0 }, /* * */
  { 52, 52, 4148, 8244, 0 }, /* 4 */
  { 53, 53, 4149, 8245, 0 }, /* 5 */
  { 54, 54, 4150, 8246, 0 }, /* 6 */
  { 45, 45, 4141, 0, 0 }, /* - */
  { 49, 49, 149, 8241, 0 }, /* 1 */
  { 50, 50, 4146, 8242, 0 }, /* 2 */
  { 51, 51, 4147, 8243, 0 }, /* 3 */
  { 43, 43, 4139, 0, 0 }, /* + */
  { 48, 48, 60, 8240, 0 }, /* 0 */
  { 46, 46, 62, 8238, 0 }, /* . */
  { 173, 173, 4372, 8365, 0 }, /* (-) */
  { 113, 81, 63, 8273, 0 }, /* Q */
  { 119, 87, 33, 8279, 0 }, /* W */
  { 101, 69, 0, 8261, 0 }, /* E */
  { 114, 82, 64, 8274, 0 }, /* R */
  { 116, 84, 35, 8276, 0 }, /* T */
  { 121, 89, 18, 8281, 0 }, /* Y */
  { 117, 85, 0, 8277, 0 }, /* U */
  { 105, 73, 151, 8265, 0 }, /* I */
  { 111, 79, 0, 8271, 0 }, /* O */
  { 112, 80, 95, 8272, 0 }, /* P */
  { 97, 65, 0, 8257, 0 }, /* A */
  { 115, 83, 223, 8275, 0 }, /* S */
  { 100, 68, 176, 8260, 0 }, /* D */
  { 102, 70, 159, 8262, 0 }, /* F */
  { 103, 71, 0, 8263, 0 }, /* G */
  { 104, 72, 38, 8264, 0 }, /* H */
  { 106, 74, 190, 8266, 0 }, /* J */
  { 107, 75, 124, 8267, 0 }, /* K */
  { 108, 76, 34, 8268, 0 }, /* L */
  { 0, 0, 0, 0, 0 }, /* Shift */
  { 122, 90, 0, 8282, 0 }, /* Z */
  { 120, 88, 169, 8280, 0 }, /* X */
  { 98, 66, 0, 8259, 0 }, /* C */
  { 118, 86, 157, 8278, 0 }, /* V */
  { 98, 66, 39, 8258, 0 }, /* B */
  { 110, 78, 0, 8270, 0 }, /* N */
  { 109, 77, 59, 8269, 0 }, /* M */
  { 136, 136, 58, 8328, 0 }, /* Theta */
  { 0, 0, 0, 0, 0 }, /* ON */
  { 0, 0, 0, 0, 0 }, /* Diamond */
  { 258, 258, 4354, 8450, 0 }, /* STO */
  { 32, 32, 32, 8224, 0 }, /* Spacebar */
  { 61, 61, 92, 8253, 0 }, /* = */
  { 257, 257, 4353, 8449, 0 }, /* Backspace */
  { 342, 16726, 4438, 8534, 33110 }, /* RIGHT + UP */
  { 348, 16732, 4444, 8540, 33116 }, /* RIGHT + DOWN */
  { 339, 16723, 4435, 8531, 33107 }, /* LEFT + UP */
  { 345, 16729, 4441, 8437, 33113 }, /* LEFT + DOWN */
};
