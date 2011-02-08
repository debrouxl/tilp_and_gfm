man_MANS = tilp.1
pkgdata_DATA = Manpage.txt

EXTRA_DIST = $(man_MANS) cleaner.c Manpage.txt

all: dist_win

view: $(man_MANS)
	groff -Tascii -man $(man_MANS) | less

dist_win: $(man_MANS)
	groff -Tascii -man $(man_MANS) > Manpage
	C_INCLUDE_PATH="" LIBRARY_PATH="" $(CC) cleaner.c -o cleaner
	./cleaner Manpage
	rm Manpage cleaner
