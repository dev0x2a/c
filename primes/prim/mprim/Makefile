#!/bin/make
#	ryan keleti
#	WIP

SRCS:=$(wildcard *.c)
OBJS:=${SRCS:.c=.o}
NAME:=$(patsubst %.c,%,$(SRCS))
CFLAGS:=-ansi -lm -O -Wall
TARGET:=prog
CC=cc

.PHONY: all clean remove


all: $(NAME)	

$(NAME): $(NAME).c
	$(CC) -c $< -o $@

$(TARGET): $(NAME)
	$(CC) $(NAME).c -o $@

clean:
	rm -i `find . -perm /111 -type f`

remove:
	rm -I `find . -perm /111 -type f`

