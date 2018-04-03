/* DahuaSDK.h */

#import <Cordova/CDV.h>

@interface DahuaSDK : CDVPlugin

- (void)login:(CDVInvokedUrlCommand*)command;
- (void)talk:(CDVInvokedUrlCommand*)command;
@end