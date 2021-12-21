#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main() {
    char buf[8];
    uint32_t count = 0;
    uint32_t prev = 0;
    uint32_t cur;

    /* Read each line from stdin. */
    while(fgets(buf, 8, stdin) != NULL) {
        /* Convert the string to an integer. */
        cur = atoi(buf);

        if(prev != 0) {
            /* Count the number of times the value increased. */
            count += cur > prev;
        }

        /* Keep track of the current value to compare it later. */
        prev = cur;
    }

    printf("(DAY 01A) Value increased %u times!\n", count);
    return 0;
}
