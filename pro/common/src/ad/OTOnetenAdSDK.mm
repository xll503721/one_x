//
//  OTOneTenAdSDK.m
//  SDKCommon
//
//  Created by li zhixuan on 2022/12/11.
//

#import "OTOnetenAdSDK.h"
#include "oneten_ad_sdk.h"
#include "oneten_ad_sdk_delegate.h"

@interface OTOnetenAdSDK ()

@property ONETEN_AD::AdSDKDelegate sdk_delegate;

/// init app id
/// @param appId appId description
- (void)startWithAppId:(NSString *)appId;

@end

@implementation OTOnetenAdSDK

- (instancetype)init
{
    self = [super init];
    if (self) {
        _sdk_delegate.SetOCPrt((__bridge void *)self);
    }
    return self;
}

- (void)startWithAppId:(NSString *)appId {
    _appId = appId;
    ONETEN_AD::OnetenAdSDK::GetInstance().Register(appId.UTF8String);
}

- (void)loadWithPlacementId:(NSString *)placementId {
    [self loadWithPlacementId:placementId userInfo:nil];
}

- (BOOL)loadWithPlacementId:(NSString *)placementId userInfo:(NSDictionary<NSString *, NSString *> *)userInfo {
    std::map<std::string, std::string> user_info;
    for (int i = 0; i < userInfo.allKeys.count; i++) {
        NSString *key = userInfo.allKeys[i];
        NSString *value = userInfo.allValues[i];
        
        std::string c_key(key.UTF8String);
        std::string c_value(value.UTF8String);
        user_info[c_key] = c_value;
    }
    
    if (self.stageCallBack) {
        self.stageCallBack(OTOnetenAdSDKStageTypeStart, placementId, nil, userInfo);
    }
    
    ONETEN_AD::OnetenAdSDK::GetInstance().StartAdLoad(placementId.UTF8String, user_info, _sdk_delegate);
}

- (OTAdViewController *)showWithPlacementId:(NSString *)placementId error:(NSError **)error {
    bool isReady = ONETEN_AD::OnetenAdSDK::GetInstance().IsAdReady(placementId.UTF8String);
    if (!isReady) {
        *error = [NSError errorWithDomain:@"ad show" code:1000 userInfo:@{}];
        return nil;
    }
    
    auto ad_source_model = ONETEN_AD::OnetenAdSDK::GetInstance().ShowAd(placementId.UTF8String, _sdk_delegate);
    if (!ad_source_model) {
        return nil;
    }
    void* platformObj = ad_source_model->GetPlatformObj();
    OTAdViewController *adViewController = [[OTAdViewController alloc] initWithAdSource:(__bridge id<OTAdSourceProtocol>)platformObj category:(OTAdSourceStyleType)ad_source_model->GetStyle()];
    
    return adViewController;
}

@end

BEGIN_NAMESPACE_ONETEN_AD

void AdSDKDelegate::SetOCPrt(void *prt) {
    oc_prt_ = prt;
}

void AdSDKDelegate::LoadSucceed() {
    if (oc_prt_) {
        OTOnetenAdSDK *ad_sdk = (__bridge OTOnetenAdSDK *)oc_prt_;
        if (ad_sdk.stageCallBack) {
            dispatch_async(dispatch_get_main_queue(), ^{
                ad_sdk.stageCallBack(OTOnetenAdSDKStageTypeLoaded, @"", nil, nil);
            });
        }
        
    }
}

void AdSDKDelegate::ShowSucceed() {
    if (oc_prt_) {
        OTOnetenAdSDK *ad_sdk = (__bridge OTOnetenAdSDK *)oc_prt_;
        if (ad_sdk.stageCallBack) {
            dispatch_async(dispatch_get_main_queue(), ^{
                ad_sdk.stageCallBack(OTOnetenAdSDKStageTypeShow, @"", nil, nil);
            });
        }
        
    }
}

void AdSDKDelegate::CloseSucceed() {
    if (oc_prt_) {
        OTOnetenAdSDK *ad_sdk = (__bridge OTOnetenAdSDK *)oc_prt_;
        if (ad_sdk.stageCallBack) {
            dispatch_async(dispatch_get_main_queue(), ^{
                ad_sdk.stageCallBack(OTOnetenAdSDKStageTypeDismiss, @"", nil, nil);
            });
        }
        
    }
}

void AdSDKDelegate::ClickSucceed() {
    if (oc_prt_) {
        OTOnetenAdSDK *ad_sdk = (__bridge OTOnetenAdSDK *)oc_prt_;
        if (ad_sdk.stageCallBack) {
            dispatch_async(dispatch_get_main_queue(), ^{
                ad_sdk.stageCallBack(OTOnetenAdSDKStageTypeClick, @"", nil, nil);
            });
        }
        
    }
}

END_NAMESPACE_ONETEN_AD
