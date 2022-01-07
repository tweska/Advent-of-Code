#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_BUF 1024

uint64_t get_score(char c) {
    switch (c) {
        case ')' : return 3;
        case ']' : return 57;
        case '}' : return 1197;
        case '>' : return 25137;
        default  : return 0;
    }
}

int main() {
    char buf;
    char expected[MAX_BUF];
    uint64_t size = 0;
    uint64_t score = 0;
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
            case '\n': size = 0;
                       skip = 0;
                       break;
            default  : if (!skip && buf != expected[--size]) {
                           score += get_score(buf);
                           skip = 1;
                       }
        }
    }

    printf("(DAY 10A) Syntax error score is: %lu!\n", score);

    return 0;
}
