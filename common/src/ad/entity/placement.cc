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

std::vector<std::shared_ptr<AdSource>> Placement::GetRequestAdSources() {
    return ad_sources_;
}

void Placement::Parse(const std::string& json_string) {
    
    test_json_.Parse(json_string.c_str(), json_string.size());
    test_json_["id"];
    
    otlog_info << "parse placement json string:" << json_string;
    json_ = std::make_shared<BASE_JSON::Json>();
    json_->Parse(json_string.c_str(), json_string.size());
    BASE_JSON::Json id = json_->operator[]("id");
    if (id && id.IsString()) {
        identifier_ = id.AsString();
    }
    ParseAdSource();
}

void Placement::ParseAdSource() {
    BASE_JSON::Json ad_sources = json_->operator[]("ad_sources");
    if (ad_sources.IsArray()) {
        size_t count = ad_sources.Size();
        for (int i = 0; i < count; i++) {
            BASE_JSON::Json ad_source_json = ad_sources[i];
            std::shared_ptr<BASE_JSON::Json> ad_source_ptr = std::make_shared<BASE_JSON::Json>(ad_source_json);
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
