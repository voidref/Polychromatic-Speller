//
//  DVTTextStorage+PLYHighlightingHook.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/10/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTTextStorage+PLYHighlightingHook.h"

#import "Polychromatic.h"
#import "PLYSwizzling.h"
#import "PLYVariableManager.h"
#import "DVTSourceModelItem+PLYIdentification.h"

static IMP originalColorAtCharacterIndexImplementation;

@implementation DVTTextStorage (PLYHighlightingHook)

+ (void)initialize
{
    originalColorAtCharacterIndexImplementation = PLYPoseSwizzle([DVTTextStorage class], NSSelectorFromString(@"colorAtCharacterIndex:effectiveRange:context:"), self, @selector(ply_colorAtCharacterIndex:effectiveRange:context:), YES);
}

- (NSColor *)ply_colorAtCharacterIndex:(unsigned long long)index effectiveRange:(NSRangePointer)effectiveRange context:(NSDictionary *)context
{
    /* Basically, Xcode calls you a given range. It seems to start with the entirety and spiral its way inward. Once given a range, its broken down by the colorAt: method. It replaces the range pointer passed, which Xcode then applies changes, and adapts the numerical changes.  So, the next thing it asks about is whatever is just beyond whatever the replaced range is. It also takes the previous length (assuming it can fit in the total text range, at which point it defaults to the max value before subtracting), and subtracts the new range length from it to determine the next passed length.     */

    /* We should probably be doing the "effectiveRange" finding, but for now we'll let Xcode solve it out for us. */

    if (![[Polychromatic sharedPlugin] pluginEnabled])
    {
        return originalColorAtCharacterIndexImplementation(self, @selector(colorAtCharacterIndex:effectiveRange:context:), index, effectiveRange, context);
    }

    NSColor *color = originalColorAtCharacterIndexImplementation(self, @selector(colorAtCharacterIndex:effectiveRange:context:), index, effectiveRange, context);
    NSRange newRange = *effectiveRange;

    DVTSourceModelItem *item = [self.sourceModelService sourceModelItemAtCharacterIndex:newRange.location];
    NSString *string = [self.sourceModelService stringForItem:item];

    IDEIndex *workspaceIndex = context[@"IDEIndex"];
    IDEWorkspace *workspace = [workspaceIndex valueForKey:@"_workspace"];
    
    if ( item.isIdentifier ) {
        NSColor *change = [self checkSpelling:string item:item context:context];
        if ( change ) {
            return change;
        }
    }
    
    /* It's possible for us to simply use the source model, but we may want to express fine-grain control based on the node. Plus, we already have the item onhand. */

    if ([item ply_isIdentifier] && ![[DVTSourceNodeTypes nodeTypeNameForId:item.parent.nodeType] isEqualToString:@"xcode.syntax.name.partial"] && workspaceIndex)
    {
        color = [[PLYVariableManager sharedManager] colorForVariable:string inWorkspace:workspace];
    }

    return color;
}


- (NSColor *)checkSpelling:(NSString *)string item:(DVTSourceModelItem *)item context:(NSDictionary *)context {

    static NSMutableOrderedSet *spelledCorrectly = nil;
    static NSMutableOrderedSet *knownMisspellings = nil;
    
    // flush the misspellings cache every so often
    if ( knownMisspellings && knownMisspellings.count > 1024 ) {
        knownMisspellings = nil;
    }
    
    if ( !knownMisspellings ) {
        knownMisspellings = [NSMutableOrderedSet orderedSet];
    }
    
    if ( !spelledCorrectly ) {
        spelledCorrectly = [NSMutableOrderedSet orderedSet];
    }

    if ( [spelledCorrectly containsObject:string] ) {
        return nil;
    }
    
    if ( [knownMisspellings containsObject:string] ) {
        return NSColor.whiteColor;
    }
    
    NSColor *errorColor = nil;
    NSSpellChecker *checker = [NSSpellChecker sharedSpellChecker];
    NSRange spellRange = [checker checkSpellingOfString:string startingAt:0];
    
    BOOL spelledWrong = spellRange.length > 0;

    if ( spelledWrong ) {
        
        // SpellChecker seems to have a problem with the number of words in a camel case string.
        NSArray *split = [self splitCamelHalves:string];
        
        if ( split.count == 2 ) {
            NSRange firstHalf = [checker checkSpellingOfString:split.firstObject startingAt:0];
            
            if ( firstHalf.length == 0 ) {
                NSRange secondHalf = [checker checkSpellingOfString:split.lastObject startingAt:0];
                
                if ( secondHalf.length == 0 ) {
                    spelledWrong = NO;
                }
            }
        }
    }
    
    if ( spelledWrong ) {
        errorColor = NSColor.whiteColor;
        [knownMisspellings addObject:string];
    } else {
        [spelledCorrectly addObject:string];
    }
    
    return errorColor;
}

- (NSArray *)splitCamelHalves:(NSString *)identifier {
    NSRange firstHalf = NSMakeRange(0, identifier.length / 2);
    NSRange lastHalf = NSMakeRange(firstHalf.length, identifier.length - firstHalf.length);
    
    NSRange split = [identifier rangeOfCharacterFromSet:[NSCharacterSet uppercaseLetterCharacterSet] options:0 range:lastHalf];
    
    if ( split.length == 0 ) {
        return nil;
    }
    firstHalf.length = split.location;
    lastHalf.location = split.location;
    lastHalf.length = identifier.length - firstHalf.length;
    
    return @[ [identifier substringWithRange:firstHalf], [identifier substringWithRange:lastHalf] ];
}

@end
