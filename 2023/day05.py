#!/usr/bin/env python3

# Note: part 2 is very slow and takes about 5 minutes to run.

import sys

input = sys.stdin.read().strip().split('\n\n')
seeds = [int(x) for x in input[0].replace('seeds: ', '').split(' ')]
maps = [[[int(x) for x in x.split(" ")] for x in input[i].splitlines()[1:]] for i in range(1, 8)]  # (dest, source, len)
rmaps = [[[source, dest, length] for dest, source, length in map] for map in reversed(maps)]  # (source, dest, len)


def x2y(x, map):
    for dest, source, length in map:
        offset = x - source
        if offset < 0 or offset >= length:
            continue
        return dest + offset
    return x


def contains(x):
    return any([start <= x < start + length for start, length in zip(seeds[::2], seeds[1::2])])


a = sys.maxsize
for n in seeds:
    for map in maps:
        n = x2y(n, map)
    a = min(a, n)

for b in range(sys.maxsize):
    x = b
    for rmap in rmaps:
        x = x2y(x, rmap)
    if contains(x):
        break

print(a, b)
