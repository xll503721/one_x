//
//  OTTianmuAdapter.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/12.
//

#import "OTTianmuAdapter.h"
#import <TianmuSDK/TianmuRewardVodAd.h>

@interface OTTianmuAdapter ()<TianmuRewardVodAdDelegate>

@end

@implementation OTTianmuAdapter

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    switch (styleType) {
        case OTAdSourceStyleTypeInterstitial: {
            
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[TianmuRewardVodAd class]]) {
                return (TianmuRewardVodAd *)self.delegate.adSourceObject;
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
    // 申请的 appid 必须与您的包名一一对应
    [TianmuSDK initWithAppId:@"1001006" completionBlock:^(NSError * _Nullable error) {
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
            if ([self.delegate.adSourceObject isKindOfClass:[TianmuRewardVodAd class]]) {
                [(TianmuRewardVodAd *)self.delegate.adSourceObject setController:viewController];
                [(TianmuRewardVodAd *)self.delegate.adSourceObject showFromRootViewController:viewController];
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
    // 1、初始化激励视频广告
    TianmuRewardVodAd *rewardVodAd = [[TianmuRewardVodAd alloc] init];
    rewardVodAd.delegate = self;
    rewardVodAd.posId = @"31dab847fc60";
    [rewardVodAd loadAdData];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:rewardVodAd];
    }
}

#pragma mark - TianmuRewardVodAdDelegate
/**
 *  激励视频广告数据请求成功
 */
- (void)tianmuRewardVodAdSuccessToLoadAd:(TianmuRewardVodAd *)rewardVodAd {
    
}

/**
 *  激励视频广告数据请求失败
 */
- (void)tianmuRewardVodAdFailToLoadAd:(TianmuRewardVodAd *)rewardVodAd error:(NSError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

/**
 *  激励视频广告视频缓存成功
 */
- (void)tianmuRewardVodAdVideoCacheFinish:(TianmuRewardVodAd *)rewardVodAd {
    
}

/**
 *  激励视频广告渲染成功
 *  建议在此回调后展示广告
 */
- (void)tianmuRewardVodAdVideoReadyToPlay:(TianmuRewardVodAd *)rewardVodAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 *  激励视频广告播放失败
 *
 */
- (void)tianmuRewardVodAdVideoPlayFail:(TianmuRewardVodAd *)rewardVodAd error:(NSError *)error {
    
}

/**
 *  激励视频视图展示成功回调
 *  激励视频展示成功回调该函数
 */
- (void)tianmuRewardVodAdDidPresentScreen:(TianmuRewardVodAd *)rewardVodAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 *  激励视频广告视图展示失败回调
 *  激励视频广告展示失败回调该函数
 */
- (void)tianmuRewardVodAdFailToPresent:(TianmuRewardVodAd *)rewardVodAd error:(NSError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}

/**
 *  激励视频广告曝光回调
 */
- (void)tianmuRewardVodAdWillExposure:(TianmuRewardVodAd *)rewardVodAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 *  激励视频广告点击回调
 */
- (void)tianmuRewardVodAdClicked:(TianmuRewardVodAd *)rewardVodAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 *  激励视频广告页关闭
 */
- (void)tianmuRewardVodAdAdDidDismissClose:(TianmuRewardVodAd *)rewardVodAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidCloseWithStyleType:error:)]) {
        [self.delegate adDidCloseWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 *  激励视频广告达到激励条件
 */
- (void)tianmuRewardVodAdAdDidEffective:(TianmuRewardVodAd *)rewardVodAd {
    
}

/**
 *  激励视频广告视频播放结束
 */
- (void)tianmuRewardVodAdAdVideoPlayFinish:(TianmuRewardVodAd *)rewardVodAd {
    
}

/**
 *  激励视频广告关闭落地页
 */
- (void)tianmuRewardVodAdCloseLandingPage:(TianmuRewardVodAd *)rewardVodAd {
    
}

@end
