#!/bin/bash

for i in `ls`;do
	F=`echo $i | grep "s[0-9]\.sh"`
	if [ ! $F = "" ];then
		echo $F >> solutions.txt
		echo >> solutions.txt
		cat $F >> solutions.txt
		echo >> solutions.txt
	fi
done
