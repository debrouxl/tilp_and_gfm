man_MANS = tilp.1

EXTRA_DIST = $(man_MANS) cleaner.c Manpage.txt

all: dist_win

view: $(man_MANS)
	groff -Tascii -man $(man_MANS) | less

dist_win: $(man_MANS)
	groff -Tascii -man $(man_MANS) > Manpage
	gcc cleaner.c -o cleaner
	./cleaner Manpage
	dos2unix Manpage.txt
