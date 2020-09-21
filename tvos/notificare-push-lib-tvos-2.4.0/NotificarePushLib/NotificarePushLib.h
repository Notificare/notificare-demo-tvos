//
//  NotificarePushLib.h
//  NotificarePushLib
//
//  Created by Joel Oliveira on 11/25/12.
//  Copyright (c) 2012 Notificare. All rights reserved.
//
//
//

/* Utils */
#import "NotificareDefinitions.h"

/* Models */
#import "NotificareNotification.h"
#import "NotificareUser.h"
#import "NotificareUserPreference.h"
#import "NotificareSegment.h"
#import "NotificareProduct.h"
#import "NotificareDevice.h"
#import "NotificareDeviceInbox.h"
#import "NotificationType.h"
#import "NotificareAttachment.h"
#import "NotificareContent.h"
#import "NotificareAction.h"
#import "NotificareAsset.h"
#import "NotificareUserData.h"
#import "NotificareDeviceDnD.h"
#import "NotificareLocation.h"
#import "NotificareSystemNotification.h"


/* Main Classes */
#import "NotificareLogging.h"
#import "NotificareCrashReport.h"
#import "NotificareAppConfig.h"
#import "NotificareNetworkWrapper.h"
#import "NotificareEventLogger.h"
#import "NotificareAppDelegateSurrogate.h"
#import "NotificareDeviceManager.h"
#import "Notificare.h"
#import "NotificareActions.h"
#import "NotificarePush.h"
#import "NotificareMonetize.h"
#import "NotificareInboxManager.h"
#import "NotificareStorage.h"
#import "NotificareGeo.h"

/* Libraries */
#import "NotificareNetworkHost.h"


NS_ASSUME_NONNULL_BEGIN
/**
 * Blocks definitions
 */
typedef void (^NotificareCompletionBlock)(id _Nullable response , NSError * _Nullable error);

/*!
 * @brief The NotificarePushLib class
 */
@class NotificarePushLib;

/**
 * Main class protocol delegates
 * Optional delegates of NotificarePushLib, these should be implmented or not according to your implementation.
 */
@protocol NotificarePushLibDelegate <NSObject>

@optional

/*
 * Device Delegates
 */

/*!
 * @brief Optional. This delegate method will be triggered when a device is registered for the first time or updated.
 * @param device A NotificareDevice object containing the device registered or updated
 */
- (void)notificarePushLib:(NotificarePushLib *)library didRegisterDevice:(NotificareDevice *)device;

/*!
 * @brief Optional. This delegate method will be triggered when a device could not register for notifications with APNS in response to the registerForNotifications method.
 * @param error A NSError object containing the error
 */
- (void)notificarePushLib:(NotificarePushLib *)library didFailToRegisterForNotificationsWithError:(NSError *)error;

/*
 * Push Delegates
 */
/*!
 * @brief Optional. This delegate method will be triggered when changes to notification settings occur.
 * @param granted A boolean representing if users granted authorization to post user notifications
 */
- (void)notificarePushLib:(NotificarePushLib *)library didChangeNotificationSettings:(BOOL)granted;
/*!
 * @brief Optional. This delegate method will be triggered when a launch URL key is detected.
 * @param launchURL A NSURL object containing the url received on launch
 */
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveLaunchURL:(NSURL *)launchURL;
/*!
 * @brief Optional. This delegate method will be triggered when a remote notification is received in the background.
 * @param notification A NotificareNotification object containing the notification received
 */
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveRemoteNotificationInBackground:(NotificareNotification *)notification withController:(id _Nullable)controller;
/*!
 * @brief Optional. This delegate method will be triggered when a remote notification is received in the foreground.
 * @param notification A NotificareNotification object containing the notification received
 */
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveRemoteNotificationInForeground:(NotificareNotification *)notification withController:(id _Nullable)controller;

/*!
 * @brief Optional. This delegate method will be triggered when a system (silent) remote notification is received in the background.
 * @param notification A NotificareNotification object containing the notification received
 */
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveSystemNotificationInBackground:(NotificareSystemNotification *)notification;

/*!
 * @brief Optional. This delegate method will be triggered when a system (silent) remote notification is received in the foreground.
 * @param notification A NotificareNotification object containing the notification received
 */
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveSystemNotificationInForeground:(NotificareSystemNotification *)notification;

/*!
 * @brief Optional. This delegate method will be triggered when a remote notification is received from an unrecognizable source.
 * @param notification A NSDictionary object containing the notification received
 */
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveUnknownNotification:(NSDictionary *)notification;

/*!
 * @brief Optional. This delegate method will be triggered when a remote or local notification is opened from an unrecognizable source while in background.
 * @param notification A NSDictionary object containing the notification received
 */
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveUnknownNotificationInBackground:(NSDictionary *)notification;

/*!
 * @brief Optional. This delegate method will be triggered when a remote or local notification is opened from an unrecognizable source while in foreground.
 * @param notification A NSDictionary object containing the notification received
 */
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveUnknownNotificationInForeground:(NSDictionary *)notification;

/*!
 * @brief Optional. This delegate method will be triggered just before the notification opens.
 * @param notification A NotificareNotification object that represents the notification
 */
- (void)notificarePushLib:(NotificarePushLib *)library willOpenNotification:(NotificareNotification *)notification;
/*!
 * @brief Optional. This delegate method will be triggered when the notification opens.
 * @param notification A NotificareNotification object that represents the notification
 */
- (void)notificarePushLib:(NotificarePushLib *)library didOpenNotification:(NotificareNotification *)notification;
/*!
 * @brief Optional. This delegate method will be triggered when the notification closes.
 * @param notification A NotificareNotification object that represents the notification
 */
- (void)notificarePushLib:(NotificarePushLib *)library didCloseNotification:(NotificareNotification *)notification;
/*!
 * @brief Optional. This delegate method will be triggered when the it fails to open the notification.
 * @param notification A NotificareNotification object that represents the notification
 */
- (void)notificarePushLib:(NotificarePushLib *)library didFailToOpenNotification:(NotificareNotification *)notification;
/*!
 * @brief Optional. This delegate method will be triggered when a user interacts with clickable content or events in WebView
 * @param url A NSURL object that represents the URL clicked
 * @param notification A NotificareNotification object that represents the notification
 */
- (void)notificarePushLib:(NotificarePushLib *)library didClickURL:(NSURL *)url inNotification:(NotificareNotification *)notification;

/*!
 * @brief Optional. This delegate method will be triggered just before the action will is executed.
 * @param action A NotificareAction object that represents the notification
 */
- (void)notificarePushLib:(NotificarePushLib *)library willExecuteAction:(NotificareAction *)action;
/*!
 * @brief Optional. This delegate method will be triggered when the action is executed.
 * @param action A NotificareAction object that represents the user selectable action
 */
- (void)notificarePushLib:(NotificarePushLib *)library didExecuteAction:(NotificareAction *)action;
/*!
 * @brief Optional. This delegate method will be triggered when the user clicks an action of type Custom. you should use it to perform a method in your own code.
 * @param url A NSURL object
 * @code -(void)notificarePushLib:(NotificarePushLib *)library shouldPerformSelectorWithURL:(NSURL *)url{
 [self performSelector:[url host] withObject:[url path]]
 }
 */
- (void)notificarePushLib:(NotificarePushLib *)library shouldPerformSelectorWithURL:(NSURL *)url inAction:(NotificareAction *)action;
/*!
 * @brief Optional. This delegate method will be triggered when the action was cancelled.
 * @param action A NotificareAction object that represents the user selectable action
 */
- (void)notificarePushLib:(NotificarePushLib *)library didNotExecuteAction:(NotificareAction *)action;
/*!
 * @brief Optional. This delegate method will be triggered when the user selectable action fails to be executed.
 * @param error A NSError object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didFailToExecuteAction:(NotificareAction *)action withError:(NSError *)error;

/*
 * Inbox Delegates
 */
/*!
 * @brief Optional. This delegate method will be triggered when the inbox is loaded, notifications arrive or is updated. This delegate will only be triggered if application has useInbox ON. It will contain the recently received messages if any. Use this delegate to refresh your list of messages.
 * @param items A NSArray of NotificareDeviceInbox objects
 */
- (void)notificarePushLib:(NotificarePushLib *)library didLoadInbox:(NSArray<NotificareDeviceInbox*>*)items;

/*!
 * @brief Optional. This delegate method will be triggered when the inbox is loaded, notifications arrive or is updated. This delegate will only be triggered if application has autoBadge ON. Use this delegate to refresh your UI.
 * @param badge A int number
 */
- (void)notificarePushLib:(NotificarePushLib *)library didUpdateBadge:(int)badge;


/*
 * Location Services Delegates
 */
/*!
 * @brief Optional. This delegate method will be triggered when it fails to start location updates.
 * @param error A NSError object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didFailToStartLocationServiceWithError:(NSError *)error;
/*!
 * @brief Optional. This delegate method will be triggered as response to a start location updates.
 * @param status A NotificareGeoAuthorizationStatus state
 */
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveLocationServiceAuthorizationStatus:(NotificareGeoAuthorizationStatus)status;
/*!
 * @brief Optional. This delegate method will be triggered every time a new location update is received.
 * @param locations A NSArray that contains a list of NotificareLocation objects
 */
- (void)notificarePushLib:(NotificarePushLib *)library didUpdateLocations:(NSArray<NotificareLocation*> *)locations;

/*
 * In-App Purchase Delegates
 */

/*!
 * @brief Optional. This delegate method will be triggered soon the product's store is loaded. Use it to update UI.
 * @param products A NSArray containing the list of products
 */
- (void)notificarePushLib:(NotificarePushLib *)library didLoadStore:(NSArray<NotificareProduct *> *)products;
/*!
 * @brief Optional. This delegate method will be triggered every time the store fails to load. We will automatically retry to load the store.
 * @param error A NSError object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didFailToLoadStore:(NSError *)error;
/*!
 * @brief Optional. This delegate method will be triggered when a transaction is completed.
 * @param transaction A SKPaymentTransaction object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didCompleteProductTransaction:(SKPaymentTransaction *)transaction;
/*!
 * @brief Optional. This delegate method will be triggered when a transaction is restored.
 * @param transaction A SKPaymentTransaction object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didRestoreProductTransaction:(SKPaymentTransaction *)transaction;
/*!
 * @brief Optional. This delegate method will be triggered when a transaction fails.
 * @param transaction A SKPaymentTransaction object
 * @param error A NSError object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didFailProductTransaction:(SKPaymentTransaction *)transaction withError:(NSError *)error;
/*!
 * @brief Optional. This delegate method will be triggered when a transaction's content starts downloading.
 * @param transaction A SKPaymentTransaction object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didStartDownloadContent:(SKPaymentTransaction *)transaction;
/*!
 * @brief Optional. This delegate method will be triggered when a download is paused.
 * @param download A SKDownload object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didPauseDownloadContent:(SKDownload *)download;
/*!
 * @brief Optional. This delegate method will be triggered when a download is cancelled.
 * @param download A SKDownload object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didCancelDownloadContent:(SKDownload *)download;
/*!
 * @brief Optional. This delegate method will be triggered whenever a download progress is updated.
 * @param download A SKDownload object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didReceiveProgressDownloadContent:(SKDownload *)download;
/*!
 * @brief Optional. This delegate method will be triggered whenever a download fails.
 * @param download A SKDownload object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didFailDownloadContent:(SKDownload *)download;
/*!
 * @brief Optional. This delegate method will be triggered whenever a download progress is finished.
 * @param download A SKDownload object
 */
- (void)notificarePushLib:(NotificarePushLib *)library didFinishDownloadContent:(SKDownload *)download;

@required

/*!
 * @brief Required. This delegate method will be triggered whenever the library is ready. Only after this delegate has been triggered you will be able to call any other method or receive any delegate from this library.
 * @param application A NotificareApplication object containing information about this app's information
 * @code - (void)notificarePushLib:(NotificarePushLib *)library onReady:(NotificareApplication *)application{
     [[NotificarePushLib shared] registerForNotifications];
 }
 */
- (void)notificarePushLib:(NotificarePushLib *)library onReady:(NotificareApplication *)application;

@end


@interface NotificarePushLib : NSObject <UIApplicationDelegate, NotificareDeviceManagerDelegate, NotificarePushDelegate, NotificareMonetizeDelegate, NotificareInboxManagerDelegate, NotificareGeoDelegate>

/*!
 *  @abstract Protocol of NotificarePushLib class that handles events
 *  @property NotificarePushLibDelegate
 *
 */
@property (nonatomic, assign) id <NotificarePushLibDelegate> delegate;

/*!
 *  @abstract Authorization Options for tvOS 10 and higher
 *  @discussion
 *  A UNAuthorizationOptions holds constants indicating which authorization options should be used. Possible values are: UNAuthorizationOptionAlert, UNAuthorizationOptionSound, UNAuthorizationOptionBadge, UNAuthorizationOptionProvisional, UNAuthorizationOptionProvidesAppNotificationSettings and UNAuthorizationOptionCriticalAlert. If none is provided it will default to UNAuthorizationOptionAlert, UNAuthorizationOptionSound, UNAuthorizationOptionBadge.
 *  @property presentationOptions
 *
 */
@property (nonatomic,assign) UNAuthorizationOptions authorizationOptions;

/*!
 *  @abstract Presentation Options for tvOS
 *  @discussion
 *  A UNNotificationPresentationOptions holds constants indicating how to handle notifications when app is active. Possible values are: UNNotificationPresentationOptionAlert, UNNotificationPresentationOptionBadge, UNNotificationPresentationOptionSound or UNNotificationPresentationOptionNone. If none is provided it will default to UNNotificationPresentationOptionNone.
 *  @property presentationOptions
 *
 */
@property (nonatomic,assign) UNNotificationPresentationOptions presentationOptions;

/*!
 *  @abstract User Notification Center for tvOS
 *  @discussion
 *    A UNUserNotificationCenter object holds a reference to the device notification center.
 *  @property userNotificationCenter
 *
 */
@property (nonatomic,assign) UNUserNotificationCenter *userNotificationCenter;

/*!
 *  @abstract The shared singleton implementation
 *
 *  @discussion
 *    Returns the operation's method type
 *
 */
+(NotificarePushLib*)shared;

/*!
 *  @abstract Initializer
 *  @property key The App key
 *  @property secret The App secret
 
 *  @discussion
 *  Initializes the NotificarePushLib, should be the first method to be invoked in your App Delegate. In this method you can override the app keys defined in Notificare.plist.
 */
-(void)initializeWithKey:(NSString * _Nullable)key andSecret:(NSString * _Nullable)secret;

/*!
 *  @abstract Initial setup
 *
 *  @discussion
 *  Launches the NotificarePushLib with the initialized coniguration. This method should be invoked whenever you want to start using the library. In response to this method the onReady delegate will be triggered.
 */
- (void)launch;
/*!
 *  @abstract Destroy Setup
 *
 *  @discussion
 *  Destroys an initialized NotificarePushLib instances. This method should be invoked whenever you want to stop using the library. It will unregister a device, stop location services and reset Notificare to its pre-launch state.
 */
- (void)unlaunch;
/*!
 *  @abstract The App
 *  @property application
 *
 *  @discussion
 *  A NotificareApplication object representing the Application
 *
 */
@property (strong, nonatomic) NotificareApplication * application;

/*!
 *  @abstract The Inbox Manager
 *  @property inboxManager
 *
 *  @discussion
 *  A NotificareInboxManager class that handles the inbox items
 *
 */
@property (strong, nonatomic) NotificareInboxManager * inboxManager;


/*!
 *  @abstract Handle URL Schemes
 *  @property url
 *  @property options
 *
 *  @discussion
 *  Handles additional functionality to a URL Schemes interaction. Should be used in -(BOOL)application:openURL:options:
 *
 */
-(void)handleOpenURL:(NSURL *)url withOptions:(NSDictionary * _Nullable)options;

/*!
 *  @abstract Handle User Activity
 *  @property userActivity
 *  @property restorationHandler
 *
 *  @discussion
 *  Handles additional functionality in response to UIApplication's continueUserActivity:restorationHandler. Should be used in -(BOOL)application:continueUserActivity:restorationHandler:
 *
 */
-(void)continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray<id<UIUserActivityRestoring>> * _Nullable))restorationHandler;

/*!
 *  @abstract Handle User Activity
 *  @property userActivity
 *
 *  @discussion
 *  Handles additional functionality in response to UIScene's continueUserActivity. Should be used in -(void)scene:(UIScene *)scene continueUserActivity:(NSUserActivity *)userActivity
 *
 */
-(void)continueUserActivity:(NSUserActivity *)userActivity;

/*!
 *  @abstract Fetch a Link
 *
 *  @discussion
 *  Use this method to fetch the underlying URL for a Dynamic Link created in Notificare via the Links feature. Usually in response to -(BOOL)application:continueUserActivity:restorationHandler: or  -(void)scene:(UIScene *)scene continueUserActivity:(NSUserActivity *)userActivity
 *  @param url  A NSURL representing the URL of the Dynamic Link.
 *
 */
-(void)fetchLink:(NSURL *)url completionHandler:(NotificareCompletionBlock)completionBlock;
/*!
 *  @abstract Register For Notifications
 *
 *  @discussion
 *  Register the device for remote push notifications. Make sure you only invoke this method after the onReady delegate.
 */
- (void)registerForNotifications;

/*!
 *  @abstract Unregister For Notifications
 *
 *  @discussion
 *  Unregister the device for remote push notifications. Make sure you only invoke this method after the onReady delegate.
 */
- (void)unregisterForNotifications;

/*!
 *  @abstract Check if Remote Notifications are ON
 *
 *  @discussion
 *  Use this method to quickly identify if the user has a valid APNS token
 *  @return A Boolean indicating if an APNS token has been requested and registered
 */
-(BOOL)remoteNotificationsEnabled;
/*!
 *  @abstract Check if User allowed Alerts, Badges and Sounds
 *
 *  @discussion
 *  Use this method to quickly identify if the user has allowed alerts, badge and sounds
 *  @return A Boolean indicating if the user has allowed alerts, badge and sounds
 */
-(BOOL)allowedUIEnabled;
/*!
 *  @abstract Check if Remote Notification is from Notificare
 *
 *  @discussion
 *  Use this method to quickly identify if a notification is from Notificare
 *  @return A Boolean indicating if a notification is from Notificare
 */
-(BOOL)isNotificationFromNotificare:(NSDictionary*)userInfo;
/*!
 *  @abstract The device
 *
 *  @discussion
 *  Access the registered device if any
 */
- (NotificareDevice *)myDevice;

/*!
 * @brief This method should be used to register the device token with Notificare. Make sure you only invoke this method after the onReady delegate.
 * @param userID A NSString representing the userID. It should be unique.
 * @param username A NSString representing the username.
 */
- (void)registerDevice:(NSString * _Nullable)userID withUsername:(NSString * _Nullable)username completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 * @abstract Preferred Language
 *
 * @discussion
 * Use this method to retrieve the current preferred language. If none was set before this completion block will return nil.
 *  @return A NSString or nil indicating if a preferred langauge has been set
 */
- (NSString * _Nullable)preferredLanguage;

/*!
 * @abstract Update Preferred Language
 *
 * @discussion
 *  This method should be used to override the system language for this device. Make sure you only invoke this method after the didRegisterDevice delegate. If never invoked, the [NSLocale preferredLanguages] will be used.
 * @param language A NSString representing the language (ISO 639-1) and region (ISO 3166-2) (e.g. en-US).
 */
- (void)updatePreferredLanguage:(NSString * _Nullable)language completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Get all tags
 *
 *  @discussion
 *  Get all the tags a device has been added to the device. Make sure you only invoke this method after the onReady delegate.
 */
- (void)fetchTags:(NotificareCompletionBlock)completionBlock;
/*!
 *  @abstract Add one or more tags to the device
 *
 *  @discussion
 *  Add one or more tags to a device. This method uses blocks that returns success or failure for this operation. Make sure you only invoke this method after the onReady delegate.
 *  @param tags A NSArray that contains a list of tags to be added to the device
 */
- (void)addTags:(NSArray *)tags completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Add a tag to the device
 *
 *  @discussion
 *  Add one tag to a device. This method uses blocks that returns success or failure for this operation. Make sure you only invoke this method after the onReady delegate.
 *  @param tag A NSString that represents the tag to be added to the device
 */
- (void)addTag:(NSString *)tag completionHandler:(NotificareCompletionBlock)completionBlock;
/*!
 *  @abstract Remove one or more tags from the device
 *
 *  @discussion
 *  Remove one or more tags from a device. This method uses blocks that returns success or failure for this operation. Make sure you only invoke this method after the onReady delegate.
 *  @param tags A NSArray with a list of tags to be removed from the device
 */
- (void)removeTags:(NSArray *)tags completionHandler:(NotificareCompletionBlock)completionBlock;
/*!
 *  @abstract Remove a tag to the device
 *
 *  @discussion
 *  Remove a tag from a device. This method uses blocks that returns success or failure for this operation. Make sure you only invoke this method after the onReady delegate.
 *  @param tag A NSString that represents the tag to be removed from the device
 */
- (void)removeTag:(NSString *)tag completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Remove all tags from the device
 *
 *  @discussion
 *  Remove all tags from a device. This method uses blocks that returns success or failure for this operation. Make sure you only invoke this method after the onReady delegate.
 */
- (void)clearTags:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Fetch User Data
 *
 *  @discussion
 *  Invoke this method to retrieve an NSArray of NotificareUserData objects associated with this device. Make sure you only invoke this method after the onReady delegate.
 */
- (void)fetchUserData:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Update User Data
 *
 *  @discussion
 *  Invoke this method to update User Data Fields associated with this device. Only fields added to the application will be considered. Make sure you only invoke this method after the onReady delegate.
 *  @param fields A NSArray of NotificareUserData objects to be updated
 */
- (void)updateUserData:(NSArray<NotificareUserData *> *)fields completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Fetch Do Not Disturb Times
 *
 *  @discussion
 *  Retrieves the NotificareDeviceDnD object with the do not disturb times for a device. Make sure you only invoke this method after the onReady delegate.
 */
- (void)fetchDoNotDisturb:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Update Do Not Disturb Times
 *
 *  @discussion
 *  Updates the device do not disturb times
 *  @param dnd A NotificareDeviceDnD object that represents the DnD for this device. Make sure you only invoke this method after the onReady delegate.
 */
- (void)updateDoNotDisturb:(NotificareDeviceDnD *)dnd completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Clear Do Not Disturb Times
 *
 *  @discussion
 *  Clears the device do not disturb times. Make sure you only invoke this method after the onReady delegate.
 */
- (void)clearDoNotDisturb:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Get a NotificareNotification object
 *
 *  @discussion
 *  Helper method to get a NotificareNotification object on-demand. Make sure you only invoke this method after the onReady delegate.
 *  @param notification A NSString/NotificareDeviceInbox/NSDictionary object
 */
- (void)fetchNotification:(id)notification completionHandler:(NotificareCompletionBlock)completionBlock;
/*!
 *  @abstract Get a controller for a NotificareNotification object
 *
 *  @discussion
 *  Helper method to get a controller for a NotificareNotification object on-demand.
 *  @param notification A NotificareNotification object
 */
- (id)controllerForNotification:(NotificareNotification *)notification;
/*!
 *  @abstract Clear a Private Notification
 *
 *  @discussion
 *  This method will remove any data from a private notification (sent to a user or device). Invoking this method on any other notification will scope will result in an error. Make sure you only invoke this method after the onReady delegate.
 *  @param notification A NotificareNotification object
 */
- (void)clearPrivateNotification:(NotificareNotification *)notification completionHandler:(NotificareCompletionBlock)completionBlock;
/*!
 *  @abstract Reply to a Notification
 *
 *  @discussion
 *  This method will reply to a notification's action. This is usually done by the notification itself but with this method it can be requested on-demand. Make sure you only invoke this method after the onReady delegate.
 *  @param notification A NotificareNotification object
 *  @param action A NotificareAction object
 *  @param data A NSDictionary object
 */
- (void)reply:(NotificareNotification *)notification forAction:(NotificareAction *)action andData:(NSDictionary * _Nullable)data completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Present a Notification
 *
 *  @discussion
 *  This helper method will handle a notification presentation given your own navigation controller and the controller received from us. This is usually done in response to the didReceiveNotificationInBackground or from the completion block of the openInboxItem.
 *  @param notification A NotificareNotification object
 *  @param navigationController A UINavigationController object
 *  @param controller A UIAlertController or UIViewController object
 */
-(void)presentNotification:(NotificareNotification*)notification inNavigationController:(UINavigationController*)navigationController withController:(id)controller;

/*!
 *  @abstract Present an Inbox Item
 *
 *  @discussion
 *  This helper method will handle an inbox item presentation given your own navigation controller and the controller received from us. This is usually done in response to the completion block of the openInboxItem method.
 *  @param inboxItem A NotificareDeviceInbox object
 *  @param navigationController A UINavigationController object
 *  @param controller A UIAlertController or UIViewController object
 */
-(void)presentInboxItem:(NotificareDeviceInbox*)inboxItem inNavigationController:(UINavigationController*)navigationController withController:(id)controller;

/*!
 *  @abstract Fetch an Asset Group
 *
 *  @discussion
 *  Retrieves a list of assets from a specific group
 *  @param group A NSString that indentifies the group name
 */
-(void)fetchAssets:(NSString*)group completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Get all Products
 *
 *  @discussion
 *  Use this method to get a list of all the NotificareProduct objects that you created in both iTunes Connect and Notificare dashboard.
 */
- (void)fetchProducts:(NotificareCompletionBlock)completionBlock;
/*!
 *  @abstract Get purchased Products
 *
 *  @discussion
 *  Use this method to get a list of all the non-consumable product identifiers that this AppleID has purchased.
 */
- (void)fetchPurchasedProducts:(NotificareCompletionBlock)completionBlock;
/*!
 *  @abstract Product
 *
 *  @discussion
 *  Use this method to get specific NotificareProduct object by providing a product identifier (SKU).
 *  @param productIdentifier A NSString that represents the product identifier
 */
- (void)fetchProduct:(NSString *)productIdentifier completionHandler:(NotificareCompletionBlock)completionBlock;
/*!
 *  @abstract Buy Product
 *
 *  @discussion
 *  Use this method to allow the user to buy a product. Use the NotificareProduct object retreived by the methods
 *  above to buy a product.
 *  @param product A NotificareProduct object
 */
- (void)buyProduct:(NotificareProduct *)product;
/*!
 *  @abstract Pause Download
 *
 *  @discussion
 *  Use this method to pause any active downloads.
 *  @param downloads A NSArray of SKDownload objects
 */
- (void)pauseDownloads:(NSArray<SKDownload *> *)downloads;
/*!
 *  @abstract Cancel Download
 *
 *  @discussion
 *  Use this method to cancel one or more active downloads.
 *  @param downloads A NSArray of SKDownload objects
 */
- (void)cancelDownloads:(NSArray<SKDownload *>  *)downloads;
/*!
 *  @abstract Resume Download
 *
 *  @discussion
 *  Use this method to resume one or more paused downloads.
 *  @param downloads A NSArray of SKDownload objects
 */
- (void)resumeDownloads:(NSArray<SKDownload *>  *)downloads;
/*!
 *  @abstract Downloaded Content Path
 *
 *  @discussion
 *  Retrieve the path for the download content of a product using its SKU.
 *  @param productIdentifier A NSString provided by the delegate didFinishLaunchingWithOptions:
 *  @return A NSString representing the path to the product's content
 */
- (NSString *)contentPathForProduct:(NSString *)productIdentifier;

/*!
 *  @abstract Start Location Updates
 *
 *  @discussion
 *  Starts the location manager for geo-targeting, geo-fencing and beacons. It will prompt the user with a permission dialog for location services if the user allows location services, this dialog will never be shown. Since iOS8 the key NSLocationAlwaysUsageDescription in your app's info.plist is required. For app's supporting older versions, use NSLocationUsageDescription key too. These keys should contain a text explaining why your app requires locations updates. After iOS 11 you should also use NSLocationAlwaysAndWhenInUseUsageDescription and NSLocationWhenInUseUsageDescription keys.
 */
-(void)startLocationUpdates;
/*!
 *  @abstract Check if Location Updates are ON
 *
 *  @discussion
 *  Use this method to quickly identify if the user has allowed location services
 *  @return A Boolean indicating if location services are on or off
 */
-(BOOL)locationServicesEnabled;
/*!
 *  @abstract Stop Location Updates
 *
 *  @discussion
 *  Stops the location manager from collecting location updates
 */
-(void)stopLocationUpdates;

/*!
 *  @abstract Clear Device Location
 *
 *  @discussion
 *  Use this method to manually clear a device's location. This will make sure that any location data stored remotely in our server is deleted from a device.
 */
-(void)clearDeviceLocation:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Log a custom event
 *
 *  @discussion
 *  Helper method to log a custom event
 *  @param event A NSString representing the event name
 *  @param data A NSDictionary object containing extraneous data for an event (optional)
 */
- (void)logCustomEvent:(NSString *)event withData:(NSDictionary* _Nullable)data completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 *  @abstract Log an event
 *
 *  @discussion
 *  Helper method to log a Notificare event
 *  @param event A NSString representing the event type (please check all macro definitions starting with kNotificareEvent)
 *  @param data A NSDictionary object containing extraneous data for an event (optional)
 */
- (void)logEvent:(NSString *)event withData:(NSDictionary* _Nullable)data completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 * @abstract Basic request method for Push API
 *
 * @discussion
 * Creates and executes a Push API request.
 * @param HTTPMethod HTTP method, i.e. @"POST"
 * @param path The relative path of the request, i.e. device
 * @param URLParams URL encoded parameters that are added to the request's URL
 * @param bodyJSON The JSON payload for the request's body
 */
- (void)doPushHostOperation:(NSString *)HTTPMethod path:(NSString *)path URLParams:(NSDictionary<NSString *, NSString *> * _Nullable)URLParams bodyJSON:(id _Nullable)bodyJSON completionHandler:(NotificareCompletionBlock)completionBlock;

/*!
 * @abstract Basic request method for Cloud API
 *
 * @discussion
 * Creates and executes a Cloud API request.
 * @param HTTPMethod HTTP method, i.e. @"POST"
 * @param path The relative path of the request, i.e. device
 * @param URLParams URL encoded parameters that are added to the request's URL
 * @param customHeaders Key/value pairs for optional custom HTTPS headers
 * @param bodyJSON The JSON payload for the request's body
 */
- (void)doCloudHostOperation:(NSString *)HTTPMethod path:(NSString *)path URLParams:(NSDictionary<NSString *, NSString *> * _Nullable)URLParams customHeaders:(NSDictionary<NSString *, NSString *> * _Nullable)customHeaders bodyJSON:(id _Nullable)bodyJSON completionHandler:(NotificareCompletionBlock)completionBlock;


/**
 * Non-Managed Methods
 * To be implemented in case you need to disable App Delegate Proxy. This is done by setting the property (boolean) DISABLE_APP_DELEGATE_PROXY to YES in the Notificare.plist under OPTIONS.
 */

/*!
 * @abstract Handle Launch Options
 *
 * @discussion
 * When the App Delegate Proxy is disabled this method must be implemented in order to handle launch options. Implement this method after launching the library in the application:didFinishLaunchingWithOptions.
 * @param launchOptions The NSDictionary object provided by the application launch
 */
- (void)didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
/*!
 * @abstract Handle Device registration
 *
 * @discussion
 * When the App Delegate Proxy is disabled this method must be implemented in order to handle device registration. Must be used in the delegate method application:didRegisterForRemoteNotificationsWithDeviceToken.
 * @param deviceToken The NSData object provided by the app delegate method application:didRegisterForRemoteNotificationsWithDeviceToken
 */
- (void)didRegisterForRemoteNotificationsWithDeviceToken:(nonnull NSData *)deviceToken;
/*!
 * @abstract Handle Remote Notifications
 *
 * @discussion
 * When the App Delegate Proxy is disabled this method must be implemented in order to handle remote notifications. Must be used in the delegate method application:didReceiveRemoteNotification.
 * @param userInfo The NSDictionary object provided by the app delegate method application:didReceiveRemoteNotification
 */
- (void)didReceiveRemoteNotification:(nonnull NSDictionary *)userInfo completionHandler:(NotificareCompletionBlock)completionBlock;

@end

NS_ASSUME_NONNULL_END
