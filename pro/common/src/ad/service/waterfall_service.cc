//
//  ad_srouce_service_model.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#include "waterfall_service.h"
#include <ad/model/cache_model.h>

BEGIN_NAMESPACE_ONETEN_AD

void WaterfallService::MarkPreAdSourceFinish() {
    loading_layer_index_++;
}

std::shared_ptr<AdSourceModel> WaterfallService::LoadNextAdSource() {
    if (!loading_placement_model_) {
        otlog_fault << "call the CheckWaterfallFinish method first";
        return nullptr;
    }
    std::shared_ptr<AdSourceModel> ad_source_model = nullptr;
    auto ad_source_model_list = loading_placement_model_->GetAdSourceModelStatus(AdSourceModel::Status::kReadyToLoad);
    if (!(ad_source_model_list.size() > loading_layer_index_)) {
        return nullptr;
    }
    
    int32_t pre_loading_layer_index = (loading_layer_index_ - 1 < 0 ?: 0);
    auto pre_ad_source_model = ad_source_model_list[pre_loading_layer_index];
    if (pre_ad_source_model->GetStatus() == AdSourceModel::Status::kLoading) {
        otlog_fault << "repeat loading";
        return nullptr;
    }
    
    ad_source_model = ad_source_model_list[loading_layer_index_];
    
    loading_ad_unit_model_vector_.push_back(ad_source_model);
    return ad_source_model;
}

bool WaterfallService::CheckWaterfallFinish(const std::string& load_id, std::shared_ptr<PlacementModel> placement_model) {
    loading_placement_model_ = placement_model;
    
    bool has_cache = false;
    auto cache_model = CacheModel::Read(placement_model->Identifier());
    if (cache_model) {
        has_cache = cache_model->HasCache(load_id);
    }
    
    auto ad_source_model_list = loading_placement_model_->GetAdSourceModel(AdSource::RequestType::kNormal);
    bool is_waterfall_finish = !(ad_source_model_list.size() > loading_layer_index_);
    bool is_c2s_finish = CheckC2SFinish();
    
    otlog_info << "waterfall finish:" << is_waterfall_finish << ", has cache:" << has_cache;
    if ((is_waterfall_finish || has_cache) && is_c2s_finish) {
        return true;
    }
    
    return false;
}

bool WaterfallService::CheckC2SFinish() {
    auto ad_source_model_list = loading_placement_model_->GetAdSourceModel(AdSource::RequestType::kC2S);
    for (auto ad_source_model : ad_source_model_list) {
        if (ad_source_model->GetStatus() == AdSourceModel::Status::kLoading) {
            return false;
        }
    }
    return true;
}


END_NAMESPACE_ONETEN_AD
