//
//  OTOneTenSdk.h
//  OnTen
//
//  Created by li zhixuan on 2022/10/29.
//

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "OTOnetenAdSDK.h"

typedef NS_ENUM(NSUInteger, OTOneTenSDKType) {
    OTOneTenSDKTypeAd,
    OTOneTenSDKTypeIm,
    OTOneTenSDKTypeAudio,
    OTOneTenSDKTypeVideo,
};

@interface OTOnetenSDK : NSObject

@property (nonatomic, strong, readonly) OTOnetenAdSDK *adSDK;

+ (OTOnetenSDK *)defalutSDK;

- (void)initAppId:(NSString *)appId type:(OTOneTenSDKType)type;

@end

#endif
