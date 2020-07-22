#!/bin/bash

date=`date +%d.%m`
if [ $# -eq 0 ];then
	echo "Give arguments"
	exit 1
fi
touch raport.txt
>raport.txt
for i in $*;do
	if [ ! -f $i ];then
		echo "$i Not a file"
	else
		for j in `cat $i`;do
			d=`echo $j | awk -F- '{print substr($1,0,5)}'`
			if [ $d == $date ];then
				name=`echo $j | awk -F- '{print $2}'`
				echo $name >> raport.txt	
			fi
		done
	fi
done
