#!/usr/bin/env python3

import sys

# Put the number of calories per elf in a list.
calories = [0]
for line in sys.stdin:
    stripped_line = line.strip()
    if stripped_line == "":
        calories.append(0)
    else:
        calories[-1] += int(stripped_line)

# Sort the list from high to low.
calories.sort(reverse=True)

print(f"(DAY 01A) Most calories carried by a single elf is {calories[0]}")
print(f"(DAY 01B) Calories carried by top 3 elves is {sum(calories[0:3])}")
