#!/bin/sh

make
./parser.exe $1
length=`expr length "$1"`
subseq=$(echo $1|cut -c-$(($length-2)))

g++ -std=c++14 $subseq"cpp" -o $subseq"exe"
./$subseq"exe"
