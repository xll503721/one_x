//
//  OTMTGSource.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/10/29.
//

#import <Foundation/Foundation.h>
#import <OneTenSDK/OTAdSourceProtocol.h>
#import <MTGSDK/MTGSDK.h>
#import <MTGSDKReward/MTGRewardAdManager.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTMTGAdapter : NSObject<OTAdSourceProtocol>

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
