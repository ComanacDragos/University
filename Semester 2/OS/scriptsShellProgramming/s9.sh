#!/bin/bash

paths=`find ../Data/dir`


for i in $paths
do
	for j in $paths
	do
	if [ -f $i ] && [ -f $j ]
	then
		f1=`md5sum $i | awk '{print $1}'`
		f2=`md5sum $j | awk '{print $1}'`
		if [ $f1 = $f2 ] && [ $i != $j ]
		then
			echo $i " " $j
		fi
	fi
	done
done

