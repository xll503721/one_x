//
//  OTDigitalTurbineSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/4.
//

#import "OTDigitalTurbineAdapter.h"

@interface OTDigitalTurbineAdapter ()

@end

@implementation OTDigitalTurbineAdapter

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    return YES;
}

- (void)loadWithStyleType:(OTAdSourceStyleType)styleType adSourceType:(OTAdSourceType)type userInfo:(NSDictionary<id,id> *)userInfo {
    switch (styleType) {
        case OTAdSourceStyleTypeNative:
            break;
        case OTAdSourceStyleTypeRewardedVideo:
            [self loadRewardedVideoWithType:type userInfo:userInfo];
            break;
        case OTAdSourceStyleTypeSplash:
            [self loadSplashWithType:type userInfo:userInfo];
            break;
        case OTAdSourceStyleTypeInterstitial:
            
            break;
        default:
            break;
    }
}

- (void)registerWithUserInfo:(NSDictionary<id,id> *)userInfo {
    [IASDKCore.sharedInstance initWithAppID:@"YOUR APP ID"
                            completionBlock:^(BOOL success, NSError * _Nullable error) {
        if (self.delegate && [self.delegate respondsToSelector:@selector(registerWithUserInfo:error:)]) {
            [self.delegate registerWithUserInfo:userInfo error:error];
        }
    } completionQueue:nil];
}

- (void)showWithStyleType:(OTAdSourceStyleType)styleType rootViewController:(UIViewController *)viewController {
    
}

/// start load rewarded video ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadRewardedVideoWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    IAAdRequest *adRequest = [IAAdRequest build:^(id<IAAdRequestBuilder>  _Nonnull builder) {
        builder.spotID = @"YOUR SPOT ID";
        builder.timeout = 5;
        builder.useSecureConnections = NO;
    }];
}

@end
