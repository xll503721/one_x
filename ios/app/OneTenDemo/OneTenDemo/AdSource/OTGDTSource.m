//
//  OTGDTSource.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/7/16.
//

#import "OTGDTSource.h"
#import <GDTUnifiedNativeAd.h>
#import <GDTSDKConfig.h>

#import <OTAdViewController.h>

static NSString *kGDTMobSDKAppId = @"1105344611";

@interface OTGDTSource ()<GDTUnifiedNativeAdDelegate, GDTUnifiedNativeAdViewDelegate, OTAdSourceProtocol>

@property (nonatomic, strong) NSMutableArray<GDTUnifiedNativeAdDataObject *> *unifiedNativeAdDataObjects;

@end

@implementation OTGDTSource

- (void)dealloc {
    
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        static dispatch_once_t onceToken ;
        dispatch_once(&onceToken, ^{
            BOOL result = [GDTSDKConfig registerAppId:kGDTMobSDKAppId];
        });
        
        _unifiedNativeAdDataObjects = @[].mutableCopy;
    }
    return self;
}

- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType {
    switch (styleType) {
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
            [self loadNativeWithType:type userInfo:userInfo];
            break;
        default:
            break;
    }
}

#pragma mark - Native
- (void)loadNativeWithType:(OTAdSourceType)type userInfo:(NSDictionary *)userInfo {
    GDTUnifiedNativeAd *unifiedNativeAd = [[GDTUnifiedNativeAd alloc] initWithPlacementId:@"2000566593234845"];
    unifiedNativeAd.delegate = self;
    [unifiedNativeAd loadAd];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(adWillLoadWithStyleType:adSourceObject:)]) {
        [self.delegate adWillLoadWithStyleType:OTAdSourceStyleTypeInterstitial adSourceObject:unifiedNativeAd];
    }
}


- (void)showWithStyleType:(OTAdSourceStyleType)styleType rootViewController:(UIViewController *)viewController {
    switch (styleType) {
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
