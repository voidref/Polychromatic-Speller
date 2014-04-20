//
//  IDEFontAndColorPrefsPaneController+PLYPrefsPaneHook.m
//  Polychromatic
//
//  Created by Kolin Krewinkel on 4/3/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "IDEFontAndColorPrefsPaneController+PLYPrefsPaneHook.h"

#import "Polychromatic.h"
#import "PLYSwizzling.h"
#import "PLYView.h"
#import "DVTFontAndColorTheme+PLYDataInjection.h"

static IMP originalViewLoadImp;
static IMP originalTabChangeImp;
static IMP originalFontPickerImp;

static char *PLYVariableColorModifierViewIdentifier = "PLYVariableColorModifierViewIdentifier";

@implementation IDEFontAndColorPrefsPaneController (PLYPrefsPaneHook)

#pragma mark - Swizzling

+ (void)load
{
    originalViewLoadImp = PLYSwizzleMethod([IDEFontAndColorPrefsPaneController class], @selector(loadView), self, @selector(ply_loadView), YES);
    originalTabChangeImp = PLYSwizzleMethod([IDEFontAndColorPrefsPaneController class], @selector(_handleTabChanged), self, @selector(ply_handleTabChanged), YES);
    originalFontPickerImp = PLYSwizzleMethod(self, @selector(_updateFontPickerAndColorWell), self, @selector(ply_updateFontPickerAndColorWell), YES);
}

#pragma mark - View Methods

- (void)ply_loadView
{
    // Load the original view.
    originalViewLoadImp(self, @selector(loadView));

    [self ply_configureTabChooserView];
    [self setupVariablesPane];
}

- (void)ply_configureTabChooserView
{
    // This is the view that acts as a tab/replacement view.
    DVTTabChooserView *tabChooser = [self ply_tabChooserView];

    if (tabChooser.choices.count == 3)
    {
        return;
    }

    // Customize the choices in two stages:
    // First, add the variables object (for changing saturation and brightness and whatnot)
    // Change the original "Source Editor" one to be more descriptive.

    NSMutableArray *choices = [[NSMutableArray alloc] initWithArray:tabChooser.choices];
    [choices addObject:[[DVTChoice alloc] initWithTitle:@"Variables" toolTip:@"Variables" image:nil representedObject:nil]];

    DVTChoice *sourceCodeEditorChoice = choices[0];
    [sourceCodeEditorChoice setValue:@"Types" forKey:@"title"];

    DVTChoice *consoleChoice = choices[1];
    [consoleChoice setValue:@"LLDB" forKey:@"title"];

    tabChooser.choices = choices;
}

- (void)ply_updateFontPickerAndColorWell
{
    originalFontPickerImp(self, @selector(_updateFontPickerAndColorWell));

    [self enabledSwitch].state = [[self theme] ply_polychromaticEnabled];
    [self ply_setEnabled:[[self theme] ply_polychromaticEnabled]];

    [self saturationSlider].floatValue = [[self theme] ply_saturation];
    [self ply_setSaturation:[[self theme] ply_saturation]];

    [self brightnessSlider].floatValue = [[self theme] ply_brightness];
    [self ply_setBrightness:[[self theme] ply_brightness]];

    if ([self ply_varPrefsView].superview)
    {
        [self adjustColorWellSamples];
        [self adjustControlsToEnabledState];
    }
}

- (void)setupVariablesPane
{
    PLYView *variablePrefsView = [[PLYView alloc] initWithFrame:CGRectMake(0.f, 0.f, [self ply_fontAndColorItemTable].frame.size.width, 305.f)];
    [variablePrefsView setAutoresizingMask:NSViewHeightSizable];

    NSButton *polychromaticSwitch = [[NSButton alloc] initWithFrame:NSMakeRect(40.f, 29.f, 250.f, 20.f)];
    [polychromaticSwitch setButtonType:NSSwitchButton];
    [polychromaticSwitch setTarget:self];
    [polychromaticSwitch setAction:@selector(enabledChanged:)];
    polychromaticSwitch.title = @"Highlight variables dynamically";
    [variablePrefsView addSubview:polychromaticSwitch];
    [self ply_setEnabledSwitch:polychromaticSwitch];

    NSTextField *saturationLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(40.f, 70.f, 80.f, 20.f)];
    [saturationLabel setEditable:NO];
    [saturationLabel setBezeled:NO];
    [saturationLabel setSelectable:NO];
    saturationLabel.stringValue = @"Saturation:";
    saturationLabel.wantsLayer = YES;
    [variablePrefsView addSubview:saturationLabel];

    NSSlider *saturationSlider = [[NSSlider alloc] initWithFrame:NSMakeRect(115.f, 67.f, variablePrefsView.frame.size.width - (115.f * 2.f), 30.f)];
    [saturationSlider setAction:@selector(saturationChanged:)];
    [saturationSlider setTarget:self];
    saturationSlider.numberOfTickMarks = 2;
    saturationSlider.maxValue = 1;
    [variablePrefsView addSubview:saturationSlider];
    [self ply_setSaturationSlider:saturationSlider];

    NSTextField *brightnessLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(40.f, 110.f, 80.f, 20.f)];
    [brightnessLabel setEditable:NO];
    [brightnessLabel setBezeled:NO];
    [brightnessLabel setSelectable:NO];
    brightnessLabel.stringValue = @"Brightness:";
    brightnessLabel.wantsLayer = YES;
    [variablePrefsView addSubview:brightnessLabel];

    NSSlider *brightnessSlider = [[NSSlider alloc] initWithFrame:NSMakeRect(115.f, 107.f, variablePrefsView.frame.size.width - (115.f * 2.f), 30.f)];
    [brightnessSlider setAction:@selector(brightnessChanged:)];
    [brightnessSlider setTarget:self];
    brightnessSlider.numberOfTickMarks = 2;
    brightnessSlider.maxValue = 1;
    [variablePrefsView addSubview:brightnessSlider];
    [self ply_setBrightnessSlider:brightnessSlider];

    NSTextField *descriptionLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(40.f, 155.f, 400.f, 160.f)];
    [descriptionLabel setEditable:NO];
    [descriptionLabel setBezeled:NO];
    [descriptionLabel setSelectable:NO];
    descriptionLabel.font = [NSFont systemFontOfSize:[NSFont smallSystemFontSize]];
    descriptionLabel.textColor = [NSColor darkGrayColor];
    descriptionLabel.stringValue = @"Local variables, properties, and ivars, as well as statics and arguments, are colored.\n\nThey are dynamically assigned a color by adding them to a sorted set, essentially giving them a position on the spectrum; to maintain consistency, saturation and brightness levels are constant.";
    [variablePrefsView addSubview:descriptionLabel];

    [self ply_setVarPrefsView:variablePrefsView];

    [self _updateFontPickerAndColorWell];
}

- (void)ply_handleTabChanged
{
    if ([[self ply_tabChooserView].choices indexOfObject:[self ply_tabChooserView].selectedChoice] < 2)
    {
        [self setVariablePrefsViewHidden:YES];
        originalTabChangeImp(self, @selector(_handleTabChanged));

        return;
    }

    [self setVariablePrefsViewHidden:NO];
}

- (void)setVariablePrefsViewHidden:(BOOL)hidden
{
    // Hide the font/color list view
    NSTableView *fontsTableView = [self ply_fontAndColorItemTable];

    if (hidden && !fontsTableView.superview)
    {
        for (NSColorWell *colorWell in [self colorWells])
        {
            [self restoreColorWell:colorWell];
        }

        NSScrollView *scrollView = (NSScrollView *)[self ply_varPrefsView].superview.superview;
        scrollView.documentView = fontsTableView;
    }
    else if (!hidden && fontsTableView.superview)
    {
        NSScrollView *scrollView = (NSScrollView *)fontsTableView.superview.superview;
        scrollView.documentView = [self ply_varPrefsView];

        for (NSColorWell *colorWell in [self colorWells])
        {
            [self preserveColorWell:colorWell];
        }

        [self adjustColorWellSamples];
        [self adjustControlsToEnabledState];
    }
}

#pragma mark - View Utilities

- (void)addSubviewsOfView:(NSView *)view withClass:(Class)class inArray:(NSMutableArray *)array excludingView:(NSView *)excludingView
{
    if (view == excludingView)
    {
        return;
    }

    for (NSView *subview in view.subviews)
    {
        if ([subview isKindOfClass:class])
        {
            [array addObject:subview];
        }

        [self addSubviewsOfView:subview withClass:class inArray:array excludingView:excludingView];
    }
}

#pragma mark - Color Well Management

- (NSArray *)colorWells
{
    NSMutableArray *colorWells = [[NSMutableArray alloc] init];
    [self addSubviewsOfView:self.view withClass:[NSColorWell class] inArray:colorWells excludingView:[self ply_varPrefsView].superview.superview.superview];

    return colorWells;
}

- (void)adjustColorWellSamples
{
    NSArray *colorWells = [self colorWells];

    NSUInteger index = 0;
    for (NSColorWell *colorWell in colorWells)
    {
        CGFloat hue = (CGFloat)index/colorWells.count;
        [colorWell setColor:[NSColor colorWithCalibratedHue:hue saturation:self.ply_Saturation brightness:self.ply_Brightness alpha:1.f]];

        index++;

        NSView *superview = colorWell.superview;
        NSTextField *label = [superview.subviews lastObject];
        label.stringValue = [NSString stringWithFormat:@"Sample %lu", index];
    }

    dispatch_async(dispatch_get_main_queue(), ^{
        [[Polychromatic plugin] refreshAllWindows];
    });
}

- (void)preserveColorWell:(NSColorWell *)colorWell
{
    NSView *superview = colorWell.superview;
    NSTextField *label = [superview.subviews lastObject];

    [colorWell setEnabled:NO];

    objc_setAssociatedObject(colorWell, "ply_prevColor", colorWell.color, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
    objc_setAssociatedObject(colorWell, "ply_prevTitle", label.stringValue, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

- (void)restoreColorWell:(NSColorWell *)colorWell
{
    NSView *superview = colorWell.superview;
    NSTextField *label = [superview.subviews lastObject];

    colorWell.color = objc_getAssociatedObject(colorWell, "ply_prevColor");
    label.stringValue = objc_getAssociatedObject(colorWell, "ply_prevTitle");

    objc_setAssociatedObject(colorWell, "ply_prevColor", nil, OBJC_ASSOCIATION_ASSIGN);
    objc_setAssociatedObject(colorWell, "ply_prevTitle", nil, OBJC_ASSOCIATION_ASSIGN);

    [colorWell setEnabled:YES];
}

#pragma mark - State

- (void)adjustControlsToEnabledState
{
    [[self brightnessSlider] setEnabled:[self ply_Enabled]];
    [[self saturationSlider] setEnabled:[self ply_Enabled]];
}

- (void)enabledChanged:(NSButton *)button
{
    BOOL enabled = (button.state ? YES : NO);

    [self ply_setEnabled:enabled];

    [[self theme] ply_setPolychromaticEnabled:enabled];
    [self theme].contentNeedsSaving = YES;

    [self adjustControlsToEnabledState];

    [[Polychromatic plugin] refreshAllWindows];
}

- (void)saturationChanged:(NSSlider *)slider
{
    [self ply_setSaturation:slider.floatValue];

    [[self theme] ply_setSaturation:slider.floatValue];
    [self theme].contentNeedsSaving = YES;
    
    [self adjustColorWellSamples];
}

- (void)brightnessChanged:(NSSlider *)slider
{
    [self ply_setBrightness:slider.floatValue];

    [[self theme] ply_setBrightness:slider.floatValue];
    [self theme].contentNeedsSaving = YES;

    [self adjustColorWellSamples];
}

#pragma mark - Convenience

- (DVTTabChooserView *)ply_tabChooserView
{
    return [self valueForKey:@"_tabChooserView"];
}

- (DVTFontAndColorTheme *)theme
{
    return [[self valueForKey:@"_currentThemeObjectController"] content];
}

- (NSTableView *)ply_fontAndColorItemTable
{
    return [self valueForKey:@"_fontAndColorItemTable"];
}

#pragma mark - Associated Object Getters

- (PLYView *)ply_varPrefsView
{
    return objc_getAssociatedObject(self, PLYVariableColorModifierViewIdentifier);
}

- (BOOL)ply_Enabled
{
    return [objc_getAssociatedObject(self, "ply_Enabled") boolValue];
}

- (CGFloat)ply_Saturation
{
    return [objc_getAssociatedObject(self, "ply_Saturation") floatValue];
}

- (CGFloat)ply_Brightness
{
    return [objc_getAssociatedObject(self, "ply_Brightness") floatValue];
}

- (NSButton *)enabledSwitch;
{
    return objc_getAssociatedObject(self, "ply_enabledSwitch");
}

- (NSSlider *)saturationSlider
{
    return objc_getAssociatedObject(self, "ply_saturationSlider");
}

- (NSSlider *)brightnessSlider
{
    return objc_getAssociatedObject(self, "ply_brightnessSlider");
}

#pragma mark - Associated Object Setters

- (void)ply_setVarPrefsView:(PLYView *)varPrefsView
{
    objc_setAssociatedObject(self, PLYVariableColorModifierViewIdentifier, varPrefsView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)ply_setEnabled:(BOOL)enabled
{
    objc_setAssociatedObject(self, "ply_Enabled", @(enabled), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)ply_setSaturation:(CGFloat)saturation
{
    objc_setAssociatedObject(self, "ply_Saturation", @(saturation), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)ply_setBrightness:(CGFloat)brightness
{
    objc_setAssociatedObject(self, "ply_Brightness", @(brightness), OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)ply_setEnabledSwitch:(NSButton *)enabledSwitch
{
    objc_setAssociatedObject(self, "ply_enabledSwitch", enabledSwitch, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)ply_setSaturationSlider:(NSSlider *)slider
{
    objc_setAssociatedObject(self, "ply_saturationSlider", slider, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)ply_setBrightnessSlider:(NSSlider *)slider
{
    objc_setAssociatedObject(self, "ply_brightnessSlider", slider, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

@end
