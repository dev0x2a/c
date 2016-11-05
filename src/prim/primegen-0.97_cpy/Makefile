SHELL:=/bin/sh
CC:=cc
RM:=rm -i
CFLAGS:=-lm

.PHONY: primes primespeed eratspeed clean

primes:
	$(CC) primes.c -o primes $(CFLAGS)

primespeed:
	$(CC) primespeed.c -o primespeed $(CFLAGS)

eratspeed:
	$(CC) eratspeed.c -o eratspeed $(CFLAGS)

clean:
	$(RM) `find . -perm /111 -type f`

