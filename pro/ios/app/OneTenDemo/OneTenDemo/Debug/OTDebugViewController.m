//
//  OTDebugViewController.m
//  OneTenDemo
//
//  Created by li zhixuan on 2023/7/24.
//

#import "OTDebugViewController.h"
#import "OTDebugCell.h"
#import "OTDebugView.h"

@interface OTDebugViewController ()<UITableViewDelegate, UITableViewDataSource>

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@property (nonatomic, strong) NSMutableArray<NSString *> *printDatas;

@end

@implementation OTDebugViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor clearColor];
    
    self.printDatas = @[].mutableCopy;
}

- (void)refreshWithPrint:(NSString *)print {
    if (print) {
        [self.printDatas addObject:print];
        [self.tableView reloadData];
    }
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.printDatas.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellIdentifier = @"OTDebugCell";
        
    OTDebugCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    
    if (self.printDatas.count > indexPath.row) {
        cell.textLabel.text = [NSString stringWithFormat:@"%@", self.printDatas[indexPath.row]];
    }
    
    return cell;
}

@end
