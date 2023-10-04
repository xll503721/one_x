//
//  cache_repository.h
//  oneten_util
//
//  Created by li zhixuan on 2023/10/1.
//

#ifndef ONETEN_AD_CACHE_REPOSITORY_H
#define ONETEN_AD_CACHE_REPOSITORY_H

#include <ad/service/cache_service.h>
#include <ad/service/ad_srouce_service.h>
#include <oneten_ad_sdk_delegate.h>

BEGIN_NAMESPACE_ONETEN_AD

class CacheRepository {
    
public:
    CacheRepository(AdSDKDelegate& delegate);
    
    std::shared_ptr<AdSourceModel> GetHighestPrice(const std::string& placement_id);
    std::shared_ptr<CacheModel> GetAnyOne(const std::string& placement_id);
    
private:
    AdSDKDelegate* delegate_;
    
    std::shared_ptr<CacheService> cache_service_;
    std::shared_ptr<AdSourceService> ad_source_service_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_CACHE_REPOSITORY_H */
