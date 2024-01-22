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

class PlacementModel: public Model {
    
public:
    PlacementModel() = default;
    PlacementModel(const std::string& json_string);
    PlacementModel(std::shared_ptr<PlacementCache> placement_cache);
    PlacementModel(const PlacementModel& placement_model);
    virtual ~PlacementModel();
    
    std::string Identifier() override;
    
    std::vector<std::shared_ptr<AdSourceModel>> GetAdSourceModelStatus(AdSourceModel::Status status);
    std::vector<std::shared_ptr<AdSourceModel>> GetAdSourceModel(AdSource::RequestType request_type);
    
    std::shared_ptr<PlacementModel> ConvertToCacheObject();
    void AddAdSourceModel(std::shared_ptr<AdSourceModel> ad_source_model);
    std::vector<std::shared_ptr<AdSourceModel>> GetAdSourceModelCache();
    bool RemoveAdSourceModel(const std::string& ad_source_id);
    
public:
    std::shared_ptr<Placement> placement_;
    std::shared_ptr<PlacementCache> placement_cache_;
    std::vector<std::shared_ptr<AdSourceModel>> ad_sources_model_vector_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_PLACEMENT_MODEL_H */
