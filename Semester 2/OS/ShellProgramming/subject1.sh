#!/bin/bash

if [ $# -eq 0 ];then
	echo "Numar insuficient de argumente"
	exit 1
fi

while [ 1 ];do
	read -p "Give word: " word
	if [ $word = "stop" ];then
		echo "Terminating..."
		exit 1
	fi
	for f in $*;do
		if [ -f $f ];then
			if file $f | grep -q "ASCII text";then
				echo 
				echo "Cuvant: $word"
				echo "Fisier: $f"
				aparitii=`grep -o "\<$word\>" $f | wc -l`
				echo "Numar de apartiii $aparitii"
				if [ `expr $aparitii % 2` -eq 1 ];then
					echo $word >> $f
				fi
				echo "Fisier: "
				cat $f
				
				echo
			else
				echo
				echo "Fisier: $f"	
				echo "Fisierul dat nu este de tip text"
				echo
			fi
		fi
	done
done
