#!/usr/bin/env python3

import sys
import functools


def parse_str_list(str_list):
    if "[" not in str_list and "," not in str_list:
        return int(str_list)

    list = []
    elem = []
    indent = []
    for i in range(len(str_list)):
        if str_list[i] == "[":
            indent.append(i)
        elif str_list[i] == "]":
            p = indent.pop()
            if len(indent) == 1:
                list.append(parse_str_list(str_list[p:i+1]))
        elif len(indent) == 1:
            if str_list[i] == ",":
                if len(elem) > 0:
                    list.append(parse_str_list("".join(elem)))
                    elem = []
            else:
                elem.append(str_list[i])
    if len(elem) > 0:
        list.append(parse_str_list("".join(elem)))

    return list


def compare(a, b):
    """Return negative if a < b, positive if a > b and 0 if equal"""
    if type(a) != list:
        if type(b) != list:
            return compare([a], [b])
        return compare([a], b)
    elif type(b) != list:
        return compare(a, [b])

    for i in range(len(a)):
        if i >= len(b):
            return len(a) - len(b)
        elif type(a[i]) != int or type(b[i]) != int:
            order = compare(a[i], b[i])
            if order != 0:
                return order
        elif a[i] - b[i] != 0:
            return a[i] - b[i]
    return len(a) - len(b)


indices = []
packets = [[[2]], [[6]]]
for i, (a_str, b_str) in enumerate([lines for lines in list(zip(*[iter([line.strip() for line in sys.stdin.read().replace("\n\n", "\n").split("\n")])]*2))]):
    a, b = parse_str_list(a_str), parse_str_list(b_str)

    # PartA
    indices.append(i+1 if compare(a, b) < 0 else 0)

    #  PartB
    packets.append(a)
    packets.append(b)
packets.sort(key=functools.cmp_to_key(compare))

print(f"(DAY 13A) {sum(indices)} packets are in the right order")
print(f"(DAY 13B) decoder key is {(packets.index([[2]])+1) * (packets.index([[6]])+1)}")
