CC:=cc
RM:=rm -i
CFLAGS:=-Wall -Wextra
OFLAGS:=-O2

.PHONY: all chess ttt clean

all: chess ttt

chess:
	$(CC) chess.c -o chess $(CFLAGS) $(OFLAGS)

ttt:
	$(CC) ttt.c -o ttt $(CFLAGS) $(OFLAGS)

clean:
	$(RM) `find . -perm /111 -type f`
