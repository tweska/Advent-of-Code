#!/usr/bin/env python3

import sys

lines = [l for l in sys.stdin]
score = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"[i]: i+1 for i in range(0, 52)}

# Part A
sumA = 0
for line in lines:
    stripped = line.strip()
    a, b = stripped[:int(len(stripped)/2)], stripped[int(len(stripped)/2):]
    for item in a:
        if item in a and item in b:
            sumA += score[item]
            break

# Part B
sumB = 0
for i in range(0, len(lines), 3):
    a, b, c = lines[i].strip(), lines[i+1].strip(), lines[i+2].strip()
    for item in a:
        if item in a and item in b and item in c:
            sumB += score[item]
            break

print(f"(DAY 03A) Sum of priorities is {sumA}")
print(f"(DAY 03B) Sum of priorities is {sumB}")
