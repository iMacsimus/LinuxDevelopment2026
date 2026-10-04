DESTDIR = /
BINDIR = usr/bin

Show: Show.c
	cc Show.c -o Show -lncursesw
install: Show
	install -D Show $(DESTDIR)/$(BINDIR)/Show
clean:
	rm -f Show