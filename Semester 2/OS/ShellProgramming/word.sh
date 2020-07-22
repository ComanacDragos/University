#!/bin/bash

if [ $# -lt 2 ];then
	echo "Gib params"
	exit 1
fi

word=$1

shift

dir=0
while [ $# -ne 0 ];do
	files=0
	for i in `find $1 -type f`;do
		if grep -q "$word" $i;then
			files=`expr $files + 1`
		fi
	done
	if [ $files -ge 2 ];then
		dir=`expr $dir + 1`
	fi
	shift	
done
echo $dir
