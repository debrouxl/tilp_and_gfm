/*
 * TiLP Cocoa GUI for Mac OS X
 *
 * This code is derived from Apple Sample Code (DragNDropOutlineView)
 * Apple is not liable for anything regarding this code, according to
 * the Apple Sample Code License.
 *
 */

#import <Cocoa/Cocoa.h>

@interface ImageAndTextCell : NSTextFieldCell {
@private
    NSImage	*image;
}

- (void)setImage:(NSImage *)anImage;
- (NSImage *)image;

- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;
- (NSSize)cellSize;

@end