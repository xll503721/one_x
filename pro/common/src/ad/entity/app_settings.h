//
//  app_settings.h
//  oneten_ad_entity
//
//  Created by li zhixuan on 2024/1/14.
//

#ifndef ONETEN_AD_SDK_APP_SETTINGS_H
#define ONETEN_AD_SDK_APP_SETTINGS_H

#include <json/json.h>
#include "entity_interface.h"
#include "adn_ids.h"

BEGIN_NAMESPACE_ONETEN_AD

class AppSettings: EntityInterface<AppSettings> {
    
public:
    struct ADN {
        AdnId::All id_;
        std::string app_id_;
        std::string app_key_;
    };
    
    
    AppSettings() = default;
    explicit AppSettings(const std::string& json_string);
    virtual ~AppSettings();
    
    using this_class = AppSettings;
    
    std::string Identifier() override;
    std::map<AdnId::All, AppSettings::ADN> GetAllADN();
    
private:
    void Parse(const std::string& json_string);
    
private:
    std::shared_ptr<BASE_JSON::Json> json_;
    std::map<AdnId::All, ADN> id_adn_map_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_APP_SETTINGS_H */
