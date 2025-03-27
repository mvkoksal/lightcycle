CC := clang
CFLAGS := -g -Wall

all: lightcycle

clean:
	rm -rf lightcycle lightcycle.dSYM

lightcycle: lightcycle.c
	$(CC) $(CFLAGS) -o lightcycle lightcycle.c -lncurses

.PHONY: all clean
