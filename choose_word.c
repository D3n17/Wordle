#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "choose_word.h"

static char word[6];

char* player_word() {
ASK:
    puts("The first player should enter a 5-letter word:");
    scanf("%s", word);
    if (strlen(word) != 5) {
        goto ASK;
    }
    printf("\x1b[2J\x1b[H");
    return word;
}

char* random_word() {
    FILE* f;
    f = fopen("words", "r");
    if (f == NULL) {
        printf("Couldn't find file\n");
    }

    fseek(f, 0, SEEK_END);
    long total = ftell(f);
    long count = total / 6;

    srand(time(NULL));
    long line = rand() % (count + 1);

    fseek(f, 6 * line, SEEK_SET);
    fgets(word, 6, f);
    fclose(f);
    printf("\x1b[2J\x1b[H");
    return word;
}
