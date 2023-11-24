//
//  run_loader.hpp
//  oneten_ad_loader
//
//  Created by li zhixuan on 2023/9/29.
//

#ifndef ONETEN_AD_SDK_RUN_LOADER_H
#define ONETEN_AD_SDK_RUN_LOADER_H

#include "loader.h"
#include "main_loader.h"
#include <oneten_object.h>
#include <thread/thread_pool.h>
#include <oneten_ad_sdk_delegate.h>
#include <ad/model/ad_source_model.h>

BEGIN_NAMESPACE_ONETEN_AD

class RunLoaderDelegate {
    
public:
    virtual void LoaderDidLoaded() = 0;
};

class RunLoader: public ONETEN::Object<RunLoader> {
    
public:
    ~RunLoader();
    RunLoader(const std::string& placement_id, AdSDKDelegate& delegate, std::map<std::string, std::string> user_info);
    
    std::string GetId();
    BASE_THREAD::ThreadPool& GetThreadPool();
    
    using RunCompletion = std::function<void()>;
    void Run(RunCompletion run_completion);
    
private:
    void EndAdLoad();
    void RequestPlacement();
    void WaterfallFlow();
    void LoadAdapter();
    void NextAdapter();
    void SaveCache();
    
private:
    RunCompletion run_completion_;
    
    std::shared_ptr<LoaderInterface> start_loader_;
    std::shared_ptr<LoaderInterface> waterfall_loader_;
    std::shared_ptr<LoaderInterface> request_loader_;
    std::shared_ptr<LoaderInterface> cache_loader_;
    
    BASE_THREAD::ThreadPool thread_pool_;
    
    std::string placement_id_;
    std::string loader_id_;
    AdSDKDelegate* delegate_;
    std::map<std::string, std::string> user_info_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_RUN_LOADER_H */
