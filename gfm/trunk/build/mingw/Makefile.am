BASE	 = gfm
RC	?= windres

EXTRA_DIST = $(BASE).rc

if OS_WIN32
  noinst_DATA = $(BASE)-rc.o
endif

if OS_WIN32
all: $(BASE)-rc.o

$(BASE)-rc.o : $(BASE).rc
	$(RC) $(BASE).rc $@
endif