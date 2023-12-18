#!/usr/bin/env python3

import sys

cards = []
for line in sys.stdin:
    w, h = line.strip().split(': ')[1].split(' | ')
    win, have = [int(n) for n in w.split()], [int(n) for n in h.split()]
    cards.append([1, win, have])

a = 0
for i, card in enumerate(cards):
    k, h, w = card
    matches = sum([1 for n in h if n in w])
    a += 2**matches // 2
    for j in range(i+1, i+matches+1):
        cards[j][0] += k
b = sum([card[0] for card in cards])

print(a, b)
