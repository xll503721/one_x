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

BEGIN_NAMESPACE_ONETEN_AD

class AdSourceDelegate {
    
public:
    virtual void RegisterCompletion(std::map<std::string, std::string> user_info, ONETEN::Error* error = nullptr) {};
    virtual void LoadCompletion(int32_t categroy_type, ONETEN::Error* error = nullptr) {};
    virtual void ShowCompletion(int32_t categroy_type, ONETEN::Error* error = nullptr) {};
    virtual void CloseCompletion(int32_t categroy_type, ONETEN::Error* error = nullptr) {};
    virtual void ClickCompletion(int32_t categroy_type, ONETEN::Error* error = nullptr) {};
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
    
    void InitSDK();
    
    std::shared_ptr<BASE_JSON::Json> GetJson();

    std::string Identifier() override;
    
    READONLY_PROPERTY(RequestType, RequestType, request_type);
    READONLY_PROPERTY(Style, Style, style);
    
private:
    int32_t level_;
    std::string clazz_name_;
    std::shared_ptr<BASE_JSON::Json> json_;
    
public:
    std::weak_ptr<AdSourceDelegate> delegate_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SOURCE_H */
