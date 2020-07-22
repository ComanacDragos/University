#!/bin/bash

files=`find ../Data/copyDirS3 | grep "\.log$"`

for f in $files;do
	sort $f > file.txt
	cat file.txt > $f
	rm file.txt
done
