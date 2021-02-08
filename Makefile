CC = gcc
CFLAGS = -g3 -Wall -Wextra -Wconversion -Wcast-qual -Wcast-align -g
CFLAGS += -Winline -Wfloat-equal -Wnested-externs -funroll-loops
CFLAGS += -pedantic -std=gnu99 -Werror
CFLAGS += -lncurses -pg
EXECS = calypso
DEPENDENCIES = user/sh.c graph/graph.c user/builtin.c basic/combinatorics.c

.PHONY: all clean

PROMPT = -DPROMPT

all: $(EXECS)

calypso: $(DEPENDENCIES)
	$(CC) $(CFLAGS) $^ -o $@ 
clean:
	rm -f $(EXECS)
	rm -rf *.dSYM
