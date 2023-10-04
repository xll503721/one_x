//
//  oneten_ad_sdk.hpp
//  SDKCommon
//
//  Created by li zhixuan on 2023/3/16.
//

#ifndef ONETEN_AD_SDK_AD_SDK_H
#define ONETEN_AD_SDK_AD_SDK_H

#include <ad/loader/loader.h>
#include <ad/loader/run_loader.h>
#include <oneten_ad_sdk_delegate.h>
#include <oneten_object.h>
#include <ad/service/cache_service.h>
#include <storage/memory/storage_memory.h>
#include <ad/entity/cache.h>
#include <ad/repository/cache_repository.h>

BEGIN_NAMESPACE_ONETEN_AD

#pragma mark - OnetenAdSDK

class OnetenAdSDK: ONETEN::Object<OnetenAdSDK> {
    
public:
    OnetenAdSDK();
    virtual ~OnetenAdSDK();
    
    static OnetenAdSDK &GetInstance();
    void Register(const std::string& app_id);
    
    void StartAdLoad(const std::string& placement_id, std::map<std::string, std::string>& user_info, AdSDKDelegate& delegate);
    std::shared_ptr<AdSourceModel> ShowAd(const std::string& placement_id, AdSDKDelegate& delegate);
    bool IsAdReady(const std::string& placement_id);
    
private:
    
    std::map<std::string, std::shared_ptr<RunLoader>> run_id_and_run_loader_map_;
    std::shared_ptr<CacheRepository> cache_repository_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SDK_H */
