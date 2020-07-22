#!/bin/bash

read -p "Give number: " N
> file.txt
while true;do
	read -p "Give file: " F
	if [ ${#F} != 0 ];then
		if [ $F = "stop" ];then
			echo "Terminating..."
			exit 1
		fi
		if [ -f $F ] && [ `cat $F | wc -l` -eq $N ];then
			echo $F >> file.txt	
		fi
	fi
done
