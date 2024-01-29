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
status_(Status::kReadyToLoad) {
}

AdSourceModel::AdSourceModel(std::shared_ptr<AdSourceCache> ad_source_cache):
ad_source_cache_(ad_source_cache),
status_(Status::kReadyToLoad) {
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

void AdSourceModel::Load() {
    if (!delegate_.lock()) {
        otlog_fault << "Set the delegate before load";
    }

    status_ = Status::kLoading;
    SET_PLATFORM_GENERATE_NAME(ad_source_->GetClassName());
    BASE_THREAD::ThreadPool::DefaultPool().Schedule(BASE_THREAD::Thread::Type::kMain, [=](){
        auto style_type = PLATFORM_VAR_GENERATE(static_cast<unsigned long>(ad_source_->GetStyle()));
        auto ad_source_type = PLATFORM_VAR_GENERATE(static_cast<unsigned long>(ad_source_->GetRequestType()));
        
        std::map<std::string, BASE_PLATFORM::Platform::Var> map;
        map["placement_id"] = PLATFORM_VAR_GENERATE(ad_source_->GetplacementId());
        
        std::vector<BASE_PLATFORM::Platform::Var> vector;
        BASE_PLATFORM::Platform::Var user_info = &map;
        
        otlog_info << "load ad source class name:" << ad_source_->GetClassName().c_str() << ", id:" << ad_source_->Identifier() << ", type:" << static_cast<int32_t>(ad_source_->GetStyle()) << ", request type:" << static_cast<int32_t>(ad_source_->GetRequestType());
        
        PLATFORM_INVOKE(&style_type, &ad_source_type, &user_info)
    });
}

void AdSourceModel::Register() {
    SET_PLATFORM_GENERATE_NAME(ad_source_->GetClassName());
    
    std::map<std::string, BASE_PLATFORM::Platform::Var> map;
    map["1"] = PLATFORM_VAR_GENERATE(1);
    
    std::vector<BASE_PLATFORM::Platform::Var> vector;
    BASE_PLATFORM::Platform::Var user_info = &map;
    
    otlog_info << "register ad source class name:" << ad_source_->GetClassName().c_str() << ", id:" << ad_source_->Identifier() << ", type:" << static_cast<int32_t>(ad_source_->GetStyle()) << ", request type:" << 2;
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

void AdSourceModel::SetDelegate(std::shared_ptr<AdSourceModelDelegate> delegate) {
    delegate_ = delegate;
}

#pragma mark - AdSourceDelegate

void AdSourceModel::RegisterCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error) {
    if (error) {
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
    } else {
        otlog_info << "success";
    }
    
    if (auto s_delegate = delegate_.lock()) {
        s_delegate->RegisterCompletion(ad_source_model, error);
    }
}

void AdSourceModel::LoadCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error) {
    otlog_info << "class name:" << ad_source_->GetClassName().c_str() << ", id:" << ad_source_->Identifier() << ", type:"
    << static_cast<int32_t>(ad_source_->GetStyle()) << ", request type:" << 2;
    if (error) {
        status_ = Status::kLoadFailed;
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
    } else {
        status_ = Status::kLoaded;
        otlog_info << "success";
    }
    
    
    if (auto s_delegate = delegate_.lock()) {
        s_delegate->LoadCompletion(ad_source_model, error);
    }
}

void AdSourceModel::ShowCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error) {
    if (error) {
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
        return;
    }
    
    if (auto s_delegate = delegate_.lock()) {
        s_delegate->ShowCompletion(ad_source_model);
    }
}

void AdSourceModel::CloseCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error) {
    otlog_info << "success" << ad_source_cache_->GetClassName().c_str() << ", type:"
    << static_cast<int32_t>(ad_source_cache_->GetStyle()) << ", request type:" << static_cast<int32_t>(ad_source_cache_->GetRequestType());
    
    if (error) {
        otlog_info << "failed code:" << error->GetCode() << ", msg:" << error->GetMsg();
        return;
    }
    
    if (auto s_delegate = delegate_.lock()) {
        s_delegate->CloseCompletion(ad_source_model);
    }
}

void AdSourceModel::ClickCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error) {
    if (error) {
        return;
    }
    
    if (auto s_delegate = delegate_.lock()) {
        s_delegate->ClickCompletion(ad_source_model);
    }
}

END_NAMESPACE_ONETEN_AD
