/*
 Licensed to the Apache Software Foundation (ASF) under one
 or more contributor license agreements.  See the NOTICE file
 distributed with this work for additional information
 regarding copyright ownership.  The ASF licenses this file
 to you under the Apache License, Version 2.0 (the
 "License"); you may not use this file except in compliance
 with the License.  You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing,
 software distributed under the License is distributed on an
 "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND, either express or implied.  See the License for the
 specific language governing permissions and limitations
 under the License.
 */

//
//  AppDelegate.m
//  helloDahua
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//  Copyright ___ORGANIZATIONNAME___ ___YEAR___. All rights reserved.
//

#import "AppDelegate.h"
#import "MainViewController.h"

#import "global_macro_define.h"
#import "Global.h"

@implementation AppDelegate

void cbDisConnect(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    // save C-string to NSString to get the GCD capture mechanism working correctly
    NSString* ip = [[NSString alloc] initWithUTF8String:pchDVRIP];
    ALERT(_L(@"Device %@ disconnected, please re-login"), ip);
    //    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"提示" message:@"Device disconnected" preferredStyle:UIAlertControllerStyleAlert];
    //    [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
    
    //    [self.window.rootViewController presentViewController:alert animated:YES completion:nil];
    //    [[[UIAlertView alloc] initWithTitle:nil message:[NSString stringWithFormat:__VA_ARGS__] delegate:nil cancelButtonTitle:_L(@"OK") otherButtonTitles:nil] show]
}

- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{
    self.viewController = [[MainViewController alloc] init];
    
    if (!CLIENT_Init(cbDisConnect, NULL)) {
        ALERT_ERROR(CLIENT_Init);
        return FALSE;
    }
    NSLog(@"CLIENT_GetSDKVersion() = %u", CLIENT_GetSDKVersion());
    //    CLIENT_SetAutoReconnect(cbhaveReConnect, 0);
    
    NET_PARAM netParam = {5000, 3000, 3, 100};
    CLIENT_SetNetworkParam(&netParam);
    
    
    return [super application:application didFinishLaunchingWithOptions:launchOptions];
    
    
}
@end
