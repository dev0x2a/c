CC:=cc
RM:=rm -i
CFLAGS:=-Wall -Wextra
OFLAGS:=-O2

.PHONY: all chess ttt clean help

all: chess ttt

chess:
	$(CC) chess.c -o chess $(CFLAGS) $(OFLAGS)

ttt:
	$(CC) ttt.c -o ttt $(CFLAGS) $(OFLAGS)

clean:
	$(RM) `find . -perm /111 -type f`

help:
	@echo
	@echo "all    make all (chess.c,ttt.c)"
	@echo "chess  make chess.c"
	@echo "ttt    make ttt.c"
	@echo "clean  remove -perm /111"
	@echo "help   disp this message"
	@echo
