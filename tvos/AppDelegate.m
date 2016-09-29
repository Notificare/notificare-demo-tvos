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

static os_log_t tvOSApp;

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    tvOSApp = os_log_create("re.notifica.tvos", "MyApp");

    
    [[NotificarePushLib shared] launch];
    [[NotificarePushLib shared] setDelegate:self];
    [[NotificarePushLib shared] handleOptions:launchOptions];
    
    return YES;
}

-(void)notificarePushLib:(NotificarePushLib *)library onReady:(NSDictionary *)info{

    [[NotificarePushLib shared] registerForNotifications];
    //[[NotificarePushLib shared] registerForWebsockets];
    

}

#pragma APNS Delegates
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    
    os_log(tvOSApp, "didRegisterForRemoteNotificationsWithDeviceToken");
    //If you don't identify users you can just use this
    [[NotificarePushLib shared] registerDevice:deviceToken completionHandler:^(NSDictionary *info) {
        
        [[NotificarePushLib shared] startLocationUpdates];
        
    } errorHandler:^(NSError *error) {
        //
        //  [self registerForAPNS];
        
    }];
    
    
}

- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error{
    
    os_log(tvOSApp, "didFailToRegisterForRemoteNotificationsWithError %{public}@", error);

}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(nonnull NSDictionary *)userInfo fetchCompletionHandler:(nonnull void (^)(UIBackgroundFetchResult))completionHandler{

    [[NotificarePushLib shared] handleNotification:userInfo forApplication:application completionHandler:^(NSDictionary * _Nonnull info) {
        //
        completionHandler(UIBackgroundFetchResultNewData);
    } errorHandler:^(NSError * _Nonnull error) {
        //
        completionHandler(UIBackgroundFetchResultNoData);
    }];
}

-(void)notificarePushLib:(NotificarePushLib *)library didUpdateBadge:(int)badge{
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"incomingNotification" object:nil];

}


#pragma WebSockets Delegates
- (void)notificarePushLib:(NotificarePushLib *)library didRegisterForWebsocketsNotifications:(NSString *)uuid {
    
    //If you don't identify users you can just use this
    [[NotificarePushLib shared] registerDeviceForWebsockets:uuid completionHandler:^(NSDictionary *info) {
        
        
        
    } errorHandler:^(NSError *error) {
        //
        //  [self registerForAPNS];
        
    }];
    
}


- (void)notificarePushLib:(NotificarePushLib *)library didReceiveWebsocketNotification:(NSDictionary *)info {
    
    [[NSNotificationCenter defaultCenter] postNotificationName:@"incomingNotification" object:nil];
    
    UNMutableNotificationContent *content = [[UNMutableNotificationContent alloc] init];

    content.badge = @([[UIApplication sharedApplication] applicationIconBadgeNumber] + 1);
 
    UNTimeIntervalNotificationTrigger *trigger = [UNTimeIntervalNotificationTrigger
                                                  triggerWithTimeInterval:2.f repeats:NO];
    UNNotificationRequest *request = [UNNotificationRequest requestWithIdentifier:@"TwoSeconds"
                                                                          content:content trigger:trigger];
  
    [[[NotificarePushLib shared] notificationCenter] addNotificationRequest:request withCompletionHandler:^(NSError * _Nullable error) {
        if (!error) {
            NSLog(@"add NotificationRequest succeeded!");
        }
    }];
    
}

- (void)notificarePushLib:(NotificarePushLib *)library didFailToRegisterWebsocketNotifications:(nonnull NSError *)error{
    NSLog(@"didFailToRegisterWebsocketNotifications %@", error);
}

- (void)notificarePushLib:(NotificarePushLib *)library didCloseWebsocketConnection:(nonnull NSString *)reason{
NSLog(@"didCloseWebsocketConnection %@", reason);
}


- (void)notificarePushLib:(NotificarePushLib *)library didUpdateLocations:(nonnull NSArray *)locations{

    os_log(tvOSApp, "didUpdateLocations %{public}@", locations);
    
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
