//
//  OTAdViewController.m
//  oneten_ad
//
//  Created by li zhixuan on 2023/4/5.
//

#import "OTAdViewController.h"
#import "OTOnetenSDK.h"

@interface OTAdView ()

@end

@implementation OTAdView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
    }
    return self;
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
    
}

- (void)willMoveToWindow:(nullable UIWindow *)newWindow {
    [super willMoveToWindow:newWindow];
}

- (void)didMoveToWindow {
    [super didMoveToWindow];
}

@end


@interface OTAdViewController ()

@property (nonatomic, strong) id<OTAdSourceProtocol> adSource;
@property (nonatomic, assign) OTAdSourceStyleType category;

@property (nonatomic, assign) BOOL isShowing;

@end

@implementation OTAdViewController

- (void)dealloc {
    
}

- (instancetype)initWithAdSource:(id<OTAdSourceProtocol>)adSource category:(OTAdSourceStyleType)category
{
    self = [super init];
    if (self) {
        _adSource = adSource;
        _category = category;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    OTAdView *view = [[OTAdView alloc] initWithFrame:self.view.bounds];
    self.view = view;
}

- (void)willMoveToParentViewController:(UIViewController *)parent {
    [super willMoveToParentViewController:parent];
    
    if (!self.isShowing) {
        self.isShowing = !self.isShowing;
        
        if (self.category == OTAdSourceStyleTypeSplash && [self.adSource.delegate.adSourceObject isKindOfClass:[UIView class]]) {
            UIView *splashView = (UIView *)self.adSource.delegate.adSourceObject;
            splashView.frame = self.frame;
            [self.view addSubview:splashView];
        }
        
        if ([self.adSource respondsToSelector:@selector(showWithStyleType:rootViewController:)]) {
            [self.adSource showWithStyleType:self.category rootViewController:self];
        }
    }
}

@end
