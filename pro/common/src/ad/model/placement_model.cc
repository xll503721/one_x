//
//  placement.cpp
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//
#include "placement_model.h"
#include "ad_source_model.h"

#include <ad/util/storage.h>

BEGIN_NAMESPACE_ONETEN_AD

PlacementModel::PlacementModel(const std::string& json_string) {
    placement_ = std::make_shared<Placement>(json_string);
}

PlacementModel::PlacementModel(std::shared_ptr<PlacementCache> placement_cache):placement_cache_(placement_cache) {
    
}

PlacementModel::PlacementModel(const PlacementModel& placement_model) {
}

PlacementModel::~PlacementModel() {
    otlog_info << "~PlacementModel";
}

std::string PlacementModel::Identifier() {
    std::string identifier;
    if (placement_) {
        identifier = placement_->Identifier();
    } else if (placement_cache_) {
        identifier = placement_cache_->Identifier();
    }
    return identifier;
}

std::vector<std::shared_ptr<AdSourceModel>> PlacementModel::GetAdSourceModel(AdSource::RequestType request_type) {
    std::vector<std::shared_ptr<AdSource>> ad_sources;
    switch (request_type) {
        case AdSource::RequestType::kNormal:
            ad_sources = placement_->GetNormalAdSources();
            break;
        case AdSource::RequestType::kC2S:
            ad_sources = placement_->GetC2SAdSources();
            break;
        case AdSource::RequestType::kS2S:
            ad_sources = placement_->GetS2SAdSources();
            break;
            
        default:
            break;
    }

    std::vector<std::shared_ptr<AdSourceModel>> ad_sources_model_vector;
    for (std::shared_ptr<AdSource> ad_source: ad_sources) {
        std::shared_ptr<AdSourceModel> ad_source_model = std::make_shared<AdSourceModel>(ad_source);
        ad_sources_model_vector.push_back(ad_source_model);
    }
    return ad_sources_model_vector;
}

std::vector<std::shared_ptr<AdSourceModel>> PlacementModel::GetAdSourceModelStatus(AdSourceModel::Status status) {
    std::vector<std::shared_ptr<AdSource>> ad_sources;
    switch (status) {
        case AdSourceModel::Status::kLoading:
            ad_sources = placement_->GetRequestingAdSources();
            break;
        case AdSourceModel::Status::kLoaded:
            ad_sources = placement_->GetLoadedAdSources();
            break;
        case AdSourceModel::Status::kReadyToLoad:
            ad_sources = placement_->GetNormalAdSources();
            break;
            
        default:
            break;
    }

    std::vector<std::shared_ptr<AdSourceModel>> ad_sources_model_vector;
    for (std::shared_ptr<AdSource> ad_source: ad_sources) {
        std::shared_ptr<AdSourceModel> ad_source_model = std::make_shared<AdSourceModel>(ad_source);
        ad_sources_model_vector.push_back(ad_source_model);
    }
    return ad_sources_model_vector;
}

std::shared_ptr<PlacementModel> PlacementModel::ConvertToCacheObject() {
    auto placement_cache = PlacementCache::Convert(placement_);
    auto self = std::make_shared<PlacementModel>(placement_cache);
    return self;
}

void PlacementModel::AddAdSourceModel(std::shared_ptr<AdSourceModel> ad_source_model) {
    ad_sources_model_vector_.push_back(ad_source_model);
}

std::vector<std::shared_ptr<AdSourceModel>> PlacementModel::GetAdSourceModelCache() {
    return ad_sources_model_vector_;
}

bool PlacementModel::RemoveAdSourceModel(const std::string& ad_source_id) {
    auto ad_sources_model_vector_copy = ad_sources_model_vector_;
    for (int i = 0; i < ad_sources_model_vector_copy.size(); i++) {
        auto ad_sources_model = ad_sources_model_vector_copy[i];
        if (ad_sources_model->Identifier() == ad_source_id) {
            ad_sources_model_vector_.erase(ad_sources_model_vector_.begin() + i);
            break;
        }
    }
}

END_NAMESPACE_ONETEN_AD
