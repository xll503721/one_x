//
//  OTStartSource.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/11/4.
//

#import <Foundation/Foundation.h>
#import <OneTenSDK/OTAdSourceProtocol.h>
#import <StartApp/StartApp.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTStartAdapter : NSObject<OTAdSourceProtocol>

@property (nonatomic, strong) id<OTAdSourceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
