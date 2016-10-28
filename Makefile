#                              #
#		c makefile                 #
#                              #
#		ryan keleti                #
#                              #

SRCS:=$(wildcard *.c)
NAME:=$(patsubst %.c,%,$(SRCS))
OBJS:=${SRCS:.c=.o}

#INCLUDE_DIR:=
#LIBRARY_DIR:=
#LIBS:=
RM=rm
CC=cc

#LDFLAGS +=$(foreach libdir,$(LIBRARY_DIR),-L$(libdir))
#LDFLAGS +=$(foreach lib,$(LIBS),-l$(lib))
CFLAGS:=-std=c99 -ansi

.PHONY: all clean remove

all: $(NAME)	

$(NAME): $(NAME) 
	$(CC) $@.c -o $@ $(CFLAGS)

clean: 
	@- $(RM) -I $(NAME)
	@- $(RM) -I $(OBJS)

remove:
	$(RM) -i `find . -perm /111 -type f`

