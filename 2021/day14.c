#include <stdio.h>
#include <string.h>

#define MAX_INPUT 32
#define MAX_PAIRS 128

typedef struct pair {
    char pair[2];
    char rule;
    size_t count;
} pair;

inline pair *find_pair(pair *pairs, size_t pairs_len, char str[2]) {
    for (size_t i = 0; i < pairs_len; i++) {
        if (strncmp(pairs[i].pair, str, 2) == 0) {
            return &pairs[i];
        }
    }
    return NULL;
}

void solution(char *template, pair *pairs, size_t pairs_len, size_t gens) {
    /* Make sure counters are all zero! */
    for (size_t i = 0; i < pairs_len; i++) {
        pairs[i].count = 0;
    }

    /* Initialize counters based on template. */
    for (size_t i = 0; i < strlen(template)-1; i++) {
        char str[2] = { template[i], template[i+1] };
        pair *p = find_pair(pairs, pairs_len, str);
        p->count++;
    }

    /* Calculate pair counts for the number of generations. */
    for (size_t gen = 0; gen < gens; gen++) {
        pair tmp_pairs[MAX_PAIRS*2];
        size_t tmp_pairs_len = 0;
        for (size_t i = 0; i < pairs_len; i++) {
            pair *p = &pairs[i];
            if (!p->count) { continue; }

            /* Determine the resulting new pairs. */
            char a[2] = { p->pair[0], p->rule };
            char b[2] = { p->rule, p->pair[1] };

            /* Use tmp pairs to avoid counting conflicts later on. */
            pair *p_a = &tmp_pairs[tmp_pairs_len++];
            pair *p_b = &tmp_pairs[tmp_pairs_len++];
            strncpy(p_a->pair, a, 2);
            strncpy(p_b->pair, b, 2);

            /* Update counts: two new pairs are spawned and all instances of
             * the original pair are replaced! */
            p_a->count = p->count;
            p_b->count = p->count;
            p->count = 0;
        }

        /* Merge the intermediate counts in tmp_pairs with the actual pairs. */
        for (size_t i = 0; i < tmp_pairs_len; i++) {
            pair *tmp_p = &tmp_pairs[i];
            pair *p = find_pair(pairs, pairs_len, tmp_p->pair);
            p->count += tmp_p->count;
        }
    }

    /* Count how often each character occurs by looking at the first character
     * of each pair. */
    size_t alphabet[26] = { 0 };
    for (size_t i = 0; i < pairs_len; i++) {
        alphabet[pairs[i].pair[0]-'A'] += pairs[i].count;
    }
    alphabet[template[strlen(template)-1]-'A'] += 1;  // Last char of template!

    /* Find the least and most common character. */
    size_t min = -1, max = 0;
    for (size_t i = 0; i < 26; i++) {
        if (!alphabet[i]) { continue; }  // Ignore char if it does not occur!
        if (alphabet[i] < min) { min = alphabet[i]; }
        if (alphabet[i] > max) { max = alphabet[i]; }
    }

    printf("%lu - %lu = %lu\n", max, min, max-min);
}


int main(void) {
    char buf[MAX_INPUT];
    char template[MAX_INPUT];
    pair pairs[MAX_PAIRS];

    /* Read the polymer template from stdin. */
    if (!fgets(template, sizeof(template)-1, stdin)) { return -1; }
    template[strlen(template)-1] = '\00';
    if (!fgets(buf, sizeof(buf)-1, stdin)) { return -1; }  // Ignore!

    /* Initialize pairs. */
    size_t pairs_len = 0;
    while (fgets(buf, sizeof(buf) - 1, stdin)) {
        pairs[pairs_len].pair[0] = buf[0];
        pairs[pairs_len].pair[1] = buf[1];
        pairs[pairs_len].rule    = buf[6];
        pairs_len++;
    }

    printf("(DAY 14A) ");
    solution(template, pairs, pairs_len, 10);

    printf("(DAY 14B) ");
    solution(template, pairs, pairs_len, 40);

    return 0;
}
