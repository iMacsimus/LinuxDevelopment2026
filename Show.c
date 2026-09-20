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

char *read_line(char *buf, size_t bufsize, FILE *fin) {
  if (!fgets(buf, bufsize, fin)) {
    return NULL;
  }
  size_t cur_len = strlen(buf);
  if (buf[cur_len - 1] == '\n') {
    buf[cur_len - 1] = '\0';
  }
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
    size_t linebuf_size = COLS;
    char *linebuf = malloc(linebuf_size);
    WINDOW *frame = newwin(LINES, COLS, 0, 0);
    WINDOW *win = newwin(LINES - 2, COLS - 2, 1, 1);

    box(frame, 0, 0);
    const size_t PATH_OUTPUT_OFFSET = 4;
    mvwaddstr(frame, 0, PATH_OUTPUT_OFFSET, "[");
    mvwaddstr(frame, 0, PATH_OUTPUT_OFFSET+1, path);
    mvwaddstr(frame, 0, PATH_OUTPUT_OFFSET+1+strlen(path), "]");
    wrefresh(frame);
    keypad(win, TRUE);
    scrollok(win, TRUE);

    for (int i = 0; i < LINES-2; ++i) {
      if (!read_line(linebuf, linebuf_size, fin)) {
        break;
      }
      wprintw(win, "\n%s", linebuf);
    }

    int c = 0;
    while ((c = wgetch(win)) != 27) {
      if (c == ' ') {
        if (!read_line(linebuf, linebuf_size, fin)) {
          wprintw(win, "\n~");
        } else {
          wprintw(win, "\n%s", linebuf);
        }
      }
    }

    delwin(win);
    delwin(frame);
    free(linebuf);
  }
  terminate_curses();

  fclose(fin);
  return 0;
}