//
//  ad_srouce_service.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_AD_SOURCE_SERVICE_H
#define ONETEN_AD_SDK_AD_SOURCE_SERVICE_H

#include <ad/model/ad_source_model.h>
#include <error.h>

BEGIN_NAMESPACE_ONETEN_AD

class AdSourceService: public ONETEN::Object<AdSourceService>, public AdSourceModelDelegate {
    
public:
    ~AdSourceService();
    using ActionCompletionInvoke = std::function<void(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error)>;
    
    void Register(std::shared_ptr<AdSourceModel> ad_source_model, ActionCompletionInvoke register_complete);
    void Load(std::shared_ptr<PlacementModel> placement_model, std::shared_ptr<AdSourceModel> ad_source_model, ActionCompletionInvoke load_complete);
    void Show(std::shared_ptr<AdSourceModel> ad_source_model, ActionCompletionInvoke show_complete);
    void Close(std::shared_ptr<AdSourceModel> ad_source_model, ActionCompletionInvoke close_complete);
    void Click(std::shared_ptr<AdSourceModel> ad_source_model, ActionCompletionInvoke click_complete);
    
private:
    void RegisterCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void LoadCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void ShowCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void CloseCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    void ClickCompletion(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<ONETEN::Error> error = nullptr) override;
    
private:
    void* ad_source_service_ios_;
    
    ActionCompletionInvoke register_complete_;
    ActionCompletionInvoke load_complete_;
    ActionCompletionInvoke show_complete_;
    ActionCompletionInvoke close_complete_;
    ActionCompletionInvoke click_complete_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SOURCE_SERVICE_H */
