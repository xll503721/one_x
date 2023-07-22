//
//  Error.cc
//  OneTenSDK
//
//  Created by li zhixuan on 2023/3/30.
//

#include "error.h"

BEGIN_NAMESPACE_ONETEN

Error::Error(int32_t code, const std::string& msg, std::map<std::string, std::string>& user_info):
code_(code),
msg_(msg),
user_info_(user_info)
{
    
}

END_NAMESPACE_ONETEN
