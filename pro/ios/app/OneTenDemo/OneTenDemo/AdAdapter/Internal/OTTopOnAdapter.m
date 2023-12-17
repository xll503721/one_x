//
//  OTTopOnSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/5.
//

#import "OTTopOnAdapter.h"

@interface OTTopOnAdapter ()<ATAdLoadingDelegate, ATRewardedVideoDelegate>

@end

@implementation OTTopOnAdapter

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    BOOL isReady = NO;
    isReady = [[ATAdManager sharedManager] adReadyForPlacementID:@"b64eeeca71989b"];
    return isReady;
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
    NSError *error = nil;
    [[ATAPI sharedInstance] startWithAppID:@"a64eeeafb9c81a" appKey:@"360db8f37195a6a3aabe47dc05d347c8" error:&error];
    if (self.delegate && [self.delegate respondsToSelector:@selector(registerWithUserInfo:error:)]) {
        [self.delegate registerWithUserInfo:userInfo error:error];
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
            [[ATAdManager sharedManager] showRewardedVideoWithPlacementID:@"b64eeeca71989b" inViewController:viewController delegate:self];
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
    [[ATAdManager sharedManager] loadADWithPlacementID:@"b64eeeca71989b" extra:@{} delegate:self];
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:nil];
    }
}

#pragma mark - ATAdLoadingDelegate
/// Callback when the successful loading of the ad
- (void)didFinishLoadingADWithPlacementID:(NSString *)placementID {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/// Callback of ad loading failure
- (void)didFailToLoadADWithPlacementID:(NSString*)placementID
                                 error:(NSError*)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

#pragma mark - ATRewardedVideoDelegate
/// Rewarded video ad play starts
- (void)rewardedVideoDidStartPlayingForPlacementID:(NSString *)placementID
                                             extra:(NSDictionary *)extra {
    
}

/// Rewarded video ad play ends
- (void)rewardedVideoDidEndPlayingForPlacementID:(NSString *)placementID
                                           extra:(NSDictionary *)extra {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/// Rewarded video ad clicks
- (void)rewardedVideoDidClickForPlacementID:(NSString *)placementID
                                      extra:(NSDictionary *)extra {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/// Rewarded video ad closed
- (void)rewardedVideoDidCloseForPlacementID:(NSString *)placementID
                                   rewarded:(BOOL)rewarded
                                      extra:(NSDictionary *)extra {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/// Rewarded video ad reward distribution
- (void)rewardedVideoDidRewardSuccessForPlacemenID:(NSString *)placementID
                                             extra:(NSDictionary *)extra {
    
}

/// Rewarded video ad play failed
- (void)rewardedVideoDidFailToPlayForPlacementID:(NSString *)placementID
                                           error:(NSError *)error
                                           extra:(NSDictionary *)extra {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

/// Whether the click jump of rewarded video ad is in the form of Deeplink
/// note: only suport TopOn Adx ad
- (void)rewardedVideoDidDeepLinkOrJumpForPlacementID:(NSString *)placementID
                                               extra:(NSDictionary *)extra
                                              result:(BOOL)success {
    
}

@end
