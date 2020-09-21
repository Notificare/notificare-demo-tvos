//
//  ViewController.m
//  tvos
//
//  Created by Joel Oliveira on 27/09/2016.
//  Copyright © 2016 Notificare. All rights reserved.
//

#import "ViewController.h"
#import "NSDate+TimeAgo.h"

#define INBOX_CELLHEIGHT 220

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
    
    [[[NotificarePushLib shared] inboxManager] fetchInbox:^(id  _Nullable response, NSError * _Nullable error) {
        if (!error) {
            if([response count] == 0){
                [[self navSections] addObject:@[]];
            } else {
                [[self navSections] removeAllObjects];
                [[self navSections] addObject:response];
                [[self loadingView] removeFromSuperview];
            }
            
            [[self tableView] reloadData];
        } else {
            [[self navSections] removeAllObjects];
            [[self navSections] addObject:@[]];
            [[self tableView] reloadData];
        }
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
    
    [[[NotificarePushLib shared] inboxManager] clearInbox:^(id  _Nullable response, NSError * _Nullable error) {
        if (!error) {
            [self showEmptyView];
            [self reloadData];
        }
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

    static NSString *cellIdentifier = @"InboxCell";
    UITableViewCell * cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    
    UILabel *title, *subtitle, *date;
    UIImageView *img;
    UITextView * message;
    
    if (cell == nil) {
        
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
        
        img = [[UIImageView alloc] initWithFrame:CGRectMake(5, ((INBOX_CELLHEIGHT / 2) / 2), (INBOX_CELLHEIGHT / 2) , (INBOX_CELLHEIGHT / 2) )];
        [img setContentMode:UIViewContentModeScaleAspectFill];
        [img setClipsToBounds:YES];
        [img setTag:102];
        
        title = [[UILabel alloc] initWithFrame:CGRectMake((INBOX_CELLHEIGHT / 2) + 20, 5, self.view.frame.size.width - (((INBOX_CELLHEIGHT / 2) + 20) + 100), 20)];
        [title setFont:[UIFont systemFontOfSize:20]];
        [title setTag:100];
        
        subtitle = [[UILabel alloc] initWithFrame:CGRectMake((INBOX_CELLHEIGHT / 2) + 20, 25, self.view.frame.size.width - (((INBOX_CELLHEIGHT / 2) + 20) + 100), 20)];
        [subtitle setFont:[UIFont systemFontOfSize:20]];
        [subtitle setTag:101];
        
        message = [[UITextView alloc] initWithFrame:CGRectMake((INBOX_CELLHEIGHT / 2) + 20, 35, self.view.frame.size.width - (((INBOX_CELLHEIGHT / 2) + 20) + 100), 80)];
        [message setFont:[UIFont systemFontOfSize:20]];
        [message setBackgroundColor:[UIColor clearColor]];
        message.textContainer.lineFragmentPadding = 0;
        [message setScrollEnabled:NO];
        [message setUserInteractionEnabled:NO];
        [message setTag:103];
        
        [[cell contentView] addSubview:title];
        [[cell contentView] addSubview:subtitle];
        [[cell contentView] addSubview:message];
        [[cell contentView] addSubview:img];
        
        date = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 200, 30)];
        [date setTextAlignment:NSTextAlignmentRight];
        [date setFont:[UIFont systemFontOfSize:16]];
        [cell setAccessoryView:date];
        
    } else {
        title = (UILabel *)[cell.contentView viewWithTag:100];
        subtitle = (UILabel *)[cell.contentView viewWithTag:101];
        img = (UIImageView *)[cell.contentView viewWithTag:102];
        message = (UITextView *)[cell.contentView viewWithTag:103];
    }
    
    NotificareDeviceInbox * item = (NotificareDeviceInbox *)[[[self navSections] objectAtIndex:[indexPath section]] objectAtIndex:[indexPath row]];
    
    [img setImage:[UIImage imageNamed:@"noAttachment"]];
    
    if ([item title]) {
        [title setText:[item title]];
    } else {
        [title setText:@""];
    }
    
    if ([item subtitle]) {
        [subtitle setText:[item subtitle]];
    } else {
        [subtitle setText:@""];
    }
    
    [message setText:[item message]];
    
    if ([item attachment] && [[item attachment] objectForKey:@"uri"]) {
        NSURL *imageURL = [NSURL URLWithString:[[item attachment] objectForKey:@"uri"]];
        
        NotificareNetworkHost *notificareNetworkHost = [[NotificareNetworkHost alloc] initWithHostName:[imageURL host]
                                                                                              isSecure:[[imageURL scheme] isEqualToString:@"https"]];
        [notificareNetworkHost setDefaultCachePolicy:NSURLRequestUseProtocolCachePolicy];
        
        
        NotificareNetworkOperation *imageOperation = [notificareNetworkHost operationWithHTTPMethod:@"GET" withPath:[imageURL path]];
        
        [imageOperation setSuccessHandler:^(NotificareNetworkOperation *operation) {
            
            [img setImage:[operation responseDataToImage]];
            [img setContentMode:UIViewContentModeScaleAspectFill];
            [img setClipsToBounds:YES];
            
            [cell setNeedsLayout];
            
        }];
        
        [imageOperation setErrorHandler:^(NotificareNetworkOperation *operation, NSError *error) {
            NSLog(@"Notificare Loading Image: %@",error);
        }];
        
        [imageOperation buildRequest];
        
        [notificareNetworkHost startOperation:imageOperation];
        
    }
    
    
    NSArray* arrayDate = [[item time] componentsSeparatedByString: @"."];
    NSString* dateString = [arrayDate objectAtIndex: 0];
    
    NSDateFormatter *dateFormat = [[NSDateFormatter alloc] init];
    [dateFormat setTimeZone:[NSTimeZone timeZoneWithName:@"GMT"]];
    [dateFormat setDateFormat:@"yyyy-MM-dd'T'HH:mm:ss"];
    
    NSDate * time = [dateFormat dateFromString:dateString];
    [date setText:[time timeAgo]];
    
    
    if([item opened]){
        [title setTextColor:[UIColor grayColor]];
        [subtitle setTextColor:[UIColor grayColor]];
        [message setTextColor:[UIColor grayColor]];
        [date setTextColor:[UIColor grayColor]];
        [img setAlpha:.5];
    } else {
        [title setTextColor:[UIColor whiteColor]];
        [subtitle setTextColor:[UIColor whiteColor]];
        [message setTextColor:[UIColor whiteColor]];
        [date setTextColor:[UIColor whiteColor]];
        [img setAlpha:1];
    }

    return cell;
    
}



-(BOOL) tableView:(UITableView *)tableView canFocusRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return true;
    
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return INBOX_CELLHEIGHT;
    
}


- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section{
    
    return 0;
    
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    NotificareDeviceInbox * item = (NotificareDeviceInbox *)[[[self navSections] objectAtIndex:[indexPath section]] objectAtIndex:[indexPath row]];
    
    [[[NotificarePushLib shared] inboxManager] openInboxItem:item completionHandler:^(id  _Nullable response, NSError * _Nullable error) {
        if (!error) {
            [[NotificarePushLib shared] presentInboxItem:item inNavigationController:[self navigationController] withController:response];
        }
    }];
    
    
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

        [[[NotificarePushLib shared] inboxManager] removeFromInbox:item completionHandler:^(id  _Nullable response, NSError * _Nullable error) {
            if (!error) {
//                [tableView beginUpdates];
//                [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
//                [[[self navSections] objectAtIndex:0] removeObject:item];
//                [tableView endUpdates];
            }
        }];
        
    }
}


-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [self reloadData];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadData) name:@"inboxReady" object:nil];
    
}


-(void)viewDidDisappear:(BOOL)animated{
    [super viewDidDisappear:animated];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:@"inboxReady"
                                                  object:nil];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
