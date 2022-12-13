#!/usr/bin/env python3

import sys
import functools


def compare(list_a, list_b):
    """Return negative if a < b, positive if a > b and 0 if equal"""
    if type(list_a) != list:
        return compare([list_a], list_b)
    if type(list_b) != list:
        return compare(list_a, [list_b])

    for a, b in zip(list_a, list_b):
        if type(a) != int or type(b) != int:
            order = compare(a, b)
            if order != 0:
                return order
        elif a - b != 0:
            return a - b
    return len(list_a) - len(list_b)


indices, packets = [], [[[2]], [[6]]]
for i, (a, b) in enumerate([lines for lines in list(zip(*[iter([eval(line) for line in sys.stdin.read().split()])]*2))]):
    # PartA
    indices.append(i+1 if compare(a, b) < 0 else 0)

    #  PartB
    packets += [a, b]
packets.sort(key=functools.cmp_to_key(compare))

print(f"(DAY 13A) {sum(indices)} packets are in the right order")
print(f"(DAY 13B) decoder key is {(packets.index([[2]])+1) * (packets.index([[6]])+1)}")
