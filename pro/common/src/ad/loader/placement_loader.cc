//
//  placement_loader.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/12/3.
//

#include "placement_loader.h"

#include <ad/oneten_ad_sdk.h>
#include <ad/model/placement_model.h>

BEGIN_NAMESPACE_ONETEN_AD

PlacementLoader::~PlacementLoader() {
    
}

PlacementLoader::PlacementLoader(std::shared_ptr<LoaderInterface> loader, std::shared_ptr<void> run_loader): MainLoader(loader, run_loader) {
    otlog_info << "";
    
    placement_service_ = std::make_shared<PlacementService>();
}

void PlacementLoader::Start(const std::string& placement_id) {
    super_class::Start(placement_id);
    
    placement_service_->GetPlacementModel("", [=](std::shared_ptr<PlacementModel> placement_model) {
        if (placement_model) {
            std::map<std::string, std::shared_ptr<void>> map;
            map["placement_model"] = std::static_pointer_cast<void>(placement_model);
            NextLoader(map);
        }
    });
}

void PlacementLoader::RequestPlacement(const std::string& placement_id) {
    otlog_info << "";
}

void PlacementLoader::End() {
    super_class::End();
    otlog_info << "";
};


END_NAMESPACE_ONETEN_AD
