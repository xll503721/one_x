//
//  header_bid_loader.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/12/3.
//

#include "normal_loader.h"

#include <ad/oneten_ad_sdk.h>
#include <ad/entity/cache.h>

BEGIN_NAMESPACE_ONETEN_AD

NormalLoader::~NormalLoader() {
    
}

NormalLoader::NormalLoader(std::shared_ptr<LoaderInterface> loader): MainLoader(loader) {
    otlog_info << "";
    ad_source_service_ = std::make_shared<AdSourceService>();
    cache_service_ = std::make_shared<CacheService>();
}

void NormalLoader::Flow(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<PlacementModel> placement_model) {
    super_class::Flow(ad_source_model, placement_model);
    if (ad_source_model->GetRequestType() != AdSource::RequestType::kNormal) {
        otlog_fault << "ad source model must be normal type";
        return;
    }
    otlog_info << "flow normal";
    
    std::weak_ptr<PlacementModel> w_placement_model = placement_model;
    std::weak_ptr<AdSourceModel> w_ad_source_model = ad_source_model;
    ad_source_service_->Load(ad_source_model, [=](int32_t categroy_type, ONETEN::Error* error) {
        auto s_placement_model = w_placement_model.lock();
        auto s_ad_source_model = w_ad_source_model.lock();
        
        std::map<std::string, std::shared_ptr<void>> map;
        map["placement_model"] = s_placement_model;
        map["ad_source_model"] = s_ad_source_model;
        map["load_succeed"] = std::make_shared<bool>((error ? false : true));
        NextLoader(map);
    });
}

void NormalLoader::End() {
    super_class::End();
    otlog_info << "";
};


END_NAMESPACE_ONETEN_AD
