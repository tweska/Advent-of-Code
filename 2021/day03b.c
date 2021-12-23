#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_LEN 16

struct node {
    uint32_t count_zero, count_one;
    struct node *zero, *one;
};

/* Recursively allocate and initialize memory for the tree, bottom-up. */
struct node *init_tree(uint32_t depth) {
    struct node *root = malloc(sizeof(struct node));
    memset(root, 0, sizeof(struct node));

    if (depth > 1) {
        root->zero = init_tree(depth - 1);
        root->one = init_tree(depth - 1);
    }

    return root;
}

/* Recursively free the allocated memory for the tree, bottom-up. */
void free_tree(struct node *root) {
    if (root->zero != NULL) free_tree(root->zero);
    if (root->one != NULL) free_tree(root->one);
    free(root);
}

int main() {
    char c;
    uint8_t bits = 0;

    /* Count the length of the first bitstring. */
    do {
        c = fgetc(stdin);
        bits++;
    } while(c != '\n');
    bits--;
    rewind(stdin);

    /* Initialize the decision tree. */
    struct node *root = init_tree(bits);
    struct node *cur = root;

    /* Read each character from stdin. */
    do {
        c = fgetc(stdin);

        /* Add each bit by incrementing the right counter in the tree. */
        switch(c) {
            case '\n':  cur = root;
                        break;
            case '0':   cur->count_zero++;
                        cur = cur->zero;
                        break;
            case '1':   cur->count_one++;
                        cur = cur->one;
                        break;
        }
    } while(c != EOF);

    /* Find the oxygen generator rating. */
    uint16_t oxygen = 0;
    cur = root;
    while (cur != NULL) {
        if (cur->count_zero > cur->count_one) {
            cur = cur->zero;
            oxygen = (oxygen << 1);
        } else {
            cur = cur->one;
            oxygen = (oxygen << 1) | 1;
        }
    }

    /* Find the CO2 scrubber rating. */
    uint16_t co2 = 0;
    cur = root;
    while (cur != NULL) {
        if (-cur->count_zero >= -cur->count_one) {
            cur = cur->zero;
            co2 = (co2 << 1);
        } else {
            cur = cur->one;
            co2 = (co2 << 1) | 1;
        }
    }

    printf("(DAY 03B) Oxygen generator rating is: %u; CO2 scrubber rating is: %u; live support rating is: %u.\n", oxygen, co2, oxygen * co2);

    free_tree(root);
    return 0;
}
