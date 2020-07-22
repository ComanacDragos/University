#!/bin/bash

D=`date +%Y$m`
T="${D}01000000"

cat ../Data/last.fake | \
sed "s/ .*//" | \
sort | \
uniq -c | \
sort -n -r | \
grep -v "wtmp" |\
head -n -1 | \
while read L U;do \
	N=`grep "^$U:" ../Data/passwd.fake`
	echo $N $U
done


