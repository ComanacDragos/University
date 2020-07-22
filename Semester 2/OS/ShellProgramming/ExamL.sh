#!/bin/bash


if [ $# -eq 0 ];then
	echo "NR insuficent de argumente"
	exit 1
fi

while [ 1 ];do
	read -p "Numar: " nr
	if [ $nr -eq 0 ];then
		break
	fi
	read -p "Fisier: " fisier
	>$fisier

	len=`wc -l $1 | awk '{print $1}'`
	i=1
	prop=""
	while [ $i -le $len ];do
		cuv=`head -$i $1 | tail -1`
		prop=$prop" "$cuv
		if [ `expr $i % $nr` -eq 0 ];then
			echo $prop >> $fisier
			#echo $i
			#echo $prop
			prop=""	
		fi
		i=`expr $i + 1`
	done
	if [ `echo $prop | wc -w` -ne 0 ];then
		echo $prop >> $fisier
	fi
	chars=`wc -m $fisier | awk '{print $1}'`
	chars=`expr $chars - 1`

	echo "Linii: `wc -l $fisier | awk '{print $1}'` Cuvinte: `wc -w $fisier | awk '{print $1}'` Caractere: $chars"

done
