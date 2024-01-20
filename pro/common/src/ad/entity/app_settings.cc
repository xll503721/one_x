//
//  app_settings.cc
//  oneten_ad_entity
//
//  Created by li zhixuan on 2024/1/14.
//

#include "app_settings.h"

BEGIN_NAMESPACE_ONETEN_AD

AppSettings::~AppSettings() {
    otlog_info << "~AppSettings";
}

AppSettings::AppSettings(const std::string& json_string) {
    Parse(json_string);
}

std::string AppSettings::Identifier() {
    return "";
}

void AppSettings::Parse(const std::string& json_string) {
    otlog_info << "parse app settings json string:" << json_string;
    
    json_ = std::make_shared<BASE_JSON::Json>();
    json_->Parse(json_string.c_str(), json_string.size());
    BASE_JSON::Json id = json_->operator[]("id");
    if (id.IsString()) {
        identifier_ = id.AsString();
    }
    
    BASE_JSON::Json ad_sources = json_->operator[]("ad_sources");
    if (ad_sources.IsArray()) {
        for (int i = 0; i < ad_sources.Size(); i++) {
            ADN adn;
            BASE_JSON::Json adn_json = ad_sources[i];
            
            BASE_JSON::Json network_id_json = adn_json["network_id"];
            if (network_id_json.IsInteger()) {
                int64_t adn_id = network_id_json.AsInteger();
                adn.id_ = static_cast<AdnId::All>(adn_id);
            } else {
                continue;
            }
            
            BASE_JSON::Json app_id_json = adn_json["app_id"];
            if (app_id_json.IsString()) {
                adn.app_id_ = app_id_json.AsString();
            }
            
            BASE_JSON::Json app_key_json = adn_json["app_key"];
            if (app_key_json.IsString()) {
                adn.app_key_ = app_key_json.AsString();
            }
            
            id_adn_map_[adn.id_] = adn;
        }
    }
}

std::map<AdnId::All, AppSettings::ADN> AppSettings::GetAllADN() {
    return id_adn_map_;
}

END_NAMESPACE_ONETEN_AD
