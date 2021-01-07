#!/bin/sh

make
./parser.exe $1
basename "$1"
f="$(basename -- $1)"
length=`expr length $f`
subseq=$(echo $f|cut -c-$(($length-2)))

g++ -std=c++14 $subseq"cpp" -o $subseq"exe"
./$subseq"exe"
