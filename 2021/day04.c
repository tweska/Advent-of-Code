#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 1024
#define MAX_DRAWS 128
#define MAX_CARDS 128

/* Representation of a bingo card in memory. */
struct bingo_card {
    uint32_t numbers[25];
    uint8_t drawn[25];
    uint8_t won;
};

/* Allocate memory for a new bingo card and zero it. */
struct bingo_card *init_bingo_card() {
    struct bingo_card *card = malloc(sizeof(struct bingo_card));
    memset(card, 0, sizeof(struct bingo_card));
    return card;
}

/* Check the score of a bingo card, but optimized for usage during the drawing
 * process. First we check if this card has already won, then we can skip it.
 * Second the given row and column will be checked, if not all numbers are
 * drawn in the row or column then the score is 0. Otherwise we calculate the
 * sum of the unmarked numbers. */
uint32_t check_score(struct bingo_card *card, uint32_t row, uint32_t col) {
    /* Early return if this card has already won. */
    if (card->won != 0) return 0;

    /* Check if all numbers are drawn in the row or column. */
    uint32_t i, j;
    for (i = 0; i < 5; i++)
        if (card->drawn[row * 5 + i] == 0) break;
    for (j = 0; j < 5; j++)
        if (card->drawn[j * 5 + col] == 0) break;
    if (i != 5 && j != 5) return 0;

    /* Keep track of the just drawn number. */
    uint32_t number = card->numbers[row * 5 + col];

    /* If the column or row is marked the intermediate score shall be
     * calculated. */
    uint32_t sum = 0;
    for(row = 0; row < 5; row++) {
        for(col = 0; col < 5; col++) {
            if (card->drawn[row * 5 + col] != 0) continue;
            sum += card->numbers[row * 5 + col];
        }
    }

    /* Update the won status of the card and return the score. */
    card->won = sum > 0;
    return sum * number;
}

/* Draw a number on the given bingo card. Returns the score of this card after
 * the draw. */
uint32_t draw_number(struct bingo_card *card, uint32_t number) {
    for(uint32_t row = 0; row < 5; row++) {
        for(uint32_t col = 0; col < 5; col++) {
            if (card->numbers[row * 5 + col] != number) continue;

            /* Found the number on the bingo card, return the score. */
            card->drawn[row * 5 + col] = 1;
            return check_score(card, row, col);
        }
    }

    return 0;
}

int main() {
    char buf[MAX_LEN];
    uint32_t draws[MAX_DRAWS];
    uint32_t len = 0;
    struct bingo_card *cards[MAX_CARDS];
    uint32_t num = 0;

    /* Read the first line, it contains the numbers that are drawn at random. */
    assert(fgets(buf, MAX_LEN, stdin) != NULL);

    /* Convert the first line into an array. */
    {
        char *number = strtok(buf, ",");
        while(number != NULL) {
            assert(len < MAX_DRAWS);
            draws[len++] = atoi(number);
            number = strtok(NULL, ",");
        }
    }


    /* Read all the bingo cards. */
    while(fgets(buf, MAX_LEN, stdin) != NULL) {
        assert(buf[0] == '\n');
        assert(num < MAX_CARDS);

        /* Initialize a new (blank) bingo card. */
        cards[num++] = init_bingo_card();

        /* Walk through the bingo card. Each row is one line and between each
         * column is a space. */
        for(uint32_t row = 0; row < 5; row++) {
            assert(fgets(buf, MAX_LEN, stdin) != NULL);
            char *number = strtok(buf, " ");
            for(uint32_t col = 0; col < 5; col++) {
                assert(number != NULL);

                /* Convert the string representation of this cell to an int. */
                cards[num - 1]->numbers[row * 5 + col] = atoi(number);

                number = strtok(NULL, " ");
            }
        }
    }

    /* Draw the numbers until the first BINGO is called! */
    uint32_t score = 0;
    uint8_t first = 0;
    for(uint32_t i = 0; i < len; i++) {
        uint32_t number = draws[i];
        for (uint32_t j = 0; j < num; j++) {
            uint32_t tmp = draw_number(cards[j], number);
            if (tmp > 0) score = tmp;
        }
        if (score > 0 && first == 0) {
            printf("(DAY 04A) First BINGO score is: %u\n", score);
            first = 1;
        }
    }

    printf("(DAY 04B) Last  BINGO score is: %u\n", score);

    for(uint32_t k = 0; k < num; k++) free(cards[k]);
    return 0;
}
