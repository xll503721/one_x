//
//  OTPangleSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/10/29.
//

#import "OTPangleSource.h"

@interface OTPangleSource ()<PAGRewardedAdDelegate>

@end

@implementation OTPangleSource


- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    switch (styleType) {
        case OTAdSourceStyleTypeInterstitial: {
            
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[PAGRewardedAd class]]) {
                return (self.delegate.adSourceObject != nil);
            }
        }
            break;
        case OTAdSourceStyleTypeNative: {
            
        }
            break;
            
        default:
            break;
    }
    return NO;
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
    PAGConfig *config = [PAGConfig shareConfig];
    config.appID = @"YOUR_APP_ID";
#if DEBUG
    config.debugLog = YES;
#endif
    [PAGSdk startWithConfig:config completionHandler:^(BOOL success, NSError * _Nonnull error) {
        if (self.delegate && [self.delegate respondsToSelector:@selector(registerWithUserInfo:error:)]) {
            [self.delegate registerWithUserInfo:userInfo error:error];
        }
    }];
}

- (void)showWithStyleType:(OTAdSourceStyleType)styleType rootViewController:(UIViewController *)viewController {
    switch (styleType) {
        case OTAdSourceStyleTypeInterstitial: {
            
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[PAGRewardedAd class]]) {
                return [(PAGRewardedAd *)self.delegate.adSourceObject presentFromRootViewController:viewController];
            }
        }
            break;
        case OTAdSourceStyleTypeNative: {
            
        }
            break;
            
        default:
            break;
    }
}

/// start load rewarded video ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadRewardedVideoWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    PAGRewardedRequest *request = [PAGRewardedRequest request];
    [PAGRewardedAd loadAdWithSlotID:@"YOUR_AD_PLACEMENT_ID" request:request completionHandler:^(PAGRewardedAd * _Nullable rewardedAd, NSError * _Nullable error) {
        if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
            [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:rewardedAd];
        }
        
        rewardedAd.delegate = self;
        
        if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
            [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
        }
    }];
}

#pragma mark - PAGAdDelegate
/// This method is called when the ad has been shown
- (void)adDidShow:(id<PAGAdProtocol>)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/// This method is called when the add has been clicked
- (void)adDidClick:(id<PAGAdProtocol>)ad{
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

///This method is called when the ad has been dismissed.
- (void)adDidDismiss:(id<PAGAdProtocol>)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

///This method is called when the ad has been show fail
- (void)adDidShowFail:(id<PAGAdProtocol>)ad error:(NSError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

#pragma mark - PAGRewardedAdDelegate
/// Tells the delegate that the user has earned the reward.
/// @param rewardedAd rewarded ad instance
/// @param rewardModel user's reward info
- (void)rewardedAd:(PAGRewardedAd *)rewardedAd userDidEarnReward:(PAGRewardModel *)rewardModel {
    
}

/// Tells the delegate that the user failed to earn the reward.
/// @param rewardedAd rewarded ad instance
/// @param error failed reson
- (void)rewardedAd:(PAGRewardedAd *)rewardedAd userEarnRewardFailWithError:(NSError *)error {
    
}

@end
