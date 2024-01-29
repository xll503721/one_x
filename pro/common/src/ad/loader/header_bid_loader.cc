//
//  header_bid_loader.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/12/3.
//

#include "header_bid_loader.h"

#include "../oneten_ad_sdk.h"

BEGIN_NAMESPACE_ONETEN_AD

HeaderBidLoader::~HeaderBidLoader() {
    otlog_info<< "~HeaderBidLoader";
}

HeaderBidLoader::HeaderBidLoader(std::shared_ptr<LoaderInterface> loader, std::shared_ptr<void> run_loader): MainLoader(loader, run_loader) {
    otlog_info << "";
    ad_source_service_ = std::make_shared<AdSourceService>();
    app_service_ = std::make_shared<AppService>();
}

void HeaderBidLoader::Flow(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<PlacementModel> placement_model) {
    super_class::Flow(ad_source_model, placement_model);

    auto c2s_ad_source_models = placement_model->GetSortAdSourceModelStatus(AdSourceModel::Status::kReadyToLoadC2S);
    for (auto c2s_ad_source_model : c2s_ad_source_models) {
        if (!app_service_->QueryWhetherRegister(c2s_ad_source_model->GetAdnId())) {
            ad_source_service_->Register(c2s_ad_source_model, [=](std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error) {
                app_service_->RegisterAdn(c2s_ad_source_model->GetAdnId());
                
                Load(c2s_ad_source_model, placement_model);
            });
            continue;
        }
        Load(c2s_ad_source_model, placement_model);
    }
}

void HeaderBidLoader::Load(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<PlacementModel> placement_model) {
    std::weak_ptr<PlacementModel> w_placement_model = placement_model;
    
    placement_model->RemoveAdSourceModel(ad_source_model, AdSourceModel::Status::kReadyToLoadC2S);
    placement_model->AddAdSourceModel(ad_source_model, AdSourceModel::Status::kLoading);
    ad_source_service_->Load(placement_model, ad_source_model, [=](std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error) {
        
        placement_model->RemoveAdSourceModel(ad_source_model, AdSourceModel::Status::kLoading);
        if (ad_source_model->GetStatus() == AdSourceModel::Status::kLoaded) {        
            placement_model->AddAdSourceModel(ad_source_model, AdSourceModel::Status::kLoaded);
        }
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

void HeaderBidLoader::End() {
    super_class::End();
    otlog_info << "";
};


END_NAMESPACE_ONETEN_AD
