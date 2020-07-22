#!/bin/bash 

#Write a script that reads filenames until the word "stop" is entered. For each filename, check if it is a text  file and if it is, print the number of words on the first line.


if [ $# -ne 0 ];then
	echo "Too many arguments"
	exit 1
fi

F=""

read -p "Give file: " F
while [ "$F" != "stop" ];do
	if [ `file $F | grep "text" | wc -l` -eq 1 ];then
		head "$F" -n 1 | wc -w
	else
		echo "Not file"
	fi	
	read -p "Give file: " F
done
