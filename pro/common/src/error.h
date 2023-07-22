//
//  Error.h
//  OneTenSDK
//
//  Created by li zhixuan on 2023/3/30.
//

#ifndef ONETEN_SDK_ERROR_H
#define ONETEN_SDK_ERROR_H

BEGIN_NAMESPACE_ONETEN
class Error {
    
public:
    Error() = default;
    Error(int32_t code, const std::string& msg, std::map<std::string, std::string>& user_info);
    
    inline std::string GetMsg() {
        return msg_;
    }
    inline int32_t GetCode() {
        return code_;
    }
    
private:
    int32_t code_;
    std::string msg_;
    std::map<std::string, std::string> user_info_;
    
};

END_NAMESPACE_ONETEN


#endif /* ONETEN_SDK_ERROR_H */
