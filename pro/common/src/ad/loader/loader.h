//
//  Loader.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/6.
//

#ifndef ONETEN_AD_SDK_LOADER_H
#define ONETEN_AD_SDK_LOADER_H

#include "../model/placement_model.h"
#include "../model/ad_source_model.h"

BEGIN_NAMESPACE_ONETEN_AD


class PlacementLoaderInterface {
public:
    virtual void RequestPlacement(const std::string& placement_id) {};
};

class WaterfallLoaderInterface {
public:
    virtual void Classify(std::shared_ptr<PlacementModel> placement) {};
    virtual void StartFlow(int32_t level, std::shared_ptr<PlacementModel> placement) {};
};

class AdSourceLoaderInterface {
public:
    virtual void Flow(std::shared_ptr<AdSourceModel> ad_source, std::shared_ptr<PlacementModel> placement) {};
};

class CacheLoaderInterface {
public:
    virtual void Save(std::shared_ptr<AdSourceModel> ad_source, std::shared_ptr<PlacementModel> placement) {};
};

class LoaderInterface:  public PlacementLoaderInterface,
                        public WaterfallLoaderInterface,
                        public AdSourceLoaderInterface,
                        public CacheLoaderInterface {
public:
    virtual void Start(const std::string& placement_id) = 0;
    virtual void End() = 0;
    virtual bool GetIsEndInvoke() {};
    virtual bool SetIsEndInvoke(bool is_end_invoke) {};
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_LOADER_H */
