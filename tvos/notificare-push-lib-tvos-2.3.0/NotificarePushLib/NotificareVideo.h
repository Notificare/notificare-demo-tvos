//
//  Video.h
//  NotificarePushLib
//
//  Created by Joel Oliveira on 1/24/13.
//  Copyright (c) 2013 Notificare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "NotificareNotification.h"
#import "NotificareAction.h"
#import "NotificareContent.h"
#import "NotificationType.h"
#import "NotificationDelegate.h"
#import "NotificareActions.h"
#import "HCYoutubeParser.h"

NS_ASSUME_NONNULL_BEGIN

@interface NotificareVideo : UIViewController <NotificationType>

@property (nonatomic, strong) id<NotificationDelegate> delegate;
@property (nonatomic, strong) NotificareNotification * notification;
@property (nonatomic, strong) NotificareActions * notificareActions;
@property (strong, nonatomic) UIView * baseView;
@property (strong, nonatomic) AVPlayer * avPlayer;
@property (strong, nonatomic) UIBarButtonItem *actionsButton;

-(id)handleNotification;

@end

NS_ASSUME_NONNULL_END
