#!/usr/bin/env python3

import sys
from collections import Counter

DIRECTIONS = ['N', 'S', 'W', 'E']


def read_input():
    map = []
    for y, line in enumerate(sys.stdin.read().split('\n')):
        for x, tile in enumerate(line):
            if tile == '#':
                map.append((x, y))
    return map


def solve(map, partB=False):
    n = 0
    while n == 0 or moved:
        # Check next move
        mapset = set(map)  # Checking if something is in a set is much faster!
        next = [None] * len(map)
        for j, (x, y) in enumerate(map):
            if all([(x+dx, y+dy) not in mapset or dx == 0 == dy for dx in [-1, 0, 1] for dy in [-1, 0, 1]]):
                pass
            else:
                for k in range(4):
                    dir = DIRECTIONS[(n+k) % 4]
                    if dir == 'N' and all([(x+dx, y-1) not in mapset for dx in [-1, 0, 1]]):
                        next[j] = (x, y-1)  # North
                    elif dir == 'S' and all([(x+dx, y+1) not in mapset for dx in [-1, 0, 1]]):
                        next[j] = (x, y+1)  # South
                    elif dir == 'W' and all([(x-1, y+dy) not in mapset for dy in [-1, 0, 1]]):
                        next[j] = (x-1, y)  # West
                    elif dir == 'E' and all([(x+1, y+dy) not in mapset for dy in [-1, 0, 1]]):
                        next[j] = (x+1, y)  # East
                    else:
                        continue  # Keep checking until you find one or all directions are checked.
                    break

        # Determine final move
        counts = Counter(next)
        moved = False
        for j, pos in enumerate(next):
            if pos != None and counts[pos] == 1:
                map[j] = pos
                moved = True

        n += 1
        if not partB and n == 10:
            return n, map
    return n, map


def print_map(map):
    minx = min(map, key=lambda p: p[0])[0]
    maxx = max(map, key=lambda p: p[0])[0]
    miny = min(map, key=lambda p: p[1])[1]
    maxy = max(map, key=lambda p: p[1])[1]

    for y in range(miny, maxy+1):
        for x in range(minx, maxx+1):
            if (x, y) in map:
                print('#', end='')
            else:
                print('.', end='')
        print()


original_map = read_input()

_, map = solve(original_map[:])

minx = min(map, key=lambda p: p[0])[0]
maxx = max(map, key=lambda p: p[0])[0]
miny = min(map, key=lambda p: p[1])[1]
maxy = max(map, key=lambda p: p[1])[1]

empty_tiles = (maxx-minx+1) * (maxy-miny+1) - len(map)
print(f"(DAY 23A) Number of empty ground tiles is {empty_tiles}")

n, _ = solve(original_map, partB=True)
print(f"(DAY 23B) The first round where no elf moved is {n}")
