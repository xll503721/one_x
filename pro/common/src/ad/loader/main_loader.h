//
//  main_loader.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/11.
//

#ifndef ONETEN_AD_SDK_MAIN_LOADER_H
#define ONETEN_AD_SDK_MAIN_LOADER_H

#include "run_loader.h"
#include "loader.h"
#include <oneten_object.h>

BEGIN_NAMESPACE_ONETEN_AD

class MainLoader: public ONETEN::Object<MainLoader>, public LoaderInterface {
    
public:
    MainLoader() = default;
    virtual ~MainLoader();
    MainLoader(std::shared_ptr<LoaderInterface> loader = nullptr, std::shared_ptr<void> app_loader = nullptr);

    void Start(const std::string& placement_id) override;
    void Classify(std::shared_ptr<PlacementModel> placement_model) override;
    void StartFlow(std::shared_ptr<PlacementModel> placement, std::shared_ptr<AdSourceModel> save_ad_source_model = nullptr) override;
    void Flow(std::shared_ptr<AdSourceModel> ad_source_model, std::shared_ptr<PlacementModel> placement_model) override;
    void End() override;

    bool GetIsEndInvoke() override;
    bool SetIsEndInvoke(bool is_end_invoke) override;

    void NextLoader(NextLoaderCallBack callBack) override;

protected:
    std::weak_ptr<void> GetRunLoader();

protected:
    void NextLoader(std::map<std::string, std::shared_ptr<void>> params);
    std::weak_ptr<void> app_loader_;
    
private:
    std::shared_ptr<LoaderInterface> mainloader_;
    bool is_end_invoke_ = false;
    NextLoaderCallBack next_loader_call_back_;
};

END_NAMESPACE_ONETEN_AD

#endif /* ONETEN_AD_SDK_MAIN_LOADER_H */
