#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main() {
    char buf[8];
    uint32_t count = 0;
    uint32_t sum[4] = {0, 0, 0, 0};
    uint32_t cur;

    /* Read each line from stdin. */
    for(uint32_t iter = 0; fgets(buf, 8, stdin) != NULL; iter++) {
        /* Convert the string to an integer. */
        cur = atoi(buf);

        /* Keep track of the current value to compare it later. */
        for(uint8_t i = 0; i < 4; i++) {
            if (i > iter) break;  // Skip check for the second 3 values.
            if (i == (iter + 1) % 4) continue;  // Always skip one inbetween.
            sum[i] += cur;
        }

        /* Skip counting for the first 3 values. */
        if(iter < 3) continue;

        /* Count the number of times the (summed) value increased. */
        count += sum[(iter + 2) % 4] > sum[(iter + 1) % 4];

        /* Reset the oldest sum. */
        sum[(iter + 1) % 4] = 0;
    }

    printf("(DAY 01B) Value increased %u times!\n", count);
    return 0;
}
