//
//  OTCSJSource.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/10/6.
//

#import <Foundation/Foundation.h>
#import <BUAdSDK/BUAdSDK.h>
#import <OneTenSDK/OTAdSourceProtocol.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTCSJSource : NSObject<OTAdSourceProtocol>

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
