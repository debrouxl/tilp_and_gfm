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

/* This code is derived from Apple Sample Code (DragNDropOutlineView)
 * Apple is not liable for anything regarding this code, according to
 * the Apple Sample Code License.
 *
 */

#import "TreeNode.h"
#import "SimpleTreeNode.h"

#define KEY_GROUPNAME	@"Group"
#define KEY_ENTRIES	@"Entries"

@implementation SimpleNodeData

- (id)initWithName:(NSString*)str isLeaf:(BOOL)leaf {
    self = [super init];
    if (self==nil) return nil;
    name = [str retain];
    isLeaf = leaf;
    iconRep = nil;
    attribute = nil;
    vartype = nil;
    varsize = nil;
    isExpandable = !isLeaf;
    
    return self;
}

// the dataNode holds all the infos about a variable
// this includes : image, varname, vartype, varsize

+ (id)leafDataWithDict:(NSDictionary *)dict
{
    SimpleNodeData *myNode;
    
    myNode = [[SimpleNodeData alloc] init];
    
    [myNode setName:[dict objectForKey:@"Varname"]];
    [myNode setIconRep:[dict objectForKey:@"Image"]];
    [myNode setAttribute:[dict objectForKey:@"Attribute"]];
    [myNode setVartype:[dict objectForKey:@"Vartype"]];
    [myNode setVarsize:[dict objectForKey:@"Varsize"]];
    [myNode setVarinfo:[dict objectForKey:@"varinfo"]];
    [myNode setIsLeaf:YES];
    
    [myNode autorelease];
    
    return myNode;
}

+ (id)leafDataWithName:(NSString*)str {
    // Convenience method to return a leaf node with its name set.
    return [[[SimpleNodeData alloc] initWithName:str isLeaf:YES] autorelease];
}

+ (id)groupDataWithName:(NSString*)str {
    // Convenience method to return a branch node with its name set.
    return [[[SimpleNodeData alloc] initWithName:str isLeaf:NO] autorelease];
}

- (void)dealloc {
    [name release];
    [iconRep release];
    name = nil;
    iconRep = nil;
    
    if (vartype != nil)
        [vartype release];
        
    if (varsize != nil)
        [varsize release];
        
    vartype = nil;
    varsize = nil;
    
    if (attribute != nil)
        [attribute release];
    
    attribute = nil;
    
    if (varinfo != nil)
        [varinfo release];
        
    varinfo = nil;   
    
    [super dealloc];
}

- (void)setName:(NSString *)str { 
    if (!name || ![name isEqualToString: str]) {
	[name release]; 
	name = [str retain]; 
    }
}

- (NSString*)name { 
    return name; 
}

- (void)setVartype:(NSString *)str
{
    if (!vartype || ![vartype isEqualToString:str])
        {
            [vartype release];
            vartype = [str retain];
        }
}

- (NSString *)vartype
{
    return vartype;
}

- (void)setVarsize:(NSString *)str
{
    if (!varsize || ![varsize isEqualToString:str])
        {
            [varsize release];
            varsize = [str retain];
        }
}

- (NSString *)varsize
{
    return varsize;
}

- (void)setVarinfo:(Varinfo *)data
{
    if (!varinfo)
        {
            [varinfo release];
            varinfo = [data retain];
        }
}

- (Varinfo *)varinfo
{
    return varinfo;
}

- (void)setIsLeaf:(BOOL)leaf { 
    isLeaf = leaf; 
}

- (BOOL)isLeaf { 
    return isLeaf; 
}

- (BOOL)isGroup { 
    return !isLeaf; 
}

- (void)setIconRep:(NSImage*)ir {
    if (!iconRep || ![iconRep isEqual: ir]) {
	[iconRep release];
	iconRep = [ir retain];
    }
}
- (NSImage*)iconRep {
    return iconRep;
}

- (void)setAttribute:(NSImage*)attr
{
    if (!attribute || ![attribute isEqual: attr]) {
	[attribute release];
	attribute = [attr retain];
    }
}
- (NSImage*)attribute
{
    return attribute;
}

- (void)setIsExpandable: (BOOL)expandable {
    isExpandable = expandable;
}

- (BOOL)isExpandable {
    return isExpandable;
}

- (NSString*)description { 
    return name; 
}

- (NSComparisonResult)compare:(TreeNodeData*)other {
    // We want the data to be sorted by name, so we compare [self name] to [other name]
    TreeNodeData *_other = other;
    return [name compare: [_other name]];
}

@end

@implementation SimpleTreeNode

- (id) initFromDictionary:(NSDictionary*)dict {
    // This is a convenience init method to return a tree root of a tree derived from an input dictionary.
    // The input dictionary for this example app is InitInfo.dict.  Look at that file to understand the format.
    SimpleNodeData *data = [SimpleNodeData groupDataWithName: [dict objectForKey: KEY_GROUPNAME]];
    NSEnumerator *entryEnum = [[dict objectForKey: KEY_ENTRIES] objectEnumerator];
    id entry;
    SimpleTreeNode *child = nil;
    
    self = [super initWithData:data parent:nil children:[NSArray array]];
    if (self==nil) return nil;
    
    while ((entry=[entryEnum nextObject])) {
        if ([entry isKindOfClass: [NSDictionary class]])
            {
                if (nil == [entry objectForKey:@"Varname"]) // it's _NOT_ a variable
                    child = [SimpleTreeNode treeFromDictionary: entry];
                else // it's a variable, do something with it :P
                    child = [[[SimpleTreeNode alloc] initWithData:[SimpleNodeData leafDataWithDict:entry] parent:nil children:[NSArray array]] autorelease];
            }
        else 
            child = [[[SimpleTreeNode alloc] initWithData:[SimpleNodeData leafDataWithName:entry] parent:nil children: [NSArray array]] autorelease];
        [self insertChild: child atIndex: [self numberOfChildren]];
    }
    
    return self;
}

+ (id) treeFromDictionary:(NSDictionary*)dict {
    return [[[SimpleTreeNode alloc] initFromDictionary:dict] autorelease];
}

@end

