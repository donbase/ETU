#!/bin/bash

gcc prog_read.c -o prog_read -lpthread
./prog_read
rm prog_read
