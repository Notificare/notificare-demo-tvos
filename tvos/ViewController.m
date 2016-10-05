//
//  ViewController.m
//  tvos
//
//  Created by Joel Oliveira on 27/09/2016.
//  Copyright © 2016 Notificare. All rights reserved.
//

#import "ViewController.h"
#import "NSDate+TimeAgo.h"



@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    [[self navigationItem] setTitle:@"INBOX"];
    
    [self setNavSections:[NSMutableArray array]];
    [self setSectionTitles:[NSMutableArray array]];
    
    [self showEmptyView];
    
}



-(void)reloadData{
    
    
    [[self sectionTitles] addObject:@"INBOX"];
    
    [[NotificarePushLib shared] fetchInbox:nil skip:[NSNumber numberWithInt:0] limit:[NSNumber numberWithInt:100] completionHandler:^(NSDictionary *info) {
        
        if([[info objectForKey:@"inbox"] count] == 0){
            [[self navSections] addObject:@[]];
        } else {
            [[self navSections] removeAllObjects];
            [[self navSections] addObject:[info objectForKey:@"inbox"]];
            [[self loadingView] removeFromSuperview];
        }
        
        [[self tableView] reloadData];

    } errorHandler:^(NSError *error) {
        [[self navSections] removeAllObjects];
        [[self navSections] addObject:@[]];
        [[self tableView] reloadData];
    }];
    
    
}


-(void)showEmptyView{
    [self setLoadingView:[[UIView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)]];
    
    [self setEmptyMessage:[[UILabel alloc] initWithFrame:CGRectMake(0, 0,self.loadingView.frame.size.width, self.loadingView.frame.size.height)]];
    
    [[self emptyMessage] setText:@"No message found"];
    [[self emptyMessage] setFont:[UIFont systemFontOfSize:14]];
    [[self emptyMessage] setTextAlignment:NSTextAlignmentCenter];
    [[self loadingView] setBackgroundColor:[UIColor whiteColor]];
    [[self loadingView] addSubview:[self emptyMessage]];
    [[self view] addSubview:[self loadingView]];
}



-(void)clearInbox{
    
    [[NotificarePushLib shared] clearInbox:^(NSDictionary *info) {
        
        [self showEmptyView];
        [self reloadData];
        
    } errorHandler:^(NSError *error) {
        
    }];
    
}


#pragma mark - Table delegates
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return [[self navSections] count];
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return [[[self navSections] objectAtIndex:section] count];
}


-(UITableViewCell*) tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    UITableViewCell* cell = [[UITableViewCell alloc] initWithStyle: UITableViewCellStyleSubtitle reuseIdentifier:nil];
    
    NotificareDeviceInbox * item = (NotificareDeviceInbox *)[[[self navSections] objectAtIndex:[indexPath section]] objectAtIndex:[indexPath row]];
    
    cell.textLabel.text = [item message];
    
    NSArray* arrayDate = [[item time] componentsSeparatedByString: @"."];
    NSString* dateString = [arrayDate objectAtIndex: 0];
    
    NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
    [dateFormat setTimeZone:[NSTimeZone timeZoneWithName:@"GMT"]];
    [dateFormat setDateFormat:@"yyyy-MM-dd'T'HH:mm:ss"];
    
    NSDate * time = [dateFormat dateFromString:dateString];
    
    cell.detailTextLabel.text = [time timeAgo];
    
    return cell;
    
}



-(BOOL) tableView:(UITableView *)tableView canFocusRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return true;
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return 100;
    
}


- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section{
    
    return 0;
    
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    
    NotificareDeviceInbox * item = (NotificareDeviceInbox *)[[[self navSections] objectAtIndex:[indexPath section]] objectAtIndex:[indexPath row]];
    
    [[NotificarePushLib shared] openInboxItem:item];
    
}

- (void)setEditing:(BOOL)editing animated:(BOOL)animated {
    [super setEditing:editing animated:animated];
    [[self tableView] setEditing:editing animated:YES];
    
    if(editing){
        UIBarButtonItem * clearButton = [[UIBarButtonItem alloc] initWithTitle:@"Clear All" style:UIBarButtonItemStylePlain target:self action:@selector(clearInbox)];
        [[self navigationItem] setLeftBarButtonItem:clearButton];
        [clearButton setTintColor:[UIColor blackColor]];
    }
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    // If row is deleted, remove it from the list.
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        
        NotificareDeviceInbox * item = (NotificareDeviceInbox *)[[[self navSections] objectAtIndex:[indexPath section]] objectAtIndex:[indexPath row]];
        
        
        [[NotificarePushLib shared] removeFromInbox:item completionHandler:^(NSDictionary *info) {
            //
            
            [tableView beginUpdates];
            [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
            [[[self navSections] objectAtIndex:0] removeObject:item];
            [tableView endUpdates];
            
        } errorHandler:^(NSError *error) {
            //
        }];
        
    }
}



-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [self reloadData];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadData) name:@"incomingNotification" object:nil];
    
}


-(void)viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:@"incomingNotification"
                                                  object:nil];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
