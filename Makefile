CC = gcc
CFLAGS = -g3 -Wall -Wextra -Wconversion -Wcast-qual -Wcast-align -g
CFLAGS += -Winline -Wfloat-equal -Wnested-externs -funroll-loops
CFLAGS += -pedantic -std=gnu99 -Werror
CFLAGS += -ledit
EXECS = calypso
DEPENDENCIES = user/sh.c graph/graph.c user/builtin.c basic/combinatorics.c

.PHONY: all clean perf run

PROMPT = -DPROMPT

all: $(EXECS)

calypso: $(DEPENDENCIES)
	./format.sh
	$(CC) $(CFLAGS) $^ -o $@ 

clean:
	rm -f $(EXECS)
	rm -rf *.dSYM

run: all
	./calypso

perf: $(DEPENDENCIES)
	$(CC) -lncurses --coverage $^
