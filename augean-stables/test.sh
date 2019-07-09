#!/bin/sh

gcc -o stables filthy_stable.c
gcc -o empty empty.c

alias valgrind="~/.brew/Cellar/valgrind/HEAD-dc950d9/bin/valgrind"

echo "Stables Leaks Summary:"
valgrind --leak-check=yes ./stables 2>&1 | tail -n 11
echo "\n\nAn Empty project Leaks Summary:"
valgrind --leak-check=yes ./empty 2>&1 | tail -n 11
