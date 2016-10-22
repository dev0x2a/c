#
#		ryan keleti

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

clean: 
	@- $(RM) $(NAME)
	@- $(RM) $(OBJS)

distclean: clean

remove:
	rm -i `find . -perm /111 -type f`

delete:
	rm -I `find . -perm /111 -type f`

help:
	@echo
	@echo 'usage: make [TARGET]'
	@echo
	@echo '   all:        make all *.c'
	@echo '   clean:      rm *.o'
	@echo '   distclean:  clean'
	@echo '   remove:     rm files w/ exec bit set (safer)'
	@echo '   delete:     rm files w/ exec bit set'
	@echo
	@echo

