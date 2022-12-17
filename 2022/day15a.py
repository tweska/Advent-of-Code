#!/usr/bin/env python3

import sys
import re

y_row = 2000000  # Set to `10` for example input.
regex = re.compile(r"^Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+)$")

beacons, not_beacons = set([]), set([])
for sx, sy, bx, by in [[int(i) for i in regex.match(line.strip()).groups()] for line in sys.stdin]:
    dist = abs(bx-sx)+abs(by-sy)
    if not (sy-dist <= y_row <= sy+dist):
        continue

    if by == y_row:
        beacons.add(bx)

    hdist = abs(dist-abs(y_row-sy))
    for x in range(sx-hdist, sx+hdist+1):
        not_beacons.add(x)

print(f"(DAY 15A) {len(not_beacons.difference(beacons))} positions cannot contain a beacon")
