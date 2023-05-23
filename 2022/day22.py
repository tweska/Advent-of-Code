#!/usr/bin/env python3

import sys
import re


def parse_input(input):
    map, path = input.split('\n\n')

    open, solid = set(), set()
    for y, line in enumerate(map.split('\n')):
        for x, tile in enumerate(line):
            if tile == '.':
                open |= {(x, y)}
            elif tile == '#':
                solid |= {(x, y)}

    path = [int(dir) if dir[0].isdigit() else dir for dir in re.findall(f"(\d+|[LR])", path)]

    return open, solid, path


def irange(start, end):
    step = 1 if start <= end else -1
    return range(start, end + step, step)


OPEN, SOLID, PATH = parse_input(sys.stdin.read())
WIDTH = max(OPEN | SOLID, key=lambda x: x[0])[0] + 1
HEIGHT = max(OPEN | SOLID, key=lambda x: x[1])[1] + 1

COR2DIR = {(1, 0): '>', (-1, 0): '<', (0, 1): 'v', (0, -1): '^'}
DIR2COR = {'>': (1, 0), '<': (-1, 0), 'v': (0, 1), '^': (0, -1)}
REVERSE = {'>': '<', '<': '>', 'v': '^', '^': 'v'}

# Mapping for when you need to hop over an edge (second part).
# Note that this will not work with the example input, but it should work with
# any given large input since they are all the same shape.
# # Source: http://redd.it/zsgbe7 (See comment by /u/topaz2078)
SIMPLE_EDGE_MAPPING = [
    (((100,  49), (149,  49), 'v'), (( 99,  50), ( 99,  99), '<')),
    ((( 50,  99), ( 50,  50), '<'), (( 49, 100), (  0, 100), 'v')),
    ((( 50, 149), ( 99, 149), 'v'), (( 49, 150), ( 49, 199), '<')),
    ((( 50,   0), ( 99,   0), '^'), ((  0, 150), (  0, 199), '>')),
    (((100,   0), (149,   0), '^'), ((  0, 199), ( 49, 199), '^')),
    (((149,   0), (149,  49), '>'), (( 99, 149), ( 99, 100), '<')),
    ((( 50,   0), ( 50,  49), '<'), ((  0, 149), (  0, 100), '>')),
]

# Expand the simple edge mapping.
EDGE_MAPPING = {}
for (fa, ta, da), (fb, tb, db) in SIMPLE_EDGE_MAPPING:
    A = [(x, y) for x in irange(fa[0], ta[0]) for y in irange(fa[1], ta[1])]
    B = [(x, y) for x in irange(fb[0], tb[0]) for y in irange(fb[1], tb[1])]
    for (xa, ya), (xb, yb) in zip(A, B):
        EDGE_MAPPING[(xa, ya, da)] = (xb, yb, db)
        EDGE_MAPPING[(xb, yb, REVERSE[db])] = (xa, ya, REVERSE[da])  # Reverse


# For first part
def get_next_a(x, y, dx, dy, dist):
    if (x+dx, y+dy) not in OPEN | SOLID:
        for i in range(1, max(WIDTH, HEIGHT)):
            new_x, new_y = (x+dx*-i) % WIDTH, (y + dy * -i) % HEIGHT
            if (new_x-dx, new_y-dy) not in (OPEN | SOLID):
                if (new_x, new_y) in SOLID:
                    return x, y, dx, dy, 0
                return new_x, new_y, dx, dy, dist-1
    if (x+dx, y+dy) in SOLID:
        return x, y, dx, dy, 0
    return x+dx, y+dy, dx, dy, dist-1


# For second part
def get_next_b(x, y, dx, dy, dist):
    if (x+dx, y+dy) not in OPEN | SOLID:
        new_x, new_y, dxy = EDGE_MAPPING[(x, y, COR2DIR[(dx, dy)])]
        if (new_x, new_y) in SOLID:
            return x, y, dx, dy, 0
        dx, dy = DIR2COR[dxy]
        return new_x, new_y, dx, dy, dist-1

    if (x+dx, y+dy) in SOLID:
        return x, y, dx, dy, 0
    return x+dx, y+dy, dx, dy, dist-1


def walk(get_next):
    x, y = min(OPEN & {(x, 0) for x in range(WIDTH)}, key=lambda x: x[0])
    dx, dy = 1, 0

    for instr in PATH:
        if type(instr) == str:
            # Rotate
            if instr == 'L':
                dx, dy = dy, -dx
            elif instr == 'R':
                dx, dy = -dy, dx
            continue
        # Go straight instead
        dist = instr
        while dist > 0:
            x, y, dx, dy, dist = get_next(x, y, dx, dy, dist)

    facings = [(1, 0), (0, 1), (-1, 0), (0, -1)]
    return 1000 * (y+1) + 4 * (x+1) + facings.index((dx, dy))


print(f"(DAY 22A) The password is {walk(get_next_a)}")
print(f"(DAY 22B) The password is {walk(get_next_b)}")
