//
//  OTKSSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/10/15.
//

#import "OTKSAdapter.h"

@interface OTKSAdapter ()<KSRewardedVideoAdDelegate, KSSplashAdViewDelegate, KSInterstitialAdDelegate>

@end

@implementation OTKSAdapter

- (instancetype)init
{
    self = [super init];
    if (self) {
    }
    return self;
}

- (void)registerWithUserInfo:(NSDictionary<id, id> *)userInfo {
    static dispatch_once_t onceToken ;
    dispatch_once(&onceToken, ^{
        NSString *appId = @"90010";
        [KSAdSDKManager setAppId:appId];
    });
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(registerWithUserInfo:error:)]) {
        [self.delegate registerWithUserInfo:userInfo error:nil];
    }
}

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    switch (styleType) {
        case OTAdSourceStyleTypeNative: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[KSRewardedVideoAd class]]) {
                return [(KSRewardedVideoAd *)self.delegate.adSourceObject isValid];
            }
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            if ([self.delegate.adSourceObject isKindOfClass:[KSSplashAdView class]]) {
                return self.delegate.adSourceObject;
            }
        }
            break;
        case OTAdSourceStyleTypeInterstitial: {
            if ([self.delegate.adSourceObject isKindOfClass:[KSInterstitialAd class]]) {
                return [(KSInterstitialAd *)self.delegate.adSourceObject isValid];
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
            break;
        case OTAdSourceStyleTypeRewardedVideo:
            [self loadRewardedVideoWithType:type userInfo:userInfo];
            break;
        case OTAdSourceStyleTypeSplash:
            [self loadSplashWithType:type userInfo:userInfo];
            break;
        case OTAdSourceStyleTypeInterstitial:
            [self loadInterstitialWithType:type userInfo:userInfo];
            break;
        default:
            break;
    }
}

- (void)showWithStyleType:(OTAdSourceStyleType)styleType rootViewController:(UIViewController *)viewController {
    switch (styleType) {
        case OTAdSourceStyleTypeInterstitial: {
            if ([self.delegate.adSourceObject isKindOfClass:[KSInterstitialAd class]]) {
                [(KSInterstitialAd *)self.delegate.adSourceObject showFromViewController:viewController];
            }
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            if ([self.delegate.adSourceObject isKindOfClass:[KSSplashAdView class]]) {
                KSSplashAdView *adView = (KSSplashAdView *)self.delegate.adSourceObject;
                adView.frame = viewController.view.frame;
                [adView setRootViewController:viewController];
                [adView showInView:viewController.view];
            }
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[KSRewardedVideoAd class]]) {
                [(KSRewardedVideoAd *)self.delegate.adSourceObject showAdFromRootViewController:viewController];
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
/// start load rewarded video ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadRewardedVideoWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    KSRewardedVideoModel *model = [KSRewardedVideoModel new];
    model.userId = @"123234";
    model.extra = @"test extra";
    KSRewardedVideoAd *rewardedVideoAd = [[KSRewardedVideoAd alloc] initWithPosId:@"90010001" rewardedVideoModel:model];
    rewardedVideoAd.delegate = self;
    [rewardedVideoAd loadAdData];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:rewardedVideoAd];
    }
}

/// start load splash ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadSplashWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    KSSplashAdView *splashAdView = [[KSSplashAdView alloc] initWithPosId:@"4000000041"];
    splashAdView.delegate = self;
    [splashAdView loadAdData];
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeSplash adSourceObject:splashAdView];
    }
}

/// start load interstitial ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadInterstitialWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    KSInterstitialAd *interstitialAd = [[KSInterstitialAd alloc] initWithPosId:@"4000000277"];
    interstitialAd.delegate = self;
    [interstitialAd loadAdData];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeInterstitial adSourceObject:interstitialAd];
    }
}

#pragma mark - KSRewardedVideoAdDelegate
/**
 This method is called when video ad material loaded successfully.
 */
- (void)rewardedVideoAdDidLoad:(KSRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}
/**
 This method is called when video ad materia failed to load.
 @param error : the reason of error
 */
- (void)rewardedVideoAd:(KSRewardedVideoAd *)rewardedVideoAd didFailWithError:(NSError *_Nullable)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}
/**
 This method is called when cached successfully.
 */
- (void)rewardedVideoAdVideoDidLoad:(KSRewardedVideoAd *)rewardedVideoAd {
    
}
/**
 This method is called when video ad slot will be showing.
 */
- (void)rewardedVideoAdWillVisible:(KSRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}
/**
 This method is called when video ad slot has been shown.
 */
- (void)rewardedVideoAdDidVisible:(KSRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}
/**
 This method is called when video ad is about to close.
 */
- (void)rewardedVideoAdWillClose:(KSRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillCloseWithStyleType:error:)]) {
        [self.delegate adWillCloseWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}
/**
 This method is called when video ad is closed.
 */
- (void)rewardedVideoAdDidClose:(KSRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 This method is called when video ad is clicked.
 */
- (void)rewardedVideoAdDidClick:(KSRewardedVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}
/**
 This method is called when video ad play completed or an error occurred.
 @param error : the reason of error
 */
- (void)rewardedVideoAdDidPlayFinish:(KSRewardedVideoAd *)rewardedVideoAd didFailWithError:(NSError *_Nullable)error {
    
}
/**
 This method is called when the user clicked skip button.
 */
- (void)rewardedVideoAdDidClickSkip:(KSRewardedVideoAd *)rewardedVideoAd {
    
}
/**
 This method is called when the user clicked skip button.
 @param currentTime played duration
 */
- (void)rewardedVideoAdDidClickSkip:(KSRewardedVideoAd *)rewardedVideoAd currentTime:(NSTimeInterval)currentTime {
    
}
/**
 This method is called when the video begin to play.
 */
- (void)rewardedVideoAdStartPlay:(KSRewardedVideoAd *)rewardedVideoAd {
    
}
/**
 This method is called when the user close video ad.
 */
- (void)rewardedVideoAd:(KSRewardedVideoAd *)rewardedVideoAd hasReward:(BOOL)hasReward {
    
}
/**
 This method is called when the user close video ad,support staged rewards.
 */
- (void)rewardedVideoAd:(KSRewardedVideoAd *)rewardedVideoAd
              hasReward:(BOOL)hasReward
               taskType:(KSAdRewardTaskType)taskType
        currentTaskType:(KSAdRewardTaskType)currentTaskType {
    
}
/**
 This method is called when the user close video ad,extra rewards verify.
 */
- (void)rewardedVideoAd:(KSRewardedVideoAd *)rewardedVideoAd extraRewardVerify:(KSAdExtraRewardType)extraRewardType {
    
}

#pragma mark - KSSplashAdViewDelegate
/**
 * splash ad request done
 */
- (void)ksad_splashAdDidLoad:(KSSplashAdView *)splashAdView {
    
}
/**
 * splash ad material load, ready to display
 */
- (void)ksad_splashAdContentDidLoad:(KSSplashAdView *)splashAdView {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}
/**
 * splash ad (material) failed to load
 */
- (void)ksad_splashAd:(KSSplashAdView *)splashAdView didFailWithError:(NSError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeSplash error:error];
    }
}
/**
 * splash ad did visible
 */
- (void)ksad_splashAdDidVisible:(KSSplashAdView *)splashAdView {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}
/**
 * splash ad video begin play
 * for video ad only
 */
- (void)ksad_splashAdVideoDidBeginPlay:(KSSplashAdView *)splashAdView {
    
}
/**
 * splash ad clicked
 * @param inMiniWindow whether click in mini window
 */
- (void)ksad_splashAd:(KSSplashAdView *)splashAdView didClick:(BOOL)inMiniWindow {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}
/**
 * splash ad will zoom out, frame can be assigned
 * for video ad only
 * @param frame target frame
 */
- (void)ksad_splashAd:(KSSplashAdView *)splashAdView willZoomTo:(inout CGRect *)frame {
    
}
/**
 * splash ad zoomout view will move to frame
 * @param frame target frame
 */
- (void)ksad_splashAd:(KSSplashAdView *)splashAdView willMoveTo:(inout CGRect *)frame {
    
}
/**
 * splash ad skipped
 * @param showDuration  splash show duration (no subsequent callbacks, remove & release KSSplashAdView here)
 */
- (void)ksad_splashAd:(KSSplashAdView *)splashAdView didSkip:(NSTimeInterval)showDuration {
    
}
/**
 * splash ad did enter conversion view controller
 */
- (void)ksad_splashAdDidOpenConversionVC:(KSSplashAdView *)splashAdView interactionType:(KSAdInteractionType)interactType {
    
}
/**
 * splash ad close conversion viewcontroller (no subsequent callbacks, remove & release KSSplashAdView here)
 */
- (void)ksad_splashAdDidCloseConversionVC:(KSSplashAdView *)splashAdView interactionType:(KSAdInteractionType)interactType {
    
}
/**
 * splash ad play finished & auto dismiss (no subsequent callbacks, remove & release KSSplashAdView here)
 */
- (void)ksad_splashAdDidAutoDismiss:(KSSplashAdView *)splashAdView {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidDismissWithStyleType:error:)]) {
        [self.delegate adDidDismissWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}
/**
 * splash ad close by user (zoom out mode) (no subsequent callbacks, remove & release KSSplashAdView here)
 */
- (void)ksad_splashAdDidClose:(KSSplashAdView *)splashAdView {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

#pragma mark - KSInterstitialAdDelegate
/**
 * interstitial ad data loaded
 */
- (void)ksad_interstitialAdDidLoad:(KSInterstitialAd *)interstitialAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeInterstitial error:nil];
    }
}
/**
 * interstitial ad render success
 */
- (void)ksad_interstitialAdRenderSuccess:(KSInterstitialAd *)interstitialAd {
    
}
/**
 * interstitial ad load or render failed
 */
- (void)ksad_interstitialAdRenderFail:(KSInterstitialAd *)interstitialAd error:(NSError * _Nullable)error {
    
}
/**
 * interstitial ad will visible
 */
- (void)ksad_interstitialAdWillVisible:(KSInterstitialAd *)interstitialAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeInterstitial error:nil];
    }
}
/**
 * interstitial ad did visible
 */
- (void)ksad_interstitialAdDidVisible:(KSInterstitialAd *)interstitialAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeInterstitial error:nil];
    }
}
/**
 * interstitial ad did click
 */
- (void)ksad_interstitialAdDidClick:(KSInterstitialAd *)interstitialAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeInterstitial error:nil];
    }
}
/**
 * interstitial ad will close
 */
- (void)ksad_interstitialAdWillClose:(KSInterstitialAd *)interstitialAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillCloseWithStyleType:error:)]) {
        [self.delegate adWillCloseWithStyleType:OTAdSourceStyleTypeInterstitial error:nil];
    }
}
/**
 * interstitial ad did close
 */
- (void)ksad_interstitialAdDidClose:(KSInterstitialAd *)interstitialAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeInterstitial error:nil];
    }
}
/**
 * interstitial ad did close other controller
 */
- (void)ksad_interstitialAdDidCloseOtherController:(KSInterstitialAd *)interstitialAd interactionType:(KSAdInteractionType)interactionType {
    
}

@end
