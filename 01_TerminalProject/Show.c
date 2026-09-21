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
  if (cur_len>0 && buf[cur_len - 1] == '\n') {
    buf[cur_len - 1] = '\0';
  }
  return buf;
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
    size_t linebuf_size = COLS-2;
    char *linebuf = malloc(linebuf_size);
    WINDOW *frame = newwin(LINES, COLS, 0, 0);
    WINDOW *win = newwin(LINES - 2, COLS - 2, 1, 1);

    box(frame, 0, 0);
    const size_t PATH_OUTPUT_PAD_LEFT = 4;
    const size_t PATH_OUTPUT_PAD_RIGHT = 4;
    size_t pathlen = strlen(path);
    if (pathlen + PATH_OUTPUT_PAD_LEFT + PATH_OUTPUT_PAD_RIGHT + 2 <= COLS) {
      mvwaddstr(frame, 0, PATH_OUTPUT_PAD_LEFT, "[");
      mvwaddstr(frame, 0, PATH_OUTPUT_PAD_LEFT+1, path);
      mvwaddstr(frame, 0, PATH_OUTPUT_PAD_LEFT+1+pathlen, "]");
    } else {
      size_t truncated_len = COLS-PATH_OUTPUT_PAD_LEFT-PATH_OUTPUT_PAD_RIGHT-2-3;
      mvwaddstr(frame, 0, PATH_OUTPUT_PAD_LEFT, "[...");
      mvwaddstr(frame, 0, PATH_OUTPUT_PAD_LEFT+4, path + pathlen - truncated_len);
      mvwaddstr(frame, 0, PATH_OUTPUT_PAD_LEFT+4+truncated_len, "]");
    }
    
    wrefresh(frame);
    keypad(win, TRUE);
    scrollok(win, TRUE);

    wprintw(win, "\n");
    int i = 0;
    for (; i < LINES-2-1; ++i) {
      if (!read_line(linebuf, linebuf_size, fin)) {
        break;
      }
      wprintw(win, "%s\n", linebuf);
    }
    for (; i < LINES-2-1; ++i) {
      wprintw(win, "~\n");
    }

    int c = 0;
    while ((c = wgetch(win)) != 27) {
      if (c == ' ') {
        if (!read_line(linebuf, linebuf_size, fin)) {
          wprintw(win, "~\n");
        } else {
          wprintw(win, "%s\n", linebuf);
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
