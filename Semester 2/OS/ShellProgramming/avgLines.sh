#!/bin/bash

nrLines=0
nrFiles=0

for i in `ls | grep "\.txt$"`;do
	nrFiles=`expr $nrFiles + 1`
	lines=`wc -l $i | awk '{print $1}'`
	nrLines=`expr $nrLines + $lines`
done

echo $nrFiles $nrLines | awk '{print $2/$1}'
echo `expr $nrLines / $nrFiles`
