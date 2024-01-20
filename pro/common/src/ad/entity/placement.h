//
//  placement.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_PLACEMENT_H
#define ONETEN_AD_SDK_PLACEMENT_H

#include <oneten_object.h>
#include "ad_source.h"
#include "entity_interface.h"

BEGIN_NAMESPACE_ONETEN_AD

class Placement: public EntityInterface<Placement> {
    
public:
    Placement() = default;
    explicit Placement(const std::string& json_string);
    virtual ~Placement();
    
    std::vector<std::shared_ptr<AdSource>> GetRequestAdSources();
    
    std::string Identifier() override;
    std::shared_ptr<BASE_JSON::Json> GetJson();
    
private:
    void Parse(const std::string& json_string);
    void ParseAdSource();
    void ParseAdSource(AdSource::RequestType request_type, BASE_JSON::Json& ad_sources_json);
    
private:
    std::vector<std::shared_ptr<AdSource>> requesting_ad_sources_;
    std::vector<std::shared_ptr<AdSource>> completed_ad_sources_;
    std::vector<std::shared_ptr<AdSource>> ad_sources_;
    std::vector<std::shared_ptr<AdSource>> s2s_ad_sources_;
    std::vector<std::shared_ptr<AdSource>> c2s_ad_sources_;
    std::vector<std::shared_ptr<AdSource>> normal_ad_sources_;
    
    std::shared_ptr<BASE_JSON::Json> json_;
    BASE_JSON::Json test_json_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_PLACEMENT_H */
