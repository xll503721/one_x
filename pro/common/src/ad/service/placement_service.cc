//
//  placement_service_model.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#include "placement_service.h"

BEGIN_NAMESPACE_ONETEN_AD

static const std::string& host = "http://192.168.0.105:8088";
static const std::string& path = "/adn/queryId";

PlacementService::PlacementService(): https_client_(BASE_HTTPS::HTTPsClient::DefaultClient(host)) {
    
}

void PlacementService::GetPlacementModel(const std::string& placement_id, PlacementModelCallBack callBack) {
    otlog_info << "placement request";
    https_client_.Get(path, [=](BASE_HTTPS::HTTPsClient* client, BASE_HTTPS::HTTPsClient::Status status, const std::string& body) {
        std::shared_ptr<PlacementModel> placement_model = nullptr;
        do {
            if (status != BASE_HTTPS::HTTPsClient::Status::kStatus200) {
                otlog_error << "placement request error:" << static_cast<int32_t>(status) << ", msg:" << body.c_str();
                break;
            }
            
            std::string placement_json_string = "{\"id\":\"123456789\",\"format\":0,\"c2s\":[],\"waterfall\":[{\"network_id\":0,\"list\":[{\"id\":\"111111\",\"placement_id\":\"123456\",\"ecpm_price\":100.0,\"params\":{}},{\"id\":\"2222\",\"placement_id\":\"123456789\",\"ecpm_price\":100.0,\"params\":{}},{\"id\":\"3333\",\"placement_id\":\"123456\",\"ecpm_price\":100.0,\"params\":{}},{\"id\":\"44444\",\"placement_id\":\"123456789\",\"ecpm_price\":100.0,\"params\":{}}]}]}";
            placement_model = std::make_shared<PlacementModel>(placement_json_string);
            for (auto normal_ad_source_model : placement_model->GetAdSourceModel(AdSource::RequestType::kNormal)) {
                placement_model->AddAdSourceModel(normal_ad_source_model, AdSourceModel::Status::kReadyToLoad);
            }
            for (auto normal_ad_source_model : placement_model->GetAdSourceModel(AdSource::RequestType::kC2S)) {
                placement_model->AddAdSourceModel(normal_ad_source_model, AdSourceModel::Status::kReadyToLoadC2S);
            }
            
            
        } while (false);
        
        if (callBack) {
            callBack(placement_model);
        }
    });
}

void PlacementService::SetPlacementModel(std::shared_ptr<PlacementModel> placement_model) {
    placement_model_ = placement_model;
}

END_NAMESPACE_ONETEN_AD
