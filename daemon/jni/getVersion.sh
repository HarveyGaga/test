#!/bin/sh

clear

k=3

./daemonProc -v > tmp.txt

awk 'NR==1 {print $3}' tmp.txt > version

rm tmp.txt
#echo ${var#*:}

