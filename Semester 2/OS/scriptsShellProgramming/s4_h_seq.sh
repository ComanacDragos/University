#!/bin/bash

n=0
while [ $# -ne 0 ];do
	if [ -f $1 ];then
		a[$n]=`du -b $1`
		n=$((n+1))		
	fi	
	shift 1
done
aux=""
for i in $(seq 0 $(($n-1)));do
	aux=$aux"\n"${a[i]}
done

echo -e $aux | tail -n +2 | sort -rn

