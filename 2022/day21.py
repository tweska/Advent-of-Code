#!/usr/bin/env python3

import sys


class Expr:
    def __init__(self, op=None, lhs=None, rhs=None):
        self.op = op
        self.lhs = lhs
        self.rhs = rhs

    def __repr__(self):
        return f"({self.lhs} {self.op} {self.rhs})"

    def simplify(self):
        if type(self.lhs) == Expr:
            self.lhs = self.lhs.simplify()
        if type(self.rhs) == Expr:
            self.rhs = self.rhs.simplify()
        if type(self.lhs) == type(self.rhs) == int:
            return eval(f"{self.lhs} {self.op} {self.rhs}")
        return self

    def solve(self):
        if type(self.lhs.lhs) == int:
            assert self.lhs.op != '//'
            if self.lhs.op in ('+', '*'):  # x+n -> n+x and x*n -> n*x
                tmp = self.lhs.lhs
                self.lhs.lhs = self.lhs.rhs
                self.lhs.rhs = tmp
        if self.lhs.op == '+':  # x+n=y -> x=y-n
            new = Expr('-', self.rhs, self.lhs.rhs)
            self.lhs = self.lhs.lhs
            self.rhs = new
        elif self.lhs.op == '-':
            if type(self.lhs.lhs) == int:  # n-x=y -> x=n-y
                new = Expr('-', self.lhs.lhs, self.rhs)
                self.lhs = self.lhs.rhs
                self.rhs = new
            else:  # x-n=y -> x=n+y
                new = Expr('+', self.lhs.rhs, self.rhs)
                self.lhs = self.lhs.lhs
                self.rhs = new
        elif self.lhs.op == '*':  # x*n=y -> x=y/n
            new = Expr('//', self.rhs, self.lhs.rhs)
            self.lhs = self.lhs.lhs
            self.rhs = new
        elif self.lhs.op == '//':  # x/n=y -> x=y*n
            new = Expr('*', self.rhs, self.lhs.rhs)
            self.lhs = self.lhs.lhs
            self.rhs = new


VARS = {var: int(val) if val[0].isdigit() else tuple(val.split(' ')) for var, val in
        [[s.strip() for s in l.strip().replace('/', '//').split(':')] for l in sys.stdin]}


def convert(vars, var='root'):
    if type(vars[var]) in (int, str):
        return vars[var]
    return Expr(vars[var][1], convert(vars, vars[var][0]), convert(vars, vars[var][2]))


# Part A
print(f"(DAY 21A) root = {convert(VARS).simplify()}")

# Part B
VARS['root'] = (VARS['root'][0], '=', VARS['root'][2])
VARS['humn'] = 'x'

equation = convert(VARS).simplify()
while type(equation.lhs) != str:
    equation.solve()
print(f"(DAY 21A) humn = {equation.rhs.simplify()}")
