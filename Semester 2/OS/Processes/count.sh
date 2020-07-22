#!/bin/bash

lines=0
dirs=0

for f in `ls | grep "\.c$"`;do
	#cat $f | grep -v "^[ \t]*$\|^[ \t]*.$"
	cat $f | grep "[a-zA-Z]\{2\}"
done
