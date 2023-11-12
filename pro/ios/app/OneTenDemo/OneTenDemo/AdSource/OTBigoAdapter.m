//
//  OTBigoSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/9.
//

#import "OTBigoAdapter.h"
#import <BigoADS/BigoRewardVideoAdLoader.h>

@interface OTBigoAdapter ()<BigoRewardVideoAdLoaderDelegate, BigoRewardVideoAdInteractionDelegate>

@end

@implementation OTBigoAdapter

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    switch (styleType) {
        case OTAdSourceStyleTypeInterstitial: {
            
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[BigoRewardVideoAd class]]) {
                return [(BigoRewardVideoAd *)self.delegate.adSourceObject isExpired];
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
    //init
    BigoAdConfig *adConfig = [[BigoAdConfig alloc] initWithAppId:@"10048891"];
//    adConfig.age = 18;
//    adConfig.gender = BigoAdGenderMale;
//    adConfig.activatedTime = 12345678;
//    adConfig.testMode = YES;

    [[BigoAdSdk sharedInstance] initializeSdkWithAdConfig:adConfig completion:^{
//        NSString *bidderToken = [[BigoAdSdk sharedInstance] getBidderToken];
        
        if (self.delegate && [self.delegate respondsToSelector:@selector(registerWithUserInfo:error:)]) {
            [self.delegate registerWithUserInfo:userInfo error:nil];
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
            if ([self.delegate.adSourceObject isKindOfClass:[BigoRewardVideoAd class]]) {
                [(BigoRewardVideoAd *)self.delegate.adSourceObject show:viewController];
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
    BigoRewardVideoAdRequest *request = [[BigoRewardVideoAdRequest alloc] initWithSlotId:@"10048891-10194136"];
    BigoRewardVideoAdLoader *adLoader = [[BigoRewardVideoAdLoader alloc] initWithRewardVideoAdLoaderDelegate:self];
    [adLoader loadAd:request];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:adLoader];
    }
}

#pragma mark - BigoAdInteractionDelegate
//广告异常
- (void)onAd:(BigoAd *)ad error:(BigoAdError *)error {
    
}

//广告展示
- (void)onAdImpression:(BigoAd *)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

//广告点击
- (void)onAdClicked:(BigoAd *)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

//广告打开
- (void)onAdOpened:(BigoAd *)ad {
    
}

//广告关闭
- (void)onAdClosed:(BigoAd *)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

//广告已被屏蔽（由负反馈触发）
- (void)onAdMuted:(BigoAd *)ad {
    
}

#pragma mark - BigoRewardVideoAdLoaderDelegate
- (void)onRewardVideoAdLoaded:(BigoRewardVideoAd *)ad {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adSaveSourceObject:)]) {
        [self.delegate adSaveSourceObject:ad];
    }
    
    [ad setRewardVideoAdInteractionDelegate:self];
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

- (void)onRewardVideoAdLoadError:(BigoAdError *)bigoAdError {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        NSError *error = [NSError errorWithDomain:bigoAdError.errorMsg code:bigoAdError.errorCode userInfo:nil];
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

//激励视频激励回调
- (void)onAdRewarded:(BigoRewardVideoAd *)ad {
    
}

@end
