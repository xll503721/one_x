//
//  OTKSSource.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/10/15.
//

#import <Foundation/Foundation.h>
#import <OneTenSDK/OTAdSourceProtocol.h>
#import <KSAdSDK/KSAdSDK.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTKSAdapter : NSObject<OTAdSourceProtocol>

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
