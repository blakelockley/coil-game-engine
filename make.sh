#!/usr/bin/env sh

NAME=engine

gcc -c src/*.c -I includes/
ar -cr lib${NAME}.a *.o
rm *.o