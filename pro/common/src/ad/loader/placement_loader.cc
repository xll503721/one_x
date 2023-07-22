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

PlacementLoader::PlacementLoader(std::shared_ptr<LoaderInterface> loader): MainLoader(loader) {
    otlog_info << "";
    
    placement_service_ = std::shared_ptr<PlacementService>();
}

void PlacementLoader::Start(const std::string& placement_id) {
    super_class::Start(placement_id);
    otlog_info << "placement request";
    
    std::string placement_json_string = "{\"id\": \"123456789\", \"ad_sources\": [{\"clazz_name\": \"OTSigmobSource\", \"style\": 1, \"request_type\": 2, \"id\": \"123456789\"}]}";
    std::shared_ptr<PlacementModel> placement_model = placement_service_->GetPlacementMode(placement_json_string);
    
    ONETEN_AD::OnetenAdSDK::GetInstance().GetWaterfallLoader()->Classify(placement_model);
}

void PlacementLoader::RequestPlacement(const std::string& placement_id) {
    otlog_info << "";
}

void PlacementLoader::End() {
    super_class::End();
    otlog_info << "";
};


END_NAMESPACE_ONETEN_AD
