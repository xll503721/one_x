//
//  main_loader.cc
//  SDKCommon
//
//  Created by li zhixuan on 2022/11/11.
//

#include "main_loader.h"

BEGIN_NAMESPACE_ONETEN_AD

MainLoader::~MainLoader() {
}

MainLoader::MainLoader(std::shared_ptr<LoaderInterface> loader, std::shared_ptr<void> app_loader):
mainloader_(loader),
app_loader_(app_loader) {
}

void MainLoader::Start(const std::string& placement_id) {
    if (mainloader_) {
        mainloader_->Start(placement_id);
        CastAndMergeParams();
    }
}

void MainLoader::Classify(std::shared_ptr<PlacementModel> placement) {
    if (mainloader_) {
        mainloader_->Classify(placement);
        CastAndMergeParams();
    }
}

void MainLoader::StartFlow(std::shared_ptr<PlacementModel> placement, std::shared_ptr<AdSourceModel> save_ad_source_model) {
    if (mainloader_) {
        mainloader_->StartFlow(placement, save_ad_source_model);
        CastAndMergeParams();
    }
}

void MainLoader::Flow(std::shared_ptr<AdSourceModel> ad_source, std::shared_ptr<PlacementModel> placement) {
    if (mainloader_) {
        mainloader_->Flow(ad_source, placement);
        CastAndMergeParams();
    }
}

void MainLoader::End() {
    if (mainloader_ && !mainloader_->GetIsEndInvoke()) {
        mainloader_->SetIsEndInvoke(true);
        mainloader_->End();
    }
}

void MainLoader::NextLoader(std::map<std::string, std::shared_ptr<void>> params) {
    if (next_loader_call_back_) {
        next_loader_call_back_(params);
    }
}

void MainLoader::NextLoader(NextLoaderCallBack callBack) {
    next_loader_call_back_ = callBack;
}

bool MainLoader::GetIsEndInvoke() {
    return is_end_invoke_;
}

bool MainLoader::SetIsEndInvoke(bool is_end_invoke) {
    is_end_invoke_ = is_end_invoke;
}

std::weak_ptr<void> MainLoader::GetRunLoader() {
    return app_loader_;
}

void MainLoader::CastAndMergeParams() {
    auto main_loader_prt = std::dynamic_pointer_cast<MainLoader>(mainloader_);
    if (main_loader_prt) {
        MergeParams(main_loader_prt->GetParams());
    }
}

END_NAMESPACE_ONETEN_AD
