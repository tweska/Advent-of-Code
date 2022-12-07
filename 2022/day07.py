#!/usr/bin/env python3

import sys
import re


def new_file(name, size):
    return {
        "name": name,
        "type": "f",
        "size": size,
        "tree": None,
    }


def new_dir(name):
    return {
        "name": name,
        "type": "d",
        "size": 0,
        "tree": [],
    }


def new_node(name, size):
    return new_dir(name.strip()) if size.strip() == "dir" else new_file(name, int(size))


def find_dir(root, name):
    for node in root["tree"]:
        if node["name"] == name:
            return node


def find_all_dirs(root):
    dirs = []
    if root["tree"]:
        dirs.append(root)
        for node in root["tree"]:
            dirs += find_all_dirs(node)
    return dirs


def calc_size(root):
    if root["tree"]:
        for node in root["tree"]:
            root["size"] += calc_size(node)
    return root["size"]


def print_tree(root, print_dir_size=False, tabs=0):
    if root["type"] == "f":
        print(f"{' '*2*tabs}- {root['name']} (file, size={root['size']})")
    elif print_dir_size:
        print(f"{' '*2*tabs}- {root['name']} (dir, size={root['size']})")
    else:
        print(f"{' '*2*tabs}- {root['name']} (dir)")
    if root["tree"]:
        for node in root["tree"]:
            print_tree(node, print_dir_size, tabs+1)


root = new_dir("/")
cur_dir = None
par_dir = []
for line in sys.stdin:
    if line[0] == "$":
        cmd, dir = re.search(r"\$ (cd|ls) ?(/|[a-zA-Z.]+)?\n", line).groups()
        if cmd == "cd":
            if dir == "/":
                cur_dir = root
            elif dir == "..":
                cur_dir = par_dir.pop()
            else:
                # Find directory in current directory
                par_dir.append(cur_dir)
                cur_dir = find_dir(cur_dir, dir)
    else:
        size, name = line.strip().split(" ")
        cur_dir["tree"].append(new_node(name, size))

calc_size(root)
# print_tree(root, True)

# PartA
def partA(root):
    sum = 0
    if root["tree"]:
        for node in root["tree"]:
            sum += partA(node)
        if root["size"] <= 100000:
            sum += root["size"]
    return sum
sizeA = partA(root)

# PartB
needed = 30000000 - (70000000 - root["size"])
dirs = sorted([(dir["size"], dir["name"]) for dir in find_all_dirs(root) if dir["size"] > needed])
sizeB = dirs[0][0]

print(f"(DAY 07A) Sum of the total sizes of the directories with at most size 100000 is {sizeA}")
print(f"(DAY 07B) Size of the directory to be removed is {sizeB}")
