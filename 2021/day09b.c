#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define WORLD_SIZE 10000
#define MAX_BASINS 10000

void read_input_world(uint8_t **world, uint64_t *size, uint64_t *width) {
    char buf;
    *size = 0;
    *width = ~0;
    *world = (uint8_t *) malloc(sizeof(uint8_t) * WORLD_SIZE);

    while ((buf = fgetc(stdin)) != EOF) {
        if(buf == '\n') {
            if(*size < *width) *width = *size;
        } else {
            assert(*size < WORLD_SIZE);
            (*world)[(*size)++] = atoi(&buf);
        }
    }
}

/* Very simple sorting algorithm. */
void sort(uint64_t *list, uint64_t len) {
    uint64_t tmp;
    uint64_t i = 0;

    while (i < len-1) {
        if (list[i] >= list[i+1]) {
            i++;
            continue;
        }

        /* Swap... */
        tmp = list[i];
        list[i] = list[i+1];
        list[i+1] = tmp;

        if (i > 0) i--;
    }
}

/* Recursively explore a basin and marking already visited cells to avoid
 * counting the same basin twice. */
uint64_t explore(uint8_t *world, uint64_t w, uint64_t h, uint64_t x, uint64_t y) {
    /* Check if the coordinate is valid.
     * Note when using unsigned integers: -1 is just a very high number! */
    if (x >= w || y >= h) return 0;

    /* Check if this tile is not a border or already visited. */
    if (world[x + y * w] >= 9) return 0;

    /* Mark tile as visited. */
    world[x + y * w] = ~0;

    /* Return the result after exploring adjacent tiles. */
    return 1 + explore(world, w, h, x, y-1) + explore(world, w, h, x-1, y) + explore(world, w, h, x+1, y) + explore(world, w, h, x, y+1);
}

/* Explore all the basins and keep track of their size. */
uint64_t find_basins(uint8_t *world, uint64_t w, uint64_t h) {
    uint64_t basins[MAX_BASINS];
    uint64_t len = 0;

    for (int64_t y = 0; y < h; y++) {
        for (int64_t x = 0; x < w; x++) {
            uint64_t size = explore(world, w, h, x, y);
            if (size == 0) continue;
            basins[len++] = size;
        }
    }

    /* Find the 3 largest basins and multiply them. */
    sort(basins, len);
    return basins[0] * basins[1] * basins[2];
}

int main() {
    uint8_t *world;
    uint64_t size, width;

    /* Read the world from stdin! */
    read_input_world(&world, &size, &width);

    /* Find the basins by recursively exploring each unvisited cell. */
    uint64_t basins = find_basins(world, width, size/width);

    /* Free the world! */
    free(world);

    printf("(DAY 09B) Product of three largest basin sizes is: %lu!\n", basins);
    return 0;
}
