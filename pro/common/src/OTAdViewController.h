//
//  OTAdViewController.h
//  oneten_ad
//
//  Created by li zhixuan on 2023/4/5.
//

#import <UIKit/UIKit.h>
#import "OTAdSourceProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface OTAdView : UIView

@property (nonatomic, strong) UILabel *titleLabel;

@end

#pragma mark - OTAdViewController

@interface OTAdViewController : UIViewController

- (instancetype)initWithAdSource:(id<OTAdSourceProtocol>)adSource category:(OTAdSourceStyleType)category;

@property (nonatomic, assign) CGRect frame;

@end

NS_ASSUME_NONNULL_END
