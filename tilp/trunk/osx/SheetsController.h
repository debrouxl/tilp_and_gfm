//
//  SheetsController.h
//  TiLP
//
//  Created by julien on Fri Dec 07 2001.
//  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface SheetsController : NSObject
{
    IBOutlet id dlgboxentryButton1;
    IBOutlet id dlgboxentryButton2;
    IBOutlet id dlgboxentryEntry;
    IBOutlet id dlgboxentryText;
    IBOutlet id dlgboxentryWindow;
    IBOutlet id pbar1PBar;
    IBOutlet id pbar1Rate;
    IBOutlet id pbar1Window;
    IBOutlet id pbar2Button;
    IBOutlet id pbar2Text;
    IBOutlet id pbar2Window;
    IBOutlet id pbar3PBar1;
    IBOutlet id pbar3PBar2;
    IBOutlet id pbar3Rate;
    IBOutlet id pbar3Window;
    IBOutlet id pbar4PBar;
    IBOutlet id pbar4Rate;
    IBOutlet id pbar4Text;
    IBOutlet id pbar4Window;
    IBOutlet id pbar5PBar1;
    IBOutlet id pbar5PBar2;
    IBOutlet id pbar5Rate;
    IBOutlet id pbar5Text;
    IBOutlet id pbar5Window;
    IBOutlet id user1Button;
    IBOutlet id user1Text;
    IBOutlet id user1Window;
    IBOutlet id user2Button1;
    IBOutlet id user2Button2;
    IBOutlet id user2Text;
    IBOutlet id user2Window;
    IBOutlet id user3Button1;
    IBOutlet id user3Button2;
    IBOutlet id user3Button3;
    IBOutlet id user3Text;
    IBOutlet id user3Window;
    IBOutlet id mainWindow;
    
    IBOutlet id myTilpController;
    IBOutlet id myBoxesController;
    IBOutlet id myMenuController;
    IBOutlet id myPrefsController;
    
    id pbar1;
    id pbar2;
    id pbar_text;
    id pbar_rate;
    id pbarWindow;
}

- (void)msgSheet:(NSString *)message title:(NSString *)title;

- (int)user1Sheet:(NSString *)message button1:(NSString *)button1;
- (int)user2Sheet:(NSString *)message button1:(NSString *)button1 button2:(NSString *)button2;
- (int)user3Sheet:(NSString *)message button1:(NSString *)button1 button2:(NSString *)button2 button3:(NSString *)button3;

- (NSString *)dlgboxEntry:(NSString *)message content:(NSString *)content;

- (void)pbarType2:(NSString *)message;

- (void)pbarType1;
- (void)pbarType3;
- (void)pbarType4:(NSString *)message;
- (void)pbarType5:(NSString *)message;

- (void)destroyPbar;

// refresh part
- (void)refreshPbar1;
- (void)refreshPbar2;
- (void)refreshLabel;

@end
