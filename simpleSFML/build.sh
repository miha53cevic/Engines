#!/bin/bash

g++ main.cpp -Wall -std=c++17 $(pkg-config sfml-graphics sfml-window sfml-system --libs --cflags) -o test
