//
//  NotificareGeo.h
//  NotificarePushLib
//
//  Created by Joel Oliveira on 18/10/2017.
//  Copyright © 2017 Notificare. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MapKit.h>
#import "NotificareLocation.h"

NS_ASSUME_NONNULL_BEGIN

typedef enum NotificareGeoAuthorizationStatus : NSInteger {
    NotificareGeoAuthorizationStatusDenied = 0,
    NotificareGeoAuthorizationStatusRestricted = 1,
    NotificareGeoAuthorizationStatusNotDetermined = 2,
    NotificareGeoAuthorizationStatusAuthorizedWhenInUse = 4
} NotificareGeoAuthorizationStatus;


@class NotificareGeo;

@protocol NotificareGeoDelegate <NSObject>

@optional

- (void)notificareGeo:(NotificareGeo *)notificareGeo didFailToStartLocationServiceWithError:(NSError *)error;
- (void)notificareGeo:(NotificareGeo *)notificareGeo didReceiveLocationServiceAuthorizationStatus:(NotificareGeoAuthorizationStatus)status;
- (void)notificareGeo:(NotificareGeo *)notificareGeo didUpdateLocations:(NSArray<NotificareLocation*> *)locations;

@end


@interface NotificareGeo : NSObject <CLLocationManagerDelegate>

@property (nonatomic, assign) id<NotificareGeoDelegate> notificareGeoDelegate;
@property (nonatomic, strong) CLLocationManager * locationManager;

+(NotificareGeo*)shared;
-(void)launch;
-(void)startLocationUpdates;
-(void)stopLocationUpdates;
-(BOOL)locationServicesEnabled;

@end

NS_ASSUME_NONNULL_END
