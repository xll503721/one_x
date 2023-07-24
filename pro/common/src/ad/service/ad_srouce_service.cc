//
//  OTAdSourceService.m
//  oneten_ad_service
//
//  Created by li zhixuan on 2023/3/26.
//

#import "ad_srouce_service.h"


BEGIN_NAMESPACE_ONETEN_AD

AdSourceService::~AdSourceService() {
    ad_source_service_ios_ = nullptr;
}

void AdSourceService::Load(std::shared_ptr<AdSourceModel> ad_source_model, LoadCompletionInvoke load_complete) {
    load_complete_ = load_complete;
    
    ad_source_model->Load(shared_from_this());
}

void AdSourceService::LoadCompletion(int32_t categroy_type, ONETEN::Error* error) {
    if (load_complete_) {
        load_complete_(categroy_type, error);
    }
}

END_NAMESPACE_ONETEN_AD
