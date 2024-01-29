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

using CPlusPlusPrt = std::shared_ptr<void>;

@interface OTAdSourceModelObjectDelegate : NSObject <OTPlatformObjectDelegate, OTAdSourceDelegate>

- (void)setCPlusPlusPrt:(std::shared_ptr<void>)cPlusPlusPrt;
@property (nonatomic, readonly) id adSourceObject;

@end

NS_ASSUME_NONNULL_END
