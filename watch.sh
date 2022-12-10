#!/bin/bash

while true; do
inotifywait -q -e close_write src/* test/* input/*
echo -e "\n\e[32m*** WATCH ***\e[0m\n"
make $1

if [ ! $1 = "test" ]; then
  build/$1 $2 $3 $4
fi
done
