#!/bin/bash

if [ $# -eq 0 ];then
	echo Give arguments
	exit 1
fi

N=$1
Files=""
>report.txt
shift

for i in $*;do
	if [ -f $i ];then
		if [ `wc -l $i | awk '{print $1}'` -ge $N ];then
			Files=$Files"\n"$i
		fi
	elif [ -d $i ];then
		count=0
		for j in `ls $i`;do
			if [ -d $j ];then
				count=`expr $count + 1`
			fi
		done	
		echo $i $count
		if [ $count -le $N ];then
			echo $i >> report.txt
		fi
	else
		echo "Bad input: $i"
	fi
done
echo -e $Files | tail -n -1
