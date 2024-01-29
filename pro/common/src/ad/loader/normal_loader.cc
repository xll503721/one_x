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
    otlog_info << "~NormalLoader";
}

NormalLoader::NormalLoader(std::shared_ptr<LoaderInterface> loader, std::shared_ptr<void> run_loader): MainLoader(loader, run_loader) {
    otlog_info << "";
    ad_source_service_ = std::make_shared<AdSourceService>();
    cache_service_ = std::make_shared<CacheService>();
    placement_service_ = std::make_shared<PlacementService>();
    app_service_ = std::make_shared<AppService>();
}

void NormalLoader::Flow(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<PlacementModel> placement_model) {
    super_class::Flow(ad_source_model, placement_model);
    if (ad_source_model->GetRequestType() != AdSource::RequestType::kNormal) {
        otlog_fault << "ad source model must be normal type";
        return;
    }
    
    std::weak_ptr<PlacementModel> w_placement_model = placement_model;
    std::weak_ptr<AdSourceModel> w_ad_source_model = ad_source_model;
    
    if (!app_service_->QueryWhetherRegister(ad_source_model->GetAdnId())) {
        ad_source_service_->Register(ad_source_model, [=](std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error) {
            app_service_->RegisterAdn(ad_source_model->GetAdnId());
            
            Load(ad_source_model, placement_model);
        });
        return;
    }
    
    Load(ad_source_model, placement_model);
}

void NormalLoader::Load(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<PlacementModel> placement_model) {
    std::weak_ptr<PlacementModel> w_placement_model = placement_model;
    std::weak_ptr<AdSourceModel> w_ad_source_model = ad_source_model;
    
    ad_source_service_->Load(placement_model, ad_source_model, [=](std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error) {
        auto s_placement_model = w_placement_model.lock();
        
        std::map<std::string, std::shared_ptr<void>> map;
        if (s_placement_model) {
            map["placement_model"] = s_placement_model;
        }
        map["ad_source_model"] = ad_source_model;
        
        if (error) {
            map["error"] = error;
        }
        NextLoader(map);
    });
}

void NormalLoader::End() {
    super_class::End();
    otlog_info << "";
};


END_NAMESPACE_ONETEN_AD
