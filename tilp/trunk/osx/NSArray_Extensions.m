/*
 * TiLP Cocoa GUI for Mac OS X
 *
 * This code is derived from Apple Sample Code (DragNDropOutlineView)
 * Apple is not liable for anything regarding this code, according to
 * the Apple Sample Code License.
 *
 */
 
#import "NSArray_Extensions.h"


@implementation NSArray (MyExtensions)

- (BOOL) containsObjectIdenticalTo: (id)obj { 
    return [self indexOfObjectIdenticalTo: obj]!=NSNotFound; 
}

@end

@implementation NSMutableArray (MyExtensions)

- (void) insertObjectsFromArray:(NSArray *)array atIndex:(int)index {
    NSObject *entry = nil;
    NSEnumerator *enumerator = [array objectEnumerator];
    while ((entry=[enumerator nextObject])) {
        [self insertObject:entry atIndex:index++];
    }
}

@end
