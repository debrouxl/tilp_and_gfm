SHELL=/bin/sh
#PREFIX=@prefix@
SHARE_DIR=$(prefix)/share/tilp
INSTALL=@INSTALL@

FILES = ../RELEASE ../COPYING  ../man/Manpage.txt
APPSIGN = appsign-linux-i386-bin.zip
EXTRA_DIST = $(FILES) $(APPSIGN)

install: $(FILES) extract
	@echo Installing miscellaneous files...
	@$(INSTALL) -d $(SHARE_DIR)
	@$(INSTALL) -m644 ../RELEASE $(SHARE_DIR)
	@$(INSTALL) -m644 ../COPYING $(SHARE_DIR)
	@$(INSTALL) -m644 ../man/Manpage.txt $(SHARE_DIR)
	@echo Done

extract: $(APPSIGN)
	@echo Extracting AppSign
	@unzip -o $(APPSIGN)
	@$(INSTALL) -m755 -d $(prefix)/share
	@$(INSTALL) -m755 -d $(prefix)/share/appsign83
	@$(INSTALL) -m644 appsign  $(prefix)/share/appsign83
	@$(INSTALL) -m644 0104.key $(prefix)/share/appsign83
	@echo Done

dos2unix:
	dos2unix
	lowercase
	uppercase