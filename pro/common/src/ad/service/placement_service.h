//
//  placement_service.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_PLACEMENT_SERVICE_H
#define ONETEN_AD_SDK_PLACEMENT_SERVICE_H

#include <ad/model/placement_model.h>

BEGIN_NAMESPACE_ONETEN_AD

class PlacementService {
    
public:
    PlacementService(const std::string placement_id, void* delegate);
    
    std::shared_ptr<PlacementModel> GetPlacementMode(const std::string& json_str);
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_PLACEMENT_SERVICE_MODEL_H */
