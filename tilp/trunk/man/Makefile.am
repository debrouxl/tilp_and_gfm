man_MANS = tilp.1

EXTRA_DIST = $(man_MANS) cleaner.c dos2unix.c Manpage.txt

all: dist_win

view: $(man_MANS)
	groff -Tascii -man $(man_MANS) | less

dist_win: $(man_MANS)
	groff -Tascii -man $(man_MANS) > Manpage
	gcc cleaner.c -o cleaner
	gcc dos2unix.c -o dos2unix
	./cleaner Manpage
	./dos2unix Manpage.txt
