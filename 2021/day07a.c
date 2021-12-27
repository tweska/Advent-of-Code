#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define MAX_BUF 4096
#define MAX_LEN 1024

uint64_t get_cost(uint32_t *crabs, uint32_t len, uint32_t target) {
    uint64_t cost = 0;
    for(uint32_t i = 0; i < len; i++) {
        cost += abs(target - crabs[i]);
    }
    return cost;
}

uint64_t get_avg(uint32_t *crabs, uint32_t len) {
    uint64_t sum = 0;
    for(uint32_t i = 0; i < len; i++) {
        sum += crabs[i];
    }
    return sum / len;
}

int main() {
    char buf[MAX_BUF];
    uint32_t crabs[MAX_LEN];

    /* Read one line from stdin. */
    assert(fgets(buf, MAX_BUF, stdin) != NULL);

    /* Initialize the array with the crabs positions. */
    uint32_t len = 0;
    char *tmp = strtok(buf, ",");
    while(tmp != NULL) {
        assert(len < MAX_LEN);
        crabs[len++] = atoi(tmp);
        tmp = strtok(NULL, ",");
    }

    /* Calculate the average position and calculate the cost of moving to the
     * average and surounding positions. */
    uint32_t avg = get_avg(crabs, len);
    uint64_t cost_avg = get_cost(crabs, len, avg);
    uint64_t cost_lft = get_cost(crabs, len, avg - 1);
    uint64_t cost_rgt = get_cost(crabs, len, avg + 1);

    /* Determine the search direction. */
    uint32_t dir = 1;
    uint32_t cur = avg + 1;
    uint64_t cur_cost = cost_rgt;
    uint64_t prev_cost = cost_avg;
    if (cost_lft < cost_avg) {
        dir = -1;
        cur = avg - 1;
        cur_cost = cost_lft;
    }

    /* Search for the optimal solution in the search direction until the
     * minimum is reached. */
    while(cur_cost < prev_cost) {
        printf("step!\n");
        cur += dir;
        prev_cost = cur_cost;
        cur_cost = get_cost(crabs, len, cur);
    }

    printf("(DAY 07A) Optimal position is %u and requires %lu fuel!\n", cur + -dir, prev_cost);

    return 0;
}
