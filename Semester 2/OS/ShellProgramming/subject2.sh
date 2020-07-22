#!/bin/bash

if [ $# -lt 2 ];then
	echo "Numar insuficient"
	exit 1
fi

drepturi=$1
shift

for dir in $*;do
	if [ ! -d $dir ];then
		echo
		echo "Director $dir"
		echo "Directorul dat nu exista"
		continue
		echo
	fi
	for f in `find $dir -type f`;do
		if ls -l $f | grep -q "^-$drepturi";then
			cp  $f "$f.bak"
			chmod 400 "$f.bak"
			echo
			echo "Permisiuni: $drepturi"
			echo "Director: $dir"
			echo "	Fisier: $f"
			echo "	Permisiuni: `ls -l $f | awk '{print $1}'`"
			echo "	Copie: ""$f.bak"
			echo "	Permisiuni: `ls -l "$f.bak" | awk '{print $1}'`"
			echo 
		fi
	done
done
