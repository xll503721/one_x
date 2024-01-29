//
//  app_service.cc
//  oneten_ad_service
//
//  Created by li zhixuan on 2024/1/14.
//

#include "app_service.h"

static const std::string& host = "http://192.168.0.105:8088";
static const std::string& path = "/adn/queryId";

BEGIN_NAMESPACE_ONETEN_AD

AppService::AppService(): https_client_(BASE_HTTPS::HTTPsClient::DefaultClient(host)) {
    
}

void AppService::GetAppSettingsModel(const std::string& app_id, AppSettingsModelCallBack call_back) {
    https_client_.Get(path, [=](BASE_HTTPS::HTTPsClient* client, BASE_HTTPS::HTTPsClient::Status status, const std::string& body) {
        if (status != BASE_HTTPS::HTTPsClient::Status::kStatus200) {
            otlog_error << "app settings request error:" << static_cast<int32_t>(status) << ", msg:" << body.c_str();
            if (call_back) {
                call_back(nullptr);
            }
            return;
        }
        
        std::string app_settings_json_string = "{\"id\":\"123456789\",\"ad_sources\":[{\"network_id\":3,\"app_id\":\"11111\",\"app_key\":\"22222\"},{\"network_id\":0,\"app_id\":\"11111\",\"app_key\":\"22222\"}]}";
        app_settings_model_ = std::make_shared<AppSettingsModel>(app_settings_json_string);
        app_settings_model_->Save();
        
        if (call_back) {
            call_back(app_settings_model_);
        }
    });
}

std::shared_ptr<AppSettingsModel> AppService::GetAppSettingsModel() {
    if (!app_settings_model_) {
        app_settings_model_ = AppSettingsModel::Read();
    }
    return app_settings_model_;
}

void AppService::RegisterAdn(AdnId::All id) {
    GetAppSettingsModel()->SetRegisterAdn(id);
}

bool AppService::QueryWhetherRegister(AdnId::All id) {
    return GetAppSettingsModel()->GetRegisterAdn(id);
}

END_NAMESPACE_ONETEN_AD
