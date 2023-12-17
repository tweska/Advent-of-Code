#!/usr/bin/env python3

import sys

a_games = set()
b_powers = []
for line in sys.stdin:
    game, bag = line.strip().split(': ')
    i = int(game[5:])
    a_games.add(i)

    r, g, b = 0, 0, 0
    for grab in bag.split('; '):
        for k, color in [item.split(' ') for item in grab.split(', ')]:
            k = int(k)

            if color == 'red' and k > r:
                r = k
            elif color == 'green' and k > g:
                g = k
            elif color == 'blue' and k > b:
                b = k

            if k > 12 and color == 'red' or k > 13 and color == 'green' or k > 14 and color == 'blue':
                a_games.discard(i)

    b_powers.append(r * g * b)

print(sum(a_games), sum(b_powers))
