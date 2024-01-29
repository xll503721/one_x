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
        normal_loader_ = normal_loader;
        header_bid_loader_ = header_bid_loader;
        cache_loader_ = cache_loader;
        
        WaterfallFlow();
        LoadAdapter();
        NextAdapter();
        SaveCache();
        
        RequestPlacement();
    });
}

void RunLoader::RequestPlacement() {
    otlog_info << "************load placement id:"<< placement_id_ << ", load id:" << loader_id_ << "************";
    otlog_info << "========placement loader start========";
    start_loader_->Start(placement_id_);
}

void RunLoader::WaterfallFlow() {
    start_loader_->NextLoader([=](std::map<std::string, std::shared_ptr<void>> params) {
        auto placement_model = params["placement_model"];
        std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
        
        otlog_info << "========waterfall loader start flow========";
        waterfall_loader_->StartFlow(placement_model_ptr);
    });
}

void RunLoader::LoadAdapter() {
    waterfall_loader_->NextLoader([=](std::map<std::string, std::shared_ptr<void>> params) {
        auto placement_model = params["placement_model"];
        auto next_ad_source_model = params["next_ad_source_model"];
        
        bool is_waterfall_finish = *std::static_pointer_cast<bool>(params["is_waterfall_finish"]);
        
        std::shared_ptr<AdSourceModel> next_ad_source_model_ptr = std::static_pointer_cast<AdSourceModel>(next_ad_source_model);
        std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
        if (is_waterfall_finish) {
            EndAdLoad();
            return;
        }
        
        otlog_info << "========request loader flow========";
        normal_loader_->Flow(next_ad_source_model_ptr, placement_model_ptr);
    });
}

void RunLoader::NextAdapterSave(std::map<std::string, std::shared_ptr<void>> params) {
    thread_pool_.Schedule(BASE_THREAD::Thread::Type::kOther, [&, copy_params = params]() {
        auto placement_model = copy_params.at("placement_model");
        auto ad_source_model = copy_params.at("ad_source_model");
        if (copy_params.find("error") == copy_params.end()) {
            std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
            std::shared_ptr<AdSourceModel> ad_source_model_ptr = std::static_pointer_cast<AdSourceModel>(ad_source_model);
            otlog_info << "========cache loader save========";
            cache_loader_->Save(ad_source_model_ptr, placement_model_ptr);
        }
        
        std::shared_ptr<PlacementModel> placement_model_ptr = std::static_pointer_cast<PlacementModel>(placement_model);
        std::shared_ptr<AdSourceModel> ad_source_model_ptr = std::static_pointer_cast<AdSourceModel>(ad_source_model);
        
        otlog_info << "========waterfall loader start flow========";
        waterfall_loader_->StartFlow(placement_model_ptr, ad_source_model_ptr);
    });
}

void RunLoader::NextAdapter() {
    normal_loader_->NextLoader([=](std::map<std::string, std::shared_ptr<void>> params) {
        NextAdapterSave(params);
    });
    
    header_bid_loader_->NextLoader([=](std::map<std::string, std::shared_ptr<void>> params) {
        NextAdapterSave(params);
    });
}

void RunLoader::SaveCache() {
    cache_loader_->NextLoader([=](std::map<std::string, std::shared_ptr<void>> params) {
    });
}

void RunLoader::EndAdLoad() {
    otlog_info << "************end load placement id: "<< placement_id_ << "************";
    
    if (!run_completion_) {
        return;
    }
    start_loader_->End();
    waterfall_loader_->End();
    normal_loader_->End();
    cache_loader_->End();
    
    run_completion_();
    run_completion_ = nullptr;
}

END_NAMESPACE_ONETEN_AD
