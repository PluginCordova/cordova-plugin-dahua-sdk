//
//  global_functions.h
//  NetSDK_Demo
//
//  Created by NetSDK on 2017/4/6.
//  Copyright © 2017年 NetSDK. All rights reserved.
//

#ifndef global_functions_h
#define global_functions_h


#include <sstream>
#include <time.h>

std::string strip_after(const std::string& str, const std::string sep);

// str.size() >= 2 && num >= 2
std::string strip_n(const std::string& str, size_t num);

//std::string str_now();


#endif /* global_functions_h */
