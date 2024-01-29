//
//  OTGDTSource.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/7/16.
//

#import <Foundation/Foundation.h>
#import <OneTenSDK/OTAdSourceProtocol.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTGDTAdapter : NSObject<OTAdSourceProtocol>

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
