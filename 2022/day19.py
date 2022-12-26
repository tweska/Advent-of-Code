#!/usr/bin/env python3

# Note: This program has some optimizations, but it still takes over 3 minutes
#       to run!

import sys
import re
import functools

TIME = 24
REGEX = re.compile(r"^Blueprint (\d+): Each ore robot costs (\d+) ore. Each clay robot costs (\d+) ore. Each obsidian robot costs (\d+) ore and (\d+) clay. Each geode robot costs (\d+) ore and (\d+) obsidian.$")

# Read the input.
blueprints = []
for line in sys.stdin:
    data = [int(n) for n in REGEX.match(line.strip()).groups()]

    blueprints.append((data[0], [
        ((data[1], 0, 0, 0), (1, 0, 0, 0)),
        ((data[2], 0, 0, 0), (0, 1, 0, 0)),
        ((data[3], data[4], 0, 0), (0, 0, 1, 0)),
        ((data[5], 0, data[6], 0), (0, 0, 0, 1)),
    ]))


__blueprint = None


@functools.lru_cache(maxsize=None)
def __max_geodes(time, stockpile, reward):
    if time <= 0:
        return stockpile[3]

    max_cost = [max([__blueprint[1][i][0][j] for i in range(4)]) for j in range(3)]

    # Reduce the state by capping the stockpile to the max amount that can be spent.
    if any(stockpile[i] > max_cost[i]*time-reward[i]*(time-1) for i in range(3)):
        stockpile = tuple([min(stockpile[i], max_cost[i]*time-reward[i]*(time-1)) for i in range(3)] + [stockpile[3]])
        return __max_geodes(time, stockpile, reward)

    outcomes = [__max_geodes(time-1, tuple([stockpile[i]+reward[i] for i in range(4)]), reward)]
    for c, r in __blueprint[1]:
        if any(stockpile[i] < c[i] for i in range(3)):
            continue  # Not enough resources for this robot.
        if any(reward[i]+r[i] > max_cost[i] for i in range(3)):
            continue  # Can't possibly spend all the resources in the future.

        outcomes.append(__max_geodes(
            time-1,
            tuple([stockpile[i]+reward[i]-c[i] for i in range(4)]),
            tuple([reward[i]+r[i] for i in range(4)])
        ))
    return max(outcomes)


def max_geodes(blueprint, time=24, stockpile=(0, 0, 0, 0), reward=(1, 0, 0, 0)):
    global __blueprint
    __blueprint = blueprint
    __max_geodes.cache_clear()
    return __max_geodes(time, stockpile, reward)


# Part A
score = 0
for blueprint in blueprints:
    ql = max_geodes(blueprint)
    score += ql * blueprint[0]
print(f"(DAY 19A) Sum of quality levels is {score}")

# Part B
score = 1
for blueprint in blueprints[:3]:
    ql = max_geodes(blueprint, 32)
    score *= ql
print(f"(DAY 19B) Max number of geodes multiplied is {score}")
