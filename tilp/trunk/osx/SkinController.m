/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2002 Julien BLACHE <jb@technologeek.org>
 *
 *  skinedit - a skin editor for TiEmu v2.00
 *  Copyright (C) 2002 Julien BLACHE <jb@technologeek.org>
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

#import "SkinController.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "cocoa_structs.h"

#define ENDIANNESS_FLAG 0xfeedbabe

#define bswap_32(a) (a >> 24) | ((a & 0xff0000) >> 16) << 8 | ((a & 0xff00) >> 8) << 16 | (a & 0xff) << 8

@implementation SkinController

// skin loading methods
- (int)loadSkin:(NSString *)path skinSize:(NSSize *)skinSize lcd:(RECT_ *)lcd keys:(RECT_ *)keys
{
    int ret;
    NSData *skin = nil;
    
    skin = [NSData dataWithContentsOfFile:path];
    
    if (skin == nil)
        return -1;
        
    if (strncmp([skin bytes], "VTIv2.1", 7) == 0)
      ret = [self loadSkinOldVTi:skin skinSize:skinSize lcd:lcd keys:keys];
    else if (strncmp([skin bytes], "VTIv2.5", 7) == 0)
        ret = [self loadSkinVTi:skin skinSize:skinSize lcd:lcd keys:keys];
    else
        ret = [self loadSkinTiEmu:skin skinSize:skinSize lcd:lcd keys:keys];

    if (ret != 0)
      return -1;

    return 0;
}


- (int)loadSkinVTi:(NSData *)skin skinSize:(NSSize *)skinSize lcd:(RECT_ *)lcd keys:(RECT_ *)keys
{
  unsigned char *bytes = NULL;
  int i;

  bytes = (unsigned char *)[skin bytes];
  
  if (bytes == NULL)
    return -1;

  bytes += 152;

  memcpy(lcd, bytes, 16);
  bytes += 16;

  memcpy(keys, bytes, 80*16);

#if (G_BYTE_ORDER == G_BIG_ENDIAN) || defined(__MACOSX__)
  /*
   * VTI skins are usually designed on a little endian architecture
   */

  lcd->top = bswap_32(lcd->top);
  lcd->left = bswap_32(lcd->left);
  lcd->bottom = bswap_32(lcd->bottom);
  lcd->right = bswap_32(lcd->right);

  for (i = 0; i < 80; i++)
  {
    keys[i].top = bswap_32(keys[i].top);
    keys[i].bottom = bswap_32(keys[i].bottom);
    keys[i].left = bswap_32(keys[i].left);
    keys[i].right = bswap_32(keys[i].right);
  }
#endif

  return [self loadJPEG:skin atOffset:1448 skinSize:skinSize lcd:lcd keys:keys];
}


- (int)loadSkinOldVTi:(NSData *)skin skinSize:(NSSize *)skinSize lcd:(RECT_ *)lcd keys:(RECT_ *)keys
{
  unsigned char *bytes = NULL;
  int i;

  bytes = (unsigned char *)[skin bytes];

  if (bytes == NULL)
    return -1;

  bytes += 88;

  memcpy(lcd, bytes, 16);
  bytes += 16;
  
  memcpy(keys, bytes, 80*16);

#if (G_BYTE_ORDER == G_BIG_ENDIAN) || defined(__MACOSX__)
  /*
   * VTI skins are usually designed on a little endian architecture
   */

  lcd->top = bswap_32(lcd->top);
  lcd->left = bswap_32(lcd->left);
  lcd->bottom = bswap_32(lcd->bottom);
  lcd->right = bswap_32(lcd->right);

  for (i = 0; i < 80; i++)
  {
    keys[i].top = bswap_32(keys[i].top);
    keys[i].bottom = bswap_32(keys[i].bottom);
    keys[i].left = bswap_32(keys[i].left);
    keys[i].right = bswap_32(keys[i].right);
  }
#endif

  return [self loadJPEG:skin atOffset:1384 skinSize:skinSize lcd:lcd keys:keys];
}

- (int)loadSkinTiEmu:(NSData *)skin skinSize:(NSSize *)skinSize lcd:(RECT_ *)lcd keys:(RECT_ *)keys
{
  int i;
  unsigned char *bytes = NULL;
  uint32_t endian;
  uint32_t jpeg_offset;
  uint32_t length;

  bytes = (unsigned char *)[skin bytes];

  bytes += 16;
  
  memcpy(&endian, bytes, 4);
  bytes += 4;
  
  memcpy(&jpeg_offset, bytes, 4);
  bytes += 4;
  
  if (endian != ENDIANNESS_FLAG)
    jpeg_offset = bswap_32(jpeg_offset);

  bytes += 20;

  /*
   * Skin name
   */
  memcpy(&length, bytes, 4);
  bytes += 4;
  
  if (endian != ENDIANNESS_FLAG)
    length = bswap_32(length);

  bytes += length;
  
  /*
   * Skin author
   */

  memcpy(&length, bytes, 4);
  bytes += 4;
  
  if (endian != ENDIANNESS_FLAG)
    length = bswap_32(length);

  bytes += length;

  memcpy(lcd, bytes, 16);
  bytes += 16;
  
  /* number of RECT struct to read */
  memcpy(&length, bytes, 4);
  bytes += 4;
  
  if (endian != ENDIANNESS_FLAG)
    length = bswap_32(length);

  if (length > SKIN_KEYS)
    return -1;

  memcpy(keys, bytes, length*16);

  if (endian != ENDIANNESS_FLAG)
  {
    lcd->top = bswap_32(lcd->top);
    lcd->left = bswap_32(lcd->left);
    lcd->bottom = bswap_32(lcd->bottom);
    lcd->right = bswap_32(lcd->right);

    for (i = 0; i < length; i++)
    {
      keys[i].top = bswap_32(keys[i].top);
      keys[i].bottom = bswap_32(keys[i].bottom);
      keys[i].left = bswap_32(keys[i].left);
      keys[i].right = bswap_32(keys[i].right);
    }
  }

  return [self loadJPEG:skin atOffset:jpeg_offset skinSize:skinSize lcd:lcd keys:keys];  
}

- (int)loadJPEG:(NSData *)skin atOffset:(uint32_t)jpeg_offset skinSize:(NSSize *)skinSize lcd:(RECT_ *)lcd keys:(RECT_ *)keys
{
  NSRange jpegRange;
  NSSize winSize;
  NSImage *skinImage;
  NSData *jpegData;

  jpegRange = NSMakeRange(jpeg_offset, [skin length] - jpeg_offset);

  jpegData = [skin subdataWithRange:jpegRange];

  skinImage = [[NSImage alloc] initWithData:jpegData];

  if (skinImage == nil)
    return -1;

  *skinSize = [skinImage size];

  // set the size of the NSWindow
  // 1/2 of the skin size by default
  winSize.width = skinSize->width / 2.0;
  winSize.height = skinSize->height / 2.0;

  [keyboardWindow setContentSize:winSize];
  
  [skinView setImage:skinImage];
  
  return 0;
}

@end
