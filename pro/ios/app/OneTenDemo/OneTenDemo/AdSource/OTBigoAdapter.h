//
//  OTBigoSource.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/9.
//

#import <Foundation/Foundation.h>
#import <OneTenSDK/OTAdSourceProtocol.h>
#import <BigoADS/BigoAdSdk.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTBigoAdapter : NSObject<OTAdSourceProtocol>

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
