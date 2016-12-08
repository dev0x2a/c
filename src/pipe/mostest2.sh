mkfifo a b q
cat <a >/dev/null & # a is high
cat <b >/dev/null & # b is high
./nand.sh a b q &
tr '\000' '\a' <q   # q should be low => bell

