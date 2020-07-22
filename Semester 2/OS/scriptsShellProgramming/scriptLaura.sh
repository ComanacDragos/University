#!/bin/bash

#Să se scrie un script bash care pentru fiecare fişier cu
#drepturile 755 dintr-un director (şi subdirectoarele sale)
#dat ca parametru îi va modifica drepturile de acces în 744.
#Înainte de a modifica drepturile de acces, script-ul va cere
#confirmarea din partea utilizatorului (pentru fiecare fişier în parte).
#(comenzi: find, chmod, read)
if [ $# -ne 1 ];then
	echo "GIB DIR!"	
	exit 1
fi

 if [ ! -d $1 ];then
	echo "NOT DIR GIB DIR!"
	exit 1
fi

for i in `find $1`;do
	if [ ! -d $i ] && ls -l $i | grep -q "^-rwxr-xr-x";then
 		read -p "Change permissions? " X
		if [ $X = "yes" ];then
			chmod 744 $i
		fi
	fi	
done
