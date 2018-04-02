//
//  VideoWnd.m
//  netsdk_demo
//
//  Created by wu_pengzhou on 14-4-2.
//  Copyright (c) 2014年 wu_pengzhou. All rights reserved.
//

#import "VideoWnd.h"
#import <QuartzCore/QuartzCore.h>

@implementation VideoWnd

+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        self.backgroundColor = [UIColor lightGrayColor];
        
        CAEAGLLayer *eaglLayer = (CAEAGLLayer*) self.layer;
		eaglLayer.opaque = YES;
		eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:@NO, kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
    }
    
    return self;
}


// DO NOT comment this!!!
// or only the lower-left corner of frame will be drawed
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}

@end
