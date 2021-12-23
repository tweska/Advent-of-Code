#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_LEN 16

int main() {
    uint32_t counter[MAX_LEN];
    uint32_t lines = 0;
    uint32_t index = 0;
    uint8_t bits = 0;
    char c;
    uint8_t i;

    /* Initialize the counters. */
    memset(counter, 0, MAX_LEN * sizeof(uint32_t));

    /* Read each character from stdin. */
    do {
        c = fgetc(stdin);

        /* Count the number of 1's in each position. */
        switch(c) {
            case '\n':  bits = index;
                        index = 0;
                        lines++;
                        break;
            case '1':   counter[index]++;
            case '0':   index++;
                        break;
        }
    } while(c != EOF);

    /* Calculate Gamma and Epsilon using some bit manipulation magic. */
    uint16_t gamma = 0;
    uint16_t epsilon = 0;
    for(i = 0; i < bits; i++) {
        gamma = (gamma << 1) | (counter[i] >= lines >> 1);
        epsilon = (epsilon << 1) | (~gamma & 1);
    }

    printf("(DAY 03A) Gamma is: %u; Epsilon is: %u; Power consumption is: %u.\n", gamma, epsilon, gamma * epsilon);

    return 0;
}
