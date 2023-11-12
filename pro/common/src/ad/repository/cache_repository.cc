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
        ad_source_service_->Show(ad_source_model, [=](int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
            if (delegate_) {
                AdSDKDelegate::ActionType action = error ? AdSDKDelegate::ActionType::kShowFail : AdSDKDelegate::ActionType::kShowSuccess;
                delegate_->ActionCompletion(action, placement_id);
            }
        });
        ad_source_service_->Click(ad_source_model, [=](int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
            if (delegate_) {
                AdSDKDelegate::ActionType action = error ? AdSDKDelegate::ActionType::kClickFail : AdSDKDelegate::ActionType::kClickSuccess;
                delegate_->ActionCompletion(action, placement_id);
            }
        });
        ad_source_service_->Close(ad_source_model, [=](int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
            if (delegate_) {
                AdSDKDelegate::ActionType action = error ? AdSDKDelegate::ActionType::kCloseFail : AdSDKDelegate::ActionType::kCloseSuccess;
                delegate_->ActionCompletion(action, placement_id);
            }
            cache_service_->Remove(ad_source_model->Identifier());
        });
    }
    return ad_source_model;
}

std::shared_ptr<AdSourceModel> CacheRepository::GetAnyOne(const std::string& placement_id) {
    auto cache_model = cache_service_->GetAnyOne(placement_id);
    if (!cache_model || cache_model->GetSortAdSourceModelCache().size() <= 0) {
        return nullptr;
    }
    return cache_service_->GetAnyOne(placement_id)->GetSortAdSourceModelCache()[0];
}

END_NAMESPACE_ONETEN_AD
