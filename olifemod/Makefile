CC:=cc
RM:=rm
CFLAGS:=-Wall
LIFE:=life
UO:=uolife

.PHONY: life uolife help

life: life.c
	$(CC) life.c -o $(LIFE) $(CFLAGS)

uolife: uolife.c
	$(CC) uolife.c -o $(UO) $(CFLAGS)

clean:
	$(RM) -i life uolife
	#$(RM) -i `find . -perm /111 -type f`

help:
	@echo -e "$(LIFE):\tmake $(LIFE).c"
	@echo -e "$(UO):\tmake $(UO).c"
	@echo -e "clean:\tremove executables"
	@echo "./$(LIFE) or ./$(UO) to run"
