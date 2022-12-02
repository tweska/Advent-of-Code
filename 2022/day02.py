#!/usr/bin/env python3

import sys

# There is only 9 possibilities so just hardcode the choices!
score_table_a = {
    'A': {
        'X': 1 + 3,
        'Y': 2 + 6,
        'Z': 3 + 0,
    },
    'B': {
        'X': 1 + 0,
        'Y': 2 + 3,
        'Z': 3 + 6,
    },
    'C': {
        'X': 1 + 6,
        'Y': 2 + 0,
        'Z': 3 + 3,
    },
}

score_table_b = {
    'A': {
        'X': 3 + 0,
        'Y': 1 + 3,
        'Z': 2 + 6,
    },
    'B': {
        'X': 1 + 0,
        'Y': 2 + 3,
        'Z': 3 + 6,
    },
    'C': {
        'X': 2 + 0,
        'Y': 3 + 3,
        'Z': 1 + 6,
    },
}

score_a, score_b = 0, 0
for line in sys.stdin:
    elf, you = line[0], line[2]
    score_a += score_table_a[elf][you]
    score_b += score_table_b[elf][you]

print(f"(DAY 02A) Final score is {score_a}")
print(f"(DAY 02B) Final score is {score_b}")
