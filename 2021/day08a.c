#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define MAX_BUF 1024

uint64_t count_unique(char *combination) {
    uint32_t len = strlen(combination);
    if (combination[len-1] == '\n') len--;  // Don't count the newline!

    /* Count digits '1', '4', '7' and '8'. These have unique segment counts! */
    if(len == 2 || len == 3 || len == 4 || len == 7) return 1;
    return 0;
}

int main() {
    char buf[MAX_BUF];
    uint64_t count = 0;

    /* Read each line from stdin. */
    while(fgets(buf, MAX_BUF, stdin) != NULL) {
        strtok(buf, "|");
        char *out = strtok(NULL, "|");

        /* Check each output digit. */
        char *tmp = strtok(out, " ");
        while(tmp != NULL) {
            count += count_unique(tmp);
            tmp = strtok(NULL, " ");
        }
    }

    printf("(DAY 08A) Digits '1', '4', '7' and '8' appear %lu times!\n", count);
    return 0;
}
