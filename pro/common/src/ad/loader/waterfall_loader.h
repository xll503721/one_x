//
//  waterfall_loader.h
//  TenoneSDK
//
//  Created by li zhixuan on 2022/11/5.
//

#ifndef ONETEN_AD_SDK_WATERFALL_LOADER_H
#define ONETEN_AD_SDK_WATERFALL_LOADER_H

#include "main_loader.h"

BEGIN_NAMESPACE_ONETEN_AD

class WaterfallLoader: public MainLoader {
    
private:
    using super_class = MainLoader;
    
public:
    WaterfallLoader(std::shared_ptr<LoaderInterface> loader, std::shared_ptr<void> run_loader);
    virtual ~WaterfallLoader();
    
    void Classify(std::shared_ptr<PlacementModel> placement_model);
    void StartFlow(int32_t level, std::shared_ptr<PlacementModel> placement_model);
    void InternalStartFlow(int32_t level, std::shared_ptr<PlacementModel> placement_model);
    
    void End();
    
private:
    std::shared_ptr<PlacementModel> placement_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_WATERFALL_LOADER_H */
