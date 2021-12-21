#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_LEN 32

int main() {
    char buf[MAX_LEN];
    int32_t horizontal = 0;
    int32_t depth = 0;

    /* Read each line from stdin. */
    while(fgets(buf, MAX_LEN, stdin) != NULL) {
        /* Check the first character of the line to determine the instruction.
         * Note that each instruction has a unique firs character! */
        switch(buf[0]) {
            case 'f':   horizontal += atoi(&buf[8]);
                        break;
            case 'd':   depth += atoi(&buf[5]);
                        break;
            case 'u':   depth -= atoi(&buf[3]);
                        break;
        }
    }

    printf("(DAY 02A) Horizontal positon: %d; Depth: %d; Final answer: %d.\n", horizontal, depth, horizontal * depth);
    return 0;
}
