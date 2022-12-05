#!/usr/bin/env python3

import sys
import re
import copy

stacks = []

# Parse the initial state
for line in sys.stdin:
    stripped = line.strip()
    if len(stripped) > 0 and stripped[0] != '[':
        sys.stdin.readline()
        break

    for i, j in zip(range(0, len(line) // 4 + 1), range(1, len(line), 4)):
        if i > len(stacks) - 1:
            stacks.append([])
        if line[j] == ' ':
            continue
        stacks[i].append(line[j])

for stack in stacks:
    stack.reverse()

# Read move instructions
moves = [[int(d) for d in re.findall(r"\d+", line)] for line in sys.stdin]

# PartA
stacksA = copy.deepcopy(stacks)
for move in moves:
    for _ in range(move[0]):
        stacksA[move[2]-1].append(stacksA[move[1]-1].pop())
msgA = "".join([stack[-1] for stack in stacksA if len(stack) > 0])

# PartB
stacksB = copy.deepcopy(stacks)
for move in moves:
    items = []
    for _ in range(move[0]):
        items.append(stacksB[move[1]-1].pop())
    stacksB[move[2]-1] += reversed(items)
msgB = "".join([stack[-1] for stack in stacksB if len(stack) > 0])

print(f"(DAY 05A) Message is \"{msgA}\"")
print(f"(DAY 05B) Message is \"{msgB}\"")
