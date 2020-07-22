#!/bin/bash

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

for F in `find $D`;do
	if [ -f $F ]; then 
		N=`ls -l $F | awk '{print $5}'`
		if [ $N -gt $S ]; then
			echo $F $N
		fi
	fi
done 
