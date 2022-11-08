CC=gcc
CFLAGS=-Wall -O2

DAYS = day01a day01b day02a day02b day03a day03b day04 day05a day05b day06 day07a day07b day08a day08b day09a day09b day10a day10b day11 day12 day13 day14

.PHONY: all
.PHONY: run
all: $(DAYS)

%: %.c
	mkdir -p bin
	$(CC) $(CFLAGS) $< -o bin/$@

.PHONY: clean
clean:
	rm bin/*
