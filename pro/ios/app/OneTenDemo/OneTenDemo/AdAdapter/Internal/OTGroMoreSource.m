//
//  OTGroMoreSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/7/16.
//

#import "OTGroMoreSource.h"
#import <BUAdSDK/BUAdSDK.h>
#import <OTAdViewController.h>

@interface OTGroMoreSource ()<OTAdSourceProtocol, BUMNativeAdsManagerDelegate, BUMNativeAdDelegate,
                                                  BUSplashAdDelegate, BUSplashCardDelegate, BUSplashZoomOutDelegate>

@property (nonatomic, strong) NSMutableArray<BUNativeAd *> *nativeAdDataArray;

@end

@implementation OTGroMoreSource

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
    configuration.useMediation = YES;
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
            
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            if ([self.delegate.adSourceObject isKindOfClass:[BUSplashAd class]]) {
                return self.delegate.adSourceObject;
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
        case OTAdSourceStyleTypeNative: {
            BUNativeAdsManager *adManager = self.delegate.adSourceObject;
            OTAdViewController *adViewController = (OTAdViewController *)viewController;
            if ([adManager isKindOfClass:[BUNativeAdsManager class]] && [adViewController isKindOfClass:[OTAdViewController class]]) {
                adManager.mediation.rootViewController = viewController;
                OTAdView *view = (OTAdView *)adViewController.view;
                
                BUNativeAd *nativeAd = self.nativeAdDataArray.lastObject;
                self.nativeAdDataArray.lastObject.mediation.canvasView.titleLabel.text = nativeAd.data.AdTitle;
                
                nativeAd.mediation.canvasView.frame = CGRectMake(0, 0, 100, 100);
                [view addSubview:nativeAd.mediation.canvasView];
            }
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            if ([self.delegate.adSourceObject isKindOfClass:[BUSplashAd class]]) {
                [(BUSplashAd *)self.delegate.adSourceObject showSplashViewInRootViewController:viewController];
            }
        }
            break;
        default:
            break;
    }
}

- (void)loadWithStyleType:(OTAdSourceStyleType)styleType adSourceType:(OTAdSourceType)type userInfo:(NSDictionary<id,id> *)userInfo {
    switch (styleType) {
        case OTAdSourceStyleTypeNative: {
            [self loadNativeWithType:type userInfo:userInfo];
        }
            break;
        case OTAdSourceStyleTypeSplash: {
            [self loadSplashWithType:type userInfo:userInfo];
        }
            break;
        default:
            break;
    }
    
}

#pragma mark - Load
- (void)loadNativeWithType:(OTAdSourceType)type userInfo:(NSDictionary *)userInfo {
    BUAdSlot *slot1 = [[BUAdSlot alloc] init];
    BUSize *imgSize1 = [[BUSize alloc] init];
    imgSize1.width = 1080;
    imgSize1.height = 1920;
    slot1.imgSize = imgSize1;
    
    slot1.ID = @"945838734";
    // 如果是模板广告，返回高度将不一定是300，而是按照414和对应代码位在平台的配置计算出的高度
    slot1.adSize = CGSizeMake([UIScreen mainScreen].bounds.size.width, 400);
    
    slot1.mediation.mutedIfCan = YES;
    
    BUNativeAdsManager *adManager = [[BUNativeAdsManager alloc] initWithSlot:slot1];
    adManager.delegate = self;
    [adManager loadAdDataWithCount:1];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeInterstitial adSourceObject:adManager];
    }
}

/// start load splash ad
/// @param type c2s s2s
/// @param userInfo info
- (void)loadSplashWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo {
    BUAdSlot *slot = [[BUAdSlot alloc]init];
    slot.ID = @"800546851";

    BUSplashAd *splashAd = [[BUSplashAd alloc] initWithSlot:slot adSize:[UIScreen mainScreen].bounds.size];
    splashAd.delegate = self;
    splashAd.cardDelegate = self;
    splashAd.zoomOutDelegate = self;
    
    splashAd.supportCardView = YES;
    splashAd.supportZoomOutView = YES;
    splashAd.tolerateTimeout = 3.0;
    [splashAd loadAdData];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeInterstitial adSourceObject:splashAd];
    }
}

#pragma mark - Native
- (void)nativeAdsManagerSuccessToLoad:(BUNativeAdsManager *)adsManager nativeAds:(NSArray<BUNativeAd *> *_Nullable)nativeAdDataArray {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        self.nativeAdDataArray = nativeAdDataArray.mutableCopy;
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeNative error:nil];
    }
}

- (void)nativeAdsManager:(BUNativeAdsManager *)adsManager didFailWithError:(NSError *_Nullable)error {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeNative error:error];
    }
}

/// 广告即将展示全屏页面/商店时触发
/// @param nativeAd 广告视图
- (void)nativeAdWillPresentFullScreenModal:(BUNativeAd *_Nonnull)nativeAd {
    
}

/// 聚合维度混出模板广告时渲染成功回调，可能不会回调
/// @param nativeAd 模板广告对象
- (void)nativeAdExpressViewRenderSuccess:(BUNativeAd *_Nonnull)nativeAd {
    
}

/// 聚合维度混出模板广告时渲染失败回调，可能不会回调
/// @param nativeAd 模板广告对象
/// @param error 渲染出错原因
- (void)nativeAdExpressViewRenderFail:(BUNativeAd *_Nonnull)nativeAd error:(NSError *_Nullable)error {
    
}

/// 当视频播放状态改变之后触发
/// @param nativeAd 广告视图
/// @param playerState 变更后的播放状态
- (void)nativeAdVideo:(BUNativeAd *_Nullable)nativeAd stateDidChanged:(BUPlayerPlayState)playerState {
    
}

/// 广告视图中视频视图被点击时触发
/// @param nativeAd 广告视图
- (void)nativeAdVideoDidClick:(BUNativeAd *_Nullable)nativeAd {
    
}

/// 广告视图中视频播放完成时触发
/// @param nativeAd 广告视图
- (void)nativeAdVideoDidPlayFinish:(BUNativeAd *_Nullable)nativeAd {
    
}

/// 广告摇一摇提示view消除时调用该方法
/// @param nativeAd 广告视图
- (void)nativeAdShakeViewDidDismiss:(BUNativeAd *_Nullable)nativeAd {
    
}

/// 激励信息流视频进入倒计时状态时调用
/// @param nativeAdView 广告视图
/// @param countDown : 倒计时
/// @Note : 当前该回调仅适用于CSJ广告 - v4200
- (void)nativeAdVideo:(BUNativeAd *_Nullable)nativeAdView rewardDidCountDown:(NSInteger)countDown {
    
}

/**
 This method is called when native ad material loaded successfully. This method will be deprecated. Use nativeAdDidLoad:view: instead
 @Note :  Mediation dimension does not support this interface.
 */
- (void)nativeAdDidLoad:(BUNativeAd *)nativeAd {
    
}


/**
 This method is called when native ad material loaded successfully.
 @Note :  Mediation dimension does not support this interface.
 */
- (void)nativeAdDidLoad:(BUNativeAd *)nativeAd view:(UIView *_Nullable)view {
    
}

/**
 This method is called when native ad materia failed to load.
 @param error : the reason of error
 @Note :  Mediation dimension does not support this interface.
 */
- (void)nativeAd:(BUNativeAd *)nativeAd didFailWithError:(NSError *_Nullable)error {
    
}

/**
 This method is called when native ad slot has been shown.
 */
- (void)nativeAdDidBecomeVisible:(BUNativeAd *)nativeAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adDidLoadWithStyleType:error:)]) {
        [self.nativeAdDataArray removeLastObject];
        [self.delegate adDidLoadWithStyleType:OTAdSourceStyleTypeNative error:nil];
    }
}

/**
 This method is called when another controller has been closed.
 @param interactionType : open appstore in app or open the webpage or view video ad details page.
 */
- (void)nativeAdDidCloseOtherController:(BUNativeAd *)nativeAd interactionType:(BUInteractionType)interactionType {
    
}

/**
 This method is called when native ad is clicked.
 */
- (void)nativeAdDidClick:(BUNativeAd *)nativeAd withView:(UIView *_Nullable)view {
    
}

/**
 This method is called when the user clicked dislike reasons.
 Only used for dislikeButton in BUNativeAdRelatedView.h
 @param filterWords : reasons for dislike
 */
- (void)nativeAd:(BUNativeAd *_Nullable)nativeAd dislikeWithReason:(NSArray<BUDislikeWords *> *_Nullable)filterWords {
    
}

/**
 This method is called when the Ad view container is forced to be removed.
 @param nativeAd : Ad material
 @param adContainerView : Ad view container
 @Note :  Mediation dimension does not support this interface.
 */
- (void)nativeAd:(BUNativeAd *_Nullable)nativeAd adContainerViewDidRemoved:(UIView *)adContainerView {
    
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
/// @Note :  Mediation dimension does not support this callBack.
- (void)splashAdRenderSuccess:(BUSplashAd *)splashAd {
    
}

/// This method is called when splash view render failed
/// @Note :  Mediation dimension does not support this callBack.
- (void)splashAdRenderFail:(BUSplashAd *)splashAd error:(BUAdError *_Nullable)error {
    
}

/// This method is called when splash view will show
- (void)splashAdWillShow:(BUSplashAd *)splashAd {
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillShowWithStyleType:error:)]) {
        [self.delegate adWillShowWithStyleType:OTAdSourceStyleTypeSplash error:nil];
    }
}

/// This method is called when splash view did show
/// @Note :  Mediation dimension does not support this callBack.
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
/// @Note :  Mediation dimension does not support this callBack.
- (void)splashAdViewControllerDidClose:(BUSplashAd *)splashAd {
    
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

/// This method is called when splash card is ready to show.
- (void)splashCardReadyToShow:(BUSplashAd *)splashAd {
    
}

/// This method is called when splash card is clicked.
- (void)splashCardViewDidClick:(BUSplashAd *)splashAd {
    
}

/// This method is called when splash card is closed.
- (void)splashCardViewDidClose:(BUSplashAd *)splashAd {
    
}

/// This method is called when splash zoomout is ready to show.
- (void)splashZoomOutReadyToShow:(BUSplashAd *)splashAd {
    
}

/// This method is called when splash zoomout is clicked.
- (void)splashZoomOutViewDidClick:(BUSplashAd *)splashAd {
    
}

/// This method is called when splash zoomout is closed.
- (void)splashZoomOutViewDidClose:(BUSplashAd *)splashAd {
    
}

@end
