#!/bin/bash

if [ $# -eq 0 ];then
	echo "GIVE ARGUMENTS"
	exit 1
fi
>file.txt
files=0
dir=0
reads=0
writes=0
executes=0
positives=0
negatives=0
for i in $*;do
	if [ -d $i ];then
		dir=`expr $dir + 1`
	elif [ -f $i ];then
		files=`expr $files + 1`
		if ls -l $i | grep -q "^-r";then
			reads=`expr $reads + 1`
		fi
		if ls -l $i | grep -q "^-.w";then
			writes=`expr $writes + 1`
		fi  
		if ls -l $i | grep -q "^-..x";then
			executes=`expr $executes + 1`
		fi
	elif echo $i | grep -q "^[0-9]\+$";then
		positives=`expr $positives + 1`
	elif echo $i | grep -q "^-[0-9]\+$";then
		negatives=`expr $negatives + 1`
	elif [ -n $i ];then
		echo $i@scs.ubbcluj.ro >> file.txt	
	fi	
done

echo "Files: $files"
echo "Dirs: $dir"
echo "Readable files: $reads"
echo "Writable files: $writes"
echo "Executable files: $executes"

echo "Positives: $positives"
echo "Negatives: $negatives"
echo 
cat file.txt
