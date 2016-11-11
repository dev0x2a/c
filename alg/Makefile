#!/bin/make
#	ryan keleti
#	WIP

SRCS:=$(wildcard *.c)
OBJS:=${SRCS:.c=.o}
NAME:=$(patsubst %.c,%,$(SRCS))

INCLUDE_DIR:=
LIBRARY_DIR:=
LIBS:=

LDFLAGS +=$(foreach libdir,$(LIBRARY_DIR),-L$(libdir))
LDFLAGS +=$(foreach lib,$(LIBS),-l$(lib))
CFLAGS:=-lm -O -ansi 

CC=cc
GCC=gcc
RM=rm

.PHONY: all gcc clean remove help

all: $(NAME)	

$(NAME): $(NAME)
	${CC} $@.c -o $@ ${CFLAGS}

gcc:
	${GCC} $(NAME).c ${CFLAGS} $? -o $@

clean:
	rm -i `find . -perm /111 -type f`

remove:
	rm -I `find . -perm /111 -type f`

help:
	@echo
	@echo 'usage: make [TARGET]'
	@echo
	@echo '	all:    make all *.c'
	@echo '	gcc:    use gcc'
	@echo '	clean:  rm files w/ exec bit set (safer)'
	@echo '	remove: rm files w/ exec bit set'
	@echo '	help:   display this message'
	@echo

