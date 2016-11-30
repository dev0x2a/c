SHELL:=/bin/sh
CC:=cc
RM:=rm -i
CFLAGS:=-Wall -O

.PHONY: primes primespeed eratspeed clean remove

primes:
	$(CC) primes.c -o primes $(CFLAGS)

primespeed:
	$(CC) primespeed.c -o primespeed $(CFLAGS)

primegaps:
	$(CC) primegaps.c -o primegaps  $(CFLAGS)

eratspeed:
	$(CC) eratspeed.c -o eratspeed $(CFLAGS)

clean:
	$(RM) `find . -perm /111 -type f`

remove:
	$(RM) a.out

