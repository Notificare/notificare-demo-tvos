//
//  NotificareMap.h
//  NotificarePushLib
//
//  Created by Joel Oliveira on 10/02/16.
//  Copyright (c) 2016 Notificare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
#import "NotificareNotification.h"
#import "NotificareAction.h"
#import "NotificareContent.h"
#import "NotificareAttachment.h"
#import "NotificationType.h"
#import "NotificationDelegate.h"
#import "NotificareActions.h"
#import "NSString+FromBundle.h"
#import "UIImage+FromBundle.h"


@interface NotificareMap : NSObject <NotificationType, MKMapViewDelegate>

@property (nonatomic, assign) id<NotificationDelegate> delegate;
@property (nonatomic, strong) NotificareNotification * notification;
@property (nonatomic, strong) NotificareActions * notificareActions;
@property (strong, nonatomic) UIViewController * rootViewController;
@property (strong, nonatomic) UIViewController * viewController;
@property (strong, nonatomic) UINavigationController * navigationController;
@property (strong, nonatomic) UICollectionView *collectionView;
@property (strong, nonatomic) UIView *baseView;
@property (strong, nonatomic) MKMapView *mapView;
@property (strong, nonatomic) MKAnnotationView *markerView;
@property (strong, nonatomic) UITapGestureRecognizer *tapGestureRecognizer;
@property (strong, nonatomic) UIBarButtonItem * closeButton;
@property (strong, nonatomic) UIBarButtonItem * actionsButton;
@property (strong, nonatomic) UIAlertController *actionSheet;
@property (strong, nonatomic) UIViewController * originalView;


-(void)openNotification;
-(void)sendData:(NSArray *)data;

@end
