#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define WORLD_SIZE 10000

#define read_coord(world, w, x, y) (world[(x)+(y)*(w)])

void read_input_world(uint8_t **world, uint64_t *size, uint64_t *width) {
    char buf;
    *size = 0;
    *width = ~0;
    *world = (uint8_t *) malloc(sizeof(uint8_t) * WORLD_SIZE);

    while ((buf = fgetc(stdin)) != EOF) {
        if (buf == '\n') {
            if (*size < *width) *width = *size;
        } else {
            assert(*size < WORLD_SIZE);
            (*world)[(*size)++] = atoi(&buf);
        }
    }
}

/* Return the value of the point (x,y) plus one, if the value is lower than the
 * 3x3 surounding. */
uint8_t low_point(uint8_t *world, uint64_t w, uint64_t h, uint64_t x, uint64_t y) {
    uint8_t v = read_coord(world, w, x, y);  // Value at (x,y)

    if (y != 0) {
        if (x != 0 && read_coord(world, w, x-1, y-1) <= v) return 0;    // NW
        if (read_coord(world, w, x, y-1) <= v) return 0;                // N
        if (x != w-1 && read_coord(world, w, x+1, y-1) <= v) return 0;  // NE
    }
    if (x != 0 && read_coord(world, w, x-1, y) <= v) return 0;          // W
    if (x != w-1 && read_coord(world, w, x+1, y) <= v) return 0;        // E
    if (y != h-1) {
        if (x != 0 && read_coord(world, w, x-1, y+1) <= v) return 0;    // SW
        if (read_coord(world, w, x, y+1) <= v) return 0;                // S
        if (x != w-1 && read_coord(world, w, x+1, y+1) <= v) return 0;  // SE
    }

    return v + 1;  // All surounding values are higher!
}

uint64_t find_risk_level(uint8_t *world, uint64_t width, uint64_t height) {
    uint64_t risk = 0;

    for (uint64_t y = 0; y < height; y++) {
        for (uint64_t x = 0; x < width; x++) {
            risk += low_point(world, width, height, x, y);
        }
    }

    return risk;
}

int main() {
    uint8_t *world;
    uint64_t size, width;

    /* Read the world from stdin! */
    read_input_world(&world, &size, &width);

    /* Calculate the risk level. */
    uint64_t risk_level = find_risk_level(world, width, size/width);

    /* Free the world! */
    free(world);

    printf("(DAY 09A) Sum of the risk level is: %lu!\n", risk_level);
    return 0;
}
