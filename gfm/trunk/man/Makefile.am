man_MANS = gfm.1
pkgdata_DATA = Manpage.txt

EXTRA_DIST = $(man_MANS) cleaner.c dos2unix.c Manpage.txt

view: $(man_MANS)
	groff -Tascii -man $(man_MANS) | less

dist_win: $(man_MANS)
	groff -Tascii -man $(man_MANS) > Manpage
	gcc cleaner.c -o cleaner
	gcc dos2unix.c -o dos2unix
	./cleaner Manpage
	./dos2unix Manpage.txt
	rm Manpage cleaner dos2unix
