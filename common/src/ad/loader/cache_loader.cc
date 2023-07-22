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

void CacheLoader::Save(std::shared_ptr<AdSourceModel> ad_source, std::shared_ptr<PlacementModel> placement) {
    super_class::Save(ad_source, placement);
    otlog_info << "";
    
    cache_service_->Save(ad_source, placement);
}

void CacheLoader::Remove(std::shared_ptr<AdSourceModel> ad_source, std::shared_ptr<PlacementModel> placement) {
    
}

void CacheLoader::End() {
    super_class::End();
    otlog_info << "";
};


END_NAMESPACE_ONETEN_AD
