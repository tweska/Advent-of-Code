#!/usr/bin/env python3

import sys


def fingerprint(solid):
    fp = [-1] * 7
    for (x, y) in solid:
        fp[x] = max(fp[x], y)
    return tuple(-y+max(fp) for y in fp)


# Jets converted into delta on x-axis.
jets = [1 if dir == '>' else -1 for dir in sys.stdin.read().strip()]

# Rock shapes as sets of (x, y) positions.
rocks = [
    {(0, 0), (1, 0), (2, 0), (3, 0)},
    {(1, 2), (0, 1), (1, 1), (2, 1), (1, 0)},
    {(2, 2), (2, 1), (0, 0), (1, 0), (2, 0)},
    {(0, 3), (0, 2), (0, 1), (0, 0)},
    {(0, 1), (1, 1), (0, 0), (1, 0)},
]

# State at the start, just a solid floor.
solid = {(x, -1) for x in range(7)}

seen = {}

height = 0
rock_count = 0
rock = {(x+2, y+3) for (x, y) in rocks[rock_count]}
jet_index = -1
while True:
    jet_index = (jet_index + 1) % len(jets)
    jet = jets[jet_index]
    moved = {(x+jet, y) for (x, y) in rock}
    if all(0 <= x < 7 for (x, y) in moved) and not (moved & solid):
        rock = moved  # Move is legal!
    moved = {(x, y-1) for (x, y) in rock}
    if moved & solid:  # moved and solid intersect
        solid |= rock
        height = max(y for (_, y) in solid) + 1
        rock_count += 1
        if rock_count == 2022:
            print(f"(DAY 17A) The tower will be {height} units tall after 2022 rocks have stopped falling.")
        if rock_count >= 1000000000000:
            break

        # Grab a new rock for the next iteration.
        rock = {(x+2, y+height+3) for (x, y) in rocks[rock_count % len(rocks)]}

        if rock_count < 2022:
            continue  # Skip cycle detection for now...

        # Generate key used to store and retrieve cycle data.
        key = (jet_index, rock_count % 5, fingerprint(solid))
        if key in seen:
            # Assume a cycle is detected, skip forward to the end.
            prev_rock_count, prev_height = seen[key]
            cycles = (1000000000000 - rock_count) // (rock_count - prev_rock_count)
            offset = cycles * (height - prev_height)
            rock_count += cycles * (rock_count - prev_rock_count)
            seen = {}
        seen[key] = (rock_count, height)
    else:
        rock = moved

print(f"(DAY 17B) The tower will be {height+offset} units tall after a trillion rocks have stopped falling.")
