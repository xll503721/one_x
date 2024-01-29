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
    std::shared_ptr<AdSourceModel> FilterNextAdSource();
    void MarkPreAdSourceFinish(std::shared_ptr<AdSourceModel> save_ad_source_model);
    
    bool CheckWaterfallFinish(const std::string& load_id, std::shared_ptr<PlacementModel> placement_model);
    bool CheckC2SFinish();
    
private:
    bool WhetherLoadedAdSourceModelEcpmPriceHighest(std::shared_ptr<AdSourceModel> loaded_ad_source_model, AdSourceModel::Status status);
    
private:
    std::unordered_set<std::shared_ptr<AdSourceModel>> loading_ad_unit_model_vector_;
    std::shared_ptr<PlacementModel> loading_placement_model_;
    std::shared_ptr<AdSourceModel> pre_loading_ad_source_model_;
    std::shared_ptr<AdSourceModel> loading_ad_source_model_;
    
    std::shared_ptr<AdSourceModel> finish_ad_source_model_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SOURCE_SERVICE_MODEL_H */
