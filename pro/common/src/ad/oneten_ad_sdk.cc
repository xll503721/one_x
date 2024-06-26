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

#include <storage/database/database.h>
#include <device/device.h>
#include <network/http:s/http_s_client.h>

BEGIN_NAMESPACE_ONETEN_AD

OnetenAdSDK &OnetenAdSDK::GetInstance() {
    static OnetenAdSDK ad_sdk;
    return ad_sdk;
}

OnetenAdSDK::OnetenAdSDK() {
    app_loader_ = std::make_shared<AppLoader>();
    
    Placement placement;
    bool is = std::is_same<decltype(placement.Identifier()), std::string>::value;
    otlog_info << is;
    
    auto db = BASE_STORAGE_DATABASE::DataBase::DefaultInstance();
    const char* sql_create_table =
            "CREATE TABLE IF NOT EXISTS Users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT,"
            "age INTEGER);";
    db.CreateTable(sql_create_table);

    const char* sql_insert_data = "Users";
    auto age = PLATFORM_VAR_GENERATE(1);
    auto name = PLATFORM_VAR_GENERATE("Alice");
    std::map<std::string, BASE_PLATFORM::Platform::Var> map;
    map["name"] = name;
    map["age"] = age;

    BASE_PLATFORM::Platform::Var row_var = &map;
    db.Insert(sql_insert_data, row_var);

    auto select_age = PLATFORM_VAR_GENERATE(0);
    auto select_name = PLATFORM_VAR_GENERATE("");
    std::map<std::string, BASE_PLATFORM::Platform::Var> select_map;
    select_map["name"] = select_name;
    select_map["age"] = select_age;

    BASE_PLATFORM::Platform::Var select_row_var = &select_map;
    auto select_map_get = select_row_var.GetMap();

    otlog_info << "map select_name:" << &(select_map["name"]) << ", select_name:" << &select_name << ", map:" << &select_map_get;

    db.Select(sql_insert_data, select_row_var, select_row_var);
//    printf("");
}

OnetenAdSDK::~OnetenAdSDK() {
}

void OnetenAdSDK::Register(const std::string& app_id, AdSDKDelegate& delegate) {
    app_loader_->Register(app_id, [=, s_delegate = &delegate](bool succeed) {
        have_registered_ = succeed;
        
        std::shared_ptr<ONETEN::Error> error = nullptr;
        if (!succeed) {
            std::map<std::string, std::string> user_info;
            error = std::make_shared<ONETEN::Error>(kADSDKAllAdnLoadFailed, "Registration failure", user_info);
        }
        s_delegate->ActionCompletion(succeed ? AdSDKDelegate::ActionType::kRegisterSuccess : AdSDKDelegate::ActionType::kRegisterFail, "", error);
    });
    
    if (!cache_repository_) {
        cache_repository_ = std::make_shared<CacheRepository>(delegate);
    }
}

void OnetenAdSDK::StartAdLoad(const std::string& placement_id, std::map<std::string, std::string>& user_info, AdSDKDelegate& delegate) {
    if (!have_registered_) {
        std::shared_ptr<ONETEN::Error> error = std::make_shared<ONETEN::Error>(kADSDKAllAdnLoadFailed, "Loading must be after registration", user_info);
        delegate.ActionCompletion(AdSDKDelegate::ActionType::kLoadFail, placement_id, error);
        return;
    }
    
    auto run_loader = std::make_shared<RunLoader>(placement_id, delegate, user_info);
    run_loader->Run([=, s_delegate = &delegate]() {
        AdSDKDelegate::ActionType type = IsAdReady(placement_id) ? AdSDKDelegate::ActionType::kLoadSuccess : AdSDKDelegate::ActionType::kLoadFail;
        std::shared_ptr<ONETEN::Error> error = nullptr;
        if (type == AdSDKDelegate::ActionType::kLoadFail) {
            std::map<std::string, std::string> user_info;
            error = std::make_shared<ONETEN::Error>(kADSDKAllAdnLoadFailed, "All ad source load fail", user_info);
        }
        s_delegate->ActionCompletion(type, placement_id, error);
    });
    
    run_id_and_run_loader_map_[run_loader->GetId()] = run_loader;
}

bool OnetenAdSDK::IsAdReady(const std::string& placement_id) {
    auto ad_cache = cache_repository_->GetAnyOne(placement_id);
    if (!ad_cache) {
        return false;
    }
    bool isReady = ad_cache->IsReady();
    otlog_info << "placement id:" << placement_id << " has ready:" << isReady << " ad:" << &ad_cache;
    return isReady;
}

std::shared_ptr<AdSourceModel> OnetenAdSDK::ShowAd(const std::string& placement_id, AdSDKDelegate& delegate) {
    bool isReady = IsAdReady(placement_id);
    std::shared_ptr<AdSourceModel> ad_cache = cache_repository_->GetHighestPrice(placement_id);
    if ((isReady && !ad_cache) || (ad_cache && !isReady)) {
        otlog_fault << "is ready not match get ad cache";
    }
    
    return ad_cache;
}

END_NAMESPACE_ONETEN_AD
