#!/bin/bash


for X in `ps -ef | grep -v "^root" | tail -n +2 | awk '{print $1 ":" $2}'`;do
	U=`echo $X | cut -d: -f1`
	P=`echo $X | cut -d: -f2`
	
	echo $U $P
	A=`ps -o etime $P | tail -n 1 | awk -F: '{print ($1*60+$2)}'`
	echo $A
done
