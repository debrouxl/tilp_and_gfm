man_MANS = gfm.1
pkgdata_DATA = Manpage.txt

EXTRA_DIST = $(man_MANS) cleaner.c Manpage.txt

all: dist_win

view: $(man_MANS)
	groff -Tascii -man $(man_MANS) | less

Manpage.txt:
	groff -Tascii -man $(man_MANS) > Manpage.txt
	C_INCLUDE_PATH="" LIBRARY_PATH="" $(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) cleaner.c -o cleaner
	./cleaner Manpage.txt

dist_win: $(man_MANS) Manpage.txt

clean:
	rm Manpage.txt cleaner
