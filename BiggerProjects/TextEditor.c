
#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

struct termios orig_termios;

void EnableRawMode(void);
void disableRawMode(void);

void disableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void EnableRawMode(void) {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void) {
    char c;
    EnableRawMode();
    int i = 0;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
        if (iscntrl(c)) {
            printf("%d\n", c);
        }
        else {
            printf("%d (%c)\n", c, c);
        }
    }
    return 0;
}
