//
//  OTAdSource.m
//  oneten_ad_entity
//
//  Created by li zhixuan on 2023/4/8.
//

#import "OTAdSourceModelObjectDelegate.h"
#import "OTAdSourceProtocol.h"
#include <ad/model/ad_source_model.h>
#include <ad/entity/ad_source.h>

@interface OTAdSourceModelObjectDelegate ()

@end

@implementation OTAdSourceModelObjectDelegate

@synthesize cPlusPlusPrt;

- (void)dealloc {
    
}

- (instancetype)init
{
    self = [super init];
    if (self) {
    }
    return self;
}

- (void)registerWithUserInfo:(NSDictionary<id, id> *)userInfo error:(NSError *)error {
    ONETEN_AD::AdSourceModel* ad_source_cache_model = static_cast<ONETEN_AD::AdSourceModel *>(self.cPlusPlusPrt);
    if (ad_source_cache_model) {
        std::map<std::string, std::string> user_info;
        ONETEN::Error *c_error = nullptr;
        if (error) {
            ONETEN::Error cc_error(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
            c_error = &cc_error;
        }
        ad_source_cache_model->RegisterCompletion(user_info, c_error);
    }
}

- (void)adWillLoadWithStyleType:(OTAdSourceStyleType)styleType adSourceObject:(id)adSourceObject {
    _adSourceObject = adSourceObject;
}

- (void)adDidLoadWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error {
    ONETEN_AD::AdSourceModel* ad_source_model = static_cast<ONETEN_AD::AdSourceModel *>(self.cPlusPlusPrt);
    if (ad_source_model) {
        std::map<std::string, std::string> user_info;
        if (error) {
            ONETEN::Error c_error(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
            ad_source_model->LoadCompletion((int32_t)styleType, &c_error);
            return;
        }
        ad_source_model->LoadCompletion((int32_t)styleType);
    }
}

- (void)adWillShowWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error {
//    ONETEN_AD::AdSourceModel* ad_source_cache_model = static_cast<ONETEN_AD::AdSourceModel *>(self.cPlusPlusPrt);
//    if (ad_source_cache_model) {
//        std::map<std::string, std::string> user_info;
//        ONETEN::Error *c_error = nullptr;
//        if (error) {
//            ONETEN::Error cc_error(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
//            c_error = &cc_error;
//        }
//        ad_source_cache_model->ShowCompletion((int32_t)styleType, c_error);
//    }
}

- (void)adDidShowWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error {
    ONETEN_AD::AdSourceModel* ad_source_cache_model = static_cast<ONETEN_AD::AdSourceModel *>(self.cPlusPlusPrt);
    if (ad_source_cache_model) {
        std::map<std::string, std::string> user_info;
        ONETEN::Error *c_error = nullptr;
        if (error) {
            ONETEN::Error cc_error(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
            c_error = &cc_error;
        }
        ad_source_cache_model->ShowCompletion((int32_t)styleType, c_error);
    }
}

- (void)adWillDismissWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error {
    ONETEN_AD::AdSourceModel* ad_source_cache_model = static_cast<ONETEN_AD::AdSourceModel *>(self.cPlusPlusPrt);
    if (ad_source_cache_model) {
        std::map<std::string, std::string> user_info;
        ONETEN::Error *c_error = nullptr;
        if (error) {
            ONETEN::Error cc_error(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
            c_error = &cc_error;
        }
        ad_source_cache_model->CloseCompletion((int32_t)styleType, c_error);
    }
}

- (void)adDidDismissWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error {
    ONETEN_AD::AdSourceModel* ad_source_cache_model = static_cast<ONETEN_AD::AdSourceModel *>(self.cPlusPlusPrt);
    if (ad_source_cache_model) {
        std::map<std::string, std::string> user_info;
        ONETEN::Error *c_error = nullptr;
        if (error) {
            ONETEN::Error cc_error(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
            c_error = &cc_error;
        }
        ad_source_cache_model->CloseCompletion((int32_t)styleType, c_error);
    }
}

- (void)adWillCloseWithStyleType:(OTAdSourceStyleType)styleType {
    
}

- (void)adDidCloseWithStyleType:(OTAdSourceStyleType)styleType {
    
}

- (void)adDidClickWithStyleType:(OTAdSourceStyleType)styleType {
    ONETEN_AD::AdSourceModel* ad_source_cache_model = static_cast<ONETEN_AD::AdSourceModel *>(self.cPlusPlusPrt);
    if (ad_source_cache_model) {
        ad_source_cache_model->ClickCompletion((int32_t)styleType);
    }
}

@end
