//
//  oneten_ad_sdk.cpp
//  SDKCommon
//
//  Created by li zhixuan on 2023/3/16.
//

#include "oneten_ad_sdk.h"
#include "loader/main_loader.h"
#include "loader/waterfall_loader.h"
#include "loader/header_bid_loader.h"
#include "loader/placement_loader.h"
#include "loader/normal_loader.h"
#include "loader/cache_loader.h"

#include <ad/model/placement_model.h>
#include <ad/model/cache_model.h>
#include <ad/model/model_factory.h>

#include <ad/util/storage.h>

#include <thread/thread_pool.h>
#include <storage/database/database.h>
#include <device/device.h>
#include <network/http:s/http_s_client.h>

BEGIN_NAMESPACE_ONETEN_AD

thread_local std::shared_ptr<LoaderInterface> OnetenAdSDK::start_loader_ = nullptr;
thread_local std::shared_ptr<LoaderInterface> OnetenAdSDK::waterfall_loader_ = nullptr;
thread_local std::shared_ptr<LoaderInterface> OnetenAdSDK::request_loader_ = nullptr;
thread_local std::shared_ptr<LoaderInterface> OnetenAdSDK::cache_loader_ = nullptr;

static const std::string database_name = "sdk_db";

OnetenAdSDK &OnetenAdSDK::GetInstance() {
    static OnetenAdSDK ad_sdk;
    return ad_sdk;
}

OnetenAdSDK::OnetenAdSDK() {
    cache_service_ = std::make_shared<CacheService>();
    
//    auto db = BASE_STORAGE_DATABASE::DataBase(BASE_DEVICE::Device::DefaultInstance().GetFile()->GetCachesPath() + "/" + database_name);
//    const char* sql_create_table =
//            "CREATE TABLE IF NOT EXISTS Users ("
//            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
//            "name TEXT,"
//            "age INTEGER);";
//    db.CreateTable(sql_create_table);
//    
//    const char* sql_insert_data = "Users";
//    auto age = PLATFORM_VAR_GENERATE(1);
//    auto name = PLATFORM_VAR_GENERATE("Alice");
//    std::map<std::string, BASE_PLATFORM::Platform::Var> map;
//    map["name"] = name;
//    map["age"] = age;
//    
//    BASE_PLATFORM::Platform::Var row_var = &map;
//    db.Insert(sql_insert_data, row_var);
//    
//    auto select_age = PLATFORM_VAR_GENERATE(0);
//    auto select_name = PLATFORM_VAR_GENERATE("");
//    std::map<std::string, BASE_PLATFORM::Platform::Var> select_map;
//    select_map["name"] = select_name;
//    select_map["age"] = select_age;
//    
//    BASE_PLATFORM::Platform::Var select_row_var = &select_map;
//    auto select_map_get = select_row_var.GetMap();
//    
//    otlog_info << "map select_name:" << &(select_map["name"]) << ", select_name:" << &select_name << ", map:" << &select_map_get;
//    
//    db.Select(sql_insert_data, select_row_var);
//    printf("");
}

OnetenAdSDK::~OnetenAdSDK() {
}

void OnetenAdSDK::Register(const std::string& app_id) {
//    printf("%s", app_id.c_str());
}

std::shared_ptr<LoaderInterface> OnetenAdSDK::GetMainLoader() {
    if (start_loader_) {    
        otlog_info << "start loader:" << start_loader_;
    }
    return start_loader_;
}

std::shared_ptr<LoaderInterface> OnetenAdSDK::GetWaterfallLoader() {
    if (!waterfall_loader_) {
        otlog_fault << "waterfall loader:" << waterfall_loader_;
    }
    return waterfall_loader_;
}

std::shared_ptr<LoaderInterface> OnetenAdSDK::GetCacheLoader() {
    if (!cache_loader_) {
        otlog_fault << "cache loader:" << cache_loader_;
    }
    return cache_loader_;
}

std::shared_ptr<LoaderInterface> OnetenAdSDK::GetRequestLoader() {
    if (!request_loader_) {
        otlog_info << "request loader:" << request_loader_;
    }
    return request_loader_;
}

void OnetenAdSDK::StartAdLoad(const std::string& placement_id, std::map<std::string, std::string>& user_info, AdSDKDelegate& delegate) {
    delegate_ = &delegate;
    user_info_ = user_info;
    
    BASE_THREAD::ThreadPool::DefaultPool().Schedule(BASE_THREAD::Thread::Type::kOther, [=](){
        otlog_info << "placement id:" << placement_id;
        std::shared_ptr<MainLoader> start_main_loader = std::make_shared<MainLoader>(nullptr);
        std::shared_ptr<PlacementLoader> placement_loader = std::make_shared<PlacementLoader>(start_main_loader);
        
        std::shared_ptr<MainLoader> waterfall_main_loader = std::make_shared<MainLoader>(nullptr);
        std::shared_ptr<WaterfallLoader> waterfall_loader = std::make_shared<WaterfallLoader>(waterfall_main_loader);
        
        std::shared_ptr<MainLoader> request_main_loader = std::make_shared<MainLoader>(nullptr);
        std::shared_ptr<HeaderBidLoader> header_bid_loader = std::make_shared<HeaderBidLoader>(request_main_loader);
        std::shared_ptr<NormalLoader> normal_loader = std::make_shared<NormalLoader>(header_bid_loader);
        
        std::shared_ptr<MainLoader> save_main_loader = std::make_shared<MainLoader>(nullptr);
        std::shared_ptr<CacheLoader> cache_loader = std::make_shared<CacheLoader>(save_main_loader);
        
        start_loader_ = placement_loader;
        waterfall_loader_ = waterfall_loader;
        request_loader_ = normal_loader;
        cache_loader_ = cache_loader;
        
        placement_loader->Start(placement_id);
        
        placement_loader->NextLoader([=](std::map<std::string, std::shared_ptr<void>> parmas) {
            auto placement_model = parmas["placement_model"];
            std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
            waterfall_loader_->StartFlow(0, placement_model_ptr);
        });
        
        waterfall_loader->NextLoader([=](std::map<std::string, std::shared_ptr<void>> parmas) {
            auto placement_model = parmas["placement_model"];
            int32_t level = *std::static_pointer_cast<int32_t>(parmas["level"]);
            std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
            auto ad_source_models = placement_model_ptr->GetAdSourceModel();
            if (!(ad_source_models.size() > level)) {
                EndAdLoad(placement_id);
                return;
            }
            
            auto ad_source_model_ptr = ad_source_models[level];
            request_loader_->Flow(ad_source_model_ptr, placement_model_ptr);
        });
        
        request_loader_->NextLoader([=](std::map<std::string, std::shared_ptr<void>> parmas) {
            auto placement_model = parmas["placement_model"];
            auto ad_source_model = parmas["ad_source_model"];
            bool is_load_succeed = *std::static_pointer_cast<bool>(parmas["load_succeed"]);
            if (!is_load_succeed) {
                EndAdLoad(placement_id);
                return;
            }
            
            std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
            std::shared_ptr<AdSourceModel> ad_source_model_ptr = std::static_pointer_cast<AdSourceModel>(ad_source_model);
            cache_loader->Save(ad_source_model_ptr, placement_model_ptr);
        });
        
        cache_loader->NextLoader([=](std::map<std::string, std::shared_ptr<void>> parmas) {
            auto placement_model = parmas["placement_model"];
            auto ad_source_model = parmas["ad_source_model"];
            
            std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
            std::shared_ptr<AdSourceModel> ad_source_model_ptr = std::static_pointer_cast<AdSourceModel>(ad_source_model);
            
            waterfall_loader_->StartFlow(ad_source_model_ptr->GetLevel() + 1, placement_model_ptr);
        });
        
        
        otlog_info << "========start load placement id: "<< placement_id << "========";
        start_loader_->Start(placement_id);
    });
}

void OnetenAdSDK::EndAdLoad(const std::string& placement_id) {
    start_loader_->End();
    waterfall_loader_->End();
    request_loader_->End();
    cache_loader_->End();
    
    start_loader_.reset();
    waterfall_loader_.reset();
    request_loader_.reset();
    cache_loader_.reset();
    
    otlog_info << "========end load placement id: "<< placement_id << "========";
    if (delegate_) {
        delegate_->LoadSucceed();
    }
}

void OnetenAdSDK::DidShowAd(const std::string& placement_id) {
    if (delegate_) {
        delegate_->ShowSucceed();
    }
}

void OnetenAdSDK::DidCloseAd(const std::string& ad_source_id) {
    if (delegate_) {
        delegate_->CloseSucceed();
    }
    
    cache_service_->Remove(ad_source_id);
}

void OnetenAdSDK::DidClickAd(const std::string& placement_id) {
    if (delegate_) {
        delegate_->ClickSucceed();
    }
}

bool OnetenAdSDK::IsAdReady(const std::string& placement_id) {
    auto model_cache = cache_service_->GetAnyOne(placement_id);
    return (model_cache != nullptr);
}

std::shared_ptr<AdSourceModel> OnetenAdSDK::ShowAd(const std::string& placement_id, AdSDKDelegate& delegate) {
    auto ad_source_model = cache_service_->GetHighestPrice(placement_id);
    return ad_source_model;
}

END_NAMESPACE_ONETEN_AD
