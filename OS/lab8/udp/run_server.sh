#!/bin/bash

gcc server.c -o server

./server

rm server server_socket.soc
