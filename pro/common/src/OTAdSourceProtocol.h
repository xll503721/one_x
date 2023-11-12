//
//  TENAdvertSource.h
//  ONETEN_AD_sdk
//
//  Created by li zhixuan on 2022/11/10.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, OTAdSourceType) {
    OTAdSourceTypeC2S,
    OTAdSourceTypeS2S,
    OTAdSourceTypeNormal,
};

typedef NS_ENUM(NSUInteger, OTAdSourceStyleType) {
    OTAdSourceStyleTypeSplash,
    OTAdSourceStyleTypeInterstitial,
    OTAdSourceStyleTypeBanner,
    OTAdSourceStyleTypeRewardedVideo,
    OTAdSourceStyleTypeNative,
};

typedef NS_ENUM(NSUInteger, OTAdSourceCategroyLoadStatusType) {
    OTAdSourceCategroyLoadStatusTypeSucceed,
    OTAdSourceCategroyLoadStatusTypeFailed,
};

typedef NS_ENUM(NSUInteger, OTAdSourceCallbackType) {
    OTAdSourceCallbackTypeWillLoad,
    OTAdSourceCallbackTypeDidLoad,
    
    OTAdSourceCallbackTypeWillShow,
    OTAdSourceCallbackTypeDidShow,
    
    OTAdSourceCallbackTypeWillClick,
    OTAdSourceCallbackTypeDidClick,
    
    OTAdSourceCallbackTypeWillClose,
    OTAdSourceCallbackTypeDidClose,
    
    OTAdSourceCallbackTypeRegister,
    OTAdSourceCallbackTypeCallback,
};

@protocol OTPlatformProtocol <NSObject>

@property void* rawPrt;

@end

#pragma mark - OTAdSourceDelegate

@protocol OTAdSourceDelegate <NSObject>

@required

@property (nonatomic, readonly) id adSourceObject;

- (void)registerWithUserInfo:(NSDictionary<id, id> *)userInfo error:(NSError *)error;

- (void)adSaveSourceObject:(id)adSourceObject;
- (void)adWillLoadWithStyleType:(OTAdSourceStyleType)styleType adSourceObject:(id)adSourceObject;
- (void)adDidLoadWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error;
- (void)nativeStyleDidLoadWithAds:(NSArray<id> *)ads error:(NSError *)error;;

- (void)adWillShowWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error;
- (void)adDidShowWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error;

- (void)adWillDismissWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error;
- (void)adDidDismissWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error;

- (void)adWillCloseWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error;
- (void)adDidCloseWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error;

- (void)adDidClickWithStyleType:(OTAdSourceStyleType)styleType error:(NSError *)error;

- (void)adDidCallbackWithMethodName:(NSString *)methodName error:(NSError *)error;

@end

#pragma mark - OTAdSourceProtocol

@protocol OTAdSourceProtocol <NSObject>

@required

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

- (void)registerWithUserInfo:(NSDictionary<id, id> *)userInfo;

- (void)loadWithStyleType:(OTAdSourceStyleType)styleType adSourceType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo;
- (BOOL)isReadyWithStyle:(OTAdSourceStyleType)styleType;
- (void)showWithStyleType:(OTAdSourceStyleType)styleType rootViewController:(UIViewController *)viewController;

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
- (void)loadNativeWithType:(OTAdSourceType)type userInfo:(NSDictionary<id, id> *)userInfo;

- (void)sendWinNotificationWithType:(OTAdSourceStyleType)styleType userInfo:(NSDictionary *)userInfo;
- (void)sendLossNotificationWithType:(OTAdSourceStyleType)styleType userInfo:(NSDictionary *)userInfo;

@end
