#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define WIDTH 10
#define HEIGHT 10
#define STEPS 100

void read_grid(uint8_t *grid) {
    char buf;
    uint64_t index = 0;

    while ((buf = fgetc(stdin)) != EOF) {
        if (buf == '\n') continue;
        grid[index++] = atoi(&buf);
    }
}

void flash(uint8_t *grid, uint64_t x, uint64_t y);  // Is defined later...

/* Increment the energy level and trigger a flash if it reaches the threshold. */
void increment(uint8_t *grid, uint64_t x, uint64_t y) {
    if (x >= WIDTH || y >= HEIGHT) return;
    if (++grid[x + y * WIDTH] == 10) flash(grid, x, y);
}

/* Propagate energy to nearby octopuses. */
void flash(uint8_t *grid, uint64_t x, uint64_t y) {
    if (x >= WIDTH || y >= HEIGHT) return;

    increment(grid, x-1, y-1);  // NW
    increment(grid, x,   y-1);  // N
    increment(grid, x+1, y-1);  // NE
    increment(grid, x-1, y);    // W
    increment(grid, x+1, y);    // E
    increment(grid, x-1, y+1);  // SW
    increment(grid, x,   y+1);  // S
    increment(grid, x+1, y+1);  // SE
}

uint64_t step(uint8_t *grid) {
    /* Increase the energy level of each octopus, some will flash as a result! */
    for (uint64_t y = 0; y < HEIGHT; y++) {
        for (uint64_t x = 0; x < WIDTH; x++) {
            increment(grid, x, y);
        }
    }

    /* Count and reset each octopus that flashed! */
    uint64_t flashes = 0;
    for (uint64_t index = 0; index < WIDTH * HEIGHT; index++) {
        if (grid[index] > 9) {
            grid[index] = 0;
            flashes++;
        }
    }

    return flashes;
}

int main() {
    uint8_t grid[WIDTH * HEIGHT];
    read_grid(grid);

    uint64_t total_flashes = 0;
    uint64_t step_flashes = 0;
    uint64_t s = 0;
    for (s = 0; step_flashes != WIDTH * HEIGHT; s++) {
        step_flashes = step(grid);
        if (s < STEPS) total_flashes += step_flashes;
    }

    printf("(DAY 11A) Total flashes after %u steps: %lu!\n", STEPS, total_flashes);
    printf("(DAY 11B) Octopuses are synchronized after step: %lu!\n", s);
    return 0;
}
