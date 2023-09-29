//
//  oneten_ad_sdk.hpp
//  SDKCommon
//
//  Created by li zhixuan on 2023/3/16.
//

#ifndef ONETEN_AD_SDK_AD_SDK_H
#define ONETEN_AD_SDK_AD_SDK_H

#include <ad/loader/loader.h>
#include <oneten_ad_sdk_delegate.h>
#include <oneten_object.h>
#include <ad/service/cache_service.h>
#include <storage/memory/storage_memory.h>
#include <ad/entity/cache.h>
#include <thread/thread_pool.h>

BEGIN_NAMESPACE_ONETEN_AD

#pragma mark - OnetenAdSDK

class OnetenAdSDK: ONETEN::Object<OnetenAdSDK> {
    
public:
    static OnetenAdSDK &GetInstance();
    void Register(const std::string& app_id);
    void StartAdLoad(const std::string& placement_id, std::map<std::string, std::string>& user_info, AdSDKDelegate& delegate);
    std::shared_ptr<AdSourceModel> ShowAd(const std::string& placement_id, AdSDKDelegate& delegate);
    bool IsAdReady(const std::string& placement_id);
    
    std::shared_ptr<LoaderInterface> GetMainLoader();
    std::shared_ptr<LoaderInterface> GetWaterfallLoader();
    std::shared_ptr<LoaderInterface> GetRequestLoader();
    std::shared_ptr<LoaderInterface> GetCacheLoader();
    
    void EndAdLoad(const std::string& placement_id);
    void DidShowAd(const std::string& placement_id);
    void DidCloseAd(const std::string& placement_id);
    void DidClickAd(const std::string& placement_id);
    
private:
    OnetenAdSDK();
    ~OnetenAdSDK();
    
    thread_local static std::shared_ptr<LoaderInterface> start_loader_;
    thread_local static std::shared_ptr<LoaderInterface> waterfall_loader_;
    thread_local static std::shared_ptr<LoaderInterface> request_loader_;
    thread_local static std::shared_ptr<LoaderInterface> cache_loader_;
    
    AdSDKDelegate* delegate_;
    std::map<std::string, std::string> user_info_;
    
    std::shared_ptr<CacheService> cache_service_;
    
public:
    BASE_THREAD::ThreadPool thread_pool_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SDK_H */
