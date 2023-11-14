//
//  ad_srouce_service_model.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#include "waterfall_service.h"

BEGIN_NAMESPACE_ONETEN_AD

std::shared_ptr<AdSourceModel> WaterfallService::LoadNextAdSource() {
    if (!loading_placement_model_) {
        otlog_fault << "call the CheckWaterfallFinish method first";
        return nullptr;
    }
    std::shared_ptr<AdSourceModel> ad_source_model = nullptr;
    auto ad_source_model_list = loading_placement_model_->GetAdSourceModel();
    if (!(ad_source_model_list.size() > loading_layer_index_)) {
        return nullptr;
    }
    
    ad_source_model = ad_source_model_list[loading_layer_index_];
    loading_ad_unit_model_vector_.push_back(ad_source_model);
    loading_layer_index_++;
    return ad_source_model;
}

bool WaterfallService::CheckWaterfallFinish(std::shared_ptr<PlacementModel> placement_model) {
    loading_placement_model_ = placement_model;
    
    auto ad_source_model_list = loading_placement_model_->GetAdSourceModel();
    if (!(ad_source_model_list.size() > loading_layer_index_)) {
        return true;
    }
    
    return false;
}


END_NAMESPACE_ONETEN_AD
