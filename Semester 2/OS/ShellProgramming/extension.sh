#!/bin/bash

while [ $# -ne 0 ];do
	if [ -f $1 ];then
		#new="$1.file"
		#echo $new
		mv $1 $1.file
	fi
	shift 1
done
