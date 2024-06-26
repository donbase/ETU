#!/bin/bash

gcc client.c -o client

./client

rm client client_socket.soc
