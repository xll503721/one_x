//
//  app_service.h
//  oneten_ad_service
//
//  Created by li zhixuan on 2024/1/14.
//

#ifndef ONETEN_AD_SDK_APP_SERVICE_H
#define ONETEN_AD_SDK_APP_SERVICE_H

#include <network/http:s/http_s_client.h>

#include <ad/model/app_settings_model.h>

BEGIN_NAMESPACE_ONETEN_AD

class AppService {
    
public:
    AppService();
    
    using AppSettingsModelCallBack = std::function<void (std::shared_ptr<AppSettingsModel> app_settings_model)>;
    
    void GetAppSettingsModel(const std::string& app_id, AppSettingsModelCallBack call_back);
    void RegisterAdn(AdnId::All id);
    bool QueryWhetherRegister(AdnId::All id);
    
private:
    std::shared_ptr<AppSettingsModel> GetAppSettingsModel();
    
private:
    BASE_HTTPS::HTTPsClient& https_client_;
    std::shared_ptr<AppSettingsModel> app_settings_model_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_APP_SERVICE_H */
