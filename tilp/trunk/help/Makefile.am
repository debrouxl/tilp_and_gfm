SHELL=/bin/sh
INSTALL=@INSTALL@

FILES = *.htm? *.png
EXTRA_DIST = $(FILES)

install: $(FILES)
	@echo Installing html manual and images...
	@$(INSTALL) -m755 -d $(DESTDIR)$(tilp_help_dir)
	@for I in ./* ; do \
		$(INSTALL) -m644 $$I $(DESTDIR)$(tilp_help_dir)/; \
	done
	@rm -f $(SHARE_DIR)/help/Makefile*
	@echo Done

uninstall:
	@echo Removing pixmaps...
	$(RM) $(DESTDIR)$(tilp_help_dir)/*

dos2unix:
	dos2unix
	lowercase
	uppercase