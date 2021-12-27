#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 1024

/* The ring datastructure can store 9 values and keeps track of the head index
 * for relative lookups. */
struct ring{
    uint32_t head;
    uint64_t values[9];
};

/* Get the value of an index relative to the head index. */
uint64_t ring_get(struct ring *ring, uint32_t index) {
    return ring->values[(ring->head + index) % 9];
}

/* Return the head value before it was zeroed and increment the head index. */
uint64_t ring_pop(struct ring *ring) {
    uint64_t value = ring->values[ring->head];
    ring->values[ring->head] = 0;
    ring->head = (ring->head + 1) % 9;
    return value;
}

/* Increment the value at the index relative to the head pointer. */
void ring_inc(struct ring *ring, uint32_t index, uint64_t value) {
    ring->values[(ring->head + index) % 9] += value;
}

/* Return the sum of the contents of the entire ring. */
uint64_t ring_sum(struct ring *ring) {
    uint64_t sum = 0;
    for(uint32_t i = 0; i < 9; i++) {
        sum += ring->values[i];
    }
    return sum;
}

/* Do one timestep: Increment the value at (relative) position 6 and 8 with the
 * value popped from the head. */
void do_timestep(struct ring *ring) {
    uint64_t count = ring_pop(ring);
    ring_inc(ring, 6, count);
    ring_inc(ring, 8, count);
}

int main() {
    char buf[MAX_LEN];
    struct ring ring;
    memset(&ring, 0, sizeof(struct ring));

    /* Read one line from stdin. */
    assert(fgets(buf, MAX_LEN, stdin) != NULL);

    /* Initialize the ring. */
    char *tmp = strtok(buf, ",");
    while(tmp != NULL) {
        uint32_t value = atoi(tmp);
        ring_inc(&ring, value, 1);

        tmp = strtok(NULL, ",");
    }

    /* Run the simulation for 256 timesteps. */
    for(uint32_t t = 0; t < 256; t++) {
        do_timestep(&ring);

        if(t == 79) {
            uint64_t count = ring_sum(&ring);
            printf("(DAY 06A) There are %16lu lanternfish after  80 days!\n", count);
        }
    }

    uint64_t count = ring_sum(&ring);
    printf("(DAY 06B) There are %16lu lanternfish after 256 days!\n", count);

    return 0;
}
