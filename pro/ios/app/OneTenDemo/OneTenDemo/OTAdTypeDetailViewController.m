//
//  OTAdTypeDetailViewController.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/7/22.
//

#import "OTAdTypeDetailViewController.h"
#import "OTAdTypeDetailCellCell.h"
#import "OTDebugViewController.h"

#import <OTOnetenSDK.h>

static const NSInteger adTypeCellCount = 1;
static const NSInteger kOTAdTypeDetailViewControllerTableViewRequestTypeSection = 0;
static const NSInteger kOTAdTypeDetailViewControllerTableViewAdnSection = 1;

@implementation OTButton


@end

@interface OTAdTypeDetailViewController () <UITableViewDelegate, UITableViewDataSource>

@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (nonatomic, strong) NSMutableArray<NSDictionary *> *sectionTitles;
@property (nonatomic, strong) OTAdViewController *adViewController;
@property (nonatomic, strong) NSDictionary<NSString *, NSDictionary *> *allAdTypeDict;

@property (nonatomic, strong) NSMutableArray<NSString *> *selectedTypes;
@property (nonatomic, strong) NSString *selectedAdnName;
@property (nonatomic, strong) NSString *selectedRequestTypeName;
@property (nonatomic, strong) NSString *selectedPlacementId;

@property (nonatomic, strong) OTDebugViewController *debugViewController;

@end

@implementation OTAdTypeDetailViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self readPlistAdnInfo];
    [self setupTableViewSource];
    
    UIButton *customButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [customButton setTitle:@"Show Debug" forState:UIControlStateNormal];
    [customButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [customButton addTarget:self action:@selector(rightAction:) forControlEvents:UIControlEventTouchUpInside];

    UIBarButtonItem *customBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:customButton];
    self.navigationItem.rightBarButtonItem = customBarButtonItem;

    
    self.selectedTypes = @[].mutableCopy;
    
    [[OTOnetenSDK defalutSDK].adSDK setStageCallBack:^(OTOnetenAdSDKStageType stageType, NSString * _Nonnull placementId, NSError * _Nullable error, NSDictionary<NSString *,id> * _Nullable userInfo) {
        if (stageType == OTOnetenAdSDKStageTypeLoaded) {
            [self.debugViewController refreshWithPrint:@"Loaded"];
        }
        if (stageType == OTOnetenAdSDKStageTypeShow) {
            [self.debugViewController refreshWithPrint:@"Show"];
        }
        
        if (stageType == OTOnetenAdSDKStageTypeDismiss) {
            [self.adViewController.view removeFromSuperview];
            [self.adViewController removeFromParentViewController];
            [self.adViewController dismissViewControllerAnimated:NO completion:nil];
        }
    }];
    
    [self addChildViewController:self.debugViewController];
    [self.view addSubview:self.debugViewController.view];
}

- (void)readPlistAdnInfo {
    NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"Info" ofType:@"plist"];
    NSDictionary *infoDictionary = [NSDictionary dictionaryWithContentsOfFile:plistPath];

    self.allAdTypeDict = infoDictionary[@"AdType"][self.title];
}

- (void)setupTableViewSource {
    self.sectionTitles = @[@{@"Type": @[@[@"Common", @"C2S", @"S2S", @"All"]]}].mutableCopy;
    
    NSMutableSet<NSString *> *section = [NSMutableSet set];
    [self.allAdTypeDict enumerateKeysAndObjectsUsingBlock:^(NSString * _Nonnull key, NSDictionary<NSString *, NSArray *> * _Nonnull obj, BOOL * _Nonnull stop) {
        [section addObjectsFromArray:obj.allKeys];
    }];
    NSMutableArray<NSString *> *allAdTitles = section.allObjects.mutableCopy;
    NSMutableArray<NSArray<NSString *> *> *allRowAdTitles = @[].mutableCopy;
    while (allAdTitles.count > 0) {
        NSInteger count = (allAdTitles.count < 4 ? allAdTitles.count : 4);
        NSRange range = NSMakeRange(0, count);
        NSArray<NSString *> *rowTitles = [allAdTitles subarrayWithRange:range];
        [allRowAdTitles addObject:rowTitles];
        [allAdTitles removeObjectsInRange:range];
    }
    
    [self.sectionTitles addObject:@{@"Ad": allRowAdTitles}];
}

#pragma mark - Action

- (void)rightAction:(UIButton *)button {
    self.debugViewController.view.hidden = !self.debugViewController.view.hidden;
    
    [button setTitle:self.debugViewController.view.hidden ? @"Show Debug" : @"Hide Debug" forState:UIControlStateNormal];
}

- (IBAction)loadAd:(id)sender {
    [[OTOnetenSDK defalutSDK].adSDK loadWithPlacementId:self.selectedPlacementId];
}

- (IBAction)showAd:(UIButton *)sender {
    NSError *error;
    self.adViewController = [[OTOnetenSDK defalutSDK].adSDK showWithPlacementId:self.selectedPlacementId error:&error];
    if (error) {
        return;
    }
    
    self.adViewController.view.frame = self.view.frame;
    self.adViewController.frame = self.view.frame;
    [self.view addSubview:self.adViewController.view];
    [self addChildViewController:self.adViewController];
    
    OTAdView *view = (OTAdView *)self.adViewController.view;
    view.backgroundColor = [UIColor clearColor];
    view.titleLabel.frame = CGRectMake(0, 0, 100, 50);
    
    [view addSubview:view.titleLabel];
}

- (IBAction)isReadyAd:(id)sender {
}

#pragma mark - UITableViewDelegate, UITableViewDataSource

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return self.sectionTitles.count;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    return self.sectionTitles[section].allKeys.firstObject;
}

- (nonnull UITableViewCell *)tableView:(nonnull UITableView *)tableView cellForRowAtIndexPath:(nonnull NSIndexPath *)indexPath {
    OTAdTypeDetailCellCell *cell = [tableView dequeueReusableCellWithIdentifier:@"OTAdTypeDetailCellCell"];
    NSDictionary *sectionItemDict = self.sectionTitles[indexPath.section];
    NSArray<NSString *> *items = sectionItemDict[sectionItemDict.allKeys.firstObject][indexPath.row];
    
    NSArray<OTButton *> *buttons = @[cell.button1, cell.button2, cell.button3, cell.button4];
    [buttons enumerateObjectsUsingBlock:^(OTButton * _Nonnull button, NSUInteger idx, BOOL * _Nonnull stop) {
        button.hidden = !(items.count > idx);
        [button addTarget:self action:@selector(selectItem:) forControlEvents:UIControlEventTouchUpInside];
        
        if (items.count > idx) {
            button.name = items[idx];
            [button setTitle:button.name forState:UIControlStateNormal];
            button.section = indexPath.section;
            button.row = indexPath.row;
            button.column = idx;
            button.selected = NO;
            if (button.section == kOTAdTypeDetailViewControllerTableViewAdnSection) {
                if ([button.name isEqualToString:self.selectedAdnName]) {
                    button.selected = YES;
                }
            } else if (button.section == kOTAdTypeDetailViewControllerTableViewRequestTypeSection) {
                id item = self.allAdTypeDict[button.name][self.selectedAdnName];
                if (item) {
                    button.selected = YES;
                    self.selectedRequestTypeName = button.name;
                }
            }
        }
    }];
    
    return cell;
}

- (NSInteger)tableView:(nonnull UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == 0) {
        return adTypeCellCount;
    } else {
        NSDictionary *sectionItemDict = self.sectionTitles[section];
        NSArray<NSString *> *items = sectionItemDict[sectionItemDict.allKeys.firstObject];
        return items.count;
    }
    return 0;
}

#pragma mark - Action

- (void)selectItem:(OTButton *)button {
    if (button.section == kOTAdTypeDetailViewControllerTableViewAdnSection) {
        self.selectedAdnName = button.name;
    } else if (button.section == kOTAdTypeDetailViewControllerTableViewRequestTypeSection) {
        self.selectedRequestTypeName = button.name;
    }
    [self.tableView reloadData];
}

#pragma mark - getter

- (NSString *)selectedPlacementId {
    return [self.allAdTypeDict[self.selectedRequestTypeName][self.selectedAdnName] firstObject];
}

- (OTDebugViewController *)debugViewController {
    if (!_debugViewController) {
        _debugViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"OTDebugViewController"];
        _debugViewController.view.hidden = YES;
    }
    return _debugViewController;
}

@end
