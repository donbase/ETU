#!/bin/bash

gcc check.c -o prog -lcap
sudo ./prog
rm prog

