#!/bin/make
CC:=cc
RM:=rm -i
CFLAGS:=-g -Wall -O -lm
.PHONY: prog clean
prog:
	$(CC) prog.c -o prog
clean:
	$(RM) a.out
	$(RM) `find . -perm /111 -type f`

