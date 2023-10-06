//
//  run_loader.cpp
//  oneten_ad_loader
//
//  Created by li zhixuan on 2023/9/29.
//

#include "run_loader.h"
#include <ad/loader/placement_loader.h>
#include <ad/loader/waterfall_loader.h>
#include <ad/loader/header_bid_loader.h>
#include <ad/loader/normal_loader.h>
#include <ad/loader/cache_loader.h>

BEGIN_NAMESPACE_ONETEN_AD

RunLoader::~RunLoader() {
    otlog_info << "~RunLoader";
}

RunLoader::RunLoader(const std::string& placement_id, AdSDKDelegate& delegate, std::map<std::string, std::string> user_info):
    placement_id_(placement_id),
    thread_pool_(1),
    delegate_(&delegate),
    user_info_(user_info) {
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        loader_id_ = std::to_string(timestamp);
}

BASE_THREAD::ThreadPool& RunLoader::GetThreadPool() {
    return thread_pool_;
}

std::string RunLoader::GetId() {
    return loader_id_;
}

void RunLoader::Run(RunCompletion run_completion) {
    run_completion_ = run_completion;
    thread_pool_.Schedule(BASE_THREAD::Thread::Type::kOther, [=](){
        
        otlog_info << "placement id:" << placement_id_;
        std::shared_ptr<MainLoader> start_main_loader = std::make_shared<MainLoader>(nullptr);
        std::shared_ptr<PlacementLoader> placement_loader = std::make_shared<PlacementLoader>(start_main_loader, shared_from_this());
        
        std::shared_ptr<MainLoader> waterfall_main_loader = std::make_shared<MainLoader>(nullptr);
        std::shared_ptr<WaterfallLoader> waterfall_loader = std::make_shared<WaterfallLoader>(waterfall_main_loader, shared_from_this());
        
        std::shared_ptr<MainLoader> request_main_loader = std::make_shared<MainLoader>(nullptr);
        std::shared_ptr<HeaderBidLoader> header_bid_loader = std::make_shared<HeaderBidLoader>(request_main_loader, shared_from_this());
        std::shared_ptr<NormalLoader> normal_loader = std::make_shared<NormalLoader>(header_bid_loader, shared_from_this());
        
        std::shared_ptr<MainLoader> save_main_loader = std::make_shared<MainLoader>(nullptr);
        std::shared_ptr<CacheLoader> cache_loader = std::make_shared<CacheLoader>(save_main_loader, shared_from_this());
        
        start_loader_ = placement_loader;
        waterfall_loader_ = waterfall_loader;
        request_loader_ = normal_loader;
        cache_loader_ = cache_loader;
        
        placement_loader->NextLoader([=](std::map<std::string, std::shared_ptr<void>> parmas) {
            otlog_info << "========placement loader start end========";
            
            auto placement_model = parmas["placement_model"];
            std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
            
            otlog_info << "========waterfall loader start flow========";
            waterfall_loader_->StartFlow(0, placement_model_ptr);
        });
        
        waterfall_loader->NextLoader([=](std::map<std::string, std::shared_ptr<void>> parmas) {
            otlog_info << "========waterfall loader start flow end========";
            
            auto placement_model = parmas["placement_model"];
            int32_t level = *std::static_pointer_cast<int32_t>(parmas["level"]);
            std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
            auto ad_source_models = placement_model_ptr->GetAdSourceModel();
            if (!(ad_source_models.size() > level)) {
                EndAdLoad(placement_id_);
                if (run_completion) {
                    run_completion();
                }
                return;
            }
            
            auto ad_source_model_ptr = ad_source_models[level];
            otlog_info << "========request loader flow========";
            request_loader_->Flow(ad_source_model_ptr, placement_model_ptr);
        });
        
        request_loader_->NextLoader([=](std::map<std::string, std::shared_ptr<void>> parmas) {
            otlog_info << "========request loader flow end========";
            
            auto placement_model = parmas["placement_model"];
            auto ad_source_model = parmas["ad_source_model"];
            bool is_load_succeed = *std::static_pointer_cast<bool>(parmas["load_succeed"]);
            if (is_load_succeed) {
                std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
                std::shared_ptr<AdSourceModel> ad_source_model_ptr = std::static_pointer_cast<AdSourceModel>(ad_source_model);
                otlog_info << "========cache loader save========";
                cache_loader->Save(ad_source_model_ptr, placement_model_ptr);
                return;
            }
            
            std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
            std::shared_ptr<AdSourceModel> ad_source_model_ptr = std::static_pointer_cast<AdSourceModel>(ad_source_model);
            
            otlog_info << "========waterfall loader start flow========";
            waterfall_loader_->StartFlow(ad_source_model_ptr->GetLevel() + 1, placement_model_ptr);
        });
        
        cache_loader_->NextLoader([=](std::map<std::string, std::shared_ptr<void>> parmas) {
            otlog_info << "========cache loader save end========";
            EndAdLoad(placement_id_);
            if (run_completion_) {
                run_completion_();
            }
        });
        
        otlog_info << "************load placement id: "<< placement_id_ << "************";
        otlog_info << "========placement loader start========";
        start_loader_->Start(placement_id_);
    });
}

void RunLoader::EndAdLoad(const std::string& placement_id) {
    start_loader_->End();
    waterfall_loader_->End();
    request_loader_->End();
    cache_loader_->End();
    
    start_loader_.reset();
    waterfall_loader_.reset();
    request_loader_.reset();
    cache_loader_.reset();
    
    otlog_info << "************end load placement id: "<< placement_id << "************";
    if (delegate_) {
        delegate_->LoadSucceed();
    }
}

END_NAMESPACE_ONETEN_AD
