//
//  app_settings_model.cc
//  oneten_ad_model
//
//  Created by li zhixuan on 2024/1/9.
//

#include "app_settings_model.h"
#include <ad/util/storage.h>

BEGIN_NAMESPACE_ONETEN_AD

AppSettingsModel::AppSettingsModel(const std::string& json_string) {
    app_settings_ = std::make_shared<AppSettings>(json_string);
}

bool AppSettingsModel::Save() {
    STORAGE_SAVE(AppSettingsModel, shared_from_this());
}

std::shared_ptr<AppSettingsModel> AppSettingsModel::Read() {
    auto app_settings_model = std::dynamic_pointer_cast<AppSettingsModel>(STORAGE_READ(AppSettingsModel, ""));
    return app_settings_model;
}

void AppSettingsModel::SetRegisterAdn(AdnId::All adn_id) {
    register_adns_map_[adn_id] = true;
}

bool AppSettingsModel::GetRegisterAdn(AdnId::All adn_id) {
    return (register_adns_map_.find(adn_id) != register_adns_map_.end());
}

END_NAMESPACE_ONETEN_AD
