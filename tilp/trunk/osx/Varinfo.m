/*
 * TiLP Cocoa GUI for Mac OS X
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
