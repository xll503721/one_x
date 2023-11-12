//
//  OTMTGSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/10/29.
//

#import "OTMTGAdapter.h"

@interface OTMTGAdapter ()<MTGRewardAdLoadDelegate, MTGRewardAdShowDelegate>

@end

@implementation OTMTGAdapter

#pragma mark - OTAdSourceProtocol

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType { 
    switch (styleType) {
        case OTAdSourceStyleTypeNative: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            return [[MTGRewardAdManager sharedInstance] isVideoReadyToPlayWithPlacementId:@"" unitId:@""];
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            
        }
            break;
        case OTAdSourceStyleTypeInterstitial: {
            
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
        case OTAdSourceStyleTypeRewardedVideo: {
            
        }
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
            [[MTGRewardAdManager sharedInstance] showVideoWithPlacementId:@"" unitId:@"" userId:nil delegate:self viewController:viewController];
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
    [MTGRewardAdManager sharedInstance];
    /* 开始时是否播放视频静音，默认为NO。 设置为YES表示静音 */
    [MTGRewardAdManager sharedInstance].playVideoMute = YES;
    [[MTGRewardAdManager sharedInstance] loadVideoWithPlacementId:@"" unitId:@"" delegate:self];

    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:nil];
    }
}

#pragma mark - MTGRewardAdLoadDelegate

/**
*  Called when the ad is loaded , but not ready to be displayed,need to wait load video
completely
 
*  @param placementId - the placementId string of the Ad that was loaded.
*  @param unitId - the unitId string of the Ad that was loaded.
*/
- (void)onAdLoadSuccess:(nullable NSString *)placementId unitId:(nullable NSString *)unitId {
}

/**
 *  Called when the ad is successfully load , and is ready to be displayed
 
 *  @param placementId - the placementId string of the Ad that was loaded.
 *  @param unitId - the unitId string of the Ad that was loaded.
 */
- (void)onVideoAdLoadSuccess:(nullable NSString *)placementId unitId:(nullable NSString *)unitId {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 *  Called when there was an error loading the ad.
 
 *  @param placementId - the placementId string of the Ad that was loaded.
 *  @param unitId      - the unitId string of the Ad that failed to load.
 *  @param error       - error object that describes the exact error encountered when loading the ad.
 */
- (void)onVideoAdLoadFailed:(nullable NSString *)placementId unitId:(nullable NSString *)unitId error:(nonnull NSError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

/**
 *  Called when the ad display success
 
 *  @param placementId - the placementId string of the Ad that display success.
 *  @param unitId - the unitId string of the Ad that display success.
 */
- (void)onVideoAdShowSuccess:(nullable NSString *)placementId unitId:(nullable NSString *)unitId {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 *  Called when the ad display success,It will be called only when bidding is used.
 
 *  @param placementId - the placementId string of the Ad that display success.
 *  @param unitId - the unitId string of the Ad that display success.
 *  @param bidToken - the bidToken string of the Ad that display success.
 */
- (void)onVideoAdShowSuccess:(nullable NSString *)placementId unitId:(nullable NSString *)unitId bidToken:(nullable NSString *)bidToken {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 *  Called when the ad failed to display for some reason
 
 *  @param placementId      - the placementId string of the Ad that failed to be displayed.
 *  @param unitId      - the unitId string of the Ad that failed to be displayed.
 *  @param error       - error object that describes the exact error encountered when showing the ad.
 */
- (void)onVideoAdShowFailed:(nullable NSString *)placementId unitId:(nullable NSString *)unitId withError:(nonnull NSError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

/**
 *  Called only when the ad has a video content, and called when the video play completed.
 
 *  @param placementId - the placementId string of the Ad that video play completed.
 *  @param unitId - the unitId string of the Ad that video play completed.
 */
- (void)onVideoPlayCompleted:(nullable NSString *)placementId unitId:(nullable NSString *)unitId {
    
}

/**
 *  Called only when the ad has a endcard content, and called when the endcard show.
 
 *  @param placementId - the placementId string of the Ad that endcard show.
 *  @param unitId - the unitId string of the Ad that endcard show.
 */
- (void)onVideoEndCardShowSuccess:(nullable NSString *)placementId unitId:(nullable NSString *)unitId {
    
}

/**
 *  Called when the ad is clicked
 *
 *  @param placementId - the placementId string of the Ad clicked.
 *  @param unitId - the unitId string of the Ad clicked.
 */
- (void)onVideoAdClicked:(nullable NSString *)placementId unitId:(nullable NSString *)unitId {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillCloseWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 *  Called when the ad will dismiss from being displayed, and control will return to your app
 *
 *  @param placementId      - the placementId string of the Ad that has been dismissed
 *  @param unitId      - the unitId string of the Ad that has been dismissed
 *  @param converted   - BOOL describing whether the ad has converted
 *  @param rewardInfo  - the rewardInfo object containing the info that should be given to your user.
 */
- (void)onVideoAdDismissed:(nullable NSString *)placementId unitId:(nullable NSString *)unitId withConverted:(BOOL)converted withRewardInfo:(nullable MTGRewardAdInfo *)rewardInfo {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillCloseWithStyleType:error:)]) {
        [self.delegate adWillCloseWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 *  Called when the ad did dismissed;
 *
 *  @param unitId - the unitId string of the Ad that video play did dismissed.
 *  @param placementId - the placementId string of the Ad that video play did dismissed.
 */
- (void)onVideoAdDidClosed:(nullable NSString *)placementId unitId:(nullable NSString *)unitId {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

@end
