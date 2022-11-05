#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_BUF 1024
#define LEN_NAME 16

typedef struct cave cave;
typedef struct map map;

struct cave {
    char name[LEN_NAME];
    bool small;
    size_t visits;

    size_t neighbor_count;
    cave **neighbors;
};

struct map {
    size_t count;
    cave **caves;
};

cave *alloc_cave(char *name) {
    cave *c = malloc(sizeof(cave));
    assert(c != NULL);

    memset(c, 0, sizeof(cave));
    strcpy(c->name, name);

    if (islower(*c->name)) {
        c->small = true;
    }

    return c;
}

void free_caves(map *m) {
    while (m->count-- != 0) {
        free(m->caves[m->count]->neighbors);
        free(m->caves[m->count]);
    }
    free(m->caves);
}

cave *find_cave(char *name, map *m) {
    for (size_t i = 0; i < m->count; i++) {
        if (strcmp(m->caves[i]->name, name) == 0) {
            return m->caves[i];
        }
    }

    m->caves = realloc(m->caves, (m->count+1) * sizeof(cave*));
    assert(m->caves != NULL);
    cave *c = alloc_cave(name);
    assert(c != NULL);
    m->caves[m->count++] = c;
    return c;
}

void add_neighbors(cave *a, cave *b) {
    a->neighbors = realloc(a->neighbors, (a->neighbor_count+1) * sizeof(cave*));
    b->neighbors = realloc(b->neighbors, (b->neighbor_count+1) * sizeof(cave*));
    assert(a->neighbors != NULL);
    assert(b->neighbors != NULL);

    a->neighbors[a->neighbor_count++] = b;
    b->neighbors[b->neighbor_count++] = a;
}

void read_map(map *m) {
    char buf[MAX_BUF];

    /* Read each line from stdin. */
    while(fgets(buf, MAX_BUF, stdin)) {
        char *name_a = strtok(buf, "-");
        char *name_b = strtok(NULL, "\n");

        cave *a = find_cave(name_a, m);
        cave *b = find_cave(name_b, m);

        add_neighbors(a, b);
    }
}

size_t find_paths(cave *c, size_t max_visits) {
    /* Path ends when you reach "end". */
    if (strcmp(c->name, "end") == 0) {
        return 1;
    }

    /* Path may not pass through "start" twice. */
    if (strcmp(c->name, "start") == 0 && c->visits > 0) {
        return 0;
    }

    /* Limit number of passes through small cave. */
    if (c->small && c->visits >= max_visits) {
        return 0;
    }

    c->visits++;

    /* Adjust limit on number of passes through small caves. */
    if (c->small && max_visits > 1 && c->visits >= max_visits) {
        max_visits--;
    }

    /* Try all different paths. */
    size_t sum = 0;
    for (size_t i = 0; i < c->neighbor_count; i++) {
        assert(c->neighbors[i] != NULL);
        sum += find_paths(c->neighbors[i], max_visits);
    }

    c->visits--;  // Reset!
    return sum;
}

int main(void) {
    map m = {
        .count = 0,
        .caves = NULL
    };
    read_map(&m);

    cave *start = find_cave("start", &m);

    printf("(DAY 12A) Number of paths: %lu\n", find_paths(start, 1));
    printf("(DAY 12B) Number of paths: %lu\n", find_paths(start, 2));

    free_caves(&m);
    return 0;
}
