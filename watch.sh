#!/bin/bash

while true; do
inotifywait -q -e close_write src/* test/* input/*
echo -e "\n\e[32m*** WATCH ***\e[0m\n"
make $2 ARGS="$3"
done
