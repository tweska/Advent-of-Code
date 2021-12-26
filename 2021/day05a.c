#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 1024
#define MAX_SIZE 1000

/* GNU MIN/MAX macros. */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int main() {
    char buf[MAX_LEN];
    uint32_t grid[MAX_SIZE * MAX_SIZE];
    uint32_t count = 0;

    /* Zero out the grid before we start. */
    memset(grid, 0, sizeof(grid));

    /* Read every input line. */
    while(fgets(buf, MAX_LEN, stdin) != NULL) {
        /* Extract both positions from the string.  {a} -> {b} */
        char *tmpa = strtok(buf, " -> ");
        char *tmpb = strtok(NULL, " -> ");

        /* Extract the x and y of both positions.  {x},{y} */
        uint32_t ax = atoi(strtok(tmpa, ","));
        uint32_t ay = atoi(strtok(NULL, ","));
        uint32_t bx = atoi(strtok(tmpb, ","));
        uint32_t by = atoi(strtok(NULL, ","));

        assert(ax < MAX_SIZE && ay < MAX_SIZE && bx < MAX_SIZE && by < MAX_SIZE);

        /* Increment the grid positons the line goes through and increment the
         * counter if and only if one line crossed through the position in the
         * past. */
        if(ax == bx) {
            for(uint32_t y = MIN(ay, by); y <= MAX(ay, by); y++) {
                if(grid[ax + y * MAX_SIZE]++ == 1) count++;
            }
        } else if(ay == by) {
            for(uint32_t x = MIN(ax, bx); x <= MAX(ax, bx); x++) {
                if(grid[x + ay * MAX_SIZE]++ == 1) count++;
            }
        }
    }

    printf("(DAY 05A) At least two lines overlap in %u points!\n", count);
    return 0;
}
