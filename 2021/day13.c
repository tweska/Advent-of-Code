#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct position {
    int x, y;
} position;

typedef struct fold {
    char dir;
    int off;
} fold;

typedef struct context {
    size_t p_count;
    position *p;

    size_t f_count;
    fold *f;

    size_t folded;
} context;

void free_context(context *c) {
    free(c->p);
    free(c->f);
    free(c);
}

context *parse_input() {
    char buf[256];

    context *c = malloc(sizeof(context));
    assert(c != NULL);
    memset(c, 0, sizeof(context));

    /* Read the coordinates of the dots. */
    while (fgets(buf, sizeof(buf), stdin)) {
        if (strcmp(buf, "\n") == 0) { break; }

        int x = atoi(strtok(buf, ","));
        int y = atoi(strtok(NULL, "\n"));

        c->p = realloc(c->p, (++c->p_count) * sizeof(position));
        c->p[c->p_count-1].x = x;
        c->p[c->p_count-1].y = y;
    }

    /* Read the folding instructions. */
    while (fgets(buf, sizeof(buf), stdin)) {
        char *dir = &buf[11];
        char *off = &buf[13];

        c->f = realloc(c->f, (++c->f_count) * sizeof(fold));
        c->f[c->f_count-1].dir = *dir;
        c->f[c->f_count-1].off = atoi(off);
    }

    return c;
}

void do_fold(context *c) {
    fold *f = &c->f[c->folded++];

    if (f->dir == 'x') {
        for (size_t i = 0; i < c->p_count; i++) {
            position *p = &c->p[i];
            if (p->x > f->off) {
                p->x = f->off - (p->x - f->off);
            }
        }
    } else {
        for (size_t i = 0; i < c->p_count; i++) {
            position *p = &c->p[i];
            if (p->y > f->off) {
                p->y = f->off - (p->y - f->off);
            }
        }
    }
}

int count_unique(context *c) {
    int count = c->p_count;
    for (size_t i = 0; i < c->p_count; i++) {
        position *a = &c->p[i];
        /* Look ahead to check if position will be encountered later on. */
        for(size_t j = i+1; j < c->p_count; j++) {
            position *b = &c->p[j];
            if (a->x == b->x && a->y == b->y) {
                count--;
                break;
            }
        }
    }
    return count;
}

void print_sheet(context *c) {
    /* Initialize the canvas. */
    const int w = 39, h = 6;
    char canvas[(w+1)*h+1];
    memset(&canvas, ' ', (w+1)*h);
    for (size_t i = w; i < (w+1)*h; i += w+1) {
        canvas[i] = '\n';
    }
    canvas[(w+1)*h] = '\00';

    /* Write each 'dot' to the canvas. */
    for (size_t i = 0; i < c->p_count; i++) {
        position *p = &c->p[i];
        canvas[p->x + (w+1)*p->y] = '#';
    }

    printf("%s", canvas);
}


int main(void) {
    context *c = parse_input();

    do_fold(c);
    int first = count_unique(c);

    while (c->folded != c->f_count) {
        do_fold(c);
    }

    printf("(DAY 13A) Number of dots after first fold: %d\n", first);
    printf("(DAY 13B) Code after last fold:\n");
    print_sheet(c);

    free(c);
    return(0);
}
