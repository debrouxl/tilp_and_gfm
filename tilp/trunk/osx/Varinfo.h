/*
 * TiLP Cocoa GUI for Mac OS X
 */

#include "../src/struct.h"

#import <Foundation/Foundation.h>

@interface Varinfo : NSObject
{
    struct varinfo *varinfo;
}

- (id)initWithPointer:(struct varinfo *)ptr;

- (void)setVarinfo:(struct varinfo *)ptr;
- (struct varinfo *)varinfo;

@end
