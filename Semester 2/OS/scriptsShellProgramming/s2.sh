#!/bin/bash

count=0
dir=`find ../Data/dir`

for file in $dir; do
	if [ -f $file ]; then
		lines=`wc -l $file | awk '{print $1}'`
		if [ $lines -ge 500 ]; then
			echo $file
			count=`expr $count + 1`
			if [ $count -eq 2 ]; then
				break
			fi
		fi
	fi
done
