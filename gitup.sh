#!/bin/bash

function gitEX () {
local EX="$?"

  if [ $EX != 0 ]; then
    echo ":: error"
  else
    echo ":: done"
  fi
}

cd $HOME/c

files="*"

echo -e "::\n(\n$files `ls` )\n»» auto included"
echo -en ":: enter other files\n   "
read efiles

git add $files $sdir $efiles
git commit -m "gitupdate.sh >> c"
git push origin master

gitEX

