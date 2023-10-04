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
    otlog_info << "";
}

void WaterfallLoader::Classify(std::shared_ptr<PlacementModel> placement) {
    super_class::Classify(placement);
    
    StartFlow(0, placement);
}

void WaterfallLoader::StartFlow(int32_t level, std::shared_ptr<PlacementModel> placement) {
    super_class::StartFlow(level, placement);
    
    placement_ = placement;
    InternalStartFlow(level, placement);
}

void WaterfallLoader::InternalStartFlow(int32_t level, std::shared_ptr<PlacementModel> placement_model) {
    otlog_info << "flow level:" << level;
    std::shared_ptr<void> level_ptr = std::make_shared<int32_t>(level);
    
    std::map<std::string, std::shared_ptr<void>> map;
    map["placement_model"] = std::static_pointer_cast<void>(placement_model);
    map["level"] = level_ptr;
    NextLoader(map);
}

void WaterfallLoader::End() {
    super_class::End();
    otlog_info << "";
};

END_NAMESPACE_ONETEN_AD
