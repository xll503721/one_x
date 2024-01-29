//
//  ad_source_cache.cc
//  oneten_ad_entity
//
//  Created by li zhixuan on 2023/5/3.
//

#include "ad_source_cache.h"
#include <thread/thread_pool.h>

BEGIN_NAMESPACE_ONETEN_AD

AdSourceCache::AdSourceCache(std::shared_ptr<AdSource> ad_source):
//platform_(ad_source->GetPlatform()),
json_(ad_source->GetJson()) {
    Parse();
}

AdSourceCache::~AdSourceCache() {
    otlog_info << "~AdSourceCache";
}

std::string AdSourceCache::Identifier() {
    return identifier_;
}

std::shared_ptr<AdSourceCache> AdSourceCache::Convert(std::shared_ptr<AdSource> ad_source) {
    std::shared_ptr<AdSourceCache> ad_source_cache = std::make_shared<AdSourceCache>(ad_source);
    return ad_source_cache;
}

void AdSourceCache::Parse() {
    BASE_JSON::Json id = json_->operator[]("id");
    if (id.IsString()) {
        identifier_ = id.AsString();
    }
    
    BASE_JSON::Json style = json_->operator[]("format");
    if (style.IsInteger()) {
        style_ = static_cast<AdSource::Style>(style.AsInteger());
    }
    
    BASE_JSON::Json network_id_json = json_->operator[]("network_id");
    if (network_id_json.IsInteger()) {
        adn_id_ = static_cast<AdnId::All>(network_id_json.AsInteger());
    }
    
    BASE_JSON::Json request_type = json_->operator[]("request_type");
    if (request_type.IsInteger()) {
        request_type_ = static_cast<AdSource::RequestType>(request_type.AsInteger());
    }
    
    BASE_JSON::Json ecpm_price_json = json_->operator[]("ecpm_price");
    if (ecpm_price_json.IsReal()) {
        ecpm_price_ = ecpm_price_json.AsReal();
    }
    
    json_ = nullptr;
}

bool AdSourceCache::IsReady() {
    PLATFORM_SET_DELEGATE(shared_from_this());
    auto style = PLATFORM_VAR_GENERATE(static_cast<unsigned long>(GetStyle()));
    PLATFORM_INVOKE(&style)
    return static_cast<bool>(GET_PLATFORM_INVOKE_RESULT);
}

END_NAMESPACE_ONETEN_AD
