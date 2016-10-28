#
#		c makefile for euler
#
#		ryan keleti
#
##	include ../../Makefile
#

SRCS:=$(wildcard *.c)
OBJS:=${SRCS:.c=.o}
NAME:=$(patsubst %.c,%,$(SRCS))

INCLUDE_DIR:=
LIBRARY_DIR:=
LIBS:=

LDFLAGS +=$(foreach libdir,$(LIBRARY_DIR),-L$(libdir))
LDFLAGS +=$(foreach lib,$(LIBS),-l$(lib))
CFLAGS:=-lm 

.PHONY: all clean distclean remove

all: $(OBJS)	

$(OBJS): %.o: %.c
	cc $< -o $@ $(CFLAGS)
	mv *.o ../bin

clean: 
	@- $(RM) $(NAME)
	@- $(RM) $(OBJS)

distclean: clean

remove:
	rm -i `find ../bin -perm /111 -type f`

delete:
	rm -I `find ../bin -perm /111 -type f`

help:
	@echo
	@echo 'c makefile | proj euler'
	@echo
	@echo 'usage: make [TARGET]'
	@echo
	@echo '   all:        make all *.c in bin'
	@echo '   clean:      rm *.o in bin'
	@echo '   distclean:  clean'
	@echo '   remove:     rm files w/ exec bit set (safer)'
	@echo '   delete:     rm files w/ exec bit set'
	@echo
	@echo

