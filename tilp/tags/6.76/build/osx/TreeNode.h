/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2003 Julien BLACHE <jb@tilp.info>
 *
 *  $Id$
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
 
/*
 * This code is derived from Apple Sample Code (DragNDropOutlineView)
 * Apple is not liable for anything regarding this code, according to
 * the Apple Sample Code License.
 *
 */

#import <Foundation/Foundation.h>

@interface TreeNodeData : NSObject {
}
- (NSComparisonResult)compare:(TreeNodeData*)other;
- (NSString *)name;
@end

@interface TreeNode : NSObject {
@protected
    TreeNode *nodeParent;
    TreeNodeData *nodeData;
    NSMutableArray *nodeChildren;
}

+ (id)treeNodeWithData:(TreeNodeData*)data;
- (id)initWithData:(TreeNodeData*)data parent:(TreeNode*)parent children:(NSArray*)children;

- (void)setNodeData:(TreeNodeData*)data;
- (TreeNodeData*)nodeData;

- (void)setNodeParent:(TreeNode*)parent;
- (TreeNode*)nodeParent;

- (void)insertChild:(TreeNode*)child atIndex:(int)index;
- (void)insertChildren:(NSArray*)children atIndex:(int)index;
- (void)removeChild:(TreeNode*)child;
- (void)removeFromParent;

- (int)indexOfChild:(TreeNode*)child;
- (int)indexOfChildIdenticalTo:(TreeNode*)child;

- (int)numberOfChildren;
- (NSArray*)children;
- (TreeNode*)firstChild;
- (TreeNode*)lastChild;
- (TreeNode*)childAtIndex:(int)index;

- (BOOL)isDescendantOfNode:(TreeNode*)node;
    // returns YES if 'node' is an ancestor.

- (BOOL)isDescendantOfNodeInArray:(NSArray*)nodes;
    // returns YES if any 'node' in the array 'nodes' is an ancestor of ours.

- (void)recursiveSortChildren;
    // sort children using the compare: method in TreeNodeData

// Returns the minimum nodes from 'allNodes' required to cover the nodes in 'allNodes'.
// This methods returns an array containing nodes from 'allNodes' such that no node in
// the returned array has an ancestor in the returned array.
+ (NSArray *)minimumNodeCoverFromNodesInArray: (NSArray *)allNodes;

@end
