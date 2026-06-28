#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "check.h"

void get(FILE* f, char* dest, long line) {
    fseek(f, 6 * line, SEEK_SET);
    fgets(dest, 6, f);
}

bool in_dict(char* word) {
    FILE* f;
    f = fopen("words", "r");
    if (f == NULL) {
        printf("Couldn't find file\n");
        return false;
    }

    fseek(f, 0, SEEK_END);
    long total = ftell(f);
    long count = total / 6;

    long l = 0;
    long r = count - 1;
    char temp[6];

    while (l <= r) {
        long m = (l + r) / 2;
        get(f, temp, m);
        int cmp = strcmp(word, temp);
        if (cmp == 0) {
            fclose(f);
            return true;
        } else if (cmp < 0) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    fclose(f);
    return false;

}
