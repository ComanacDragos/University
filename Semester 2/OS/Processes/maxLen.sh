#!/bin/bash

i=0
min=`./p_11m | wc -l`
while [ $i -lt 100 ];do
	i=`expr $i + 1`
	minCurrent=`./p_11m | wc -l`
	echo $minCurrent
	if [ $min -lt $minCurrent ];then
		min=$minCurrent
	fi
done
echo $min
