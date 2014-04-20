//
//  DVTSourceModelItem+PLYIdentification.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/11/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTSourceModelItem+PLYIdentification.h"

@implementation DVTSourceModelItem (PLYIdentification)

#pragma mark - Convenience Node Type Methods

- (BOOL)ply_isIdentifier
{
    // 24 = Local Vars/Arguments
    // 16 = Ivars and Properties
    // 17 = Instances of Macros
    // 49 = Macro Definitions
    
    return (self.nodeType == 24) || (self.nodeType == 16) || (self.nodeType == 17) || (self.nodeType == 49);
}

@end
