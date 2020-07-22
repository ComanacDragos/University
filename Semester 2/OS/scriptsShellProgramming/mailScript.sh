#!/bin/bash

mail=`cat mail.txt | grep ":)"`
grep ":)" mail.txt | sed "s/[A-H]\|[J-Z]/\L&/g" | sed "s/[a-z]/\U&/i"

NR=0

for i in `cat mail.txt`;do
	if [ `echo $i | wc -c` -ge 11 ];then
		NR=`expr $NR + 1`
	fi
done
echo $NR
