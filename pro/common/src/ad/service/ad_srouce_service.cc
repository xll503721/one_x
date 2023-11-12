//
//  OTAdSourceService.m
//  oneten_ad_service
//
//  Created by li zhixuan on 2023/3/26.
//

#import "ad_srouce_service.h"
#include <analytics/tracker.h>

BEGIN_NAMESPACE_ONETEN_AD

AdSourceService::~AdSourceService() {
    ad_source_service_ios_ = nullptr;
}

void AdSourceService::Load(std::shared_ptr<AdSourceModel> ad_source_model, ActionCompletionInvoke load_complete) {
    load_complete_ = load_complete;
    ad_source_model->SetDelegate(shared_from_this());
    ad_source_model->AdnLoad();
}

void AdSourceService::Show(std::shared_ptr<AdSourceModel> ad_source_model,ActionCompletionInvoke show_complete) {
    ad_source_model->SetDelegate(shared_from_this());
    show_complete_ = show_complete;
}

void AdSourceService::Close(std::shared_ptr<AdSourceModel> ad_source_model, ActionCompletionInvoke close_complete) {
    ad_source_model->SetDelegate(shared_from_this());
    close_complete_ = close_complete;
}

void AdSourceService::Click(std::shared_ptr<AdSourceModel> ad_source_model, ActionCompletionInvoke click_complete) {
    ad_source_model->SetDelegate(shared_from_this());
    click_complete_ = click_complete;
}

#pragma mark - AdSourceDelegate
void AdSourceService::LoadCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
    std::map<std::string, std::string> event_properties;
    BASE_ANALYTICS::Tracker::DefaultTracker().Send("load", event_properties);
    
    if (load_complete_) {
        load_complete_(categroy_type, error);
    }
}

void AdSourceService::ShowCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
    std::map<std::string, std::string> event_properties;
    BASE_ANALYTICS::Tracker::DefaultTracker().Send("show", event_properties);
    
    if (show_complete_) {
        show_complete_(categroy_type, error);
    }
}

void AdSourceService::CloseCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
    std::map<std::string, std::string> event_properties;
    BASE_ANALYTICS::Tracker::DefaultTracker().Send("close", event_properties);
    
    if (close_complete_) {
        close_complete_(categroy_type, error);
    }
}

void AdSourceService::ClickCompletion(int32_t categroy_type, std::shared_ptr<ONETEN::Error> error) {
    std::map<std::string, std::string> event_properties;
    BASE_ANALYTICS::Tracker::DefaultTracker().Send("click", event_properties);
    
    if (click_complete_) {
        click_complete_(categroy_type, error);
    }
}

END_NAMESPACE_ONETEN_AD
