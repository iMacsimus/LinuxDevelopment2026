DESTDIR = /
BINDIR = usr/bin
NAME = Show

$(NAME): Show.c
	cc Show.c -o $(NAME) -lncursesw
install: $(NAME)
	install -D $(NAME) $(DESTDIR)/$(BINDIR)/$(NAME)
clean:
	rm -f $(NAME)