CC = gcc
# warnings
CFLAGS = -Wall -Wextra -Wconversion -Wcast-qual -Wcast-align -Wfloat-equal -Wnested-externs -Winline 
# style
CFLAGS += -pedantic -std=gnu99 -Werror
# optimizations
CFLAGS += -O3
# CFLAGS += -Og
CFLAGS += -ledit
EXECS = calypso
DEPENDENCIES = user/sh.c basic/combinatorics.c graph/graph.c user/builtin.c basic/hash.c basic/avltree.c

.PHONY: all clean perf run

PROMPT = -DPROMPT

all: $(EXECS)

calypso: $(DEPENDENCIES)
	./format.sh
	$(CC) $(CFLAGS) $^ -o $@ 

clean:
	rm -f $(EXECS)
	rm -rf *.dSYM
	rm -f test

test:
	$(CC) $(CFLAGS) basic/avltree.c basic/avltree_test.c -o test

run: all
	./calypso

