#!/bin/bash

#echo $* | sed "s/ /\\n/g" | uniq | sort 
for i in `echo $* | sed "s/ /\\n/g" | uniq | sort `;do
	#echo $i
	if [ -d $i ];then
	#ls -l $i
	DIRS=`ls -l $i | grep -c "^d.*"`
	FILES=`ls -l $i | grep -c "^-.*"`
  	echo "$FILES/$DIRS-$i"	
	fi
done
