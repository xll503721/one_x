//
//  OTStartSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/4.
//

#import "OTStartSource.h"

@interface OTStartSource ()<STADelegateProtocol>

@end

@implementation OTStartSource

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    switch (styleType) {
        case OTAdSourceStyleTypeInterstitial: {
            
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[STAStartAppAd class]]) {
                return [(STAStartAppAd *)self.delegate.adSourceObject isReady];
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
    // initialize the SDK with your appID
    STAStartAppSDK* sdk = [STAStartAppSDK sharedInstance];
    sdk.appID = @"your app Id";
    
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
            if ([self.delegate.adSourceObject isKindOfClass:[STAStartAppAd class]]) {
                [(STAStartAppAd *)self.delegate.adSourceObject showAd];
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
    STAStartAppAd *rewardedAd = [[STAStartAppAd alloc] init];
    [rewardedAd loadRewardedVideoAdWithDelegate:self];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:rewardedAd];
    }
}

#pragma mark - STADelegateProtocol
/*!
 * @brief Notifies delegate that ad was loaded successfully
 * @discussion This method is called when ad did finish loading successfully.
 * @param ad Ad instance that called this method
 */
- (void)didLoadAd:(STAAbstractAd *)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/*!
 * @brief Notifies delegate that ad failed to load
 * @discussion This method is called when ad failed to load. Check error parameter to understand the reason.
 * @param ad Ad instance that called this method
 * @param error Error describing the reason. See STAErrorCode.h for possible error codes and localizedDescription for explanation
 */
- (void)failedLoadAd:(STAAbstractAd *)ad withError:(NSError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

/*!
 * @brief Notifies delegate that ad did appear on screen
 * @discussion This method is called when ad did appear on screen.
 * @param ad Ad instance that called this method
 */
- (void)didShowAd:(STAAbstractAd *)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/*!
 * @brief Notifies delegate that ad did send impression
 * @discussion This method is called when ad did appear on screen and all required conditions were met for impression to be sent.
 * @param ad Ad instance that called this method
 */
- (void)didSendImpression:(STAAbstractAd *)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/*!
 * @brief Notifies delegate that ad failed to display
 * @discussion This method is called when ad failed to display. Check error parameter to understand the reason.
 * @param ad Ad instance that called this method
 * @param error Error describing the reason. See STAErrorCode.h for possible error codes and localizedDescription for explanation
 */
- (void)failedShowAd:(STAAbstractAd *)ad withError:(NSError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

/*!
 * @brief Notifies delegate that ad was closed
 * @discussion This method is called when ad was closed.
 * @param ad Ad instance that called this method
 */
- (void)didCloseAd:(STAAbstractAd *)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/*!
 * @brief Notifies delegate that ad was clicked
 * @discussion This method is called when ad was clicked.
 * @param ad Ad instance that called this method
 */
- (void)didClickAd:(STAAbstractAd *)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/*!
 * @brief Notifies delegate that in-app AppStore view controller, presented after click on ad, was closed
 * @discussion This method is called when in-app AppStore view controller gets closed by cancelling it or by installing the app.
 * @param ad Ad instance that called this method
 */
- (void)didCloseInAppStore:(STAAbstractAd *)ad {
    
}

/*!
 * @brief Notifies delegate that rewarded video ad did complete playing video
 * @discussion This method is called when rewarded ad completes playing video
 * @param ad Ad instance that called this method
 */
- (void)didCompleteVideo:(STAAbstractAd *)ad {
    
}

/*!
 * @brief Notifies delegate that impression was sent for specified nativeAdDetails
 * @discussion This method is called when impression tracking view did become viewable and all required conditions were met for impression to be sent.
 * @param nativeAdDetails Native ad details instance that called this method
 */
- (void)didSendImpressionForNativeAdDetails:(STANativeAdDetails *)nativeAdDetails {
    
}

/*!
 * @brief Notifies delegate that nativeAdDetails was clicked
 * @discussion This method is called when click tracking view was clicked for specified nativeAdDetails.
 * @param nativeAdDetails Native ad details instance that called this method
 */
- (void)didClickNativeAdDetails:(STANativeAdDetails *)nativeAdDetails {
    
}

@end
