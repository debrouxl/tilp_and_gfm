


				************
				*   TiLP   *
				************




REMARK
------

If you have a SilverLink cable (TI-GRAPH LINK USB), you will need to retrieve
the driver on the Linux Programmer Group at http://lpg.ticalc.org/prj_usb.

This cable is supported but may not work depending of the platform and the 
calculator. 
Sincerely, it works fine at home but does not work for few peoples...


DESCRIPTION
-----------

TiLP is a program allowing a PC to communicate with 
a TI calculator.

It works on Linux, Windows and Mac OS-X platforms. It has been
ported to BeOS (but this port is not maintained any longer).
See README.linux or README.win32 according to your platform for more 
informations.

All physical link cables are supported by TiLP: parallel, serial, 
BlackLink, GrayLink, AVRlink and SilverLink.
TiLP also support some virtual links: one for VirtualTI, the other one for
GtkTiEmu.

Supported calculators are: 
TI92+, TI92, TI89, TI86, TI85, TI83+, TI83, TI82 and TI73. 

TiLP is easily expandable through the new plugin mechanism...


FEATURES
--------

Features for the TI92+:
  - remote control of the calculator
  - screen dump
  - directory list
  - sending/receiving variable
  - sending/receiving backup
  - ROM dump
  - sending/receiving of FLASH applications
  - upgrading of Operating System (AMS)

Features for the TI92:
  - remote control of the calculator
  - screen dump
  - directory list
  - sending/receiving variable
  - sending/receiving backup
  - ROM version
  - ROM dump (require FARGO)

Features for the TI89:
  - remote control of the calculator
  - screen dump
  - directory list
  - sending/receiving variable
  - sending/receiving backup
  - ROM dump
  - sending/receiving of FLASH applications
  - upgrading of Operating System (AMS)

Features for the TI86:
  - screen dump
  - sending/receiving backup (old & new ti86 calcs)
  - sending/receiving variable
  - TIGL file support
  - ROM dump

Features for the TI85:
  - screen dump
  - sending/receiving backup
  - sending/receiving variable
  - TIGL file support
  - ROM dump

Features for the TI83+ (ROM1.14 mini):
  - screen dump
  - directory list
  - sending/receiving backup
  - sending/receiving variable
  - sending/receiving of FLASH applications
  - upgrading of Operating System (AMS)

Note: the TI83+ is the only calc which have a GROUP variable. TiLP supports it
in a specific fashion: this kind of var is saved as a single file as any other
variable. Thus, if you send it, it will stay be grouped on calc.
The TI's software has a different way: it explode the GROUP variable
into a .8Xg group file and you lost the group on calculator.

Features for the TI83:
  - screen dump
  - directory list
  - sending/receiving variable
  - sending/receiving backup
  - TIGL file support
  - ROM dump

Features for the TI82:
  - screen dump
  - sending/receiving variable
  - sending/receiving backup
  - TIGL files support
  - ROM dump

Features for the TI73:
  - screen dump
  - directory list
  - sending/receiving variable
  - sending/receiving of FLASH applications
  - upgrading of Operating System (GRAPH EXPLORER SOFTWARE)


AVAILABILITY
------------

  http://lpg.ticalc.org/prj_tilp 
	(redirected on http://tilp.sourceforge.net)


COPYRIGHT
---------

TiLP is Copyright (C) 1999-2002 by the TiLP team <tilp-users@lists.sf.net>.

Copying is allowed under the terms of GNU General Public License.  
See the file COPYING for more details.


THANKS
------

See the THANKS file, please.


----------------------------------------------------------------------
Please report any bugs, questions, ... to <tilp-users@lists.sf.net>  
(please give me your platform, your 
calculator type (with ROM version) and your link cable model).

The TiLP team <tilp-users@lists.sf.net>.
