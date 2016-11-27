#!/bin/sh

# usage: nand.sh A B out

A=$1
B=$2
OUT=$3

VDD=/dev/null
VSS=/dev/zero

cc mosfet.c -o mosfet

./mosfet <$OUT -$A >$VDD &
./mosfet <$OUT -$B >$VDD &

./mosfet <$VSS $B | ./mosfet $A >$OUT

