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

MainLoader::MainLoader(std::shared_ptr<LoaderInterface> loader, std::shared_ptr<void> run_loader):
mainloader_(loader),
run_loader_(run_loader) {
}

void MainLoader::Start(const std::string& placement_id) {
    if (mainloader_) {
        mainloader_->Start(placement_id);
    }
}

void MainLoader::Classify(std::shared_ptr<PlacementModel> placement) {
    if (mainloader_) {
        mainloader_->Classify(placement);
    }
}

void MainLoader::StartFlow(std::shared_ptr<PlacementModel> placement) {
    if (mainloader_) {
        mainloader_->StartFlow(placement);
    }
}

void MainLoader::Flow(std::shared_ptr<AdSourceModel> ad_source, std::shared_ptr<PlacementModel> placement) {
    if (mainloader_) {
        mainloader_->Flow(ad_source, placement);
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
    return run_loader_;
}

END_NAMESPACE_ONETEN_AD
