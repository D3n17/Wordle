#include <stdio.h>
#include <string.h>
#include "choose_word.h"
#include "check.h"
#include "keyboard.h"

int main(void) {

    char* word;
    int mode;

    printf("\x1b[2J\x1b[H");
    puts("Welcome to my Wordle!");
ASK:
    puts("Please, choose gamemode:");
    puts("1 - player vs player");
    puts("2 - player vs random word\n");
    if (scanf("%d", &mode) != 1) {
        while (getchar() != '\n');
        goto ASK;
    }

    switch (mode) {
        case 1:
            word = player_word();
            break;
        case 2:
            word = random_word();
            break;
        default:
            goto ASK;
    }

    puts("Try to guess the word! You have 6 attempts.\n");
    printf("\n\n\n");
    char guess[32];
    int count = 6;
    while (count > 0) {
        char color[6] = {'u', 'u', 'u', 'u', 'u', '\0'};
AGAIN:
        print_keyboard(10 - count);
        printf("\r_____\r");
        fflush(stdout);
        count--;
        scanf("%s", guess);

        if (strlen(guess) != 5 || (strcmp(guess, word) != 0 && !in_dict(guess))) {
            count++;
            printf("\x1b[A\r\x1b[2K");
            fflush(stdout);
            goto AGAIN;
        }

        for (int i = 0; i < 5; ++i) {
            if (guess[i] == word[i]) {
                color[i] = 'g';
            }
        }
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (color[i] != 'g' && guess[i] == word[j]) {
                    color[i] = 'y';
                    for (int k = i - 1; k >= 0; --k) {
                        if (guess[k] == guess[i]) {
                            color[i] = '-';
                            break;
                        }
                    }    
                }
            }
        }
        for (int i = 4; i >= 0; --i) {
            if (color[i] == 'u') {
                color[i] = '-';
            }
        }
        for (int i = 4; i >= 0; --i) {
            if (color[i] == 'g') {
                states[guess[i] - 'a'] = GREEN;
            } else if (color[i] == '-' && states[guess[i] - 'a'] != YELLOW && states[guess[i] - 'a'] != GREEN) {
                states[guess[i] - 'a'] = GRAY;
            } else if (color[i] == 'y' && states[guess[i] - 'a'] != GREEN) {
                states[guess[i] - 'a'] = YELLOW;
            }
        }

        print_keyboard(10 - count);

        printf("\x1b[A\r");
        for (int i = 0; i < 6; ++i) {
            if (color[i] == '-') {
                printf("\x1b[90m%c", guess[i]);
            } else if (color[i] == 'y') {
                printf("\x1b[43m%c", guess[i]);
            } else if (color[i] == 'g') {
                printf("\x1b[42m%c", guess[i]);
            } else if (color[i] == 'u') {
                printf("%c", guess[i]);
            }
            printf("\x1b[0m");
        }
        fflush(stdout);
        printf("\n");

        if (strcmp(guess, word) == 0) {
            printf("You won!\n");
            return 0;
        }
    }

    printf("\x1b[0mYou lost! The word was: %s\n", word);

}
