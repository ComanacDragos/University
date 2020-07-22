#!/bin/bash

aux=""

while [ $# -ne 0 ];do
	if [ -f $i ];then
		aux=`du -b "$1"`"\n"$aux
	fi
	shift 1
done

echo -e $aux | head -n -1 | uniq | sort -n -r | awk '{print $2}'
