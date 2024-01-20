//
//  cache_model.h
//  oneten_ad_model
//
//  Created by li zhixuan on 2023/5/3.
//

#ifndef ONETEN_AD_SDK_CACHE_MODEL_H
#define ONETEN_AD_SDK_CACHE_MODEL_H

#include <oneten_object.h>
#include <ad/entity/cache.h>
#include <ad/model/placement_model.h>
#include <ad/model/ad_source_model.h>
#include "model.h"

BEGIN_NAMESPACE_ONETEN_AD

class CacheModel: public Model {
    
public:
    CacheModel(const std::string& loader_id, std::shared_ptr<PlacementModel> placement_model);
    
    virtual ~CacheModel();
    std::string Identifier() override;
    bool Save(std::shared_ptr<AdSourceModel> ad_source_model);
    bool Remove(const std::string& ad_source_id);
    static std::shared_ptr<CacheModel> Read(const std::string& placement_id);
    
    std::vector<std::shared_ptr<AdSourceModel>> GetSortAdSourceModelCache();
    bool HasCache(const std::string load_id = "", const std::string ad_source_id = "");
    
private:
    std::shared_ptr<PlacementModel> placement_model_;
    std::string loader_id_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_CACHE_MODEL_H */
