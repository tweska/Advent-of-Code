#!/usr/bin/env python3

import sys


def mix(numbers, key=1, iters=1):
    numbers = [(i, n * key) for (i, n) in enumerate(numbers)]
    original = numbers[:]
    size = len(original)

    for _ in range(iters):
        for number in original:
            old_index = numbers.index(number)
            if number[1] == -old_index:  # Edge case...
                new_index = size - 1
            else:
                new_index = (old_index + number[1]) % (size - 1)
            numbers.insert(new_index, numbers.pop(old_index))

    for i, (_, n) in enumerate(numbers):
        if n == 0:
            zero = i
            break

    return sum([numbers[(zero + i) % len(numbers)][1] for i in [1000, 2000, 3000]])


numbers = [int(line.strip()) for line in sys.stdin]

print(f"(DAY 20A) Sum of groove coordinates is {mix(numbers)}")
print(f"(DAY 20A) Sum of groove coordinates is {mix(numbers, 811589153, 10)}")
