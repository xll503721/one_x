//
//  cache_repository.cc
//  oneten_util
//
//  Created by li zhixuan on 2023/10/1.
//

#include "cache_repository.h"

BEGIN_NAMESPACE_ONETEN_AD

CacheRepository::CacheRepository(AdSDKDelegate& delegate):
delegate_(&delegate) {
    cache_service_ = std::make_shared<CacheService>();
    ad_source_service_ = std::make_shared<AdSourceService>();
}

std::shared_ptr<AdSourceModel> CacheRepository::GetHighestPrice(const std::string& placement_id) {
    auto ad_source_model = cache_service_->GetHighestPrice(placement_id);
    if (ad_source_model) {
        ad_source_service_->Show(ad_source_model, [=](int32_t categroy_type, ONETEN::Error* error) {
            if (delegate_) {
                delegate_->ShowSucceed();
            }
        });
        ad_source_service_->Click(ad_source_model, [=](int32_t categroy_type, ONETEN::Error* error) {
            if (delegate_) {
                delegate_->ClickSucceed();
            }
        });
        ad_source_service_->Close(ad_source_model, [=](int32_t categroy_type, ONETEN::Error* error) {
            if (delegate_) {
                delegate_->CloseSucceed();
            }
            cache_service_->Remove(ad_source_model->Identifier());
        });
    }
    return ad_source_model;
}

std::shared_ptr<AdSourceModel> CacheRepository::GetAnyOne(const std::string& placement_id) {
    if (!(cache_service_->GetAnyOne(placement_id)->GetSortAdSourceModelCache().size() > 0)) {
        return nullptr;
    }
    return cache_service_->GetAnyOne(placement_id)->GetSortAdSourceModelCache()[0];
}

END_NAMESPACE_ONETEN_AD
