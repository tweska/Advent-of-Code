#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_BUF 255
#define MAX_LINES 255

uint64_t get_score(char c) {
    switch (c) {
        case ')' : return 1;
        case ']' : return 2;
        case '}' : return 3;
        case '>' : return 4;
        default  : return 0;
    }
}

/* Very simple sorting algorithm. */
void sort(uint64_t *list, uint64_t len) {
    uint64_t tmp;
    uint64_t i = 0;

    while (i < len-1) {
        if (list[i] >= list[i+1]) {
            i++;
            continue;
        }

        /* Swap... */
        tmp = list[i];
        list[i] = list[i+1];
        list[i+1] = tmp;

        if (i > 0) i--;
    }
}

int main() {
    char buf;
    char expected[MAX_BUF];
    uint64_t size = 0;
    uint64_t score[MAX_LINES];
    uint64_t lines = 0;
    uint8_t skip = 0;

    /* Read each input character and push the corresponding close character
     * to the expected list or check if the input character is the expected
     * close character. */
    while ((buf = fgetc(stdin)) != EOF) {
        switch (buf) {
            case '(' : expected[size++] = ')';
                       break;
            case '[' : expected[size++] = ']';
                       break;
            case '{' : expected[size++] = '}';
                       break;
            case '<' : expected[size++] = '>';
                       break;
            case '\n': if (!skip) {
                           /* Calculate score based on expected characters. */
                           score[lines] = 0;
                           for (int64_t i = size-1; i >= 0; i--) {
                               score[lines] = score[lines] * 5 + get_score(expected[i]);
                           }
                           lines++;
                       }
                       size = 0;
                       skip = 0;
                       break;
            default  : if (!skip && buf != expected[--size]) {
                           /* Skip this line for scoring because its corrupt! */
                           skip = 1;
                       }
        }
    }

    /* Sort the scores and grab the value in the middle. */
    sort(score, lines);
    printf("(DAY 10B) Middle syntax error score is: %lu!\n", score[lines/2]);

    return 0;
}
