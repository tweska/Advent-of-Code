#!/usr/bin/env python3

import sys

rope = [(0, 0)] * 10
visited = { 1: [(0, 0)],
            9: [(0, 0)] }

for line in sys.stdin:
    dir, steps = line.strip().split(" ")
    for _ in range(int(steps)):
        if dir == "L":
            rope[0] = rope[0][0]-1, rope[0][1]
        if dir == "R":
            rope[0] = rope[0][0]+1, rope[0][1]
        if dir == "U":
            rope[0] = rope[0][0], rope[0][1]-1
        if dir == "D":
            rope[0] = rope[0][0], rope[0][1]+1

        for i in range(1, 10):
            dx, dy = rope[i-1][0]-rope[i][0], rope[i-1][1]-rope[i][1]

            if abs(dx) > 1 and abs(dy) > 1:
                rope[i] = rope[i][0]+(dx//2), rope[i][1]+(dy//2)
            elif abs(dx) > 1:
                rope[i] = rope[i][0]+(dx//2), rope[i][1]+dy
            elif abs(dy) > 1:
                rope[i] = rope[i][0]+dx, rope[i][1]+(dy//2)

            if i in visited.keys() and rope[i] not in visited[i]:
                visited[i].append(rope[i])

print(f"(DAY 09A) Tail visits {len(visited[1])} positions")
print(f"(DAY 09B) Tail visits {len(visited[9])} positions")
