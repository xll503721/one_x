#import "OTOnetenSDK.h"
#import "OTOnetenAdSDK.h"
#import "OTAdSourceProtocol.h"
#import <objc/runtime.h>

#include "ad/oneten_ad_sdk.h"
#include <cross/OTPlatform.h>

#define OTOnetenMsgSend(...) ((void (*)(void *, SEL, void *))objc_msgSend)(__VA_ARGS__)

static NSString *kOTOnetenSDKPrefix = @"OT";
static NSString *kOTOnetenSDKDelegate = @"ObjectDelegate";

@interface OTOnetenSDK ()

@property (nonatomic, strong) OTPlatform *platform;

@end

@implementation OTOnetenSDK

+ (OTOnetenSDK *)defalutSDK {
    static OTOnetenSDK *shareInstance = nil;
    static dispatch_once_t onceToken ;
    
    dispatch_once(&onceToken, ^{
        shareInstance = [[OTOnetenSDK alloc] init];
    }) ;
    return shareInstance;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _adSDK = [[OTOnetenAdSDK alloc] init];
        _platform = [[OTPlatform alloc] init];
    }
    return self;
}

- (void)initAppId:(NSString *)appId type:(OTOneTenSDKType)type {
    switch (type) {
        case OTOneTenSDKTypeAd: {
            SEL selector = NSSelectorFromString(@"startWithAppId:");
            if ([self.adSDK respondsToSelector:selector]) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
                [self.adSDK performSelector:selector withObject:appId];
#pragma clang diagnostic pop
            }
        }
            break;
            
        default:
            break;
    }
}

@end
