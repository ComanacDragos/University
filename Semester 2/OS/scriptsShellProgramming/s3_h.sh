#!/bin/bash

#3. Write a script that receives as command line arguments pairs consisting of a filename and a word. For each pa
#ir, check if the given word appears at least 3 times in the file ind print a corresponding message.

if [ $# -eq 0 ] || [ `expr $# % 2` -ne 0 ];then
	echo "Give pairs"
	exit 1
fi

while [ $# -ne 0 ];do
	F=$1
	W=$2
	shift 2
	count=0
	for i in `cat $F`;do
		if [ "$W" == "$i" ];then
			count=`expr $count + 1`
		fi
	done
	if [ $count -eq 3 ];then
		echo "True"
	fi
done

