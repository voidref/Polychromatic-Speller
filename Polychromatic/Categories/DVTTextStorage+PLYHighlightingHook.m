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
<<<<<<< HEAD
    [@"initialized" writeToFile:@"/tmp/spell.out" atomically:YES encoding:NSUTF8StringEncoding error:nil];
    originalColorAtCharacterIndexImplementation = PLYPoseSwizzle([DVTTextStorage class], NSSelectorFromString(@"colorAtCharacterIndex:effectiveRange:context:"), self, @selector(ply_colorAtCharacterIndex:effectiveRange:context:), YES);
=======
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^
    {
        originalColorAtCharacterIndexImplementation = PLYPoseSwizzle([DVTTextStorage class], NSSelectorFromString(@"colorAtCharacterIndex:effectiveRange:context:"), self, @selector(ply_colorAtCharacterIndex:effectiveRange:context:), YES);
    });
>>>>>>> kolinkrewinkel/master
}

- (NSColor *)ply_colorAtCharacterIndex:(unsigned long long)index effectiveRange:(NSRangePointer)effectiveRange context:(NSDictionary *)context

{
    /* Basically, Xcode calls you a given range. It seems to start with the entirety and spiral its way inward. Once given a range, its broken down by the colorAt: method. It replaces the range pointer passed, which Xcode then applies changes, and adapts the numerical changes.  So, the next thing it asks about is whatever is just beyond whatever the replaced range is. It also takes the previous length (assuming it can fit in the total text range, at which point it defaults to the max value before subtracting), and subtracts the new range length from it to determine the next passed length.     */
    
    /* We should probably be doing the "effectiveRange" finding, but for now we'll let Xcode solve it out for us. */

<<<<<<< HEAD
    NSColor *color = originalColorAtCharacterIndexImplementation(self, @selector(colorAtCharacterIndex:effectiveRange:context:), index, effectiveRange, context);

//    if (![[Polychromatic sharedPlugin] pluginEnabled])
//    {
//        return color;
//    }

    NSRange newRange = *effectiveRange;

    DVTSourceModelItem *item = [self.sourceModelService sourceModelItemAtCharacterIndex:newRange.location];
    NSString *string = [self.sourceModelService stringForItem:item];
    [string writeToFile:@"/tmp/spell.out" atomically:YES encoding:NSUTF8StringEncoding error:nil];
    IDEIndex *workspaceIndex = context[@"IDEIndex"];
    IDEWorkspace *workspace = [workspaceIndex valueForKey:@"_workspace"];
    
    if ( item.isIdentifier ) {
        NSColor *change = [self checkSpelling:string item:item context:context];
        if ( change ) {
            return change;
        }
    }
    
    /* It's possible for us to simply use the source model, but we may want to express fine-grain control based on the node. Plus, we already have the item onhand. */
=======
    NSColor *originalColor = originalColorAtCharacterIndexImplementation(self, @selector(colorAtCharacterIndex:effectiveRange:context:), index, effectiveRange, context);

    if (![[Polychromatic sharedPlugin] pluginEnabled])
    {
        return originalColor;
    }

    NSRange newRange = *effectiveRange;

    static Class swiftLanguageServiceClass = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^
    {
        swiftLanguageServiceClass = NSClassFromString(@"IDESourceLanguageServiceSwift");
    });

    /* First account for Swift, and if it isn't, perform the normal Objective-C routine. */
    if (swiftLanguageServiceClass != nil && [self.languageService isKindOfClass:swiftLanguageServiceClass])
    {
        NSRange swiftEffectiveRange;
        long long nodeType = [self nodeTypeAtCharacterIndex:newRange.location effectiveRange:&swiftEffectiveRange context:context];

        if (nodeType == [DVTSourceNodeTypes registerNodeTypeNamed:@"xcode.syntax.identifier.variable"] ||
            nodeType == [DVTSourceNodeTypes registerNodeTypeNamed:@"xcode.syntax.identifier.constant"] ||
            nodeType == [DVTSourceNodeTypes registerNodeTypeNamed:@"xcode.syntax.identifier"])
        {
            PLYMockSwift *fauxSwiftService = (PLYMockSwift *)self.languageService;
            NSRange funcDefinitionRange = [fauxSwiftService methodDefinitionRangeAtIndex:newRange.location];

            if (funcDefinitionRange.location == NSIntegerMax)
            {
                NSArray *nameRanges;
                NSString *name = [self symbolNameAtCharacterIndex:newRange.location nameRanges:&nameRanges];
>>>>>>> kolinkrewinkel/master

                return [[PLYVariableManager sharedManager] colorForVariable:name];
            }
        }
    }
    else
    {
        DVTSourceModelItem *item = [self.sourceModelService sourceModelItemAtCharacterIndex:newRange.location];

        /* It's possible for us to simply use the source model, but we may want to express fine-grain control based on the node. Plus, we already have the item onhand. */

        BOOL isIdentifier = [item ply_isIdentifier];
        BOOL parentIsMethod = [item.parent ply_isMethod];
        BOOL inheritsFromPropertyDeclaration = [item ply_inheritsFromNodeOfType:32];

        /*
         This is relatively backwards: for some reason, explicitly defined setters and getters in @property are *not* considered methods/children of methods, whereas the property names themselves are. To combat this, the following two obscure BOOLs are used to disable the getters/setters and enable the coloring of the property var names.
         */

        /* Disallows getter/setter-attributes from being colored, as their parents are not methods but they inherit from property declarations. */
        BOOL parentIsNotMethodAndDoesNotInheritFromPropertyDeclaration = (!parentIsMethod && !inheritsFromPropertyDeclaration);

        /* Ensures property var names are colored as they are considered methods and are within property declarations. */
        BOOL parentIsMethodAndInheritsFromPropertyDeclaration = (parentIsMethod && inheritsFromPropertyDeclaration);

        if (isIdentifier &&
            (parentIsNotMethodAndDoesNotInheritFromPropertyDeclaration ||
             parentIsMethodAndInheritsFromPropertyDeclaration))
        {
            NSString *string = [self.sourceModelService stringForItem:item];

            if (string)
            {
                return [[PLYVariableManager sharedManager] colorForVariable:string];
            }
        }
    }

<<<<<<< HEAD
    int misadfasd;
    (void)misadfasd;
    return color;
=======
    return originalColor;

>>>>>>> kolinkrewinkel/master
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
