## Process this file with automake to produce Makefile.in

if OS_WIN32
 no_undefined = -no-undefined
endif

DEFS=@DEFS@ -DPLUGIN_DIR=\"${tilp_plugin_dir}\"

INCLUDES = -I$(top_srcdir) -I$(includedir) \
	-I../intl -I$(top_srcdir)/intl \
	-DPREFIX=\"${prefix}\" -I. -I../ -I../../

# program to compile and install
bin_PROGRAMS = tilpreg

tilpreg_SOURCES = main.c
tilpreg_LDFLAGS = $(LDFLAGS) $(no_undefined)

noinst_HEADERS = *.h

EXTRA_DIST = tilp.registry

install: tilp.registry
	@echo Installing plug-ins registry...
	@$(INSTALL) -m755 -d $(sysconfdir)
	@$(INSTALL) -m755 -d $(sysconfdir)/tilp
	@$(INSTALL) -m644 tilp.registry $(sysconfdir)/tilp
	@echo Done.

uninstall: $(FILES)
	@echo Removing plug-ins registry...
	cd $(sysconfdir)/tilp; $(RM) tilp.registry
	-rmdir $(sysconfdir)/tilp
	@echo Done.