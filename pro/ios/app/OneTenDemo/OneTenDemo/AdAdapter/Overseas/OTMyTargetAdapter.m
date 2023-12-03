//
//  OTMyTargetSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/5.
//

#import "OTMyTargetAdapter.h"

@interface OTMyTargetAdapter ()<MTRGRewardedAdDelegate>

@end

@implementation OTMyTargetAdapter

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    switch (styleType) {
        case OTAdSourceStyleTypeInterstitial: {
            
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            
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
#ifdef DEBUG
    [MTRGManager setDebugMode:YES];
#endif
    if (self.delegate && [self.delegate respondsToSelector:@selector(registerWithUserInfo:error:)]) {
        [self.delegate registerWithUserInfo:userInfo error:nil];
    }
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
            if ([self.delegate.adSourceObject isKindOfClass:[MTRGRewardedAd class]]) {
                [(MTRGRewardedAd *)self.delegate.adSourceObject showWithController:viewController];
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
    MTRGRewardedAd *rewardedAd = [MTRGRewardedAd rewardedAdWithSlotId:1];
    rewardedAd.delegate = self;
    [rewardedAd load];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:rewardedAd];
    }
}

#pragma mark - MTRGRewardedAdDelegate
/**
 @discussion Calls when rewarded ad is loaded. (Required)
 
 @param rewardedAd Current ad.
 */
- (void)onLoadWithRewardedAd:(MTRGRewardedAd *)rewardedAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 @discussion Calls if there is no ad.

 @param error An error code/description.
 @param rewardedAd Current ad.
 */
- (void)onLoadFailedWithError:(NSError *)error rewardedAd:(MTRGRewardedAd *)rewardedAd NS_SWIFT_NAME(onLoadFailed(error:rewardedAd:)) {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

/**
 @discussion Calls when user gets the reward.
 
 @param reward Received reward.
 @param rewardedAd Current ad.
 */
- (void)onReward:(MTRGReward *)reward rewardedAd:(MTRGRewardedAd *)rewardedAd {
    
}

/**
 @discussion Calls on click by the ad.
 
 @param rewardedAd Current ad.
 */
- (void)onClickWithRewardedAd:(MTRGRewardedAd *)rewardedAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 @discussion Calls on close the ad.
 
 @param rewardedAd Current ad.
 */
- (void)onCloseWithRewardedAd:(MTRGRewardedAd *)rewardedAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 @discussion Calls when video ad was displayed.
 
 @param rewardedAd Current ad.
 */
- (void)onDisplayWithRewardedAd:(MTRGRewardedAd *)rewardedAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 @discussion Calls on leave application while ad is showing.
 
 @param rewardedAd Current ad.
 */
- (void)onLeaveApplicationWithRewardedAd:(MTRGRewardedAd *)rewardedAd {
    
}

@end
