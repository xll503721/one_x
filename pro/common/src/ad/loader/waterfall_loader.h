//
//  waterfall_loader.h
//  TenoneSDK
//
//  Created by li zhixuan on 2022/11/5.
//

#ifndef ONETEN_AD_SDK_WATERFALL_LOADER_H
#define ONETEN_AD_SDK_WATERFALL_LOADER_H

#include "main_loader.h"
#include <ad/service/waterfall_service.h>

BEGIN_NAMESPACE_ONETEN_AD

class WaterfallLoader: public MainLoader {
    
private:
    using super_class = MainLoader;
    
public:
    WaterfallLoader(std::shared_ptr<LoaderInterface> loader, std::shared_ptr<void> run_loader);
    virtual ~WaterfallLoader();
    
    void Classify(std::shared_ptr<PlacementModel> placement_model);
    void StartFlow(std::shared_ptr<PlacementModel> placement_model);
    void End();
    
    void SetWaterfallService(std::shared_ptr<WaterfallService> waterfall_service);
    std::shared_ptr<WaterfallService> GetWaterfallService();
    
protected:
    std::shared_ptr<WaterfallService> waterfall_service_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_WATERFALL_LOADER_H */
