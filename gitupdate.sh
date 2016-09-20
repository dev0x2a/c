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
sdir=""

echo -e ":: ( $sdir $files `ls` ) »» auto included"
echo -en ":: enter other files    "
read efiles

git add $files $sdir $efiles
git commit -m "gitupdate.sh >> c"
git push origin master

gitEX

