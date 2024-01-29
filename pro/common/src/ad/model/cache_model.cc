//
//  cache_model.cc
//  oneten_ad_model
//
//  Created by li zhixuan on 2023/5/3.
//

#include "cache_model.h"
#include <ad/util/storage.h>

BEGIN_NAMESPACE_ONETEN_AD

CacheModel::~CacheModel() {
    
}

CacheModel::CacheModel(std::shared_ptr<PlacementModel> placement_model):
placement_model_(placement_model) {
    
}

std::string CacheModel::Identifier() {
    return placement_model_->Identifier();
}

std::set<std::shared_ptr<AdSourceModel>> CacheModel::GetSortAdSourceModelCache(std::string load_id, const std::string ad_source_id) {
    auto ad_source_model_cache_list = placement_model_->GetSortAdSourceModelStatus(AdSourceModel::Status::kLoaded);
    auto ad_source_model_cache_list_copy = ad_source_model_cache_list;
    
    for (auto iterator = ad_source_model_cache_list.begin(); 
         ad_source_model_cache_list.begin() != ad_source_model_cache_list.end() && (!load_id.empty() || !ad_source_id.empty());
         iterator++) {
        std::shared_ptr<AdSourceModel> ad_source_model_cache = *iterator;
        
        auto cache_load_id = ad_source_model_cache->GetLoadId();
        auto is_equal_load_id = (load_id == cache_load_id);
        
        auto cache_ad_source_id = ad_source_model_cache->Identifier();
        auto is_equal_ad_source_id = (ad_source_id == cache_ad_source_id);
        
        if ((load_id.empty() && !is_equal_load_id) || (ad_source_id.empty() && !is_equal_ad_source_id)) {
//            ad_source_model_cache_list_copy.erase(ad_source_model_cache);
        }
    }
    return ad_source_model_cache_list_copy;
}

bool CacheModel::HasCache(std::string load_id, const std::string ad_source_id) {
    auto ad_source_model_cache_list = placement_model_->GetSortAdSourceModelStatus(AdSourceModel::Status::kLoaded);
    
    for (auto iterator = ad_source_model_cache_list.begin(); 
         ad_source_model_cache_list.begin() != ad_source_model_cache_list.end() && (!load_id.empty() || !ad_source_id.empty());
         iterator++) {
        std::shared_ptr<AdSourceModel> ad_source_model_cache = *iterator;
        
        auto cache_load_id = ad_source_model_cache->GetLoadId();
        auto is_equal_load_id = (load_id == cache_load_id);
        
        auto cache_ad_source_id = ad_source_model_cache->Identifier();
        auto is_equal_ad_source_id = (ad_source_id == cache_ad_source_id);
        
        if (load_id.empty() || !is_equal_load_id) {
            continue;
        }
        if (ad_source_id.empty()) {
            return true;
        }
        if (!is_equal_ad_source_id) {
            continue;
        }
        
        return true;
    }

    return (ad_source_model_cache_list.size() > 0);
}

#pragma mark - Model

bool CacheModel::Save(std::shared_ptr<AdSourceModel> ad_source_model) {
    otlog_info << "save ad source id:" << ad_source_model->Identifier() << ", adn id:" << static_cast<int32_t>(ad_source_model->GetAdnId());
    placement_model_->AddAdSourceModel(ad_source_model, AdSourceModel::Status::kLoaded);
    STORAGE_SAVE(CacheModel, shared_from_this())
}

bool CacheModel::Remove(const std::string& ad_source_id) {
    placement_model_->RemoveAdSourceModel(ad_source_id);
}

std::shared_ptr<CacheModel> CacheModel::Read(const std::string& placement_id) {
    auto model_cache = std::dynamic_pointer_cast<CacheModel>(STORAGE_READ(CacheModel, placement_id));
    return model_cache;
}

END_NAMESPACE_ONETEN_AD
