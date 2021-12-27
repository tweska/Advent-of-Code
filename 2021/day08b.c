#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define MAX_BUF 1024

/* Check if all characters from subset occur in superset. */
int is_subset_of(char *subset, uint32_t subset_len, char* superset, uint32_t superset_len) {
    uint32_t match = 0;
    for(uint32_t i = 0; i < subset_len; i++) {
        for(uint32_t j = 0; j < superset_len; j++) {
            if(subset[i] == superset[j]) {
                match++;
                break;
            }
        }
        if(i + 1 != match) return 0;  // Atleast one subset char not in superset!
    }
    return 1;
}

/* Metadata needed for decoding. */
struct code_meta {
    char bc[2];  // Characters in a one.
    char fg[2];  // Characters in a four minus characters in a one (b&c).
};

struct code_meta *extract_meta(char *buf) {
    char one[2];
    char four[4];
    char four_minus_one[2];

    /* Find segments representing '1' and '4' first. */
    char *tmp = strtok(buf, " ");
    for(uint32_t i = 0; i < 10; i++) {
        uint32_t len = strlen(tmp);
        if (tmp[len-1] == '\n') len--;  // Don't count the newline!

        if(len == 2) memcpy(one, tmp, 2);
        if(len == 4) memcpy(four, tmp, 4);

        tmp = strtok(NULL, " ");
    }

    /* Get the two characters that are in four but not in one. */
    uint32_t k = 0;
    for(uint32_t j = 0; j < 4; j++) {
        if(four[j] != one[0] && four[j] != one[1]) four_minus_one[k++] = four[j];
        if(k >= 2) break;
    }

    /* Allocate and initialize the metadata struct. */
    struct code_meta *meta = malloc(sizeof(struct code_meta));
    memcpy(meta->bc, one, 2);
    memcpy(meta->fg, four_minus_one, 2);
    return meta;
}

uint8_t decode(struct code_meta *meta, char *combination) {
    uint32_t len = strlen(combination);
    if (combination[len-1] == '\n') len--;  // Don't count the newline!

    assert(len >= 2 && len <= 7);

    /* Early return on the digits that have a unique segment count. */
    if(len == 2) return 1;
    if(len == 4) return 4;
    if(len == 3) return 7;
    if(len == 7) return 8;

    if(len == 5) {
        if(is_subset_of(meta->bc, 2, combination, len)) {
            return 3;  // Segments b&c are subset of 3!
        } else if(is_subset_of(meta->fg, 2, combination, len)) {
            return 5;  // Segments f&g are subset of 5!
        }
        return 2;  // Both segments b&c and f&g are not a subset of 2!
    }

    /* Length is 6! */
    if(is_subset_of(meta->bc, 2, combination, len)) {
        /* Segments b&c are subset of both 0 and 9 but not 6! */
        if(is_subset_of(meta->fg, 2, combination, len)) {
            return 9;  // Segments f&g is a subset of 9!
        }
        return 0;  // Segments f&g is not a subset of 0!
    }
    return 6;  // Segments b&c are not a subset of 6.
}

int main() {
    char buf[MAX_BUF];
    uint64_t count = 0;

    /* Read each line from stdin. */
    while(fgets(buf, MAX_BUF, stdin) != NULL) {
        char *pat = strtok(buf, "|");
        char *out = strtok(NULL, "|");

        /* Get the necesairy metadata for decocding. */
        struct code_meta *meta = extract_meta(pat);

        /* Check each output digit. */
        uint64_t inter = 0;
        char *tmp = strtok(out, " ");
        while(tmp != NULL) {
            inter = inter * 10 + decode(meta, tmp);
            tmp = strtok(NULL, " ");
        }
        count += inter;

        free(meta);
    }

    printf("(DAY 08B) The sum of all the segments is %lu!\n", count);
    return 0;
}
