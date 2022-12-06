#!/usr/bin/env python3

import sys


def find_distinct(string, n):
    for i in range(0, len(string)-n):
        found = True
        for j in range(1, n):
            if string[i+j-1] in string[i+j:i+n]:
                found = False
                break
        if found:
            return i+n


signal = sys.stdin.readline().strip()
print(f"(DAY 06A) Start of packet is at {find_distinct(signal, 4)}")
print(f"(DAY 06B) Start of message is at {find_distinct(signal, 14)}")
