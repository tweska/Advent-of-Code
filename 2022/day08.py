#!/usr/bin/env python3

import sys
import operator
from itertools import accumulate, takewhile, product


def visible_and_score(grid, x, y):
    tree  = grid[y][x]
    up    = list(reversed([grid[i][x] for i in range(0, y)]))
    down  = [grid[i][x] for i in range(y+1, len(grid))]
    left  = list(reversed([grid[y][i] for i in range(0, x)]))
    right = [grid[y][i] for i in range(x+1, len(grid[y]))]

    visible = 1 if tree > min([max(up), max(down), max(left), max(right)]) else 0
    score = list(accumulate([sum([1]+[1 for _ in takewhile(lambda h: h < tree, direction)]) for direction in [up[:-1], left[:-1], down[:-1], right[:-1]]], operator.mul))[-1]
    return visible, score


grid = [[int(c) for c in l.strip()] for l in sys.stdin]
coords = list(product(list(range(1, len(grid[0])-1)), list(range(1, len(grid)-1))))
visible, score = zip(*[visible_and_score(grid, x, y) for x, y in coords])

print(f"(DAY 08A) Visible trees: {sum(visible) + len(grid) * 2 + len(grid[0]) * 2 - 4}")
print(f"(DAY 08B) Highest score: {max(score)}")
