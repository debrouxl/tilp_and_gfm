				*****************
				*     TiLP	    *
				* Win32 version *
				*****************




REQUIREMENTS
------------

 - a Windows computer: Windows 95/98/Me or Windows NT4/2000/XP
 - the GTK+ 2.x libraries (provided by Dropline Systems)
        Location: http://prdownloads.sourceforge.net/gtk-win/GTK-Runtime-Environment-2.2.4-2.exe?download
 - the SilverLink driver v2.x if you have a SilverLink cable
	Location: http://www.ticalc.org/pub/win/link/tiglusbinf.zip

NOTES
-----

1°) This release is a no longer a native port of TiLP. You need some extra libraries (GTK+ 2.0).

2°) If you have a SilverLink cable (TI-GRAPH LINK USB), you will need to retrieve
the Win32 driver on the Linux Programmer Group at http://lpg.ticalc.org/prj_usb.

Simply plug your link cable: Windows should detect a new device. Next, follow the
installation instructions.

You can install driver at any time (that is to say before or after TiLP installation).

Given that the LPG SilverLink driver has a Release date more recent than the Texas
Instruments OEM driver, this driver will be used prior to the TI one.

Note: if you are running into troubles with the SilverLink cable, please don't mail me !
This driver works (almost) perfectly but work so so for few people. I can't make this driver work 
better with hardware and skills I have. Thus, don't sue me!

3°) This setup will install the PortTalk driver (Windows NT4/2000/XP machines).
This step may require an administrator account (at least for NT4).
You will need to REBOOT your machine after installation (if you plan to 
use a parallel or serial link cable).

4°) This setup will modify your AUTOEXEC.BAT (Windows 9x/Me) to speed-up 
GTK+ 2.0 rendering. It should be better to REBOOT your machine after the first
installation...

5°) Unfortunately, TiLP does not have some nice TI fonts. By default, TiLP use the
Courier New font. Nevertheless, if you have installed the TI-Connect software, 
TiLP will use the TI's fonts.


PortTalk copyright (http://www.beyondlogic.org):
Documentation and source code Copyright © 2002 Craig Peacock, Craig.Peacock@beyondlogic.org
This driver is provided "as is", without any guarantee made as to its suitability or fitness 
for any particular use. Permission is herby granted to modify or enhance this sample code
to produce a derivative program which may only be distributed in compiled object form only.


COMPILATION
-----------

1°) MSVC: use projects with MSVC 5.0 or 6.0

2°) MinGW: ./configure, make, make install


AVAILABILITY
------------

  http://lpg.ticalc.org/prj_tilp (redirected on http://tilp.sourceforge.net)


COPYRIGHT
---------

TiLP is Copyright (C) 1999-2003 by the TiLP team <tilp-users@lists.sf.net>

Copying is allowed under the terms of GNU General Public License.  
See the file COPYING for more details.


---------------------------------------------------------------------------
Please report any bugs, questions, ...  (please give us your platform, your 
calculator type (with ROM version) and your link cable model).


The TiLP team <tilp-users@lists.sf.net>
