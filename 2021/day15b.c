#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUF_LEN 1024
#define MULTIPLIER 5

typedef struct node {
    unsigned int dist;
    unsigned int risk;
    struct node *from;
    struct node *neighbors[4];
    struct node *next;
} node;

void node_push(node **head, node *new) {
    if (*head == NULL || (*head)->dist >= new->dist) {
        new->next = *head;
        *head = new;
        return;
    }

    node *cur = *head;
    while (cur->next != NULL && cur->next->dist < new->dist) {
        cur = cur->next;
    }
    new->next = cur->next;
    cur->next = new;
}

void node_repush(node **head, node *target) {
    node *cur = *head;
    while (cur->next != NULL) {
        if (cur->next == target) {
            cur->next = target->next;
            break;
        }
        cur = cur->next;
    }
    node_push(head, target);
}

node *node_pop(node **head) {
    node *n = *head;
    if (n == NULL || n->next == NULL) {
        *head = NULL;
        return n;
    }

    *head = n->next;
    return n;
}

bool contains(node **head, node *target) {
    node *cur = *head;
    while (cur) {
        if (cur == target) { return true; }
        if (cur == target) { return true; }
        cur = cur->next;
    }
    return false;
}

unsigned int get_risk(unsigned int *risk, size_t width, size_t height,
                             size_t x, size_t y) {
    return ((risk[(x % width) + (y % height) * width] + x/width + y/height - 1) % 9) + 1;
}

int main(void) {
    char buf[BUF_LEN];

    /* Find the width and height of the cave. */
    if (!fgets(buf, sizeof(buf)-1, stdin)) { return -1; }
    size_t width = strlen(buf)-1;
    fseek(stdin, 0L, SEEK_END);
    size_t height = ftell(stdin) / (width+1);
    rewind(stdin);

    /* Read risk levels into memory. */
    unsigned int *risk = malloc(width * height * sizeof(unsigned int));
    size_t end = 0;
    char tmp[2] = { 0 };
    while(fgets(buf, sizeof(buf)-1, stdin)) {
        for (size_t i = 0; i < width; i++) {
            tmp[0] = buf[i];
            risk[end++] = atoi(tmp);
        }
    }

    /* Initialize the graph. */
    node *graph = malloc(width * height * MULTIPLIER * MULTIPLIER * sizeof(node));
    memset(graph, 0, width * height * MULTIPLIER * MULTIPLIER * sizeof(node));
    node *head = NULL;
    for (size_t y = 0; y < height*MULTIPLIER; y++) {
        for (size_t x = 0; x < width*MULTIPLIER; x++) {
            node *cur = &graph[x+y*width*MULTIPLIER];
            cur->dist = (x == 0 && y == 0) ? 0 : -1;
            cur->risk = get_risk(risk, width, height, x, y);
            if (y > 0) { cur->neighbors[0] = &graph[x+(y-1)*width*MULTIPLIER]; }
            if (x > 0) { cur->neighbors[1] = &graph[x-1+y*width*MULTIPLIER]; }
            if (x < width*MULTIPLIER-1) { cur->neighbors[2] = &graph[x+1+y*width*MULTIPLIER]; }
            if (y < height*MULTIPLIER-1) { cur->neighbors[3] = &graph[x+(y+1)*width*MULTIPLIER]; }
            node_push(&head, cur);
        }
    }
    free(risk);


    /* Dijkstra's Algorithm:
     * https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm */
    node *target = &graph[width*height*MULTIPLIER*MULTIPLIER-1];
    node *cur;
    while ((cur = node_pop(&head))) {
        if (cur == target) { break; }
        for (size_t i = 0; i < 4; i++) {
            node *neighbor = cur->neighbors[i];
            if (neighbor == NULL) { continue; }
            if (!contains(&head, neighbor)) { continue; }
            size_t alt = cur->dist + neighbor->risk;
            if (alt < neighbor->dist) {
                neighbor->dist = alt;
                neighbor->from = cur;
                node_repush(&head, neighbor);
            }
        }
    }

    printf("(DAY 15B) Lowest total risk is: %u\n", graph[width*height*MULTIPLIER*MULTIPLIER-1].dist);

    free(graph);
    return 0;
}
