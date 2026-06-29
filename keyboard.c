#include <stdio.h>
#include <string.h>
#include "keyboard.h"


int states[26] = {0};

const char* rows[] = {
    "qwertyuiop",
    "asdfghkl",
    "zxcvbnm"
};

void print_keyboard(int up) {
    char num[16];
    sprintf(num, "%d", up);
    char sym[16];
    strcpy(sym, "\x1b[");
    strcat(sym, num);
    strcat(sym, "A\r");
    printf("%s", sym);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; rows[i][j] != '\0'; ++j) {
            char c = rows[i][j];
            int ind = c - 'a';
            int state = states[ind];

            switch (state) {
                case GRAY:
                    printf("\x1b[90m%c", c);
                    break;
                case GREEN:
                    printf("\x1b[42m%c", c);
                    break;
                case YELLOW:
                    printf("\x1b[43m%c", c);
                    break;
                default:
                    printf("%c", c);
            }
            printf("\x1b[0m");
        }
        if (i != 2) {
            printf("\n");
        }
    }
    
    sprintf(num, "%d", up - 2);
    strcpy(sym,"\x1b[");
    strcat(sym, num);
    strcat(sym, "B");
    printf("%s", sym);
    

}
