//
//  OTAdSourceObjectProtocol.h
//  ONETEN_AD_sdk
//
//  Created by li zhixuan on 2022/11/10.
//

#import <Foundation/Foundation.h>

#pragma mark - OTAdSourceProtocol

@protocol OTAdSourceObjectProtocol <NSObject>

@required


@optional
/// start load interstitial ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadInterstitialWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo;

/// start load splash ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadSplashWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo;

/// start load banner ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadBannerWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo;

/// start load rewarded video ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadRewardedVideoWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo;

/// start load navite ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadNaviteWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo;

- (void)sendWinNotificationWithType:(OTAdSourceStyleType)styleType userInfo:(NSDictionary *)userInfo;
- (void)sendLossNotificationWithType:(OTAdSourceStyleType)styleType userInfo:(NSDictionary *)userInfo;

@end
