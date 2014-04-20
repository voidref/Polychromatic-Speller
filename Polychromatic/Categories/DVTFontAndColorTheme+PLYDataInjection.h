//
//  DVTFontAndColorTheme+PLYDataInjection.h
//  Polychromatic
//
//  Created by Kolin Krewinkel on 4/4/14.
//  Copyright (c) 2014 Kolin Krewinkel. All rights reserved.
//

#import "DVTInterfaces.h"

@interface DVTFontAndColorTheme (PLYDataInjection)

#pragma mark - Getters

- (BOOL)ply_polychromaticEnabled;
- (CGFloat)ply_saturation;
- (CGFloat)ply_brightness;

#pragma mark - Setters

- (void)ply_setPolychromaticEnabled:(BOOL)enabled;
- (void)ply_setSaturation:(CGFloat)saturation;
- (void)ply_setBrightness:(CGFloat)brightness;

@end
