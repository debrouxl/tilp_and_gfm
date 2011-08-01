/* Hey EMACS -*- linux-c -*- */
/* $Id: dirent.h 366 2004-03-22 18:04:07Z roms $ */

/*  tilp - Ti Linking Program
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
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifdef __WIN32__

#ifndef DIRENT_H
#define DIRENT_H

#include <sys/stat.h>

//#define S_IFMT     0170000   // bitmask for the file type bitfields
#define __S_IFMT     0170000   // bitmask for the file type bitfields
#define S_IFSOCK   0140000   // socket
#define S_IFLNK    0120000   // symbolic link
//#define S_IFREG    0100000   // regular file
#define __S_IFREG    0100000   // regular file
#define S_IFBLK    0060000   // block device
//#define S_IFDIR    0040000   // directory
#define __S_IFDIR  0040000   // directory
//#define S_IFCHR    0020000   // character device
#define S_IFIFO    0010000   // fifo
#define S_ISUID    0004000   // set UID bit
#define S_ISGID    0002000   // set GID bit (see below)
#define S_ISVTX    0001000   // sticky bit (see below)
#define S_IRWXU    00700     // mask for file owner permissions
#define S_IRUSR    00400     // owner has read permission
#define S_IWUSR    00200     // owner has write permission
#define S_IXUSR    00100     // owner has execute permission
#define S_IRWXG    00070     // mask for group permissions
#define S_IRGRP    00040     // group has read permission
#define S_IWGRP    00020     // group has write permission
#define S_IXGRP    00010     // group has execute permission
#define S_IRWXO    00007     // mask for permissions for others (not in group)
#define S_IROTH    00004     // others have read permission
#define S_IWOTH    00002     // others have write permisson
#define S_IXOTH    00001     // others have execute permisson

/* Test macros for file types.  */

#define __S_ISTYPE(mode, mask)  (((mode) & __S_IFMT) == (mask))

#define S_ISDIR(mode)    __S_ISTYPE((mode), __S_IFDIR)
#define S_ISCHR(mode)    __S_ISTYPE((mode), __S_IFCHR)
#define S_ISBLK(mode)    __S_ISTYPE((mode), __S_IFBLK)
#define S_ISREG(mode)    __S_ISTYPE((mode), __S_IFREG)
#ifdef __S_IFIFO
# define S_ISFIFO(mode)  __S_ISTYPE((mode), __S_IFIFO)
#endif


#endif

#endif
