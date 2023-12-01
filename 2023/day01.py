#!/usr/bin/env python3

import sys


digits = [str(i) for i in range(10)]
words = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']


def replace_words(s):
    if s == "":
        return s
    for i, w in enumerate(words):
        if s.startswith(w):
            return str(i) + replace_words(s[1:])
    return s[0] + replace_words(s[1:])


a, b = 0, 0
for line in sys.stdin:
    number = [c for c in line if c in digits]
    a += 10 * int(number[0]) + int(number[-1])

    number = [c for c in replace_words(line) if c in digits]
    b += 10 * int(number[0]) + int(number[-1])

print(a, b)