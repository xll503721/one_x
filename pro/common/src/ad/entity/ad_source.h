//
//  placement.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_AD_SOURCE_H
#define ONETEN_AD_SDK_AD_SOURCE_H

#include <oneten_object.h>
#include <error.h>
#include "entity_interface.h"
#include <json/json.h>
#include "adn_ids.h"

BEGIN_NAMESPACE_ONETEN_AD

static const std::map<AdnId::All, std::string> id_class_map = {
    {AdnId::All::kGDT, "OTGDTAdapter"},
    {AdnId::All::kBaidu, "OTBaiduAdapter"},
    {AdnId::All::kCSJ, "OTCSJAdapter"},
    {AdnId::All::kGromore, "OTGroMoreSource"},
    {AdnId::All::kKS, "OTKSAdapter"},
};

class AdSource: public EntityInterface<AdSource> {
public:
    enum class RequestType {
        kS2S,
        kC2S,
        kNormal,
    };
    
    enum class Style {
        kSplash,
        kInterstitial,
        kBanner,
        kRewardedVideo,
        kNative,
    };
    
    using this_class = AdSource;
    
    std::shared_ptr<AdSource> shared_from_this() {
        return std::static_pointer_cast<AdSource>(shared_from_this());
    }
    
    AdSource(std::shared_ptr<BASE_JSON::Json> json);
    virtual ~AdSource();
    
    void SetLevel(int32_t level);
    int32_t GetLevel();
    
    std::string GetClassName();
    void Parse();
    
    std::shared_ptr<BASE_JSON::Json> GetJson();

    std::string Identifier() override;
    
    READONLY_PROPERTY(double, EcpmPrice, ecpm_price)
    READONLY_PROPERTY(RequestType, RequestType, request_type);
    READONLY_PROPERTY(Style, Style, style);
    READONLY_PROPERTY(AdnId::All, AdnId, adn_id);
    READONLY_PROPERTY(std::string, placementId, placement_id);
    
private:
    int32_t level_;
    std::string clazz_name_;
    
    std::shared_ptr<BASE_JSON::Json> json_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SOURCE_H */
