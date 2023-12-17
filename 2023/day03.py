#!/usr/bin/env python3

import sys

schematic = [[c for c in l.strip()] for l in sys.stdin]
adjacent = [[set() for _ in row] for row in schematic]

numbers = []
a_num_indices = []
b_num_indices = []
for y, row in enumerate(schematic):
    num = []
    for x, col in enumerate(row):
        if col.isdigit():
            num.append(col)
            for i in range(max(0, y-1), min(len(adjacent), y+2)):
                for j in range(max(0, x-1), min(len(adjacent[0]), x+2)):
                    adjacent[i][j].add(len(numbers))
        else:
            if len(num) > 0:
                numbers.append(int(''.join(num)))
                num = []
            if col != '.':
                if col == '*':
                    b_num_indices.append(adjacent[y][x])
                a_num_indices.append(adjacent[y][x])
    if len(num) > 0:
        numbers.append(int(''.join(num)))

a = sum([numbers[i] for i in set().union(*a_num_indices)])
b = sum([numbers[i[0]] * numbers[i[1]] for i in [tuple(i) for i in b_num_indices if len(i) == 2]])
print(a, b)
