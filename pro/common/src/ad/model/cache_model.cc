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

bool CacheModel::Save(std::shared_ptr<AdSourceModel> ad_source_model) {
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
