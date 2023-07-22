//
//  OTAdSource.h
//  oneten_ad_entity
//
//  Created by li zhixuan on 2023/4/8.
//

#import <Foundation/Foundation.h>
#import "OTAdSourceProtocol.h"
#include <cross/OTPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTAdSourceModelObjectDelegate : NSObject <OTPlatformObjectDelegate, OTAdSourceDelegate>

@property (nonatomic, unsafe_unretained) void* cPlusPlusPrt;
@property (nonatomic, readonly) id adSourceObject;

@end

NS_ASSUME_NONNULL_END
