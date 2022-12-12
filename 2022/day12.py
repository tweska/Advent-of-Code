#!/usr/bin/env python3

import sys

grid = []
start, end = (0, 0), (0, 0)

# Parse the input.
for y, line in enumerate(sys.stdin):
    grid.append([])
    for x, char in enumerate(line.strip()):
        if char == "S":
            start = (x, y)
            char = "a"
        if char == "E":
            end = (x, y)
            char = "z"
        grid[y].append(ord(char) - ord("a"))

# Variation on Dijkstra's Algorithm to determine distance to top:
# https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
dist = [[(0 if (x, y) == end else sys.maxsize) for x in range(len(grid[y]))] for y in range(len(grid))]
queue = [(x, y) for x in range(len(grid[y])) for y in range(len(grid))]
while queue:
    queue.sort(key=lambda xy: (dist[xy[1]][xy[0]]))
    x, y = queue.pop(0)

    if y > 0 and grid[y][x] <= grid[y-1][x]+1:
        dist[y-1][x] = min(dist[y][x]+1, dist[y-1][x])
    if x > 0 and grid[y][x] <= grid[y][x-1]+1:
        dist[y][x-1] = min(dist[y][x]+1, dist[y][x-1])
    if x < len(grid[0])-1 and grid[y][x] <= grid[y][x+1]+1:
        dist[y][x+1] = min(dist[y][x]+1, dist[y][x+1])
    if y < len(grid)-1 and grid[y][x] <= grid[y+1][x]+1:
        dist[y+1][x] = min(dist[y][x]+1, dist[y+1][x])

# All trail lengths for second part.
trails = [dist[y][x] if grid[y][x] == 0 else sys.maxsize for x in range(len(grid[y])) for y in range(len(grid))]

print(f"(DAY 12A) Distance from S to E is {dist[start[1]][start[0]]}")
print(f"(DAY 12B) Minimum distance of trails is {min(trails)}")
