#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <errno.h>

#include <curses.h>

void init_curses(void) {
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  cbreak();
}

void terminate_curses(void) {
  endwin();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./Show <path/to/file>\n");
    return -1;
  }

  const char *path = argv[1];
  FILE *fin = fopen(path, "r");
  if (!fin) {
    perror(path);
    return errno;
  }

  init_curses();
  {
    WINDOW *frame = newwin(LINES, COLS, 0, 0);
    WINDOW *win = newwin(LINES - 2, COLS - 2, 1, 1);

    box(frame, 0, 0);
    mvwaddstr(frame, 0, 4, "[");
    mvwaddstr(frame, 0, 5, path);
    mvwaddstr(frame, 0, 5+strlen(path), "]");
    wrefresh(frame);
    keypad(win, TRUE);
    scrollok(win, TRUE);

    int c = 0;
    while ((c = wgetch(win)) != 27) {
      wprintw(win, "\n%d: %s", c, keyname(c));
    }

    delwin(win);
    delwin(frame);
  }
  terminate_curses();

  fclose(fin);
  return 0;
}