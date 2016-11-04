SHELL=/bin/sh
CC=cc
RM=rm -i

.PHONY: primes primespeed eratspeed clean

primes:
	$(CC) primes.c -o primes

primespeed:
	$(CC) primespeed.c -o primespeed

eratspeed:
	$(CC) eratspeed.c -o eratspeed

clean:
	$(RM) `find . -perm /111 -type f`

