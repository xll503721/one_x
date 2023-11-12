//
//  OTChartboostSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/4.
//

#import "OTChartboostAdapter.h"

@interface OTChartboostAdapter ()<CHBRewardedDelegate>

@end

@implementation OTChartboostAdapter

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType { 
    switch (styleType) {
        case OTAdSourceStyleTypeInterstitial: {
            
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[CHBRewarded class]]) {
                return [(CHBRewarded *)self.delegate.adSourceObject isCached];
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
    [Chartboost setLoggingLevel:CBLoggingLevelInfo];
    
    [Chartboost startWithAppID:@"4f21c409cd1cb2fb7000001b"
                  appSignature:@"92e2de2fd7070327bdeb54c15a5295309c6fcd2d"
                    completion:^(CHBStartError * error) {
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
            if ([self.delegate.adSourceObject isKindOfClass:[CHBRewarded class]]) {
                return [(CHBRewarded *)self.delegate.adSourceObject showFromViewController:viewController];
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
    CHBRewarded *rewarded = [[CHBRewarded alloc] initWithLocation:@"default" delegate:self];
    [rewarded cache];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:rewarded];
    }
}

/*!
Called after an ad is dismissed.
# Discussion #
- Implement to be notified of when an ad is no longer displayed.
- Note that this method won't get called for ads that failed to be shown. To handle that case implement didShowAd:error:
- You may use the error property inside the event to know if the dismissal was expected or caused by an error.
 
- parameter event: A dismiss event with info related to the dismissed ad.

 A typical implementation would look like this:
 ```objc
 - (void)didDismissAd:(CHBDismissEvent *)event {
    // Resume processes paused in willShowAd:
 }
 ```
*/
- (void)didDismissAd:(CHBDismissEvent *)event {
    
}

/*!
Called when a rewarded ad has completed playing.
# Discussion #
Implement to be notified when a reward is earned.

- parameter event: A reward event with info related to the ad and the reward.
*/
- (void)didEarnReward:(CHBRewardEvent *)event {
    
}

/*!
Called after a cache call, either if an ad has been loaded from the Chartboost servers and cached, or tried to but failed.
# Discussion #
Implement to be notified of when an ad is ready to be shown after the cache method has been called.
- parameter event: A cache event with info related to the cached ad.
- parameter error: An error specifying the failure reason, or nil if the operation was successful.
 
 A typical implementation would look like this:
 ```objc
 - (void)didCacheAd:(CHBCacheEvent *)event error:(nullable CHBCacheError *)error {
    if (error) {
        // Handle error
    } else {
        // At this point event.ad.isCached will be true, and the ad is ready to be shown.
    }
 }
 ```
 */
- (void)didCacheAd:(CHBCacheEvent *)event error:(nullable CHBCacheError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

/*!
Called after a showFromViewController: call, right before an ad is presented.
# Discussion #
Implement to be notified of when an ad is about to be presented.
- parameter event: A show event with info related to the ad to be shown.
A typical implementation would look like this:
```objc
- (void)willShowAd:(CHBShowEvent *)event {
   // Pause ongoing processes like video or gameplay.
}
```
*/
- (void)willShowAd:(CHBShowEvent *)event {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/*!
Called after a showFromViewController: call, either if the ad has been presented and an ad impression logged, or if the operation failed.
# Discussion #
- Implement to be notified of when the ad presentation process has finished.
- This method will be called once for each call to showFromViewController: on an interstitial or rewarded ad.
- In contrast, this may be called up to two times after showing a banner, if some error occurs after the ad has been successfully shown.

- parameter event: A show event with info related to the ad shown.
- parameter error: An error specifying the failure reason, or nil if the operation was successful.

A common practice consists of caching an ad here so there's an ad ready for the next time you need to show it.
 ```objc
 - (void)didShowAd:(CHBShowEvent *)event error:(nullable CHBShowError *)error {
    if (error) {
        // Handle error, possibly resuming processes paused in willShowAd:
    } else {
        [event.ad cache];
    }
 }
```
*/
- (void)didShowAd:(CHBShowEvent *)event error:(nullable CHBShowError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/*!
Called after an ad has been clicked.
# Discussion #
- Implement to be notified of when an ad has been clicked.
- If the click does not result into the opening of a link an error will be provided explaning why.
 
- parameter event: A click event with info related to the ad clicked.
- parameter error: An error specifying the failure reason, or nil if the operation was successful.
 
 A typical implementation would look like this:
 ```objc
 - (void)didClickAd:(CHBClickEvent *)event error:(nullable CHBClickError *)error {
    if (error) {
        // Handle error
    } else {
        // Maybe pause ongoing processes like video or gameplay when a banner ad is clicked.
    }
 }
 ```
*/
- (void)didClickAd:(CHBClickEvent *)event error:(nullable CHBClickError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/*!
Called after an ad has recorded an impression.
# Discussion #
-  Implement to be notified of when an ad has recorded an impression.
- This method will be called once a valid impression is recorded after showing the ad.
- parameter event: An impression event with info related to the visible ad.
*/
- (void)didRecordImpression:(CHBImpressionEvent *)event {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

@end
