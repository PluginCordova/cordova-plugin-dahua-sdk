//
//  Global.h
//  NetSDK_Demo
//
//  Created by NetSDK on 2017/4/6.
//  Copyright © 2017年 NetSDK. All rights reserved.
//

#ifndef Global_h
#define Global_h

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <assert.h>
#import <string>
#import "global_macro_define.h"
#import "global_functions.h"
#import "netsdk.h"
#import "configsdk.h"
#import "playEx.h"


extern const float iOSVer;
extern LLONG g_loginID;
extern int g_ChannelCount;
extern int g_AlarmInChannel;
extern int g_AlarmOutChannel;
extern DHDEV_SYSTEM_ATTR_CFG g_sysAttr;
extern const std::string g_docFolder;
extern int g_nChannel;
extern unsigned g_nWaitTime;
extern unsigned g_nP2pRetry;

extern long g_nTableRow;
extern char fileList[32][32];
extern char *mobilefilename;
extern int g_nChannelNum;

extern NSData *g_deviceToken;
extern NSString *g_szIP;
extern int g_nPort;
extern NSString *g_szUser;
extern NSString *g_szPassword;




#endif /* Global_h */
