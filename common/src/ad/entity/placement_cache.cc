//
//  placement_cache.cc
//  oneten_ad_entity
//
//  Created by li zhixuan on 2023/5/3.
//

#include "placement_cache.h"

BEGIN_NAMESPACE_ONETEN_AD

PlacementCache::PlacementCache(std::shared_ptr<Placement> placement) {
    identifier_ = placement->GetJson()->operator[]("id").AsString();
}

std::shared_ptr<PlacementCache> PlacementCache::Convert(std::shared_ptr<Placement> placement) {
    std::shared_ptr<PlacementCache> placement_cache = std::make_shared<PlacementCache>(placement);
    return placement_cache;
}

std::string PlacementCache::Identifier() {
    return identifier_;
}

#pragma mark - getter

std::shared_ptr<BASE_JSON::Json> GetJson() {
    
}

END_NAMESPACE_ONETEN_AD
