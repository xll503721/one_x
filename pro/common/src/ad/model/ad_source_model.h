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

class AdSourceModel;
class AdSourceModelDelegate {
    
public:
    virtual void RegisterCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) {};
    virtual void LoadCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) {};
    virtual void ShowCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) {};
    virtual void CloseCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) {};
    virtual void ClickCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) {};
};

class PlacementModel;

class AdSourceModel: public Model, public AdSourceModelDelegate {
    
public:
    AdSourceModel(std::shared_ptr<AdSource> ad_source);
    AdSourceModel(std::shared_ptr<AdSourceCache> ad_source_cache);
    
    virtual ~AdSourceModel();
    
    enum class Status {
        kReadyToLoad = 0,
        kReadyToLoadC2S,
        kLoaded,
        kLoading,
        kLoadingC2S,
        kLoadingS2S,
        kLoadFailed,
        kShowed,
        kShowing,
    };
    
    std::string Identifier() override;
    
    void Load();
    void Register();
    bool IsReady();
    
    void SetDelegate(std::shared_ptr<AdSourceModelDelegate> delegate);
    
    void ConvertToCacheObject();
    
    void RegisterCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void LoadCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void ShowCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void CloseCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void ClickCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    
    int32_t GetLevel() {
        return ad_source_->GetLevel();
    }
    
    AdnId::All GetAdnId() {
        if (ad_source_) {
            return ad_source_->GetAdnId();
        } else if (ad_source_cache_) {
            return ad_source_cache_->GetAdnId();
        }
        return ad_source_->GetAdnId();
    }
    
    AdSource::Style GetStyle() {
        if (ad_source_) {
            return ad_source_->GetStyle();
        } else if (ad_source_cache_) {
            return ad_source_cache_->GetStyle();
        }
        return AdSource::Style::kBanner;
    }
    
    double GetPrice() {
        if (ad_source_) {
            return ad_source_->GetEcpmPrice();
        } else if (ad_source_cache_) {
            return ad_source_cache_->GetEcpmPrice();
        }
        return 0;
    }
    
    inline Status GetStatus() {
        return status_;
    }
    inline void SetStatus(Status status) {
        status_ = status;
    }
    
    inline void SetLoadId(const std::string& load_id) {
        load_id_ = load_id;
    }
    
    inline std::string GetLoadId() {
        return load_id_;
    }
    
private:
    std::string load_id_;
    std::shared_ptr<AdSource> ad_source_;
    std::shared_ptr<AdSourceCache> ad_source_cache_;
    PLATFORM_GENERATE()
    
    inline ONETEN_AD::AdSource::RequestType GetRequestType() {
        if (ad_source_) {
            return ad_source_->GetRequestType();
        } else if (ad_source_cache_) {
            return ad_source_cache_->GetRequestType();
        }
        return ad_source_->GetRequestType();
    }
    
    Status status_;
    
    std::weak_ptr<AdSourceModelDelegate> delegate_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SOURCE_MODEL_H */
