## Process this file with automake to produce Makefile.in

SUBDIRS = test nv82 gfv

.PHONY: files

files:
	@files=`ls $(DISTFILES) 2> /dev/null`; for p in $$files; do \
	  echo $$p; \
	done
	@for subdir in $(SUBDIRS); do \
	  files=`cd $$subdir; $(MAKE) files | grep -v "make\[[1-9]\]"`; \
	  for file in $$files; do \
	    echo $$subdir/$$file; \
	  done; \
	done

install: $(PLUGINS)
	@echo Clean-up in plug-ins directory...
	$(RM) $(DESTDIR)$(tilp_plugin_dir)/*.a 
	$(RM) $(DESTDIR)$(tilp_plugin_dir)/*.la
	$(RM) $(DESTDIR)$(tilp_plugin_dir)/*.so
	$(RM) $(DESTDIR)$(tilp_plugin_dir)/*.so.?
	@echo Done.

uninstall: $(FILES)
	@echo Removing plug-ins ...
	$(RM) $(DESTDIR)$(tilp_plugin_dir)/*.*
