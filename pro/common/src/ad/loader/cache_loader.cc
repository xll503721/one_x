//
//  cache_loader.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/12/3.
//

#include "cache_loader.h"

#include <ad/oneten_ad_sdk.h>

BEGIN_NAMESPACE_ONETEN_AD

CacheLoader::CacheLoader(std::shared_ptr<LoaderInterface> loader): MainLoader(loader) {
    otlog_info << "";
    cache_service_ = std::make_shared<CacheService>();
}

void CacheLoader::Save(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<PlacementModel> placement_model) {
    super_class::Save(ad_source_model, placement_model);
    otlog_info << "";
    
    cache_service_->Save(ad_source_model, placement_model);
    
    std::map<std::string, std::shared_ptr<void>> map;
    map["placement_model"] = placement_model;
    map["ad_source_model"] = ad_source_model;
    NextLoader(map);
}

void CacheLoader::Remove(std::shared_ptr<AdSourceModel> ad_source, std::shared_ptr<PlacementModel> placement) {
    
}

void CacheLoader::End() {
    super_class::End();
    otlog_info << "";
};


END_NAMESPACE_ONETEN_AD
