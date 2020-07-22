#!/bin/bash

if [ $# -ne 1 ];then
	echo "Provide exactly one argument"
	exit 1
fi

DIR=$1
if [ ! -d $DIR ];then
	echo "Not dir"
	exit 1
fi
S=0
for F in `ls $DIR`;do
	if [ `file "$F" | grep  "text" | wc -l` -eq 1 ];then
		SIZ=`ls -l "$F" | awk '{print $5}'`
		S=$(expr $S + $SIZ)
	fi
done

echo $S

