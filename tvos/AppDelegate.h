//
//  AppDelegate.h
//  tvos
//
//  Created by Joel Oliveira on 27/09/2016.
//  Copyright © 2016 Notificare. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NotificarePushLib.h"
#import <CoreBluetooth/CoreBluetooth.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate, NotificarePushLibDelegate,CBPeripheralManagerDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (nonatomic, strong) CBPeripheralManager *peripheralManager;


@end

