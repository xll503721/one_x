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

static const std::string database_name = "sdk_db";

OnetenAdSDK &OnetenAdSDK::GetInstance() {
    static OnetenAdSDK ad_sdk;
    return ad_sdk;
}

OnetenAdSDK::OnetenAdSDK() {
}

OnetenAdSDK::~OnetenAdSDK() {
}

void OnetenAdSDK::Register(const std::string& app_id) {
}

void OnetenAdSDK::StartAdLoad(const std::string& placement_id, std::map<std::string, std::string>& user_info, AdSDKDelegate& delegate) {
    if (!cache_repository_) {
        cache_repository_ = std::make_shared<CacheRepository>(delegate);
    }
    
    auto run_loader = std::make_shared<RunLoader>(placement_id, delegate, user_info);
    run_loader->Run([=]() {
        
    });
    
    run_id_and_run_loader_map_[run_loader->GetId()] = run_loader;
}

bool OnetenAdSDK::IsAdReady(const std::string& placement_id) {
    bool isReady = (cache_repository_->GetAnyOne(placement_id) != nullptr);
    otlog_info << "placement id:" << placement_id << " has ready:" << isReady;
    return isReady;
}

std::shared_ptr<AdSourceModel> OnetenAdSDK::ShowAd(const std::string& placement_id, AdSDKDelegate& delegate) {
    auto ad_cache = cache_repository_->GetHighestPrice(placement_id);
#ifdef DEBUG
    bool isReady = IsAdReady(placement_id);
    if ((isReady && !ad_cache) || (ad_cache && !isReady)) {
        otlog_fault << "is ready not match get ad cache";
    }
#endif
    
    return ad_cache;
}

END_NAMESPACE_ONETEN_AD
