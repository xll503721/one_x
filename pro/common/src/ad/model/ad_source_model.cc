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

AdSourceModel::AdSourceModel(std::shared_ptr<AdSource> ad_source):ad_source_(ad_source) {
}

AdSourceModel::AdSourceModel(std::shared_ptr<AdSourceCache> ad_source_cache):ad_source_cache_(ad_source_cache) {
    
}

//AdSourceModel::AdSourceModel(const AdSourceModel& ad_source_model) {
//
//}

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

void AdSourceModel::Load(std::shared_ptr<AdSourceDelegate> delegate) {
    delegate_ = delegate;
    
    BASE_THREAD::ThreadPool::DefaultPool().ScheduleTransfer(BASE_THREAD::Thread::Type::kMain, [=] () {
        SET_PLATFORM_GENERATE_NAME(ad_source_->GetClassName());
        
        auto style_type = PLATFORM_VAR_GENERATE(static_cast<unsigned long>(ad_source_->GetStyle()));
        auto ad_source_type = PLATFORM_VAR_GENERATE(2);
        
        std::map<std::string, BASE_PLATFORM::Platform::Var> map;
        map["1"] = PLATFORM_VAR_GENERATE(1);
        
        std::vector<BASE_PLATFORM::Platform::Var> vector;
        BASE_PLATFORM::Platform::Var user_info = &map;
        
        otlog_info << "ad source load class name:" << ad_source_->GetClassName().c_str() << ", type:"
        << static_cast<int32_t>(ad_source_->GetStyle()) << ", request type:" << 2;
        
        PLATFORM_INVOKE(&style_type, &ad_source_type, &user_info)
    });
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

#pragma mark - AdSourceDelegate
void AdSourceModel::LoadCompletion(int32_t categroy_type, ONETEN::Error* error) {
    otlog_info << "success class name:" << ad_source_->GetClassName().c_str() << ", type:"
    << static_cast<int32_t>(ad_source_->GetStyle()) << ", request type:" << 2;
    if (error) {
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
        return;
    }
    
    std::map<std::string, std::string> event_properties;
    BASE_ANALYTICS::Tracker::DefaultTracker().Send("load", event_properties);
    
    BASE_THREAD::ThreadPool::DefaultPool().ScheduleTransferBack([=] () {
        if (auto s_delegate = delegate_.lock()) {
            s_delegate->LoadCompletion(categroy_type, error);
        }
    });
}

void AdSourceModel::ShowCompletion(int32_t categroy_type, ONETEN::Error* error) {
    if (error) {
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
        return;
    }
    std::map<std::string, std::string> event_properties;
    BASE_ANALYTICS::Tracker::DefaultTracker().Send("show", event_properties);
    
    BASE_THREAD::ThreadPool::DefaultPool().Schedule(BASE_THREAD::Thread::Type::kMain, [=](){
        ONETEN_AD::OnetenAdSDK::GetInstance().DidShowAd(Identifier());
    });
}

void AdSourceModel::CloseCompletion(int32_t categroy_type, ONETEN::Error* error) {
    otlog_info << "success" << ad_source_cache_->GetClassName().c_str() << ", type:"
    << static_cast<int32_t>(ad_source_cache_->GetStyle()) << ", request type:" << static_cast<int32_t>(ad_source_cache_->GetRequestType());
    
    if (error) {
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
        return;
    }
    std::map<std::string, std::string> event_properties;
    BASE_ANALYTICS::Tracker::DefaultTracker().Send("close", event_properties);
    
    BASE_THREAD::ThreadPool::DefaultPool().Schedule(BASE_THREAD::Thread::Type::kMain, [=](){
        ONETEN_AD::OnetenAdSDK::GetInstance().DidCloseAd(Identifier());
    });
}

void AdSourceModel::ClickCompletion(int32_t categroy_type, ONETEN::Error* error) {
    if (error) {
        return;
    }
    std::map<std::string, std::string> event_properties;
    BASE_ANALYTICS::Tracker::DefaultTracker().Send("click", event_properties);
    
    BASE_THREAD::ThreadPool::DefaultPool().Schedule(BASE_THREAD::Thread::Type::kMain, [=](){
        ONETEN_AD::OnetenAdSDK::GetInstance().DidClickAd(Identifier());
    });
}

END_NAMESPACE_ONETEN_AD
