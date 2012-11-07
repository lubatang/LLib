#!/bin/bash

if [ $# -lt 2 ]; then
  echo "Usage:"
  echo "$ ./run.sh [Path of Test Directory]"
  echo
  echo "example: ./run.sh Color\ Models/"
  exit
fi

VIEWER=lviewer.debug
DIRECTORY=$1

files=`find ${DIRECTORY} | grep --color=never ".obj$"`

for file in ${files}; do
  ${VIEWER} -f ${file}
done
