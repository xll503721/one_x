//
//  OTMyTargetSource.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/5.
//

#import <Foundation/Foundation.h>
#import <OneTenSDK/OTAdSourceProtocol.h>
#import <MyTargetSDK/MyTargetSDK.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTMyTargetAdapter : NSObject<OTAdSourceProtocol>

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
