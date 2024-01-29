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

@interface OTAdSourceModelObjectDelegate () {
    CPlusPlusPrt _cPlusPlusPrt;
}

@end

@implementation OTAdSourceModelObjectDelegate

- (void)dealloc {
    _cPlusPlusPrt.reset();
}

- (instancetype)init
{
    self = [super init];
    if (self) {
    }
    return self;
}

- (void)setCPlusPlusPrt:(std::shared_ptr<void>)cPlusPlusPrt {
    _cPlusPlusPrt = cPlusPlusPrt;
}

- (void)registerWithUserInfo:(NSDictionary<id, id> *)userInfo error:(NSError *)error {
    auto ad_source_model = std::static_pointer_cast<ONETEN_AD::AdSourceModel>(_cPlusPlusPrt);
    std::map<std::string, std::string> user_info;
    std::shared_ptr<ONETEN::Error> c_error = nullptr;
    if (error) {
        c_error = std::make_shared<ONETEN::Error>(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
    }
    ad_source_model->RegisterCompletion(ad_source_model, c_error);
}

- (void)adWillLoadWithStyleType:(OTAdSourceStyleType)styleType adSourceObject:(id)adSourceObject {
    _adSourceObject = adSourceObject;
}

- (void)adSaveSourceObject:(id)adSourceObject {
    _adSourceObject = adSourceObject;
}

- (void)adDidLoadWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error {
    auto ad_source_model = std::static_pointer_cast<ONETEN_AD::AdSourceModel>(_cPlusPlusPrt);
    if (ad_source_model) {
        std::map<std::string, std::string> user_info;
        std::shared_ptr<ONETEN::Error> c_error = nullptr;
        if (error) {
            c_error = std::make_shared<ONETEN::Error>(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
        }
        
        ad_source_model->LoadCompletion(ad_source_model, c_error);
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
    auto ad_source_model = std::static_pointer_cast<ONETEN_AD::AdSourceModel>(_cPlusPlusPrt);
    if (ad_source_model) {
        std::map<std::string, std::string> user_info;
        std::shared_ptr<ONETEN::Error> c_error = nullptr;
        if (error) {
            c_error = std::make_shared<ONETEN::Error>(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
        }
        ad_source_model->ShowCompletion(ad_source_model, c_error);
    }
}

- (void)adWillDismissWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error {
    auto ad_source_model = std::static_pointer_cast<ONETEN_AD::AdSourceModel>(_cPlusPlusPrt);
    if (ad_source_model) {
        std::map<std::string, std::string> user_info;
        std::shared_ptr<ONETEN::Error> c_error = nullptr;
        if (error) {
            c_error = std::make_shared<ONETEN::Error>(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
        }
        ad_source_model->CloseCompletion(ad_source_model, c_error);
    }
}

- (void)adDidDismissWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error {
    auto ad_source_model = std::static_pointer_cast<ONETEN_AD::AdSourceModel>(_cPlusPlusPrt);
    if (ad_source_model) {
        std::map<std::string, std::string> user_info;
        std::shared_ptr<ONETEN::Error> c_error = nullptr;
        if (error) {
            c_error = std::make_shared<ONETEN::Error>(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
        }
        ad_source_model->CloseCompletion(ad_source_model, c_error);
    }
}

- (void)adWillCloseWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error {
    auto ad_source_model = std::static_pointer_cast<ONETEN_AD::AdSourceModel>(_cPlusPlusPrt);
    if (ad_source_model) {
        std::map<std::string, std::string> user_info;
        std::shared_ptr<ONETEN::Error> c_error = nullptr;
        if (error) {
            c_error = std::make_shared<ONETEN::Error>(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
        }
        ad_source_model->CloseCompletion(ad_source_model, c_error);
    }
}

- (void)adDidCloseWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error {
    auto ad_source_model = std::static_pointer_cast<ONETEN_AD::AdSourceModel>(_cPlusPlusPrt);
    if (ad_source_model) {
        std::map<std::string, std::string> user_info;
        std::shared_ptr<ONETEN::Error> c_error = nullptr;
        if (error) {
            c_error = std::make_shared<ONETEN::Error>(static_cast<int32_t>(error.code), error.localizedDescription.UTF8String, user_info);
        }
        ad_source_model->CloseCompletion(ad_source_model, c_error);
    }
}

- (void)adDidClickWithStyleType:(OTAdSourceStyleType)styleType {
    auto ad_source_model = std::static_pointer_cast<ONETEN_AD::AdSourceModel>(_cPlusPlusPrt);
    if (ad_source_model) {
        ad_source_model->ClickCompletion(ad_source_model);
    }
}

@end
