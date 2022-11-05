#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_LEN 32

int main() {
    char buf[MAX_LEN];
    int32_t horizontal = 0;
    int32_t depth = 0;
    int32_t aim = 0;

    /* Read each line from stdin. */
    while(fgets(buf, MAX_LEN, stdin) != NULL) {
        /* Check the first character of the line to determine the instruction.
         * Note that each instruction has a unique first character! */
        int32_t tmp;
        switch(buf[0]) {
            case 'f':   tmp = atoi(&buf[8]);
                        horizontal += tmp;
                        depth += aim * tmp;
                        break;
            case 'd':   aim += atoi(&buf[5]);
                        break;
            case 'u':   aim -= atoi(&buf[3]);
                        break;
        }
    }

    printf("(DAY 02B) Horizontal position: %d; Depth: %d; Final answer: %d.\n", horizontal, depth, horizontal * depth);
    return 0;
}
