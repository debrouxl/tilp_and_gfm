/*  TiLP - Linking program for TI calculators
 *  Copyright (C) 2001-2002 Julien BLACHE <jb@technologeek.org>
 *
 *  Cocoa GUI for Mac OS X
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

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
    IBOutlet id pbar2PBar;
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
    
    IBOutlet id myTilpController;
    IBOutlet id myBoxesController;
    IBOutlet id myMenuController;
    IBOutlet id myPrefsController;
    IBOutlet id myTransfersController;
    
    id pbar1;
    id pbar2;
    id pbar_text;
    id pbar_rate;
    id pbarWindow;
}

- (void)showCurrentPBar;
- (void)hideCurrentPBar;

- (void)msgSheet:(NSString *)message title:(NSString *)title;

- (int)user1Sheet:(NSString *)title message:(NSString *)message button1:(NSString *)button1;
- (int)user2Sheet:(NSString *)title message:(NSString *)message button1:(NSString *)button1 button2:(NSString *)button2;
- (int)user3Sheet:(NSString *)title message:(NSString *)message button1:(NSString *)button1 button2:(NSString *)button2 button3:(NSString *)button3;

- (NSString *)dlgboxEntry:(NSString *)title message:(NSString *)message content:(NSString *)content;

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
