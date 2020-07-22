#!/bin/bash


files=`find ../Data/copyDirS5`

newFiles=""
for i in $files; do
	permisions=`ls -d -l $i`
	if [ `echo $permisions | grep -c "^.\{8\}w"` -eq 1 ]; then
		echo `ls -l $i`
		chmod o-w $i	
		echo `ls -l $i`
		
	fi
done
