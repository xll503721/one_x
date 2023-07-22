//
//  main_loader.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/11.
//

#ifndef ONETEN_AD_SDK_MAIN_LOADER_H
#define ONETEN_AD_SDK_MAIN_LOADER_H

#include "loader.h"
#include <oneten_object.h>

BEGIN_NAMESPACE_ONETEN_AD

class MainLoader:   public ONETEN::Object<MainLoader>,
                    public LoaderInterface {
    
public:
    MainLoader() = default;
    virtual ~MainLoader();
    MainLoader(std::shared_ptr<LoaderInterface> loader);
    void Start(const std::string& placement_id) override;

    void Classify(std::shared_ptr<PlacementModel> placement_model) override;
                        
    void StartFlow(int32_t level, std::shared_ptr<PlacementModel> placement_model) override;
    void Flow(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<PlacementModel> placement_model) override;
    
    void NextLoader();
    void End() override;

    bool GetIsEndInvoke() override;
    bool SetIsEndInvoke(bool is_end_invoke) override;
    
private:
    std::shared_ptr<LoaderInterface> mainloader_;
    bool is_end_invoke_ = false;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_MAIN_LOADER_H */
