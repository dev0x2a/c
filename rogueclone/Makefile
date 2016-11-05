CC:=cc
RM:=rm -i
OUT:=a.out
IDIR:=./include/
SRCDIR:=./src/
SRCS:=$(SRCDIR)*.c
CFLAGS:=-lncurses -Wall -I$(IDIR)

.PHONY: all rogue main clean

all: rogue

rogue:
	$(CC) $(SRCS) $(CFLAGS) -o $@

run:
	./rogue

main:
	$(CC) main.c -o $(OUT) $(CFLAGS)

clean:
	$(RM) `find . -perm /111 -type f`

