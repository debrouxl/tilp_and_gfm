## Process this file with automake to produce Makefile.in

# subdirectories to scan
SUBDIRS = \
	glade help icons man misc pixmaps src win32 \
	plugins registry \
	po intl

EXTRA_DIST = \
	ABOUT-NLS AUTHORS ChangeLog COPYING INSTALL* NEWS 	\
	README README* TODO RELEASE ./po/TRANSLATORS

INCLUDES = -I$(top_srcdir) -I$(includedir) 		\
	-I../intl -I$(top_srcdir)/intl 			\
	-DPREFIX=\"${prefix}\" -I. -I../ -I../../

# This target retrieve some files from my Win$ partition to my Linux one
SRC_DIR=/mnt/xp/devel/tilp_project/tilp
DST_DIR=/home/devel/tilp_project/tilp

win2lin: $(C_FILES)
	@echo Merging files from Win32 to Linux...
	@echo dir1
	@for I in $(SRC_DIR)/src/*.c ; do \
	cp $$I $(DST_DIR)/src; \
	done
	@for I in $(SRC_DIR)/src/*.h ; do \
	cp $$I $(DST_DIR)/src; \
	done
	@for I in $(SRC_DIR)/help/*.* ; do \
	cp $$I $(DST_DIR)/help; \
	done
	@for I in $(SRC_DIR)/registry/*.c ; do \
	cp $$I $(DST_DIR)/registry; \
	done
	@for I in $(SRC_DIR)/registry/*.h ; do \
	cp $$I $(DST_DIR)/registry; \
	done
	cd $(DST_DIR)/src; dos2unix; lowercase; uppercase;
	cd $(DST_DIR)/registry; dos2unix; lowercase; uppercase;
	@echo dir3
	@for I in $(SRC_DIR)/win32/msvc/*.* ; do \
	cp $$I $(DST_DIR)/win32/msvc; \
	done
	cp -Rfv /mnt/xp/devel/tilp_project/InnoSetup /home/devel/tilp_project
	cp $(SRC_DIR)/RELEASE $(DST_DIR)/RELEASE
	cp $(SRC_DIR)/Changelog $(DST_DIR)/ChangeLog
	@echo Done

bundle:
	tar cvf tarball.tar /usr/share/tilp /usr/bin/tilp /usr/lib/libticables* /usr/li\b/libticalcs* /usr/lib/libtifiles*
	gzip tarball.tar



