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
        case AdSource::RequestType::kNormal: {
            if (normal_sources_model_vector_.size()) {
                return normal_sources_model_vector_;
            }
            ad_sources = placement_->GetNormalAdSources();
        }
            break;
        case AdSource::RequestType::kC2S: {
            if (c2s_sources_model_vector_.size()) {
                return c2s_sources_model_vector_;
            }
            ad_sources = placement_->GetC2SAdSources();
        }
            break;
        case AdSource::RequestType::kS2S: {
            if (s2s_sources_model_vector_.size()) {
                return s2s_sources_model_vector_;
            }
            ad_sources = placement_->GetS2SAdSources();
        }
            break;
            
        default:
            break;
    }

    std::vector<std::shared_ptr<AdSourceModel>> ad_sources_model_vector;
    for (std::shared_ptr<AdSource> ad_source: ad_sources) {
        std::shared_ptr<AdSourceModel> ad_source_model = std::make_shared<AdSourceModel>(ad_source);
        switch (request_type) {
            case AdSource::RequestType::kNormal:
                normal_sources_model_vector_.push_back(ad_source_model);
                ad_sources_model_vector = normal_sources_model_vector_;
                break;
            case AdSource::RequestType::kC2S:
                c2s_sources_model_vector_.push_back(ad_source_model);
                ad_sources_model_vector = c2s_sources_model_vector_;
                break;
            case AdSource::RequestType::kS2S:
                s2s_sources_model_vector_.push_back(ad_source_model);
                ad_sources_model_vector = s2s_sources_model_vector_;
                break;
                
            default:
                break;
        }
    }
    return ad_sources_model_vector;
}

std::shared_ptr<PlacementModel> PlacementModel::ConvertToCacheObject() {
    auto placement_cache = PlacementCache::Convert(placement_);
    auto placement_model_cache = std::make_shared<PlacementModel>(placement_cache);
    return placement_model_cache;
}

void PlacementModel::AddAdSourceModel(std::shared_ptr<AdSourceModel> ad_source_model, AdSourceModel::Status status) {
    switch (status) {
        case AdSourceModel::Status::kLoading:
            loading_ad_sources_model_vector_.insert(ad_source_model);
            break;
        case AdSourceModel::Status::kLoaded:
            loaded_ad_sources_model_vector_.insert(ad_source_model);
            break;
        case AdSourceModel::Status::kReadyToLoad:
            ready_to_load_sources_model_vector_.insert(ad_source_model);
            break;
        case AdSourceModel::Status::kReadyToLoadC2S:
            ready_to_load_c2s_sources_model_vector_.insert(ad_source_model);
            break;
        default:
            break;
    }
}

std::set<std::shared_ptr<AdSourceModel>> PlacementModel::GetSortAdSourceModelStatus(AdSourceModel::Status status) {
    switch (status) {
        case AdSourceModel::Status::kLoading:
            return loading_ad_sources_model_vector_;
        case AdSourceModel::Status::kLoaded:
            return loaded_ad_sources_model_vector_;
        case AdSourceModel::Status::kReadyToLoad:
            return ready_to_load_sources_model_vector_;
        case AdSourceModel::Status::kReadyToLoadC2S:
            return ready_to_load_c2s_sources_model_vector_;
            
        default:
            break;
    }
    std::set<std::shared_ptr<AdSourceModel>> empty;
    return empty;
}

void PlacementModel::RemoveAdSourceModel(std::shared_ptr<AdSourceModel> ad_source_model, AdSourceModel::Status status) {
    switch (status) {
        case AdSourceModel::Status::kLoading:
            loading_ad_sources_model_vector_.erase(ad_source_model);
            break;
        case AdSourceModel::Status::kLoaded:
            loaded_ad_sources_model_vector_.erase(ad_source_model);
            break;
        case AdSourceModel::Status::kReadyToLoad:
            ready_to_load_sources_model_vector_.erase(ad_source_model);
            break;
        case AdSourceModel::Status::kReadyToLoadC2S:
            ready_to_load_c2s_sources_model_vector_.erase(ad_source_model);
            break;
            
        default:
            break;
    }
}

bool PlacementModel::RemoveAdSourceModel(const std::string& ad_source_id) {
    auto ad_sources_model_vector_copy = loaded_ad_sources_model_vector_;
    for (auto ad_sources_model: ad_sources_model_vector_copy) {
        if (ad_sources_model->Identifier() == ad_source_id) {
            loaded_ad_sources_model_vector_.erase(ad_sources_model);
            break;
        }
    }
}

END_NAMESPACE_ONETEN_AD
