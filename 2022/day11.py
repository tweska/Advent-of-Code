#!/usr/bin/env python3

import sys
from copy import deepcopy


class Monkey:
    def __init__(self, items, operator, const, test, throw):
        self.item = items
        self.oper = operator
        self.cons = const
        self.test = test
        self.throw = throw
        self.inspected = 0

    def do_op(self, item):
        self.inspected += 1
        const = self.cons if self.cons is not None else item
        if self.oper == "+":
            return item + const
        if self.oper == "*":
            return item * const

    def do_cp(self, item):
        return item % self.test == 0

    def do_turn(self, monkeys, mod=None):
        while len(self.item) > 0:
            item = self.item.pop(0)
            item = self.do_op(item)
            if not mod:
                item = item // 3  # PartA
            else:
                item %= mod       # PartB
            if self.do_cp(item):
                monkeys[self.throw[0]].item.append(item)
            else:
                monkeys[self.throw[1]].item.append(item)


# Parse the input.
monkeys = []
prod = 1
for input in sys.stdin.read().split("\n\n"):
    lines = input.split("\n")
    items = [int(item) for item in lines[1].split(":")[1].split(",")]
    operator = "+" if "+" in lines[2] else "*"
    const = lines[2].split(operator)[1].strip()
    const = int(const) if const != "old" else None
    test = int(lines[3].strip().split("by")[1].strip())
    throw = (int(lines[4].strip().split(" ")[5]), int(lines[5].strip().split(" ")[5]))
    monkeys.append(Monkey(items, operator, const, test, throw))
    prod *= test


# PartA
monkeysA = deepcopy(monkeys)
for _ in range(20):
    for monkey in monkeysA:
        monkey.do_turn(monkeysA)
inspections = []
for monkey in monkeysA:
    inspections.append(monkey.inspected)
inspections.sort(reverse=True)
print(f"(DAY 11A) Monkey business level is {inspections[0]*inspections[1]}")

# PartB
for _ in range(10000):
    for monkey in monkeys:
        monkey.do_turn(monkeys, mod=prod)
inspections = []
for monkey in monkeys:
    inspections.append(monkey.inspected)
inspections.sort(reverse=True)
print(f"(DAY 11B) Monkey business level is {inspections[0]*inspections[1]}")
