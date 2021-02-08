#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <ncurses.h>
#include "builtin.h"

#define updateBorder() if (x == width - 1) {   \
                        x=1;                   \
                        y++;                   \
                        }                      \
                        if (y == height - 1) { \
                            y--;               \
                            scroll(win);       \
                            wmove(win, y, x);  \
                            wclrtoeol(win);    \
                            box(win, 0, 0);    \
                        }

#define max(x,y) ((x) > (y) ? (x) : (y))
#define min(x,y) ((x) < (y) ? (x) : (y))
#define PROMPT "Type Command> " 


int parse(char buffer[BUFS], char *tokens[BUFS / 2], char *argv[BUFS / 2]) {
    /* tokenize the buffer */
    char *buff = buffer;
    char *token;
    int i = 0;
    while ((token = strtok(buff, " \t")) != NULL) {
        argv[i] = token;
        tokens[i] = token;
        buff = NULL;
        i++;
    }

    /* separate binary from path name */
    argv[i] = NULL;
    if ((argv[0] != NULL) && (strrchr(argv[0], '/') != NULL)) {
        argv[0] = strrchr(argv[0], '/') + 1;
    }

    return 0;
}

void prompt(WINDOW **win, int *y, int *x) {
    /* prompt */
    if (mvwprintw(*win, *y, *x, PROMPT) < 0) {
        fprintf(stderr, "\nLibrary function failed\n");
        exit(1);
    }
    *x = strlen(PROMPT) + 1;
    wrefresh(*win);
}

/*
    This function checks for and calls builtin functions
*/
int builtin(char *argv[BUFS / 2]) {
    if (!(strcmp(argv[0], "n"))  ||  !(strcmp(argv[0], "new"))) {
        return new(argv);
    } else if (!(strcmp(argv[0], "exit")) || !(strcmp(argv[0], "x"))) {
        return 0;
    } else if (!(strcmp(argv[0], "help")) || !(strcmp(argv[0], "h"))) {
        return help();
    }
    return -1;
}

int main() {

    srand( (unsigned int) (time(NULL)));

    char buffer[BUFS];
    char *tokens[BUFS / 2];
    char *argv[BUFS / 2];

    // {{{ ncurses init
    initscr();
    cbreak();
    noecho();
    // preparing window
    int height, width, x, y;
    getmaxyx(stdscr, height, width);
    height /= 6;
    width = width*3/4;
    WINDOW *win = newwin(height, width, height*5, width/6);
    scrollok(win, TRUE); // allow scrolling in window
    keypad(win, TRUE); // allow arrow keys
    refresh();
    // making box
    box(win, 0, 0);
    mvwprintw(win, 0, 4, "Calypso"); // title the window
    x = y = 1;
    wmove(win, y, x); // move to repl position
    wrefresh(win);
    // }}}

    /* REPL */
    while (1) {
        updateBorder();
        prompt(&win, &y, &x);
        updateBorder();
        int c = 0;
        int strindex = 0;
        // this loop fills into buffer
        while (c != 10 && strindex < BUFS) {
            switch(c = wgetch(win)) {
                case KEY_UP: case KEY_DOWN:
                    break;
                case KEY_LEFT:
                    getyx(win, y, x);
                    wmove(win, y, x-1);
                    break;
                case KEY_RIGHT:
                    getyx(win, y, x);
                    wmove(win, y, min(x+1, (int)strlen(PROMPT) + strindex));
                    break;
                case '\n':
                    buffer[strindex] = (char)c;
                    strindex++;
                    break;
                case 8: case 127: // backspace
                    wdelch(win);
                    x--;
                    strindex--;
                    break;
                default:
                    mvwaddch(win, y, x++, (chtype)c);
                    updateBorder();
                    buffer[strindex] = (char)c;
                    strindex++;
                    break;
            }
            wrefresh(win);
        }
        y++;
        x = 1;
        updateBorder();
        /* parse and eval input */
        buffer[strindex-1] = '\0';
        if (parse(buffer, tokens, argv)) {
            continue;
        }
        if (argv[0]) {
            int b;
            if ((b = builtin(argv))) {
                if (b < 0) {
                    mvwprintw(win, y++, x=1, "Command not found. Use help to see list of commands.");
                    updateBorder();
                    wrefresh(win);
                }
                continue;
            } else {
                break;
            }
        }
    }
    endwin(); // end of ncurses stuff

    return 0;
}
