//
//  OTAdSourceService.m
//  oneten_ad_service
//
//  Created by li zhixuan on 2023/3/26.
//

#include "cache_service.h"
#include <ad/entity/placement_cache.h>
#include <ad/entity/ad_source_cache.h>
#include <ad/model/model_factory.h>
#include <ad/util/storage.h>

BEGIN_NAMESPACE_ONETEN_AD

CacheService::~CacheService() {
}

CacheService::CacheService() {
}

void CacheService::Save(const std::string& loader_id, std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<PlacementModel> placement_model) {
    auto cache_model = CacheModel::Read(placement_model->Identifier());
    if (!cache_model) {
        auto placement_model_copy = placement_model->ConvertToCacheObject();
        ad_source_model->SetLoadId(loader_id);
        
        cache_model = std::make_shared<CacheModel>(placement_model_copy);
    }
    ad_source_model->ConvertToCacheObject();
    cache_model->Save(ad_source_model);
}

void CacheService::Remove(const std::string& ad_source_id) {
    if (has_showed_ad_source_id_and_placement_id_map_.find(ad_source_id) != has_showed_ad_source_id_and_placement_id_map_.end()) {
        auto placement_id = has_showed_ad_source_id_and_placement_id_map_[ad_source_id];
        auto cache_model = CacheModel::Read(placement_id);
        if (cache_model) {
            cache_model->Remove(ad_source_id);
        }
    }
}

std::shared_ptr<AdSourceModel> CacheService::GetHighestPrice(const std::string& placement_id) {
    auto cache_model = CacheModel::Read(placement_id);
    auto ad_source_model_caches = cache_model->GetSortAdSourceModelCache();
    if (ad_source_model_caches.size() <= 0) {
        return nullptr;
    }
    
    auto ret_ad_source_model = *ad_source_model_caches.begin();
    has_showed_ad_source_id_and_placement_id_map_[ret_ad_source_model->Identifier()] = placement_id;
    return ret_ad_source_model;
}

void CacheService::Sort(std::shared_ptr<AdSourceCache> obj1, std::shared_ptr<AdSourceCache> obj2) {
    
}

std::shared_ptr<CacheModel> CacheService::GetAnyOne(const std::string& placement_id) {
    auto cache_model = CacheModel::Read(placement_id);
    return cache_model;
}

END_NAMESPACE_ONETEN_AD
