CC:=cc
RM:=rm -i
OUT:=a.out
CFLAGS:=-lncurses -lm -Wall
.PHONY: main clean
main:
	$(CC) main.c -o $(OUT) $(CFLAGS)
clean:
	$(RM) `find . -perm /111 -type f`

