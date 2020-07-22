#!/bin/bash


libs=""
while [ $# -ne 0 ];do
	if echo $1 | grep -q "\.c$" && [ -f $1 ];then
		libs="$libs""\n""`grep "#include" $1`"
	fi
	shift 1
done

echo -e $libs | tail -n +2 | sed "s/> />\n/g" | sort | uniq > file.txt

