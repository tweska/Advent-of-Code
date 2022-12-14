#!/usr/bin/env python3

import os
import sys


def world_bounds(world):
    minx = min(world.keys(), key=lambda c: c[0])[0]
    maxx = max(world.keys(), key=lambda c: c[0])[0]
    miny = min(world.keys(), key=lambda c: c[1])[1]
    maxy = max(world.keys(), key=lambda c: c[1])[1]
    return minx, maxx, miny, maxy


def print_world(world, partB=True):
    """Print the world, useful for debugging!"""
    minx, maxx, miny, maxy = world_bounds(world)

    for y in range(miny, maxy+1):
        for x in range(minx, maxx+1):
            if (x, y) in world:
                print(world[(x, y)], end="")
            else:
                print(".", end="")
        print()

    if partB:
        for x in range(minx, maxx+1):
            print("#", end="")
        print()


def sign(x):
    return -1 if x < 0 else 1


# Read the input.
world = {(500, 0): "+"}
for line in sys.stdin:
    coords = [(int(x), int(y)) for x, y in [coord.split(",") for coord in line.strip().split(" -> ")]]
    for (ax, ay), (bx, by) in zip(coords, coords[1:]):
        dx, dy = bx-ax, by-ay
        for y in range(ay, ay+dy+sign(dy), sign(dy)):
            for x in range(ax, ax+dx+sign(dx), sign(dx)):
                world[(x, y)] = "#"


# Simulate the sand.
_, _, _, maxy = world_bounds(world)
i, limitA, limitB = -1, -1, -1
while True:
    x, y = 500, 0
    i = i + 1

    if world[(x, y)] == "O":
        limitB = i
        break
    while True:
        if limitA < 0 and y > maxy:
            limitA = i

        if y == maxy+1:
            world[(x, y)] = "O"
            break
        elif (x, y+1) not in world:
            y = y+1
        elif (x-1, y+1) not in world:
            x, y = x-1, y+1
        elif (x+1, y+1) not in world:
            x, y = x+1, y+1
        else:
            world[(x, y)] = "O"
            break

# Only print if it fits in the terminal.
minx, maxx, _, _ = world_bounds(world)
if maxx-minx < os.get_terminal_size().columns:
    print_world(world)

print(f"(DAY 14A) {limitA} units flow before they fall into the void")
print(f"(DAY 14B) {limitB} units flow before the source is blocked")
