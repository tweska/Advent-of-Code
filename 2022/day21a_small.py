#!/usr/bin/env python3

import sys

VARS = {var: int(val) if val[0].isdigit() else tuple(val.split(' ')) for var, val in [[s.strip() for s in l.strip().replace('/', '//').split(':')] for l in sys.stdin]}


def solve(vars, var='root'):
    if type(vars[var]) == int:
        return vars[var]
    return eval(f"{solve(vars, vars[var][0])} {vars[var][1]} {solve(vars, vars[var][2])}")


print(f"(DAY 21A) root = {solve(VARS)}")
