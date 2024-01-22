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

CacheModel::CacheModel(const std::string& loader_id, std::shared_ptr<PlacementModel> placement_model):
placement_model_(placement_model),
loader_id_(loader_id_) {
    
}

std::string CacheModel::Identifier() {
    return placement_model_->Identifier();
}

std::vector<std::shared_ptr<AdSourceModel>> CacheModel::GetSortAdSourceModelCache() {
    return placement_model_->GetAdSourceModelCache();
}

bool CacheModel::HasCache(std::string load_id, const std::string ad_source_id) {
    auto ad_source_model_cache_list = placement_model_->GetAdSourceModelCache();
    
    for (int i = 0; i < ad_source_model_cache_list.size() && (!load_id.empty() || !ad_source_id.empty()); i++) {
        auto ad_source_model_cache = ad_source_model_cache_list[i];
        
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
    placement_model_->AddAdSourceModel(ad_source_model);
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
