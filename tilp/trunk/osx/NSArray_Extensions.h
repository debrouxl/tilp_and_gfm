/*
 * TiLP Cocoa GUI for Mac OS X
 *
 * This code is derived from Apple Sample Code (DragNDropOutlineView)
 * Apple is not liable for anything regarding this code, according to
 * the Apple Sample Code License.
 *
 */

#import <Foundation/Foundation.h>

@interface NSArray (MyExtensions)
- (BOOL)containsObjectIdenticalTo: (id)object;
@end

@interface NSMutableArray (MyExtensions)
- (void) insertObjectsFromArray:(NSArray *)array atIndex:(int)index;
@end

