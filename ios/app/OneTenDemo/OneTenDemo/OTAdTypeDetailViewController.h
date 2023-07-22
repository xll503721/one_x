//
//  OTAdTypeDetailViewController.h
//  OneTenDemo
//
//  Created by li zhixuan on 2023/7/22.
//

#import <UIKit/UIKit.h>
#import <OTAdSourceProtocol.h>

NS_ASSUME_NONNULL_BEGIN

@interface OTAdTypeDetailViewController : UIViewController

@end

@interface OTButton : UIButton

@property (nonatomic, strong) NSString *name;
@property (nonatomic, assign) NSInteger section;
@property (nonatomic, assign) NSInteger row;
@property (nonatomic, assign) NSInteger column;

@end

NS_ASSUME_NONNULL_END
