//
//  OTCSJSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/10/6.
//

#import "OTCSJAdapter.h"

@interface OTCSJAdapter () <BUSplashAdDelegate, BUNativeExpressRewardedVideoAdDelegate>

@end

@implementation OTCSJAdapter

- (instancetype)init
{
    self = [super init];
    if (self) {
    }
    return self;
}

- (void)registerWithUserInfo:(NSDictionary<id, id> *)userInfo {
    BUAdSDKConfiguration *configuration = [BUAdSDKConfiguration configuration];
    configuration.appID = @"5000546";
    [BUAdSDKManager startWithAsyncCompletionHandler:^(BOOL success, NSError *error) {
        if (self.delegate && [self.delegate respondsToSelector:@selector(registerWithUserInfo:error:)]) {
            [self.delegate registerWithUserInfo:userInfo error:error];
        }
    }];
}

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    switch (styleType) {
        case OTAdSourceStyleTypeNative: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[BUNativeExpressRewardedVideoAd class]]) {
                return self.delegate.adSourceObject;
            }
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            if ([self.delegate.adSourceObject isKindOfClass:[BUSplashAd class]]) {
                return [[(BUSplashAd *)self.delegate.adSourceObject splashView] isAdValid];
            }
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
            [self loadNativeWithType:type userInfo:userInfo];
            break;
        case OTAdSourceStyleTypeRewardedVideo:
            [self loadRewardedVideoWithType:type userInfo:userInfo];
            break;
        case OTAdSourceStyleTypeSplash:
            [self loadSplashWithType:type userInfo:userInfo];
            break;
        default:
            break;
    }
}

- (void)showWithStyleType:(OTAdSourceStyleType)styleType rootViewController:(UIViewController *)viewController {
    switch (styleType) {
        case OTAdSourceStyleTypeInterstitial: {
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            if ([self.delegate.adSourceObject isKindOfClass:[BUSplashAd class]]) {
                [(BUSplashAd *)self.delegate.adSourceObject showSplashViewInRootViewController:viewController];
            }
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[BUNativeExpressRewardedVideoAd class]]) {
                [(BUNativeExpressRewardedVideoAd *)self.delegate.adSourceObject showAdFromRootViewController:viewController];
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

#pragma mark - Load
/// start load interstitial ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadInterstitialWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    
}

/// start load splash ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadSplashWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    UIWindow *keyWindow = [[UIApplication sharedApplication] keyWindow];
    BUSplashAd *splashAd = [[BUSplashAd alloc] initWithSlotID:@"800546851" adSize:keyWindow.frame.size];
    splashAd.delegate = self;
    [splashAd loadAdData];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeSplash adSourceObject:splashAd];
    }
}

/// start load banner ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadBannerWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    
}

/// start load rewarded video ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadRewardedVideoWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    BURewardedVideoModel *model = [[BURewardedVideoModel alloc] init];
    BUNativeExpressRewardedVideoAd *rewardedAd = [[BUNativeExpressRewardedVideoAd alloc] initWithSlotID:@"945113162" rewardedVideoModel:model];
    rewardedAd.delegate = self;
    [rewardedAd loadAdData];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:rewardedAd];
    }
}

/// start load navite ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadNativeWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    
}

#pragma mark - Splash
/// This method is called when material load successful
- (void)splashAdLoadSuccess:(BUSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/// This method is called when material load failed
- (void)splashAdLoadFail:(BUSplashAd *)splashAd error:(BUAdError *_Nullable)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeSplash error:error];
    }
}

/// This method is called when splash view render successful
- (void)splashAdRenderSuccess:(BUSplashAd *)splashAd {
    
}

/// This method is called when splash view render failed
- (void)splashAdRenderFail:(BUSplashAd *)splashAd error:(BUAdError *_Nullable)error {
    
}

/// This method is called when splash view will show
- (void)splashAdWillShow:(BUSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/// This method is called when splash view did show
- (void)splashAdDidShow:(BUSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/// This method is called when splash view is clicked.
- (void)splashAdDidClick:(BUSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/// This method is called when splash view is closed.
- (void)splashAdDidClose:(BUSplashAd *)splashAd closeType:(BUSplashAdCloseType)closeType {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/// This method is called when splash viewControllr is closed.
- (void)splashAdViewControllerDidClose:(BUSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidDismissWithStyleType:error:)]) {
        [self.delegate adDidDismissWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/**
 This method is called when another controller has been closed.
 @param interactionType : open appstore in app or open the webpage or view video ad details page.
 */
- (void)splashDidCloseOtherController:(BUSplashAd *)splashAd interactionType:(BUInteractionType)interactionType {
    
}

/// This method is called when when video ad play completed or an error occurred.
- (void)splashVideoAdDidPlayFinish:(BUSplashAd *)splashAd didFailWithError:(NSError *)error {
    
}

#pragma mark - RewardedVideo Delegate

/**
 This method is called when video ad material loaded successfully.
 */
- (void)nativeExpressRewardedVideoAdDidLoad:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 This method is called when video ad materia failed to load.
 @param error : the reason of error
 */
- (void)nativeExpressRewardedVideoAd:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd didFailWithError:(NSError *_Nullable)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}
/**
  this methods is to tell delegate the type of native express rewarded video Ad
 */
- (void)nativeExpressRewardedVideoAdCallback:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd withType:(BUNativeExpressRewardedVideoAdType)nativeExpressVideoType {
    
}

/**
 This method is called when cached successfully.
 For a better user experience, it is recommended to display video ads at this time.
 And you can call [BUNativeExpressRewardedVideoAd showAdFromRootViewController:].
 */
- (void)nativeExpressRewardedVideoAdDidDownLoadVideo:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd {
    
}

/**
 This method is called when rendering a nativeExpressAdView successed.
 It will happen when ad is show.
 */
- (void)nativeExpressRewardedVideoAdViewRenderSuccess:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd {
    
}

/**
 This method is called when a nativeExpressAdView failed to render.
 @param error : the reason of error
 */
- (void)nativeExpressRewardedVideoAdViewRenderFail:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd error:(NSError *_Nullable)error {
    
}

/**
 This method is called when video ad slot will be showing.
 */
- (void)nativeExpressRewardedVideoAdWillVisible:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 This method is called when video ad slot has been shown.
 */
- (void)nativeExpressRewardedVideoAdDidVisible:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 This method is called when video ad is about to close.
 */
- (void)nativeExpressRewardedVideoAdWillClose:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillDismissWithStyleType:error:)]) {
        [self.delegate adWillDismissWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 This method is called when video ad is closed.
 */
- (void)nativeExpressRewardedVideoAdDidClose:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidDismissWithStyleType:error:)]) {
        [self.delegate adDidDismissWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 This method is called when video ad is clicked.
 */
- (void)nativeExpressRewardedVideoAdDidClick:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 This method is called when the user clicked skip button.
 */
- (void)nativeExpressRewardedVideoAdDidClickSkip:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidDismissWithStyleType:error:)]) {
        [self.delegate adDidDismissWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 This method is called when video ad play completed or an error occurred.
 @param error : the reason of error
 */
- (void)nativeExpressRewardedVideoAdDidPlayFinish:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd didFailWithError:(NSError *_Nullable)error {
    
}

/**
 Server verification which is requested asynchronously is succeeded. now include two v erify methods:
      1. C2C need  server verify  2. S2S don't need server verify
 @param verify :return YES when return value is 2000.
 */
- (void)nativeExpressRewardedVideoAdServerRewardDidSucceed:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd verify:(BOOL)verify {
    
}

/**
  Server verification which is requested asynchronously is failed.
  @param rewardedVideoAd express rewardVideo Ad
  @param error request error info
 */
- (void)nativeExpressRewardedVideoAdServerRewardDidFail:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd error:(NSError *_Nullable)error {
    
}

/**
 This method is called when another controller has been closed.
 @param interactionType : open appstore in app or open the webpage or view video ad details page.
 */
- (void)nativeExpressRewardedVideoAdDidCloseOtherController:(BUNativeExpressRewardedVideoAd *)rewardedVideoAd interactionType:(BUInteractionType)interactionType {
    
}

@end
