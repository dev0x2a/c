#
#		c makefile for euler
#
#		ryan keleti
#

CC:=cc
RM:=rm
SHELL:=/bin/sh

SRCS:=$(wildcard *.c)
OBJS:=${SRCS:.c=.o}
NAME:=$(patsubst %.c,%,$(SRCS))

CFLAGS:=-lm -Wall 

.PHONY: all clean remove delete help

all: $(OBJS)	

$(OBJS):%.o:%.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	$(RM) -I *.o

remove:
	$(RM) -i `find . -perm /111 -type f`

delete:
	$(RM) -I `find . -perm /111 -type f`

help:
	@echo
	@echo 'c makefile | proj euler'
	@echo
	@echo 'usage: make [TARGET]'
	@echo
	@echo '   all:        make all *.c'
	@echo '   clean:      rm *.o'
	@echo '   remove:     rm files w/ exec bit set (safer)'
	@echo '   delete:     rm files w/ exec bit set'
	@echo

