//
//  SimpleTreeNode.h
//
//  Copyright (c) 2001 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import "TreeNode.h"

@interface SimpleNodeData : TreeNodeData {
@private
    NSString *name;
    NSString *vartype;
    NSString *varsize;
    NSImage *iconRep;
    BOOL isLeaf;
    BOOL isExpandable;
}

+ (id)leafDataWithDict:(NSDictionary *)dict;
    // Convenience method to return a leaf node with all its data set from a dict.

+ (id)leafDataWithName:(NSString*)name;
    // Convenience method to return a leaf node with its name set.
    
+ (id)groupDataWithName:(NSString*)name;
    // Convenience method to return a branch node with its name set.
    
- (void)setName:(NSString*)name;
- (NSString*)name;
    // Set and get the name.

- (void)setVartype:(NSString *)str;
- (NSString *)vartype;
    // Set and get the vartype.
    
- (void)setVarsize:(NSString *)str;
- (NSString *)varsize;
    // Set and get the varsize.

- (void)setIsLeaf:(BOOL)isLeaf;
- (BOOL)isLeaf;
- (BOOL)isGroup;
    // Set and determine the type of this item (leaf or group).

- (void)setIconRep:(NSImage*)iconRep;
- (NSImage*)iconRep;
    // Set and get the icon displayed next to the 

- (void)setIsExpandable: (BOOL)checked;
- (BOOL)isExpandable;
    // Set and get the expandability of this item.

@end

@interface SimpleTreeNode : TreeNode {
}
+ (id) treeFromDictionary:(NSDictionary*)dict;
    // This is a convenience method to return a tree root of a tree derived from an input dictionary. (see InitInfo.dict)
@end

