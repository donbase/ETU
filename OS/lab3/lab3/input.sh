#!/bin/bash

printf "Введите 1 для запуска  pipe() c блокировкой\nВведите 2 для запуска pipe2() без блокировки\nВведите 3 для запуска fcntl() без блокировки\n"

read NAME

case $NAME in
  1)
    gcc prog1.c -o prog
    ./prog
    rm prog
    ;;
  2)
    gcc prog2.c -o prog
    ./prog
    rm prog
    ;;
  3)
     gcc prog3.c -o prog
    ./prog
    rm prog
    ;;
  *)
    printf  "unknown choice\n"
    ;;
esac

