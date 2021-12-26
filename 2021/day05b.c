#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 1024
#define MAX_SIZE 1000

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

        /* Calculate the increment step of x and y. */
        int32_t sx = ax == bx ? 0 : (ax < bx ? 1 : -1);
        int32_t sy = ay == by ? 0 : (ay < by ? 1 : -1);

        /* Increment the grid positons the line goes through and increment the
         * counter if and only if one line crossed through the position in the
         * past. */
        uint32_t x = ax;
        uint32_t y = ay;
        while(x != bx + sx || y != by + sy) {
            if(grid[x + y * MAX_SIZE]++ == 1) count++;

            x += sx;
            y += sy;
        }
    }

    printf("(DAY 05B) At least two lines overlap in %u points!\n", count);
    return 0;
}
