SHELL=/bin/sh
INSTALL=@INSTALL@

GLADE_FILES = *-2.glade
EXTRA_DIST = $(GLADE_FILES)

install: $(GLADE-FILES)
	@echo Installing glade files...
	@$(INSTALL) -m755 -d $(tilp_glade_dir)
	@for I in ./$(GLADE_FILES) ; do \
		$(INSTALL) -m644 $$I $(tilp_glade_dir)/; \
	done
	@echo Done

uninstall:
	@echo Removing pixmaps...
	$(RM) $(tilp_glade_dir)/$(GLADE_FILES)

dos2unix:
	dos2unix
	lowercase
	uppercase