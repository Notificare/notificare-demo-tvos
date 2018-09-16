//
//  AppDelegate.m
//  tvos
//
//  Created by Joel Oliveira on 27/09/2016.
//  Copyright © 2016 Notificare. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@end


@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    [[NotificarePushLib shared] initializeWithKey:nil andSecret:nil];
    [[NotificarePushLib shared] launch];
    [[NotificarePushLib shared] setDelegate:self];
    
    [self setPeripheralManager:[[CBPeripheralManager alloc] init]];
    [[self peripheralManager] setDelegate:self];
    
    
    return YES;
}

-(BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options{
    [[NotificarePushLib shared] handleOpenURL:url withOptions:options];
    return YES;
}

-(void)notificarePushLib:(NotificarePushLib *)library shouldPerformSelectorWithURL:(NSURL *)url{
    
    
}

-(void)notificarePushLib:(NotificarePushLib *)library onReady:(NSDictionary *)info{

    [[NotificarePushLib shared] registerForNotifications];

}

-(void)notificarePushLib:(NotificarePushLib *)library didRegisterDevice:(nonnull NotificareDevice *)device {
    NSLog(@"%@", [device deviceID]);
    
    [[NotificarePushLib shared] startLocationUpdates];
}


-(void)notificarePushLib:(NotificarePushLib *)library didReceiveRemoteNotificationInForeground:(nonnull NotificareNotification *)notification withController:(id _Nullable)controller {
    NSLog(@"didReceiveRemoteNotificationInForeground %@", [notification notificationMessage]);
}

-(void)notificarePushLib:(NotificarePushLib *)library didReceiveRemoteNotificationInBackground:(nonnull NotificareNotification *)notification withController:(id _Nullable)controller{
    NSLog(@"didReceiveRemoteNotificationInBackground %@", [notification notificationMessage]);
    
    UINavigationController *navController = (UINavigationController *)self.window.rootViewController;
    [[NotificarePushLib shared] presentNotification:notification inNavigationController:navController withController:controller];
}

-(void)notificarePushLib:(NotificarePushLib *)library didLoadInbox:(nonnull NSArray<NotificareDeviceInbox *> *)items{
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"inboxReady" object:nil];
    
}

- (void)notificarePushLib:(NotificarePushLib *)library didUpdateBadge:(int)badge{
    
}

-(void)notificarePushLib:(NotificarePushLib *)library didUpdateLocations:(nonnull NSArray<NotificareLocation *> *)locations {
    NSLog(@"didUpdateLocations %@", locations);
}

/**
 * Advertise as a beacon
 * This is simply an example and is not part of the Notificare implementation
 */
- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral{
    
    if (self.peripheralManager.state == CBManagerStatePoweredOn){
        
        /*
        NSDictionary *beacon1 = [self beaconDataWithUUID:[[NSUUID alloc] initWithUUIDString:@"f7826da6-4fa2-4e98-8024-bc5b71e0893e"]
                                                           major:909
                                                           minor:11123
                                                   measuredPower:-59];
        
        [[self peripheralManager] startAdvertising:beacon1];
        */
        
        NSDictionary *beacon2 = [self beaconDataWithUUID:[[NSUUID alloc] initWithUUIDString:@"f7826da6-4fa2-4e98-8024-bc5b71e0893e"]
                                                           major:909
                                                           minor:26594
                                                   measuredPower:-59];
        
        [[self peripheralManager] startAdvertising:beacon2];
        
    }
}

- (void)peripheralManagerDidStartAdvertising:(CBPeripheralManager *)peripheral error:(nullable NSError *)error {
    if (error) {
        NSLog(@"There was an error advertising: %@", error);
    }
}

- (NSDictionary *)beaconDataWithUUID:(NSUUID *)uuid major:(uint16_t)major minor:(uint16_t)minor measuredPower:(NSInteger)measuredPower {
    static NSString *iBeaconKey = @"kCBAdvDataAppleBeaconKey";
    
    unsigned char advertisingData[21] = { 0 };
    [uuid getUUIDBytes:(unsigned char *)&advertisingData];
    
    advertisingData[16] = (unsigned char)(major >> 8);
    advertisingData[17] = (unsigned char)(major & 255);
    advertisingData[18] = (unsigned char)(minor >> 8);
    advertisingData[19] = (unsigned char)(minor & 255);
    advertisingData[20] = measuredPower;
    
    NSData *data = [NSData dataWithBytes:advertisingData length:sizeof(advertisingData)];
    
    return @{ iBeaconKey : data };
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
