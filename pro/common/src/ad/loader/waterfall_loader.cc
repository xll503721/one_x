//
//  waterfall_loader.cc
//  TenoneSDK
//
//  Created by li zhixuan on 2022/11/5.
//

#include "waterfall_loader.h"

#include "../oneten_ad_sdk.h"

BEGIN_NAMESPACE_ONETEN_AD

WaterfallLoader::~WaterfallLoader() {
    otlog_info << "~WaterfallLoader";
}

WaterfallLoader::WaterfallLoader(std::shared_ptr<LoaderInterface> loader, std::shared_ptr<void> run_loader):MainLoader(loader, run_loader) {
    std::shared_ptr<WaterfallLoader> waterfallLoader = std::dynamic_pointer_cast<WaterfallLoader>(loader);
    if (!waterfallLoader) {
        waterfall_service_ = std::make_shared<WaterfallService>();
    } else {
        waterfall_service_ = waterfallLoader->GetWaterfallService();
    }
}

void WaterfallLoader::Classify(std::shared_ptr<PlacementModel> placement) {
    super_class::Classify(placement);
    
    StartFlow(placement);
}

void WaterfallLoader::StartFlow(std::shared_ptr<PlacementModel> placement, std::shared_ptr<AdSourceModel> save_ad_source_model) {
    super_class::StartFlow(placement, save_ad_source_model);
    
    waterfall_service_->MarkPreAdSourceFinish(save_ad_source_model);
    
    std::string load_id;
    if (auto s_run_loader = GetRunLoader().lock()) {
        auto run_loader_ptr = std::static_pointer_cast<RunLoader>(s_run_loader);
        load_id = run_loader_ptr->GetId();
    }
    
    bool is_waterfall_finish = waterfall_service_->CheckWaterfallFinish(load_id, placement);
    bool is_c2s_finish = waterfall_service_->CheckC2SFinish();
    std::shared_ptr<AdSourceModel> next_ad_source_model = nullptr;
    if (!is_waterfall_finish) {
        next_ad_source_model = waterfall_service_->LoadNextAdSource();
        if (!next_ad_source_model) {
            otlog_info << "pre ad source model not finish, waitting for pre ad source model";
            return;
        }
    }
    if (is_waterfall_finish && !is_c2s_finish) {
        otlog_info << "waterfall finish, but c2s not finish, waitting for c2s";
        return;
    }
    
    std::map<std::string, std::shared_ptr<void>> map;
    map["next_ad_source_model"] = next_ad_source_model;
    
    std::shared_ptr<void> is_waterfall_finish_ptr = std::make_shared<bool>(is_waterfall_finish);
    map["is_waterfall_finish"] = is_waterfall_finish_ptr;
    map["placement_model"] = placement;
    NextLoader(map);
}

void WaterfallLoader::End() {
    super_class::End();
    otlog_info << "";
};

#pragma mark - setter getter

void WaterfallLoader::SetWaterfallService(std::shared_ptr<WaterfallService> waterfall_service) {
    waterfall_service_ = waterfall_service;
}

std::shared_ptr<WaterfallService> WaterfallLoader::GetWaterfallService() {
    return waterfall_service_;
}

END_NAMESPACE_ONETEN_AD
