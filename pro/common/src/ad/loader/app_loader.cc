//
//  app_loader.cc
//  oneten_ad_loader
//
//  Created by li zhixuan on 2024/1/14.
//

#include "app_loader.h"

BEGIN_NAMESPACE_ONETEN_AD

AppLoader::AppLoader() {
    app_service_ = std::make_shared<AppService>();
}

AppLoader::~AppLoader() {
    
}

void AppLoader::Register(const std::string& app_id, RegisterCallBack call_back) {
    app_service_->GetAppSettingsModel(app_id, [=](std::shared_ptr<AppSettingsModel> app_settings_model) {
        if (call_back) {
            call_back(app_settings_model != nullptr);
        }
    });
}

END_NAMESPACE_ONETEN_AD
