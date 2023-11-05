//
//  OTPangleSource.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/10/29.
//

#import <Foundation/Foundation.h>
#import <PAGAdSDK/PAGAdSDK.h>
#import <OneTenSDK/OTAdSourceProtocol.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTPangleSource : NSObject<OTAdSourceProtocol>

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
