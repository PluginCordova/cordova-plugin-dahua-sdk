//
//  global_functions.cpp
//  NetSDK_Demo
//
//  Created by NetSDK on 2017/4/6.
//  Copyright © 2017年 NetSDK. All rights reserved.
//

#include "global_functions.h"

std::string strip_after(const std::string& str, const std::string sep)
{
    // npos + 1 == 0 under 2's complement representation
    // which is also what we want
    return str.substr(str.find_last_of(sep) + 1);
}

std::string strip_n(const std::string& str, size_t num)
{
    const auto size = str.size();
    if (size > num) {
        return str.substr(0, num - 2) + "..";
    }
    else {
        return str + std::string(num - size, ' ');
    }
}

#if 0
std::string str_now()
{
    time_t t;
    time(&t);
    tm* stTime = localtime(&t);
    
    std::ostringstream oss;
    
    oss.width(2);
    oss.fill('0');
    oss << stTime->tm_year + 1900 << stTime->tm_mon+1 << stTime->tm_mday <<"_"<< stTime->tm_hour << stTime->tm_min << stTime->tm_sec ;
    
    return oss.str();
}
#endif

