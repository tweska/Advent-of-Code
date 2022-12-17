#!/usr/bin/env python3

import sys
import re

max_coord = 4000000  # Set to `20` for example input.
regex = re.compile(r"^Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+)$")


def merge(groups, a):
    start_a, end_a = a
    for i in range(len(groups)-1, -1, -1):
        start_b, end_b = groups[i]
        if start_a > end_b+1:
            groups.insert(i+1, (start_a, end_a))
            return groups
        if end_a < start_b-1:
            continue
        start_a = min(start_a, start_b)
        end_a = max(end_a, end_b)
        groups.pop(i)
    groups.insert(0, (start_a, end_a))
    return groups


not_beacons = [[] for _ in range(max_coord + 1)]
for sx, sy, bx, by in [[int(i) for i in regex.match(line.strip()).groups()] for line in sys.stdin]:
    dist = abs(bx-sx)+abs(by-sy)

    for y in range(max(sy-dist, 0), min(sy+dist, max_coord)+1):
        hdist = dist - abs(sy-y)
        start = max(sx - hdist, 0)
        end = min(sx + hdist, max_coord)
        merge(not_beacons[y], (start, end))

for y in range(len(not_beacons)):
    if len(not_beacons[y]) >= 2:
        print(f"(DAY 15B) Tuning frequency is {(not_beacons[y][0][1]+1)*4000000+y}")
        break
