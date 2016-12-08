mkfifo a b q
cat </dev/zero >a & # a is low
cat <b >/dev/null & # b is low
./nand.sh a b q &
tr '\000' '\a' <q   # q should be high => no bell

