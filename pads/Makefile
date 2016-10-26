#!/bin/make

SRCS:=$(wildcard *.c)
OBJS:=${SRCS:.c=.o}
NAME:=$(patsubst %.c,%,$(SRCS))

INCLUDE_DIR:=
LIBRARY_DIR:=
LIBS:=

LDFLAGS +=$(foreach libdir,$(LIBRARY_DIR),-L$(libdir))
LDFLAGS +=$(foreach lib,$(LIBS),-l$(lib))
CFLAGS:=-lm -O -ansi 

CC= cc
GCC= gcc
RM=rm

.PHONY: all clean remove delete help

all: $(NAME)	

$(NAME):
	${CC} $(NAME).c ${CFLAGS} $? -o $@

#$(OBJS): %.o: %.c
#	cc $< -o $@ $(CFLAGS)

clean: 
	@- $(RM) $(NAME)
	@- $(RM) $(OBJS)

remove:
	rm -i `find . -perm /111 -type f`

delete:
	rm -I `find . -perm /111 -type f`

help:
	@echo
	@echo 'c makefile | proj euler'
	@echo
	@echo 'usage: make [TARGET]'
	@echo
	@echo '   all:        make all *.c in bin'
	@echo '   remove:     rm files w/ exec bit set (safer)'
	@echo '   delete:     rm files w/ exec bit set'
	@echo
	@echo

