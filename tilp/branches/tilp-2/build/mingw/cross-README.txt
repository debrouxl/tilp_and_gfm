
Steps to build a Linux hosted MinGW cross-compilation environment:

Step 1. Download the build-cross.sh script:
	http://www.libsdl.org/extras/win32/cross/build-cross.sh
        This script builds and installs the cross-compilation tools
        into /usr/local/cross-tools by default.
Step 2. Put the script in a temporary directory with lots of space
Step 3. Edit the configuration variables in the script (if needed)
Step 4. Run the script to download files, compile and install.

You can get precompiled binaries for x86 Linux from:
http://www.libsdl.org/extras/win32/cross/mingw32-linux-x86-glibc-2.2.tar.gz

Once you have the cross-compilation tools available, you can get
the scripts cross-configure.sh and cross-make.sh and use them as
you would normally use configure and make.

These scripts are available from:
	http://www.libsdl.org/extras/win32/cross/cross-configure.sh
	http://www.libsdl.org/extras/win32/cross/cross-make.sh

-------------------------------------------------------------------------
Many thanks to Mumit Khan, who made all of this possible with his work on
GCC. Thanks to the MinGW group for continuing to improve the gcc build
environment for Windows. Thanks to Ray Kelm for writing the build-cross.sh
script and Mo Dejong for writing the original build script he started from.
