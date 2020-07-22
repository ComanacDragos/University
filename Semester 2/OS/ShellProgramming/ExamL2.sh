#!/bin/bash

if [ $# -eq 0 ];then
	echo "Give arguments"
	exit 1
fi

fisier=$1

while [ 1 ];do
	read -p "Give nr: " nr
	if [ $nr -eq 0 ];then
		break
	fi
	read -p "Give file: " f
	>$f
	prop=""
	i=1
	while read word;do
		if [ `echo $prop | wc -w` -eq 0 ];then
			prop=$word
		else 
			prop=$prop" "$word
		fi
		words=`echo $prop | wc -w`
		if [ `expr $words % $nr` -eq 0 ];then
			echo $prop >> $f
			prop=""
		fi	
	done <<< `cat $1`
	
	lines=`wc -l $f | awk '{print $1}'`
	words=`wc -w $f | awk '{print $1}'`
	chars=`wc -m $f | awk '{print $1}'`
	chars=`expr $chars - 1`
	echo  Lines: $lines Words: $words Chars: $chars	
done
