#!/bin/bash

paths=`find ..`

for i in $paths; do
	if [ -L $i ]; then
		echo $i
		if ! [ -e $i ]; then
			echo $i
		fi
	fi
done



