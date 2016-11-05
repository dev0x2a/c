CC:=cc
RM:=rm -i
OUT:=a.out
IDIR:=./include/
SRCDIR:=./src/
SRCS:=$(SRCDIR)*.c
CFLAGS:=-lncurses -Wall -I$(IDIR)

.PHONY: all rogue run clean

all: rogue

rogue:
	$(CC) $(SRCS) $(CFLAGS) -o $@

run:
	./rogue

clean:
	$(RM) `find . -perm /111 -type f`

