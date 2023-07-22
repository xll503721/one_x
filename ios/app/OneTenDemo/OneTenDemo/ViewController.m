//
//  ViewController.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/2/19.
//

#import "ViewController.h"
#import <OneTenSDK/OTOneTen.h>
#import <OneTenSDK/OTOneTenAdSDK.h>
#import <WindSDK/WindSDK.h>

#import "OTAdTypeTableViewCell.h"
#import "OTAdTypeDetailViewController.h"

#define AppId @"6877"//应用ID
#define AppKey @"eccdcdbd9adbd4a7"//应用key
#define FullScreenVideoAdPlacementId @"f21b862c1cd"//插屏广告位ID

@interface ViewController ()<WindIntersititialAdDelegate, UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) OTAdViewController *adViewController;
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (nonatomic, strong) NSArray<NSDictionary *> *adTypeItems;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.title = @"X";
    self.adTypeItems = @[
        @{@"title": @"Splash"},
        @{@"title": @"Banner"},
        @{@"title": @"Native"},
        @{@"title": @"Interstitial"},
        @{@"title": @"RewardedVideo"},
    ];
    self.tableView.rowHeight = self.view.bounds.size.height / self.adTypeItems.count;
    
    [[OTOnetenSDK defalutSDK] initAppId:@"111" type:OTOneTenSDKTypeAd];
}

- (void)showAdViewController {
    
}

#pragma mark - UITableViewDataSource, UITableViewDelegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.adTypeItems.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    OTAdTypeTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"OTAdTypeTableViewCell"];
    NSDictionary *itemDict = self.adTypeItems[indexPath.row];
    cell.mainTitleLabel.text = itemDict[@"title"];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    OTAdTypeDetailViewController *adTypeDetailViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"OTAdTypeDetailViewController"];
    NSDictionary *itemDict = self.adTypeItems[indexPath.row];
    adTypeDetailViewController.title = itemDict[@"title"];
    [self.navigationController pushViewController:adTypeDetailViewController animated:YES];
}

@end
