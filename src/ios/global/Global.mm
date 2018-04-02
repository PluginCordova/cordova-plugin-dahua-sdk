//
//  Global.m
//  NetSDK_Demo
//
//  Created by NetSDK on 2017/4/6.
//  Copyright © 2017年 NetSDK. All rights reserved.
//

#import "Global.h"
#import <objc/runtime.h>

const float iOSVer = [[[UIDevice currentDevice] systemVersion] floatValue];

LLONG g_loginID = 0;
int g_ChannelCount = 0;
int g_AlarmInChannel = 0;
int g_AlarmOutChannel = 0;

DHDEV_SYSTEM_ATTR_CFG g_sysAttr;
const std::string g_docFolder = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0] UTF8String];
int g_nChannel = 0;
unsigned g_nWaitTime = 3000;
unsigned g_nP2pRetry = 15;


long g_nTableRow = 0;
char fileList[32][32] = {0};
char* mobilefilename = {0};
int g_nChannelNum = 0;

NSData *g_deviceToken;
NSString *g_szIP;
int g_nPort;
NSString *g_szUser;
NSString *g_szPassword;

typedef id (*IMP_objectAtIndex)(id, SEL, NSUInteger);

static id imp_objectAtIndex(id self, SEL _cmd, NSUInteger index);

static IMP_objectAtIndex oldImpOfNSArrayObjectAtIndex = (IMP_objectAtIndex)class_replaceMethod([[NSArray new] class], @selector(objectAtIndex:), (IMP)imp_objectAtIndex, @encode(IMP_objectAtIndex));

static id imp_objectAtIndex(id self, SEL _cmd, NSUInteger index)
{
    @try {
        return oldImpOfNSArrayObjectAtIndex(self, _cmd, index);
    }
    @catch (NSException *exception) {
        @throw [NSException exceptionWithName:exception.name reason:exception.reason userInfo:@{@"NSArray": self}];
    }
}

