#!/usr/bin/env python3

import sys

SIZE = 64

# Initialize the world: 1 is air, 0 is lava.
world = [[[1 for _ in range(SIZE)] for _ in range(SIZE)] for _ in range(SIZE)]
for x, y, z in [[int(c) for c in l.strip().split(',')] for l in sys.stdin]:
    world[x+1][y+1][z+1] = 0

# Part A
surface = 0
for x in range(1, SIZE-1):
    for y in range(1, SIZE-1):
        for z in range(1, SIZE-1):
            if world[x][y][z] != 0:
                continue  # Don't count the surface of air...
            # Surface of a single cube is number of exposed sides so just count
            # air (a 1) around the cube.
            surface += sum([world[x][y][z-1], world[x][y][z+1],
                            world[x][y-1][z], world[x][y+1][z],
                            world[x-1][y][z], world[x+1][y][z]])
print(f"(DAY 18A) The exposed surface size is {surface}")


# Part B
# Spawn water on all the world borders.
water = [[[1 if min(x, y, z) == 0 or max(x, y, z) == SIZE-1 else 0 for z in range(SIZE)] for y in range(SIZE)] for x in range(SIZE)]
changed = True
while changed:
    changed = False
    for x in range(1, SIZE-1):
        for y in range(1, SIZE-1):
            for z in range(1, SIZE-1):
                if water[x][y][z] == 1 or world[x][y][z] == 0:
                    continue  # Water is already water and obsidian shouldn't become water!
                if sum([water[x][y][z-1], water[x][y][z+1],
                        water[x][y-1][z], water[x][y+1][z],
                        water[x-1][y][z], water[x+1][y][z]]) > 0:
                    water[x][y][z] = 1  # Spread the water to this block.
                    changed = True

surface = 0
for x in range(1, SIZE-1):
    for y in range(1, SIZE-1):
        for z in range(1, SIZE-1):
            if world[x][y][z] != 0:
                continue  # Don't count the surface of air...
            # This time don't count air but the simulated water instead to
            # avoid counting the air trapped inside the droplets.
            surface += sum([water[x][y][z-1], water[x][y][z+1],
                            water[x][y-1][z], water[x][y+1][z],
                            water[x-1][y][z], water[x+1][y][z]])
print(f"(DAY 18B) The outside exposed surface size is {surface}")
