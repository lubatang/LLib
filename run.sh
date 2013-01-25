#!/bin/bash

if [ $# -lt 1 ]; then
  echo "Usage:"
  echo "$ ./run.sh [Path of Test Directory]"
  echo
  echo "example: ./run.sh Color\ Models/"
  exit
fi

VIEWER=lviewer.debug
DIRECTORY=$1

files=`find ${DIRECTORY} | grep --color=never ".obj$"`

echo "Bump map path? (skip this step by typing \`enter')";
read BUMP_MAP;
if [ ! -z ${BUMP_MAP} ]; then
    while [ ! -f ${BUMP_MAP} ]; do
      echo "Can not find file \`${BUMP_MAP}'. Please to key-in the path again.";
      ls
      read BUMP_MAP;
    done
fi

for file in ${files}; do
  if [ -z ${BUMP_MAP} ]; then
    ${VIEWER} -f ${file}
  else
    ${VIEWER} -f ${file} -b ${BUMP_MAP}
  fi
done
