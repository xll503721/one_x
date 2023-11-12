//
//  TENSigmobSource.h
//  ONETEN_AD_sdk
//
//  Created by li zhixuan on 2022/11/6.
//

#import <Foundation/Foundation.h>
#import <OneTenSDK/OTAdSourceProtocol.h>
#import <WindSDK/WindSDK.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTSigmobAdapter : NSObject

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
