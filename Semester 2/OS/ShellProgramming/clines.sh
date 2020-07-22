#!/bin/bash

DIR=$1

S=0
echo $#
if [ $# -ne 1 ]; then
	echo "Toomuch"
	exit 1
fi

if [ ! -d $DIR ]; then
	echo "Give Dir"
	exit 1
fi

for F in $(find $DIR); do
	if [ `echo $F | grep "\.c$"` ]; then
		N=$(grep "[^ \t]" $F | wc -l)
		S=$(expr $S + $N)
	fi
done
echo $S
S=0

for F in $1/*.c; do	
	N=$(grep "[^ \t]" $F | wc -l)
	S=$(expr $S + $N)
done

echo $S
