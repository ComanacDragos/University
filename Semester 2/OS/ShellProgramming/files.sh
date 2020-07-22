#!/bin/bash

f1=$1
f2=$2
shift 2
>$f1
>$f2
while [ $# -ne 0 ];do
	for i in `find $1 -maxdepth 1 -type f`;do
		grep -o "[13579]" $i >> $f1
		grep -o "[02468]" $i >> $f2
	done
	shift
done

cat $f1
cat $f2
