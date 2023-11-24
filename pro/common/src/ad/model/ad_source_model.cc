//
//  ad_source_model.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//
#include "ad_source_model.h"

#include <thread/thread_pool.h>
#include <analytics/tracker.h>
#include <ad/oneten_ad_sdk.h>

#include "placement_model.h"

BEGIN_NAMESPACE_ONETEN_AD

AdSourceModel::AdSourceModel(std::shared_ptr<AdSource> ad_source):
ad_source_(ad_source),
status_(Status::kNormal) {
}

AdSourceModel::AdSourceModel(std::shared_ptr<AdSourceCache> ad_source_cache):
ad_source_cache_(ad_source_cache),
status_(Status::kNormal) {
    
}

AdSourceModel::~AdSourceModel() {
    otlog_info << "~AdSourceModel";
}

std::string AdSourceModel::Identifier() {
    std::string identifier;
    if (ad_source_) {
        identifier = ad_source_->Identifier();
    } else if (ad_source_cache_) {
        identifier = ad_source_cache_->Identifier();
    }
    return identifier;
}

void AdSourceModel::AdnLoad() {
    BASE_THREAD::ThreadPool::DefaultPool().Schedule(BASE_THREAD::Thread::Type::kMain, [=](){
        SET_PLATFORM_GENERATE_NAME(ad_source_->GetClassName());
        Register();
    });
}

void AdSourceModel::Load() {
    if (!delegate_.lock()) {
        otlog_fault << "Set the delegate before load";
    }
    
    auto style_type = PLATFORM_VAR_GENERATE(static_cast<unsigned long>(ad_source_->GetStyle()));
    auto ad_source_type = PLATFORM_VAR_GENERATE(2);
    
    std::map<std::string, BASE_PLATFORM::Platform::Var> map;
    map["1"] = PLATFORM_VAR_GENERATE(1);
    
    std::vector<BASE_PLATFORM::Platform::Var> vector;
    BASE_PLATFORM::Platform::Var user_info = &map;
    
    otlog_info << "ad source load class name:" << ad_source_->GetClassName().c_str() << ", type:"
    << static_cast<int32_t>(ad_source_->GetStyle()) << ", request type:" << 2;
    
    PLATFORM_INVOKE(&style_type, &ad_source_type, &user_info)
}

void AdSourceModel::Register() {
    std::map<std::string, BASE_PLATFORM::Platform::Var> map;
    map["1"] = PLATFORM_VAR_GENERATE(1);
    
    std::vector<BASE_PLATFORM::Platform::Var> vector;
    BASE_PLATFORM::Platform::Var user_info = &map;
    
    PLATFORM_INVOKE(&user_info)
}

void AdSourceModel::ConvertToCacheObject() {
    auto ad_source_cache = AdSourceCache::Convert(ad_source_);
    ad_source_cache_ = ad_source_cache;
    ad_source_.reset();
}

bool AdSourceModel::IsReady() {
    auto style = PLATFORM_VAR_GENERATE(static_cast<unsigned long>(ad_source_cache_->GetStyle()));
    PLATFORM_INVOKE(&style)
    return static_cast<bool>(GET_PLATFORM_INVOKE_RESULT);
}

void AdSourceModel::SetDelegate(std::shared_ptr<AdSourceDelegate> delegate) {
    delegate_ = delegate;
}

#pragma mark - AdSourceDelegate

void AdSourceModel::RegisterCompletion(std::map<std::string, std::string> user_info, std::shared_ptr<ONETEN::Error> error) {
    if (error) {
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
        if (auto s_delegate = delegate_.lock()) {
            s_delegate->LoadCompletion(static_cast<int32_t>(GetStyle()), error);
        }
        return;
    }
    Load();
}

void AdSourceModel::LoadCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
    otlog_info << "class name:" << ad_source_->GetClassName().c_str() << ", type:"
    << static_cast<int32_t>(ad_source_->GetStyle()) << ", request type:" << 2;
    if (error) {
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
    } else {
        otlog_info << "success";
    }
    
    if (auto s_delegate = delegate_.lock()) {
        s_delegate->LoadCompletion(categroy_type, error);
    }
}

void AdSourceModel::ShowCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
    if (error) {
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
        return;
    }
    std::map<std::string, std::string> event_properties;
    BASE_ANALYTICS::Tracker::DefaultTracker().Send("show", event_properties);
    
    if (auto s_delegate = delegate_.lock()) {
        s_delegate->ShowCompletion(categroy_type);
    }
}

void AdSourceModel::CloseCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
    otlog_info << "success" << ad_source_cache_->GetClassName().c_str() << ", type:"
    << static_cast<int32_t>(ad_source_cache_->GetStyle()) << ", request type:" << static_cast<int32_t>(ad_source_cache_->GetRequestType());
    
    if (error) {
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
        return;
    }
    
    if (auto s_delegate = delegate_.lock()) {
        s_delegate->CloseCompletion(categroy_type);
    }
}

void AdSourceModel::ClickCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
    if (error) {
        return;
    }
    
    if (auto s_delegate = delegate_.lock()) {
        s_delegate->ClickCompletion(categroy_type);
    }
}

END_NAMESPACE_ONETEN_AD
