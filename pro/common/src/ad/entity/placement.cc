//
//  placement.cpp
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#include "placement.h"
BEGIN_NAMESPACE_ONETEN_AD

Placement::~Placement() {
    otlog_info << "~Placement";
}

Placement::Placement(const std::string& json_string) {
    Parse(json_string);
}

void Placement::Parse(const std::string& json_string) {
    otlog_info << "parse placement json string:" << json_string;
    
    json_ = std::make_shared<BASE_JSON::Json>();
    json_->Parse(json_string.c_str(), json_string.size());
    BASE_JSON::Json id = json_->operator[]("id");
    if (id.IsString()) {
        identifier_ = id.AsString();
    }
    ParseAdSource();
}

void Placement::ParseAdSource() {
    BASE_JSON::Json waterfall_json = json_->operator[]("waterfall");
    if (!waterfall_json.IsArray()) {
        return;
    }
    
    ParseAdSource(AdSource::RequestType::kNormal, waterfall_json);
    
    BASE_JSON::Json c2s_json = json_->operator[]("c2s");
    if (!c2s_json.IsArray()) {
        return;
    }
    
    ParseAdSource(AdSource::RequestType::kC2S, c2s_json);
}

void Placement::ParseAdSource(AdSource::RequestType request_type, BASE_JSON::Json& ad_sources_json) {
    BASE_JSON::Json format_json = json_->operator[]("format");
    for (int i = 0; i < ad_sources_json.Size(); i++) {
        BASE_JSON::Json ad_source_json = ad_sources_json[i];
        BASE_JSON::Json network_id_json = ad_source_json["network_id"];
        BASE_JSON::Json list_json = ad_source_json["list"];
        
        if (!list_json.IsArray() || !network_id_json.IsInteger()) {
            continue;
        }
        
        for (int j = 0; j < list_json.Size(); j++) {
            BASE_JSON::Json network_item = list_json[j];
            network_item.SetJsonObject("network_id", network_id_json);
            
            BASE_JSON::Json request_type_json(static_cast<int32_t>(request_type));
            network_item.SetJsonObject("request_type", request_type_json);
            
            network_item.SetJsonObject("format", format_json);
            
            std::shared_ptr<BASE_JSON::Json> ad_source_ptr = std::make_shared<BASE_JSON::Json>(network_item);
            std::shared_ptr<AdSource> ad_source = std::make_shared<AdSource>(ad_source_ptr);
            
            ad_sources_.push_back(ad_source);
            
            if (ad_source->GetRequestType() == AdSource::RequestType::kS2S) {
                s2s_ad_sources_.push_back(ad_source);
            }
            
            if (ad_source->GetRequestType() == AdSource::RequestType::kNormal) {
                normal_ad_sources_.push_back(ad_source);
            }
            
            if (ad_source->GetRequestType() == AdSource::RequestType::kC2S) {
                c2s_ad_sources_.push_back(ad_source);
            }
        }
    }
}

#pragma mark - getter

std::string Placement::Identifier() {
    return identifier_;
}

std::shared_ptr<BASE_JSON::Json> Placement::GetJson() {
    return json_;
}

END_NAMESPACE_ONETEN_AD
