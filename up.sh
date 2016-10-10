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

git add `find .`
git add $files 
git commit -m "update `date`"
git push origin master

gitEX

