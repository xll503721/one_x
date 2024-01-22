//
//  ad_srouce_service_model.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_WATERFALL_SERVICE_MODEL_H
#define ONETEN_AD_SDK_WATERFALL_SERVICE_MODEL_H

#include <ad/model/ad_source_model.h>
#include <ad/model/placement_model.h>

BEGIN_NAMESPACE_ONETEN_AD

class WaterfallService {
    
public:
    WaterfallService() = default;
    
    std::shared_ptr<AdSourceModel> LoadNextAdSource();
    void MarkPreAdSourceFinish();
    
    bool CheckWaterfallFinish(const std::string& load_id, std::shared_ptr<PlacementModel> placement_model);
    bool CheckC2SFinish();
    
private:
    int32_t loading_layer_index_;
    std::vector<std::shared_ptr<AdSourceModel>> loading_ad_unit_model_vector_;
    std::shared_ptr<PlacementModel> loading_placement_model_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SOURCE_SERVICE_MODEL_H */
