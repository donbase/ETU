#!/bin/bash

gcc prog_write.c -o prog_write -lpthread
./prog_write
rm prog_write
