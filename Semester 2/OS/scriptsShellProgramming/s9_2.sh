#!/bin/bash


paths=`find ../Data/testDir`
f=""
for i in $paths
do
	if [ -f $i ]; then
		f1=`md5sum $i | awk '{print $1}'`
		for j in $paths
		do
			if [ -f $j ]; then
				f2=`md5sum $j | awk '{print $1}'`
				if [ $f1 = $f2 ] && [ $i != $j ] ; then
					f="$f\n$i"
				fi
			fi 
		done
	fi
done

#echo $f | sed 's/\(^\\n\)//'
#echo $f
f=$(echo $f | sed 's/\(^\\n\)//')

echo -e $f | sort | uniq
