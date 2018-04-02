//
//  Macro.h
//  NetSDK_Demo
//
//  Created by NetSDK on 2017/4/5.
//  Copyright © 2017年 NetSDK. All rights reserved.
//

#ifndef Macro_h
#define Macro_h

//MARK: - 屏幕尺寸
#define kScreenWidth            [UIScreen mainScreen].bounds.size.width
#define kScreenHeight           [UIScreen mainScreen].bounds.size.height
#define kScreenBounds           [UIScreen mainScreen].bounds
#define kStatusBarHeight        [[UIApplication sharedApplication] statusBarFrame].size.height

//MARK: -
#define kUserDefaults           [NSUserDefaults standardUserDefaults]
#define kApplication            [UIApplication sharedApplication]
#define kNotificationCenter     [NSNotificationCenter defaultCenter]

//MARK: - color
#define BUTTON_COLOR [UIColor colorWithRed:0.333 green:0.784 blue:1 alpha:1]
#define BASE_COLOR [UIColor colorWithRed:104/255.0 green:187/255.0 blue:30/255.0 alpha:1]
#define BASE_BACKGROUND_COLOR [UIColor colorWithRed:236/255.0 green:236/255.0 blue:244/255.0 alpha:1]
#define UIColorFromRGB(rgbValue)                                   \
[UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
                green:((float)((rgbValue & 0xFF00) >> 8))/255.0    \
                 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]  \

#define kRGBA(r, g, b, a)                                          \
[UIColor colorWithRed:r/255.0                                      \
                green:g/255.0                                      \
                 blue:b/255.0 alpha:a]                             \

#define kRGB(r, g, b) kRGBA(r, g, b, 1)


//MARK: - weakify strongify
#ifndef weakify
    #if DEBUG
        #if __has_feature(objc_arc)
            #define weakify(object) autoreleasepool{} __weak __typeof__(object) weak##_##object = object;
        #else
            #define weakify(object) autoreleasepool{} __block __typeof__(object) block##_##object = object;
        #endif
    #else
        #if __has_feature(objc_arc)
            #define weakify(object) try{} @finally{} {} __weak __typeof__(object) weak##_##object = object;
        #else
        #define weakify(object) try{} @finally{} {} __block __typeof__(object) block##_##object = object;
        #endif
    #endif
#endif

#ifndef strongify
    #if DEBUG
        #if __has_feature(objc_arc)
            #define strongify(object) autoreleasepool{} __typeof__(object) object = weak##_##object;
        #else
            #define strongify(object) autoreleasepool{} __typeof__(object)  object = block##_##object;
        #endif
    #else
        #if __has_feature(objc_arc)
            #define strongify(object) try{} @finally{} __typeof__(object) object = weak##_##object;
        #else
            #define strongify(object) try{} @finally{} __typeof__(object) object = block##_##object;
        #endif
    #endif
#endif

#endif /* Macro_h */
