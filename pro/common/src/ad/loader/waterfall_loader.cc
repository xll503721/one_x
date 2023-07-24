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

WaterfallLoader::WaterfallLoader(std::shared_ptr<LoaderInterface> loader):MainLoader(loader) {
    otlog_info << "";
}

void WaterfallLoader::Classify(std::shared_ptr<PlacementModel> placement) {
    super_class::Classify(placement);
    otlog_info << "prepare for flow";
    
    placement_ = placement;
    
    StartFlow(0, placement_);
}

void WaterfallLoader::StartFlow(int32_t level, std::shared_ptr<PlacementModel> placement) {
    super_class::StartFlow(level, placement);
    
    InternalStartFlow(level, placement);
}

void WaterfallLoader::InternalStartFlow(int32_t level, std::shared_ptr<PlacementModel> placement_model) {
    std::vector<std::shared_ptr<AdSourceModel>> ad_sources_model = placement_model->GetAdSourceModel();
    if (level == ad_sources_model.size()) {
        std::string placement_id;
        ONETEN_AD::OnetenAdSDK::GetInstance().EndAdLoad(placement_id);
        return;
    }
    
    if (ad_sources_model.size() > level) {
        otlog_info << "flow level:" << level;
        std::shared_ptr<AdSourceModel> ad_source_model = ad_sources_model[level];
        ONETEN_AD::OnetenAdSDK::GetInstance().GetRequestLoader()->Flow(ad_source_model, placement_model);
    }
}

void WaterfallLoader::End() {
    super_class::End();
    otlog_info << "";
};

END_NAMESPACE_ONETEN_AD
