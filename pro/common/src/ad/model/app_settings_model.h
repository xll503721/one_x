//
//  app_settings_model.h
//  oneten_ad_model
//
//  Created by li zhixuan on 2024/1/9.
//

#ifndef ONETEN_AD_SDK_APP_SETTINGS_MODEL_H
#define ONETEN_AD_SDK_APP_SETTINGS_MODEL_H

#include <oneten_object.h>
#include <ad/entity/app_settings.h>

#include "model.h"

BEGIN_NAMESPACE_ONETEN_AD

class AppSettingsModel: public Model {
    
public:
    AppSettingsModel() = default;
    AppSettingsModel(const std::string& json_string);
    
    std::string Identifier() override {
        return "";
    };
    bool Save() override;
    static std::shared_ptr<AppSettingsModel> Read();
    
    void SetRegisterAdn(AdnId::All adn_id);
    bool GetRegisterAdn(AdnId::All adn_id);
    
private:
    std::shared_ptr<AppSettings> app_settings_;
    
    std::map<AdnId::All, bool> register_adns_map_;
    
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_APP_SETTINGS_MODEL_H */
