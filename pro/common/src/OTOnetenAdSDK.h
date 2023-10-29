//
//  OTOneTenAdSDK.h
//  SDKCommon
//
//  Created by li zhixuan on 2022/12/11.
//

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "OTAdViewController.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, OTOnetenAdSDKStageType) {
    OTOnetenAdSDKStageTypeLoad,
    OTOnetenAdSDKStageTypeLoaded,
    OTOnetenAdSDKStageTypeLoadFailed,
    
    OTOnetenAdSDKStageTypeShow,
    OTOnetenAdSDKStageTypeClick,
    OTOnetenAdSDKStageTypeClose,
    OTOnetenAdSDKStageTypeDismiss,
};

typedef void (^StageCallBack) (OTOnetenAdSDKStageType stageType, NSString *placementId, NSError * _Nullable error, NSDictionary<NSString *, id> * _Nullable userInfo);

@interface OTOnetenAdSDK : NSObject

@property (nonatomic, readonly) NSString *appId;
@property (nonatomic, strong) StageCallBack stageCallBack;

- (BOOL)loadWithPlacementId:(NSString *)placementId userInfo:(nullable NSDictionary<NSString *, NSString *> *)userInfo;
- (void)loadWithPlacementId:(NSString *)placementId;

- (OTAdViewController *)showWithPlacementId:(NSString *)placementId error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END

#endif

