/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001 Julien BLACHE <jb@technologeek.org>
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
  
#include <stdlib.h>

#include "../src/struct.h"
 
#import "Varinfo.h"

@implementation Varinfo

- (id)init
{
    self = [super init];
    
    if (self == nil)
        return nil;

    varinfo = NULL;
    
    varinfo = (struct varinfo *)malloc(sizeof(struct varinfo));
    
    if (varinfo == NULL)
        return nil;

    return self;
}

- (id)initWithPointer:(struct varinfo *)ptr
{
    self = [super init];
    
    if (self == nil)
        return nil;

    varinfo = NULL;
    
    varinfo = (struct varinfo *)malloc(sizeof(struct varinfo));
    
    if (varinfo == NULL)
        return nil;

    memcpy(varinfo, ptr, sizeof(struct varinfo));

    return self;

}

- (void)dealloc
{
    if (varinfo != NULL)
        {
            free(varinfo);
        }
    
    [super dealloc];
}

- (void)setVarinfo:(struct varinfo *)ptr
{
    if (varinfo != NULL)
        free(varinfo);
        
        varinfo = NULL;
    
    varinfo = (struct varinfo *)malloc(sizeof(struct varinfo));
    
    if (varinfo == NULL)
        return;

    memcpy(varinfo, ptr, sizeof(struct varinfo));
}

- (struct varinfo *)varinfo
{
    return varinfo;
}

@end
