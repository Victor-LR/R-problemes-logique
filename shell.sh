#!/bin/sh

make
./test.out $1

g++ -std=c++14 example.cpp -o pred.exe
./pred.exe
