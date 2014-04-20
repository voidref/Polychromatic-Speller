//
//  Polychromatic.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 3/9/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "Polychromatic.h"

@interface Polychromatic()

@property (nonatomic, strong) NSBundle *bundle;

@end

@implementation Polychromatic

#pragma mark - Instantiation

+ (void)pluginDidLoad:(NSBundle *)plugin
{
    NSString *currentApplicationName = [[NSBundle mainBundle] infoDictionary][@"CFBundleName"];

    if ([currentApplicationName isEqual:@"Xcode"])
    {
        [self pluginWithBundle:plugin];
    }
}

+ (instancetype)pluginWithBundle:(NSBundle *)bundle
{
    static id sharedPlugin = nil;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^{
        sharedPlugin = [[self alloc] initWithBundle:bundle];
    });

    return sharedPlugin;
}

+ (instancetype)plugin
{
    return [self pluginWithBundle:nil];
}

- (id)initWithBundle:(NSBundle *)bundle
{
    if ((self = [super init]))
    {
        self.bundle = bundle;

        [self handleFirstRunStatus];

        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(modifyEditorMenu:) name:NSMenuDidChangeItemNotification object:nil];
    }

    return self;
}

#pragma mark - Preferences/Installation Management

- (void)handleFirstRunStatus
{
    [[NSUserDefaults standardUserDefaults] registerDefaults:@{@"PLYHasCompletedFirstRun": @NO}];

    BOOL hasCompletedFirstRun = [[NSUserDefaults standardUserDefaults] boolForKey:@"PLYHasCompletedFirstRun"];
    if (!hasCompletedFirstRun)
    {
        [self showInstallWindow:self];
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"PLYHasCompletedFirstRun"];
    }
}

- (void)showInstallWindow:(id)sender
{
    NSAlert *alert = [NSAlert alertWithMessageText:@"Polychromatic" defaultButton:@"Install Themes" alternateButton:@"Dismiss" otherButton:nil informativeTextWithFormat:@"This plugin is intended for use with monochromatic colors for all types except vibrant variables (local and instance variables, as well as properties.)\n\nTasteful sample themes are provided to demo the concept. Installing them as a basis is recommended."];

    if ([alert runModal] == 1)
    {
        __block NSError *error = nil;
        NSString *basePath = [self.bundle resourcePath];
        NSArray *themes = [[[NSFileManager defaultManager] contentsOfDirectoryAtPath:basePath error:&error] filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"self.absoluteString ENDSWITH '.dvtcolortheme'"]];

        if (error)
        {
            NSLog(@"Error in NSFileManager logic: %@", error);

            return;
        }

        NSString *destinationDirectory = [NSString stringWithFormat:@"%@/Library/Developer/Xcode/UserData/FontAndColorThemes", NSHomeDirectory()];
        [[NSFileManager defaultManager] createDirectoryAtPath:destinationDirectory withIntermediateDirectories:YES attributes:nil error:NULL];

        [themes enumerateObjectsUsingBlock:^(NSString *themePath, NSUInteger idx, BOOL *stop) {
            NSString *replacementName = [themePath.lastPathComponent stringByReplacingOccurrencesOfString:@".dvtcolortheme" withString:@" (Polychromatic).dvtcolortheme"];
            NSString *destinationPath = [NSString stringWithFormat:@"%@/%@", destinationDirectory, replacementName];

            [[NSFileManager defaultManager] copyItemAtPath:[NSString stringWithFormat:@"%@/%@", basePath, themePath] toPath:destinationPath error:nil];
        }];
    }
}

#pragma mark - (A bit of) UI Management

- (void)modifyEditorMenu:(id)sender
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSMenuItem *editorMenuItem = [[NSApp mainMenu] itemWithTitle:@"Editor"];

        if ([editorMenuItem.submenu itemWithTitle:@"Polychromatic"])
        {
            return;
        }

        NSMenu *polychromaticMenu = [[NSMenu alloc] initWithTitle:@"Polychromatic"];
        NSMenuItem *menuItem = [[NSMenuItem alloc] init];
        menuItem.title = @"Polychromatic";

        NSMenuItem *installItem = [[NSMenuItem alloc] initWithTitle:@"Install Sample Themes" action:@selector(showInstallWindow:) keyEquivalent:@"I"];
        installItem.target = self;
        [polychromaticMenu addItem:installItem];

        menuItem.submenu = polychromaticMenu;
        [editorMenuItem.submenu addItem:[NSMenuItem separatorItem]];
        [editorMenuItem.submenu addItem:menuItem];
    });
}

#pragma mark - NSMenuValidation

- (BOOL)validateMenuItem:(NSMenuItem *)menuItem
{
    return YES;
}

#pragma mark - Cleanup

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
