//
//  placement_service_model.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#include "placement_service.h"

BEGIN_NAMESPACE_ONETEN_AD

PlacementService::PlacementService(const std::string placement_id, void* delegate) {
    
}

std::shared_ptr<PlacementModel> PlacementService::GetPlacementMode(const std::string& json_str) {
    std::shared_ptr<PlacementModel> placement_model = std::make_shared<PlacementModel>(json_str);
    return placement_model;
}

END_NAMESPACE_ONETEN_AD
