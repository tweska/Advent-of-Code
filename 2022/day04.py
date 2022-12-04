#!/usr/bin/env python3

import sys

sumA, sumB = 0, 0
for line in sys.stdin:
    r = [int(d) for d in line.replace('-', ',').split(',')]

    # Part A
    if (r[0] >= r[2] and r[1] <= r[3]) or (r[2] >= r[0] and r[3] <= r[1]):
        sumA += 1

    # Part B
    if (r[2] <= r[1] <= r[3]) or (r[0] <= r[3] <= r[1]):
        sumB += 1

print(f"(DAY 04A) Number of pairs that fully overlap is {sumA}")
print(f"(DAY 04B) Number of pairs that partially overlap is {sumB}")
