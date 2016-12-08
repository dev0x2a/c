#!/bin/make
# tfm demo makefile

.PHONY: all rsa stest test timing clean
all: rsa stest test timing
rsa:
	cc rsa.c -o rsa -ltfm
stest:
	cc stest.c -o stest -ltfm
test:
	cc test.c -o test -ltfm
timing:
	cc timing.c -o timing -ltfm
clean:
	rm `find . -perm /111 -type f`
