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
    waterfall_service_ = std::make_shared<WaterfallService>();
}

void WaterfallLoader::Classify(std::shared_ptr<PlacementModel> placement) {
    super_class::Classify(placement);
    
    StartFlow(placement);
}

void WaterfallLoader::StartFlow(std::shared_ptr<PlacementModel> placement) {
    super_class::StartFlow(placement);
    
    std::map<std::string, std::shared_ptr<void>> map;
    
    bool is_waterfall_finish = waterfall_service_->CheckWaterfallFinish(placement);
    if (!is_waterfall_finish) {
        auto next_ad_source_model = waterfall_service_->LoadNextAdSource();
        if (next_ad_source_model) {
            map["next_ad_source_model"] = next_ad_source_model;
        }
    }
    
    std::shared_ptr<void> is_waterfall_finish_ptr = std::make_shared<bool>(is_waterfall_finish);
    map["is_waterfall_finish"] = is_waterfall_finish_ptr;
    map["placement_model"] = placement;
    NextLoader(map);
}

void WaterfallLoader::End() {
    super_class::End();
    otlog_info << "";
};

END_NAMESPACE_ONETEN_AD
