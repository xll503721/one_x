//
//  OTGDTSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/7/16.
//

#import "OTGDTAdapter.h"
#import <GDTUnifiedNativeAd.h>
#import <GDTSDKConfig.h>
#import <GDTRewardVideoAd.h>
#import <GDTSplashAd.h>

#import <OTAdViewController.h>

static NSString *kGDTMobSDKAppId = @"1105344611";

@interface OTGDTAdapter ()<GDTUnifiedNativeAdDelegate, GDTUnifiedNativeAdViewDelegate, GDTRewardedVideoAdDelegate, GDTSplashAdDelegate, OTAdSourceProtocol>

@property (nonatomic, strong) NSMutableArray<GDTUnifiedNativeAdDataObject *> *unifiedNativeAdDataObjects;

@end

@implementation OTGDTAdapter

- (void)dealloc {
    
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _unifiedNativeAdDataObjects = @[].mutableCopy;
    }
    return self;
}

- (void)registerWithUserInfo:(NSDictionary<id, id> *)userInfo {
    __block BOOL result = NO;
    
    static dispatch_once_t onceToken ;
    dispatch_once(&onceToken, ^{
        result = [GDTSDKConfig registerAppId:kGDTMobSDKAppId];
    });
    
    NSError *error = nil;
    if (!result) {
        error = [NSError errorWithDomain:@"" code:1 userInfo:nil];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(registerWithUserInfo:error:)]) {
        [self.delegate registerWithUserInfo:userInfo error:error];
    }
}

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    switch (styleType) {
        case OTAdSourceStyleTypeNative: {
            
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[GDTRewardVideoAd class]]) {
                return [(GDTRewardVideoAd *)self.delegate.adSourceObject isAdValid];
            }
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            if ([self.delegate.adSourceObject isKindOfClass:[GDTSplashAd class]]) {
                return [(GDTSplashAd *)self.delegate.adSourceObject isAdValid];
            }
        }
            break;
        default:
            break;
    }
    return NO;
}

- (void)showWithStyleType:(OTAdSourceStyleType)styleType rootViewController:(UIViewController *)viewController {
    switch (styleType) {
        case OTAdSourceStyleTypeInterstitial: {
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            if ([self.delegate.adSourceObject isKindOfClass:[GDTSplashAd class]]) {
                UIWindow *keyWindow = [[UIApplication sharedApplication] keyWindow];
                [(GDTSplashAd *)self.delegate.adSourceObject showFullScreenAdInWindow:keyWindow withLogoImage:nil skipView:nil];
            }
        }
            break;
        case OTAdSourceStyleTypeRewardedVideo: {
            if ([self.delegate.adSourceObject isKindOfClass:[GDTRewardVideoAd class]]) {
                [(GDTRewardVideoAd *)self.delegate.adSourceObject showAdFromRootViewController:viewController];
            }
        }
            break;
        case OTAdSourceStyleTypeNative: {
            OTAdViewController *adViewController = (OTAdViewController *)viewController;
            if ([adViewController isKindOfClass:[OTAdViewController class]]) {
                OTAdView *view = (OTAdView *)adViewController.view;
                
                GDTUnifiedNativeAdView *unifiedNativeAdView = [[GDTUnifiedNativeAdView alloc] initWithFrame:view.bounds];
                unifiedNativeAdView.delegate = self;
                unifiedNativeAdView.viewController = viewController;
                
                GDTUnifiedNativeAdDataObject *dataObject = self.unifiedNativeAdDataObjects.lastObject;
                UILabel *titleLabel = [[UILabel alloc] initWithFrame:CGRectZero];
                titleLabel.text = dataObject.title;
                view.titleLabel = titleLabel;
                
                if ([dataObject isAdValid]) {
                    [unifiedNativeAdView registerDataObject:dataObject clickableViews:@[titleLabel]];
                    [view addSubview:unifiedNativeAdView];
                }
            }
        }
            break;
            
        default:
            break;
    }
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

#pragma mark - Splash
- (void)loadSplashWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    NSString *placementId = userInfo[@"placement_id"];
    if (!placementId) {
        return;
    }
    GDTSplashAd *splashAd = [[GDTSplashAd alloc] initWithPlacementId:placementId];
    splashAd.delegate = self;
    splashAd.fetchDelay = 5;
    //如果设置了服务端验证，可以设置serverSideVerificationOptions属性
    GDTServerSideVerificationOptions *ssv = [[GDTServerSideVerificationOptions alloc] init];
    ssv.userIdentifier = @"APP's user id for server verify";
    ssv.customRewardString = @"APP's custom data";
    [splashAd loadFullScreenAd];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeInterstitial adSourceObject:splashAd];
    }
}

#pragma mark - reward video
- (void)loadRewardedVideoWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    GDTRewardVideoAd *rewardVideoAd = [[GDTRewardVideoAd alloc] initWithPlacementId:@"8020744212936426"];
    rewardVideoAd.videoMuted = YES;
    rewardVideoAd.delegate = self;
    //如果设置了服务端验证，可以设置serverSideVerificationOptions属性
    GDTServerSideVerificationOptions *ssv = [[GDTServerSideVerificationOptions alloc] init];
    ssv.userIdentifier = @"APP's user id for server verify";
    ssv.customRewardString = @"APP's custom data";
    rewardVideoAd.serverSideVerificationOptions = ssv;
    [rewardVideoAd loadAd];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo adSourceObject:rewardVideoAd];
    }
}

#pragma mark - GDTSplashAdDelegate
/**
 *  开屏广告成功展示
 */
- (void)splashAdSuccessPresentScreen:(GDTSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/**
 *  开屏广告素材加载成功
 */
- (void)splashAdDidLoad:(GDTSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/**
 *  开屏广告展示失败
 */
- (void)splashAdFailToPresent:(GDTSplashAd *)splashAd withError:(NSError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeSplash error:error];
    }
}

/**
 *  应用进入后台时回调
 *  详解: 当点击下载应用时会调用系统程序打开，应用切换到后台
 */
- (void)splashAdApplicationWillEnterBackground:(GDTSplashAd *)splashAd {
    
}

/**
 *  开屏广告曝光回调
 */
- (void)splashAdExposured:(GDTSplashAd *)splashAd {
    
}

/**
 *  开屏广告点击回调
 */
- (void)splashAdClicked:(GDTSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/**
 *  开屏广告将要关闭回调
 */
- (void)splashAdWillClosed:(GDTSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillCloseWithStyleType:error:)]) {
        [self.delegate adWillCloseWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/**
 *  开屏广告关闭回调
 */
- (void)splashAdClosed:(GDTSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidDismissWithStyleType:error:)]) {
        [self.delegate adDidDismissWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/**
 *  开屏广告点击以后即将弹出全屏广告页
 */
- (void)splashAdWillPresentFullScreenModal:(GDTSplashAd *)splashAd {
    
}

/**
 *  开屏广告点击以后弹出全屏广告页
 */
- (void)splashAdDidPresentFullScreenModal:(GDTSplashAd *)splashAd {
    
}

/**
 *  点击以后全屏广告页将要关闭
 */
- (void)splashAdWillDismissFullScreenModal:(GDTSplashAd *)splashAd {
    
}

/**
 *  点击以后全屏广告页已经关闭
 */
- (void)splashAdDidDismissFullScreenModal:(GDTSplashAd *)splashAd {
    
}

/**
 * 开屏广告剩余时间回调
 */
- (void)splashAdLifeTime:(NSUInteger)time {
    
}

/**
 开屏激励回调 (只有开屏激励广告位才会有此回调)
 @param splashAd  GDTSplashAd 实例
 @param info 包含此次广告行为的一些信息，例如 @{@"GDT_TRANS_ID":@"930f1fc8ac59983bbdf4548ee40ac353"}, 通过@“GDT_TRANS_ID”可获取此次广告行为的交易id
 */
- (void)splashAdDidRewardEffective:(GDTSplashAd *)splashAd info:(NSDictionary *)info {
    
}

#pragma mark - GDTRewardedVideoAdDelegate
/**
 广告数据加载成功回调

 @param rewardedVideoAd GDTRewardVideoAd 实例
 */
- (void)gdt_rewardVideoAdDidLoad:(GDTRewardVideoAd *)rewardedVideoAd {
    NSLog(@"回调成功");
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 视频数据下载成功回调，已经下载过的视频会直接回调

 @param rewardedVideoAd GDTRewardVideoAd 实例
 */
- (void)gdt_rewardVideoAdVideoDidLoad:(GDTRewardVideoAd *)rewardedVideoAd {
    
}

/**
 视频播放页即将展示回调

 @param rewardedVideoAd GDTRewardVideoAd 实例
 */
- (void)gdt_rewardVideoAdWillVisible:(GDTRewardVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 视频广告曝光回调

 @param rewardedVideoAd GDTRewardVideoAd 实例
 */
- (void)gdt_rewardVideoAdDidExposed:(GDTRewardVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidShowWithStyleType:error:)]) {
        [self.delegate adDidShowWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 视频播放页关闭回调

 @param rewardedVideoAd GDTRewardVideoAd 实例
 */
- (void)gdt_rewardVideoAdDidClose:(GDTRewardVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidDismissWithStyleType:error:)]) {
        [self.delegate adDidDismissWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 视频广告信息点击回调

 @param rewardedVideoAd GDTRewardVideoAd 实例
 */
- (void)gdt_rewardVideoAdDidClicked:(GDTRewardVideoAd *)rewardedVideoAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidClickWithStyleType:error:)]) {
        [self.delegate adDidClickWithStyleType:OTAdSourceStyleTypeRewardedVideo error:nil];
    }
}

/**
 视频广告各种错误信息回调

 @param rewardedVideoAd GDTRewardVideoAd 实例
 @param error 具体错误信息
 */
- (void)gdt_rewardVideoAd:(GDTRewardVideoAd *)rewardedVideoAd didFailWithError:(NSError *)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeRewardedVideo error:error];
    }
}


/**
 视频广告播放达到激励条件回调

 @param rewardedVideoAd GDTRewardVideoAd 实例
 @param info 包含此次广告行为的一些信息，例如 @{@"GDT_TRANS_ID":@"930f1fc8ac59983bbdf4548ee40ac353"}, 通过@“GDT_TRANS_ID”可获取此次广告行为的交易id
 */
- (void)gdt_rewardVideoAdDidRewardEffective:(GDTRewardVideoAd *)rewardedVideoAd info:(NSDictionary *)info {
    
}

/**
 视频广告视频播放完成

 @param rewardedVideoAd GDTRewardVideoAd 实例
 */
- (void)gdt_rewardVideoAdDidPlayFinish:(GDTRewardVideoAd *)rewardedVideoAd {
    
}

#pragma mark - Native
- (void)loadNativeWithType:(OTAdSourceType)type userInfo:(NSDictionary *)userInfo {
    GDTUnifiedNativeAd *unifiedNativeAd = [[GDTUnifiedNativeAd alloc] initWithPlacementId:@"2000566593234845"];
    unifiedNativeAd.delegate = self;
    [unifiedNativeAd loadAd];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeNative adSourceObject:unifiedNativeAd];
    }
}

#pragma mark - Native Delegate
- (void)gdt_unifiedNativeAdLoaded:(NSArray<GDTUnifiedNativeAdDataObject *> * _Nullable)unifiedNativeAdDataObjects error:(NSError * _Nullable)error {
    NSLog(@"回调成功");
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.unifiedNativeAdDataObjects addObjectsFromArray:unifiedNativeAdDataObjects];
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeNative error:error];
    }
}

- (void)gdt_unifiedNativeAdViewDidClick:(GDTUnifiedNativeAdView *)unifiedNativeAdView
{
    NSLog(@"%s",__FUNCTION__);
    NSLog(@"%@ 广告被点击", unifiedNativeAdView.dataObject);
}

- (void)gdt_unifiedNativeAdViewWillExpose:(GDTUnifiedNativeAdView *)unifiedNativeAdView
{
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.unifiedNativeAdDataObjects removeLastObject];
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeNative error:nil];
    }
}

- (void)gdt_unifiedNativeAdDetailViewClosed:(GDTUnifiedNativeAdView *)unifiedNativeAdView
{
    NSLog(@"%s",__FUNCTION__);
    NSLog(@"广告详情页已关闭");
}

- (void)gdt_unifiedNativeAdViewApplicationWillEnterBackground:(GDTUnifiedNativeAdView *)unifiedNativeAdView
{
    NSLog(@"%s",__FUNCTION__);
    NSLog(@"广告进入后台");
}

- (void)gdt_unifiedNativeAdDetailViewWillPresentScreen:(GDTUnifiedNativeAdView *)unifiedNativeAdView
{
    NSLog(@"%s",__FUNCTION__);
    NSLog(@"广告详情页面即将打开");
}

@end
