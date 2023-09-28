//
//  placement_service.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_PLACEMENT_SERVICE_H
#define ONETEN_AD_SDK_PLACEMENT_SERVICE_H

#include <ad/model/placement_model.h>
#include <network/http:s/http_s_client.h>

BEGIN_NAMESPACE_ONETEN_AD

class PlacementService {
    
public:
    PlacementService();
    
    using PlacementModelCallBack = std::function<void (std::shared_ptr<PlacementModel> placement_model)>;
    void GetPlacementModel(const std::string& placement_id, PlacementModelCallBack callBack);
    
private:
    BASE_HTTPS::HTTPsClient& https_client_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_PLACEMENT_SERVICE_MODEL_H */
