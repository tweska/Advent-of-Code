#!/usr/bin/env python3

import sys

LIT  = "#"
DARK = " "  # Space is more readable than a dot!

# Read and execute instructions.
reg_x = [1]
for line in sys.stdin:
    reg_x.append(reg_x[-1])
    if line.strip().split(" ")[0] == "addx":
        reg_x.append(reg_x[-1] + int(line.strip().split(" ")[1]))

# PartA
signal_strength_sum = sum([reg_x[cycle-1]*cycle for cycle in range(20, 221, 40)])
print(f"(DAY 10A) Sum of six signal strengths is {signal_strength_sum}")

# PartB
print("(DAY 10B) CRT screen:")
for y in range(6):
    for x in range(0, 40):
        print(LIT, end="") if reg_x[x+40*y] in [x-1, x, x+1] else print(DARK, end="")
    print()
