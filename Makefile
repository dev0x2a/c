#		c makefile
#
#
#		use on this system only
#
#		ryan keleti

BIN=bin
SRCS:=$(wildcard *.c)
OBJS:=${SRCS:.c=.o}
NAME:=$(patsubst %.c,%,$(SRCS))

INCLUDE_DIR:=
LIBRARY_DIR:=
LIBS:=

LDFLAGS +=$(foreach libdir,$(LIBRARY_DIR),-L$(libdir))
LDFLAGS +=$(foreach lib,$(LIBS),-l$(lib))
CFLAGS:=-lm 

.PHONY: all clean remove

all: $(OBJS)	

bin: $(OBJS)
	mv *.o ~/c/bin

$(OBJS): %.o: %.c
	cc $< -o $@ $(CFLAGS)

clean: 
	@- $(RM) $(NAME)
	@- $(RM) $(OBJS)

remove:
	rm -i `find . -perm /111 -type f`

