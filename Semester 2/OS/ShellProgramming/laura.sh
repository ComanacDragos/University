#!/bin/bash

>numere.txt

read T
while [ $T != "stop" ];do
	if [ `expr length $T` -ge $1 ];then
		echo $T >> numere.txt
	fi
	read T
done
