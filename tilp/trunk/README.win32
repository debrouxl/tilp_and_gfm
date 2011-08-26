				*******************
				*     TiLP        *
				* Windows version *
				*******************



REQUIREMENTS
------------

 - a Windows computer: Windows 2000, XP, Vista, 7 (32-bit or 64-bit)
 - the GTK+ 2.12 libraries with libglade
    Location: <http://downloads.sourceforge.net/gladewin32/gtk-2.12.9-win32-2.exe>
    => they can be automatically downloaded & installed by the installer.

	 Note: if you are using 'The GiMP', you might encounter DLL problems...
		The GTK+ package (1) provided with the GiMP might not be fully compatible with one used by TiLP/TiEmu.
		The package (2) requested by TiLP/TiEmu may be compatible with the GiMP.
		Thus, if you are using The GiMP, you are strongly encouraged to uninstall (1) and install (2).


NOTES
-----

1°) It is possible to install TI-Connect(tm) / TI-Nspire Computer (Link) Software(tm)
and TILP side by side, but this requires a manual configuration.
The following steps assume that TI-Connect / TINC(L)S is already installed:
* download the filter driver installer and install it, using the instructions given at
  http://sourceforge.net/apps/trac/libusb-win32/wiki , section "Filter Driver Installation";
* launch the filter wizard (accessible from the new entry in the Start menu) when the
  device (SilverLink, 84+, 89T, 84+SE, Nspire) you want to use with both TILP and
  TI-Connect / TILP and (TINCLS or TINCS) is plugged *in*;
* install the filter driver for that particular device;
* run the TILP installer.
After that, the device ought to work in both TILP and TI-Connect / TILP and (TINCLS or TINCS).


2°) This setup may download & install some extra libraries (GTK+ 2.12).

The GTK+ package includes the Wimp (Windows IMPersonator) theme engine which gives 
Windows look & feel (includes XP theming). Is also included the GTK theme selector.

3°) If anyone is getting one of these:
- ** WARNING **: Couldn't load font "MS Sans Serif 8" falling back to "Sans 8"
- ** ERROR **: file shape.c line 75: assertion failed: (glyphs->num_glyphs > 0)
or any other warning or error message regarding fonts/glyphs, the fix is to
open your C:\Program Files\Shared Files\Gtk\2.0\etc\gtk-2.0\gtkrc and to add this:
	style "user-font"
	{
	font_name="Arial"
	}
	widget_class "*" style "user-font"
This forces GTK+ to use a compatible font (Arial) and reportedly fixes both
the aforementioned problems, and probably others too.

4°) If you are getting any errors with DLLs, such as "The procedure entry point
atk_relation_set_add_relation_by_type could not be located in the dynamic link
library libatk-1.0-0.dll", make sure you have one and only ONE version of the
GTK+ DLLs. If unsure, remove all GTK+ packages and install one again.

5°) This setup will:
- copy USB drivers into C:\Program Files\{Common Files}\LPG Shared\drivers\usb,
- and register them into the Plug&Play database.

Simply plug your link cable: Windows should detect a new device and automatically
install it.

See instructions above for installing alongside TI-Connect / TI-Nspire Computer (Link) Software.

6°) This setup will install the DhaHelper driver for Windows NT4/2000/XP machines.
This step may require an administrator account (at least for NT4).
You may need to REBOOT your machine after installation (if you plan to 
use a parallel or serial link cable).

DhaHelper is copyrighted (c) 2004 Sascha Sommer and released under GPL license.
Source code is available from <http://svn.mplayerhq.hu/mplayer/trunk/vidix/dhahelperwin/>.

7°) This setup will install the GNU 'wget' utility for download of GTK+
(http://gnuwin32.sourceforge.net/packages/wget.htm).

8°) This setup will install/update the TiLP framework (libti* and drivers) which is
installed as shared components since TiLP v1.07, TiEmu v3.01 or GFM v1.00. 
Any software using the TiLP framework will take advantage of this update.


USAGE
-----

The installer automatically creates program entries in the Windows Startup menu.


AVAILABILITY
------------

  http://lpg.ticalc.org/prj_tilp (redirected from http://tilp.info)


COPYRIGHT
---------

TiLP is Copyright (C) 1999-2011 by the TiLP team <tilp-users@lists.sf.net>

Copying is allowed under the terms of GNU General Public License.  
See the file COPYING for more details.


---------------------------------------------------------------------------
Please report any bugs, questions, ...  (please give us your platform, your 
calculator type (with ROM version) and your link cable model).


The TiLP team.
