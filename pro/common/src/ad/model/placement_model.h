//
//  placement.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_PLACEMENT_MODEL_H
#define ONETEN_AD_SDK_PLACEMENT_MODEL_H

#include <oneten_object.h>
#include <ad/entity/placement.h>
#include <ad/entity/placement_cache.h>
#include <ad/entity/entity_interface.h>

#include "ad_source_model.h"

#include "model.h"

BEGIN_NAMESPACE_ONETEN_AD

// 定义一个比较函数
struct AdSourceModelCompare {
    bool operator()(const std::shared_ptr<AdSourceModel>& lhs, const std::shared_ptr<AdSourceModel>& rhs) const {
        if (!lhs || !rhs) {
            return false;
        }
        return lhs->GetPrice() > rhs->GetPrice();
    }
};

class PlacementModel: public Model {
    
public:
    PlacementModel() = default;
    PlacementModel(const std::string& json_string);
    PlacementModel(std::shared_ptr<PlacementCache> placement_cache);
    PlacementModel(const PlacementModel& placement_model);
    virtual ~PlacementModel();
    
    std::string Identifier() override;
    
    std::vector<std::shared_ptr<AdSourceModel>> GetAdSourceModel(AdSource::RequestType request_type);
    
    void AddAdSourceModel(std::shared_ptr<AdSourceModel> ad_source_model, AdSourceModel::Status status);
    std::set<std::shared_ptr<AdSourceModel>> GetSortAdSourceModelStatus(AdSourceModel::Status status);
    bool RemoveAdSourceModel(const std::string& ad_source_id);
    void RemoveAdSourceModel(std::shared_ptr<AdSourceModel> ad_source_model, AdSourceModel::Status status);
    
    std::shared_ptr<PlacementModel> ConvertToCacheObject();
private:
    std::shared_ptr<Placement> placement_;
    std::shared_ptr<PlacementCache> placement_cache_;
    
    std::set<std::shared_ptr<AdSourceModel>> ready_to_load_c2s_sources_model_vector_;
    std::set<std::shared_ptr<AdSourceModel>> ready_to_load_sources_model_vector_;
    std::set<std::shared_ptr<AdSourceModel>> loading_ad_sources_model_vector_;
    std::set<std::shared_ptr<AdSourceModel>> loaded_ad_sources_model_vector_;
    
    std::vector<std::shared_ptr<AdSourceModel>> normal_sources_model_vector_;
    std::vector<std::shared_ptr<AdSourceModel>> c2s_sources_model_vector_;
    std::vector<std::shared_ptr<AdSourceModel>> s2s_sources_model_vector_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_PLACEMENT_MODEL_H */
