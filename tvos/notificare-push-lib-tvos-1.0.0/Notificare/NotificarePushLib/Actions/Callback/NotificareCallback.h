//
//  NotificareCallback.h
//  NotificarePushLib
//
//  Created by Joel Oliveira on 2/3/13.
//  Copyright (c) 2013 Notificare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ActionType.h"
#import "ActionDelegate.h"
#import "NotificareAction.h"
#import "NotificareNotification.h"
#import "NSString+FromBundle.h"
#import "UIImage+FromBundle.h"
#import "NSDictionary+FromPlist.h"
#import "NotificareNetworkHost.h"

@interface NotificareCallback : NSObject <ActionType,UINavigationControllerDelegate,UITabBarDelegate,UITextFieldDelegate>

@property (nonatomic, assign) id<ActionDelegate> delegate;
@property (strong, nonatomic) NotificareAction * action;
@property (strong, nonatomic) NotificareNotification * notification;
@property (strong, nonatomic) UIViewController * rootViewController;
@property (strong, nonatomic) UIBarButtonItem * sendButton;
@property (strong, nonatomic) UIBarButtonItem * closeButton;
@property (strong, nonatomic) NSString * message;
@property (strong, nonatomic) UITextField * messageField;
@property (strong, nonatomic) UITextView * messageView;
@property (strong, nonatomic) UINavigationController *navController;
@property (strong, nonatomic) UIViewController *controller;
@property (strong, nonatomic) UIView *baseView;
@property (strong, nonatomic) NotificareNetworkHost *notificareNetworkHost;
@property (strong, nonatomic) UIViewController * originalView;

-(void)executeAction;

@end