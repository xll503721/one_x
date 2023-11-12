//
//  OTTianmuAdapter.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/12.
//

#import <Foundation/Foundation.h>
#import <OneTenSDK/OTAdSourceProtocol.h>
#import <TianmuSDK/TianmuSDK.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTTianmuAdapter : NSObject<OTAdSourceProtocol>

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
