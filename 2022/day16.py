#!/usr/bin/env python3

import sys
import re
import functools

regex = re.compile(r"^Valve ([A-Z]{2}) has flow rate=(\d+); tunnels? leads? to valves? ((?:[\[A-Z]{2}, )*[A-Z]{2})$")

# Parse the input.
keys, world = {}, []
for i, (valve, rate, neighbors) in enumerate([(cg[0], int(cg[1]), [v.strip() for v in cg[2].split(",")]) for cg in [regex.match(l.strip()).groups() for l in sys.stdin]]):
    keys[valve] = i
    world.append((rate, neighbors))
for i in range(len(world)):
    world[i] = (world[i][0], sorted([keys[neighbor] for neighbor in world[i][1]]))


@functools.lru_cache(maxsize=None)
def release(time, elephant=False, open=0, valve=keys['AA']):
    """Recursive function to calculate the maximum possible released pressure."""
    if time <= 0:
        return release(26, False, open) if elephant else 0

    outcomes = []
    rate, neighbors = world[valve]
    for neighbor in neighbors:
        # Don't touch valve, move to a neighbor.
        outcomes.append(release(time-1, elephant, open, neighbor))
    if rate != 0 and (open & (1 << valve)) == 0:
        # Open valve and stay for this timestep.
        new_open = open | (1 << valve)
        outcomes.append(rate*(time-1) + release(time-1, elephant, new_open, valve))

    return max(outcomes)


print(f"(DAY 16A) At most {release(30)} pressure can be released")
# Note: Second part is really slow, it takes over a minute!
print(f"(DAY 16B) At most {release(26, elephant=True)} pressure can be released")
