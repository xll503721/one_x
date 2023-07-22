//
//  placement_cache.h
//  oneten_ad_entity
//
//  Created by li zhixuan on 2023/5/3.
//

#ifndef ONETEN_AD_SDK_PLACEMENT_CACHE_H
#define ONETEN_AD_SDK_PLACEMENT_CACHE_H

#include "entity_interface.h"
#include "ad_source_cache.h"
#include "placement.h"

BEGIN_NAMESPACE_ONETEN_AD

class PlacementCache: public EntityInterface<PlacementCache> {
    
public:
    PlacementCache() = default;
    PlacementCache(std::shared_ptr<Placement> placement);
    
    static std::shared_ptr<PlacementCache> Convert(std::shared_ptr<Placement> placement);
    std::string Identifier() override;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_PLACEMENT_CACHE_H */
