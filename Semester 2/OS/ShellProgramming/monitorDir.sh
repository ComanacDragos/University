#!/bin/bash

D=$1

if [ ! -d "$D" ];then
	echo "ERROR: Directory does not exists" >&2
	exit 1
fi

STATE=""
while true;do
	S=""
	for P in `find $D`;do
		if [ -f $P ];then
			LS=`ls -l $P | sha1sum`
			CONTENT=`sha1sum $P`
		elif [ -d $P ];then
			LS=`ls -l -d $P | sha1sum`
			CONTENT=`ls -l $P | sha1sum`
		fi
		S="$S\n$LS $CONTENT" 
	done
	if [ -n "$STATE" ] && [ "$S" != "$STATE" ];then
		echo "DIR state has changed"
	fi
	STATE=$S
	sleep 1
done
