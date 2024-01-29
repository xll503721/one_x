//
//  ad_srouce_service_model.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#include "waterfall_service.h"
#include <ad/model/cache_model.h>

BEGIN_NAMESPACE_ONETEN_AD

void WaterfallService::MarkPreAdSourceFinish(std::shared_ptr<AdSourceModel> save_ad_source_model) {
    if (!save_ad_source_model) {
        return;
    }
    otlog_info << "finish ad source model id:" << save_ad_source_model->Identifier();
    finish_ad_source_model_ = save_ad_source_model;
    
    if (loading_ad_source_model_ && save_ad_source_model->Identifier() == loading_ad_source_model_->Identifier()) {
        loading_ad_source_model_ = nullptr;
        pre_loading_ad_source_model_ = save_ad_source_model;
    }
    if (save_ad_source_model->GetStatus() == AdSourceModel::Status::kLoaded) {
        loading_placement_model_->AddAdSourceModel(save_ad_source_model, AdSourceModel::Status::kLoaded);
    }
    loading_placement_model_->RemoveAdSourceModel(save_ad_source_model, AdSourceModel::Status::kLoading);
}

std::shared_ptr<AdSourceModel> WaterfallService::LoadNextAdSource() {
    if (!loading_placement_model_) {
        otlog_fault << "call the CheckWaterfallFinish method first";
        return nullptr;
    }

    auto ad_source_model_list = loading_placement_model_->GetSortAdSourceModelStatus(AdSourceModel::Status::kReadyToLoad);
    if (ad_source_model_list.size() <= 0) {
        return nullptr;
    }
    
    if (loading_ad_source_model_ && loading_ad_source_model_->GetStatus() == AdSourceModel::Status::kLoading) {
        return nullptr;
    }
    
    auto it = ad_source_model_list.begin();
    std::shared_ptr<AdSourceModel> ad_source_model = *it;
    if (ad_source_model->GetStatus() == AdSourceModel::Status::kLoaded ||
        ad_source_model->GetStatus() == AdSourceModel::Status::kLoadFailed) {
        otlog_fault << "repeat load";
        return nullptr;
    }
    
    loading_ad_source_model_ = ad_source_model;
    otlog_info << "next ad source model id:" << loading_ad_source_model_->Identifier();
    loading_placement_model_->AddAdSourceModel(ad_source_model, AdSourceModel::Status::kLoading);
    loading_placement_model_->RemoveAdSourceModel(ad_source_model, AdSourceModel::Status::kReadyToLoad);
    return ad_source_model;
}

std::shared_ptr<AdSourceModel> WaterfallService::FilterNextAdSource() {
    
}

bool WaterfallService::CheckWaterfallFinish(const std::string& load_id, std::shared_ptr<PlacementModel> placement_model) {
    loading_placement_model_ = placement_model;
    
    auto ready_to_load_ad_source_model_list = loading_placement_model_->GetSortAdSourceModelStatus(AdSourceModel::Status::kReadyToLoad);
    auto loaded_ad_source_model_list = loading_placement_model_->GetSortAdSourceModelStatus(AdSourceModel::Status::kLoaded);
    auto loading_ad_source_model_list = loading_placement_model_->GetSortAdSourceModelStatus(AdSourceModel::Status::kLoading);
    otlog_info << "adsource model array ready to load count:" << ready_to_load_ad_source_model_list.size() << ", loaded count:" << loaded_ad_source_model_list.size() << ", loading count:" << loading_ad_source_model_list.size();
    bool is_waterfall_finish = (ready_to_load_ad_source_model_list.empty() && loading_ad_source_model_list.empty());
    
    if (!is_waterfall_finish && loaded_ad_source_model_list.size() > 0) {
        auto loaded_ad_source_model = *loaded_ad_source_model_list.begin();
        if (WhetherLoadedAdSourceModelEcpmPriceHighest(loaded_ad_source_model, AdSourceModel::Status::kReadyToLoad) ||
            WhetherLoadedAdSourceModelEcpmPriceHighest(loaded_ad_source_model, AdSourceModel::Status::kLoading)) {
            is_waterfall_finish = true;
        }
    }
    
    otlog_info << "waterfall finish:" << is_waterfall_finish;
    if (is_waterfall_finish) {
        return true;
    }
    
    return false;
}

bool WaterfallService::WhetherLoadedAdSourceModelEcpmPriceHighest(std::shared_ptr<AdSourceModel> loaded_ad_source_model, AdSourceModel::Status status) {
    bool is_waterfall_finish = false;
    for (auto loading_ad_source_model : loading_placement_model_->GetSortAdSourceModelStatus(status)) {
        if (loaded_ad_source_model->GetPrice() >= loading_ad_source_model->GetPrice()) {
            otlog_info << "status:" << static_cast<int32_t>(status) << ", loaded ad source: " << loaded_ad_source_model->Identifier() << " request type:" << static_cast<int32_t>(loaded_ad_source_model->GetRequestType()) << ", price:" << loaded_ad_source_model->GetPrice() << " higher than loading ad source:" << loading_ad_source_model->Identifier() << " price:" << loading_ad_source_model->GetPrice();
            
            is_waterfall_finish = true;
            break;
        }
    }
    return is_waterfall_finish;
}

bool WaterfallService::CheckC2SFinish() {
    bool is_c2s_finish = true;
    auto ad_source_model_list = loading_placement_model_->GetAdSourceModel(AdSource::RequestType::kC2S);
    for (auto ad_source_model : ad_source_model_list) {
        if (ad_source_model->GetStatus() == AdSourceModel::Status::kLoading || ad_source_model->GetStatus() == AdSourceModel::Status::kReadyToLoad) {
            is_c2s_finish = false;
            break;
        }
    }
    otlog_info << "c2s finish:" << is_c2s_finish;
    return is_c2s_finish;
}


END_NAMESPACE_ONETEN_AD
