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

@property (weak, nonatomic) IBOutlet UIButton *loadButton;
@property (weak, nonatomic) IBOutlet UIButton *showButton;
@property (weak, nonatomic) IBOutlet UIButton *isReadyButton;
@property (weak, nonatomic) IBOutlet UITextView *logTextView;
@property (weak, nonatomic) IBOutlet UITableView *tableView;

@property (nonatomic, strong) NSMutableArray<NSDictionary *> *sectionTitles;
@property (nonatomic, strong) OTAdViewController *adViewController;
@property (nonatomic, strong) NSDictionary<NSString *, NSDictionary *> *allAdTypeDict;
@property (nonatomic, strong) OTDebugViewController *debugViewController;

@property (nonatomic, strong) NSString *selectedPlacementId;
@property (nonatomic, strong) OTButton *selectedButton;

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
    
    [self addChildViewController:self.debugViewController];
    [self.view addSubview:self.debugViewController.view];
    
    [[OTOnetenSDK defalutSDK].adSDK setStageCallBack:^(OTOnetenAdSDKStageType stageType, NSString * _Nonnull placementId, NSError * _Nullable error, NSDictionary<NSString *,id> * _Nullable userInfo) {
        NSString *text = self.logTextView.text;
        
        if (stageType == OTOnetenAdSDKStageTypeLoaded) {
            NSString *text = self.logTextView.text;
            self.logTextView.text = [text stringByAppendingFormat:@"\n%@ %@: %@ have been loaded", self.selectedButton.name, self.selectedButton.adType, placementId];
        }
        
        if (stageType == OTOnetenAdSDKStageTypeShow) {
            self.logTextView.text = [text stringByAppendingFormat:@"\n%@ %@: %@ have shown", self.selectedButton.name, self.selectedButton.adType, placementId];
        }
        
        if (stageType == OTOnetenAdSDKStageTypeClick) {
            self.logTextView.text = [text stringByAppendingFormat:@"\n%@ %@: %@ have clicked", self.selectedButton.name, self.selectedButton.adType, placementId];
        }
        
        if (stageType == OTOnetenAdSDKStageTypeDismiss) {
            [self.adViewController.view removeFromSuperview];
            [self.adViewController removeFromParentViewController];
            [self.adViewController dismissViewControllerAnimated:NO completion:nil];
            self.adViewController = nil;
            
            self.logTextView.text = [text stringByAppendingFormat:@"\n%@ %@: %@ have closed", self.selectedButton.name, self.selectedButton.adType, placementId];
        }
    }];
}

- (void)readPlistAdnInfo {
    NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"Info" ofType:@"plist"];
    NSDictionary *infoDictionary = [NSDictionary dictionaryWithContentsOfFile:plistPath];

    self.allAdTypeDict = infoDictionary[@"AdType"][self.title];
}

- (void)setupTableViewSource {
    self.sectionTitles = @[].mutableCopy;
    
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

- (IBAction)loadAd:(UIButton *)sender {
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
    NSString *text = self.logTextView.text;
    
    NSError *error;
    self.adViewController = [[OTOnetenSDK defalutSDK].adSDK showWithPlacementId:self.selectedPlacementId error:&error];
    if (error) {
        text = [text stringByAppendingFormat:@"\n%@ %@ %@ is not ready", self.selectedPlacementId, self.selectedButton.name, self.selectedButton.adType];
    } else {
        text = [text stringByAppendingFormat:@"\n%@ %@ %@ is ready", self.selectedPlacementId, self.selectedButton.name, self.selectedButton.adType];
    }
    self.logTextView.text = text;
}

#pragma mark - UITableViewDelegate, UITableViewDataSource

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
        }
    }];
    
    return cell;
}


- (NSInteger)tableView:(nonnull UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    NSDictionary *sectionItemDict = self.sectionTitles[section];
    NSArray<NSString *> *items = sectionItemDict[sectionItemDict.allKeys.firstObject];
    return items.count;
}

#pragma mark - Action

- (void)selectItem:(OTButton *)button {
    self.selectedButton.selected = !self.selectedButton.selected;
    self.selectedButton = button;
    self.selectedButton.selected = !self.selectedButton.selected;
    
    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Adn Type" message:@"select adn type, and start load" preferredStyle:UIAlertControllerStyleAlert];
    
    [self.allAdTypeDict enumerateKeysAndObjectsUsingBlock:^(NSString * _Nonnull key, NSDictionary * _Nonnull obj, BOOL * _Nonnull stop) {
        NSString *placementId = obj[button.name];
        if (placementId && ![placementId isEqualToString:@""]) {
            [alert addAction:[UIAlertAction actionWithTitle:key style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
                self.selectedPlacementId = placementId;
                self.selectedButton.name = button.name;
                self.selectedButton.adType = key;
                
                NSString *loadString = [NSString stringWithFormat:@"Load(%@ %@)", button.name, key];
                [self.loadButton setTitle:loadString forState:UIControlStateNormal];
            }]];
        }
    }];
    
    [alert addAction:[UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
    }]];
    
    [self presentViewController:alert animated:YES completion:nil];
}

#pragma mark - getter

- (OTDebugViewController *)debugViewController {
    if (!_debugViewController) {
        _debugViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"OTDebugViewController"];
        _debugViewController.view.hidden = YES;
    }
    return _debugViewController;
}

@end
