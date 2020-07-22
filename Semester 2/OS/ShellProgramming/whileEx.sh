#!/bin/bash

cat ./test.txt | while read X Y;do
	echo $X $X $Y $Y



D=$1
S=$2

if [ ! -d $D ];then
	echo Not a directory
	exit 1
fi


if ! echo $S | grep -q "^[0-9]\+$";then
	echo Size not a number
	exit 1
fi 

find $D -type f | while read F;do
		N=`ls -l $F | awk '{print $5}'`
		if [ $N -gt $S ]; then
			echo $F $N
		fi
done 
