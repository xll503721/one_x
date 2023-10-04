//
//  normal_loader.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/12/3.
//

#ifndef ONETEN_AD_SDK_NORMAL_LOADER_H
#define ONETEN_AD_SDK_NORMAL_LOADER_H

#include "main_loader.h"
#include "run_loader.h"
#include <ad/service/ad_srouce_service.h>
#include <ad/service/cache_service.h>

BEGIN_NAMESPACE_ONETEN_AD

class NormalLoader: public MainLoader {
    
public:
    using super_class = MainLoader;
    
public:
    NormalLoader(std::shared_ptr<LoaderInterface> loader, std::shared_ptr<void> run_loader);
    virtual ~NormalLoader();
    void Flow(std::shared_ptr<AdSourceModel> ad_source, std::shared_ptr<PlacementModel> placement);
    void End();
    
private:
    std::shared_ptr<AdSourceService> ad_source_service_;
    std::shared_ptr<CacheService> cache_service_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_NORMAL_LOADER_H */
