//
//  OTTopOnSource.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/5.
//

#import <Foundation/Foundation.h>
#import <OneTenSDK/OTAdSourceProtocol.h>
#import <AnyThinkSDK/AnyThinkSDK.h>
#import <AnyThinkRewardedVideo/AnyThinkRewardedVideo.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTTopOnAdapter : NSObject<OTAdSourceProtocol>

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
