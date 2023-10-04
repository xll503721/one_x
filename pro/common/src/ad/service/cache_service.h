//
//  ad_srouce_service.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_CACHE_SERVICE_H
#define ONETEN_AD_SDK_CACHE_SERVICE_H

#include <ad/model/ad_source_model.h>
#include <ad/model/placement_model.h>
#include <ad/model/cache_model.h>
#include <error.h>

BEGIN_NAMESPACE_ONETEN_AD

class AdSourceModel;

class CacheService: public ONETEN::Object<CacheService> {
    
public:
    CacheService();
    virtual ~CacheService();
    
    void Save(const std::string& runing_id, std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<PlacementModel> placement_model);
    void Remove(const std::string& ad_source_id);
    
    std::shared_ptr<CacheModel> GetAnyOne(const std::string& placement_id);
    std::shared_ptr<AdSourceModel> GetHighestPrice(const std::string& placement_id);
    
private:
    void Sort(std::shared_ptr<AdSourceCache> obj1, std::shared_ptr<AdSourceCache> obj2);
    
private:
    std::shared_ptr<CacheModel> cacheModel_;
    std::map<std::string, std::shared_ptr<PlacementModel>> placement_model_;
    std::map<std::string, std::string> has_showed_ad_source_id_and_placement_id_map_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_AD_SOURCE_SERVICE_H */
