//
//  ad_source_model.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_AD_SOURCE_MODEL_H
#define ONETEN_AD_SDK_AD_SOURCE_MODEL_H

#include <oneten_object.h>
#include <ad/entity/ad_source.h>
#include <ad/entity/ad_source_cache.h>
#include <ad/entity/placement_cache.h>

#include "model.h"

BEGIN_NAMESPACE_ONETEN_AD

class PlacementModel;

class AdSourceModel: public Model, public AdSourceDelegate {
    
public:
    AdSourceModel(std::shared_ptr<AdSource> ad_source);
    AdSourceModel(std::shared_ptr<AdSourceCache> ad_source_cache);
    
    virtual ~AdSourceModel();
    
    enum class Status {
        kNormal,
        kLoading,
        kLoaded,
    };
    
    std::string Identifier() override;
    
    void AdnLoad();
    void Register();
    bool IsReady();
    
    void SetDelegate(std::shared_ptr<AdSourceDelegate> delegate);
    
    void ConvertToCacheObject();
    
    void RegisterCompletion(std::map<std::string, std::string> user_info, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void LoadCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void ShowCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void CloseCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void ClickCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    
    int32_t GetLevel() {
        return ad_source_->GetLevel();
    }
    
    AdSource::Style GetStyle() {
        if (ad_source_) {
            return ad_source_->GetStyle();
        } else if (ad_source_cache_) {
            return ad_source_cache_->GetStyle();
        }
        return AdSource::Style::kBanner;
    }
    
    inline Status GetStatus() {
        return status_;
    }
    inline void SetStatus(Status status) {
        status_ = status;
    }
    
private:
    void Load();
    
private:
    std::shared_ptr<AdSource> ad_source_;
    std::shared_ptr<AdSourceCache> ad_source_cache_;
    PLATFORM_GENERATE()
    
    inline ONETEN_AD::AdSource::RequestType GetRequestType() {
        return ad_source_->GetRequestType();
    }
    
    Status status_;
    
    std::weak_ptr<AdSourceDelegate> delegate_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SOURCE_MODEL_H */
