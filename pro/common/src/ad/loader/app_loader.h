//
//  app_loader.h
//  oneten_ad_loader
//
//  Created by li zhixuan on 2024/1/14.
//

#ifndef ONETEN_AD_SDK_APP_LOADER_H
#define ONETEN_AD_SDK_APP_LOADER_H

#include <ad/service/app_service.h>

#include "loader.h"

BEGIN_NAMESPACE_ONETEN_AD

class AppLoader {
    
public:
    AppLoader();
    ~AppLoader();
    
    using RegisterCallBack = std::function<void (bool succeed)>;
    void Register(const std::string& app_id, RegisterCallBack call_back);
    
private:
    std::shared_ptr<AppService> app_service_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_APP_LOADER_H */
