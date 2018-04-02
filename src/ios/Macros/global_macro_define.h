//
//  global_macro_define.h
//  NetSDK_Demo
//
//  Created by NetSDK on 2017/4/6.
//  Copyright © 2017年 NetSDK. All rights reserved.
//

#ifndef global_macro_define_h
#define global_macro_define_h

#include "global_functions.h"

#define COUNT_OF(arr) (sizeof(arr)/sizeof(arr[0]))
#define MEM_ZERO(stu) memset(&stu, 0, sizeof(stu))

#define FIRST_OF(first, ...) first
#define REST_OF(first, ...) __VA_ARGS__

#define TO_STR(a) #a

#define M_TO_STR(M) TO_STR(M)

#define PREF_FILE_LINE "[" + strip_n(strip_after(__FILE__, "/"), 24) + ": " + strip_n(M_TO_STR(__LINE__), 4) + "] "
#define __printLog(...) do { printf([[NSString stringWithFormat:[NSString stringWithUTF8String:(PREF_FILE_LINE + FIRST_OF(__VA_ARGS__) + "\n").c_str()], REST_OF(__VA_ARGS__)] UTF8String]); fflush(stdin); } while(0)
#define __printLogEx(...) NSLog([NSString stringWithUTF8String:(PREF_FILE_LINE + FIRST_OF(__VA_ARGS__) + "\n").c_str()], REST_OF(__VA_ARGS__))

#define printLog(...) __printLog(__VA_ARGS__, 1)
#define printLogEx(...) __printLogEx(__VA_ARGS__, 1)

#define _L(str) NSLocalizedString(str, nil)


#define ALERT_SYNC(...) [[[UIAlertView alloc] initWithTitle:nil message:[NSString stringWithFormat:__VA_ARGS__] delegate:nil cancelButtonTitle:_L(@"OK") otherButtonTitles:nil] show]
#define ALERT(...) dispatch_async(dispatch_get_main_queue(), ^{ ALERT_SYNC(__VA_ARGS__); })

#define ALERT_ERROR(funcName) ALERT(_L(@"%s failed"), #funcName)

#define NETSDK_ERROR(funcName) printLog("%s failed: ERROR = %d", #funcName, 0x7fffffff&CLIENT_GetLastError())

#define __NET_RUN(errHandle, func, ...)\
if (func(__VA_ARGS__)) {\
printLog("%s succeeded", #func);\
}\
else do {\
ALERT_ERROR(func);\
NETSDK_ERROR(func);\
errHandle;\
} while(0)

#define NET_RUN(func, ...) __NET_RUN(return, func, __VA_ARGS__)

#define PLAYSDK_ERROR(funcName, port) printLog("%s failed: ERROR = %d", #funcName, PLAY_GetLastError(port))

#define __PLAY_RUN(errHandle, func, ...)\
if (func(__VA_ARGS__)) {\
printLog("%s succeeded", #func);\
}\
else do {\
ALERT_ERROR(func);\
PLAYSDK_ERROR(func, FIRST_OF(__VA_ARGS__));\
errHandle;\
} while(0)

#define PLAY_RUN(func, ...) __PLAY_RUN(return, func, __VA_ARGS__)

#define CATCH_BEG(Exception, ex) \
@catch (Exception* ex) { \
NSLog(@"******** Exception caught ********\nname: %@, reason: %@, callStackSymbols: %@\nuserInfo: %@", ex.name, ex.reason, ex.callStackSymbols, ex.userInfo); \
ALERT(_L(@"An exception ocurred, demo maynot work"));
#define CATCH_END }

#define CATCH_AND_LOG CATCH_BEG(NSException, e) CATCH_END

#endif /* global_macro_define_h */
