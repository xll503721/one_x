//
//  placement.cpp
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#include "ad_source.h"
#include <ad/oneten_ad_sdk.h>
#include <string/string.h>
#include <thread/thread_pool.h>

BEGIN_NAMESPACE_ONETEN_AD

AdSource::AdSource(std::shared_ptr<BASE_JSON::Json> json):
level_(0),
json_(json) {
    Parse();
}

AdSource::~AdSource() {
    otlog_info << "~AdSource";
}

std::string AdSource::Identifier() {
    
}

void AdSource::InitSDK() {
    
}

void AdSource::SetLevel(int32_t level) {
    level_ = level;
}

int32_t AdSource::GetLevel() {
    return level_;
}

std::string AdSource::GetClassName() {
    return clazz_name_;
}

void AdSource::Parse() {
    BASE_JSON::Json clazz_name = json_->operator[]("clazz_name");
    if (clazz_name.IsString()) {
        clazz_name_ = clazz_name.AsString();
    }
    
    BASE_JSON::Json id = json_->operator[]("id");
    if (id.IsString()) {
        identifier_ = id.AsString();
    }
    
    BASE_JSON::Json style = json_->operator[]("style");
    if (style.IsInteger()) {
        style_ = static_cast<Style>(style.AsInteger());
    }
    
    BASE_JSON::Json request_type = json_->operator[]("request_type");
    if (request_type.IsInteger()) {
        request_type_ = static_cast<RequestType>(request_type.AsInteger());
    }
}

#pragma mark - getter

std::shared_ptr<BASE_JSON::Json> AdSource::GetJson() {
    return json_;
}

END_NAMESPACE_ONETEN_AD
