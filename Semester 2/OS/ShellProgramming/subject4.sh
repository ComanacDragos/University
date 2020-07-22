#!/bin/bash

history=""
sum=0
files=0
>file
>dirs
filesNames=""
while [ 1 ];do
	read -p "Give input: " s
	
	if echo $s | grep -q "^-";then
		s1=`echo $s | awk '{print substr($1,2)}'`
		if echo $history | grep -q "\-$s1";then
			break
		fi
	elif echo $history | grep -q "$s";then
		break
	fi
	history=$s" "$history
	if [ -d $s ];then
		#find $d -type f | ls -l | grep "\.c$" | awk '{print $5" "$NF}' | sort -rn
		files=`find $d -type f | grep "\.c$"` #| awk '{print $5" "$NF}' | sort -rn
		info=""
		for i in $files;do
			info=`ls -l $i | awk '{print $5" "$NF}'`"\n"$info
		done
		echo DIR: $s >> dirs
		echo -e $info | head -n -1 | sort -rn | head -3 >> dirs
	elif [ -f $s ];then
		files=`expr $files + 1`
		if ls -l $s | grep -q "^-r";then
			filesNames=$filesNames" "$s
		fi
	elif echo $s | grep -q "^[0-9]\+$";then
		sum=`expr $sum + $s`
	elif echo $s | grep -q "^-[0-9]\+$";then
		sum=`expr $sum + $s`
	elif grep -q "^$s " ../Data/ps.fake;then
		nr=`grep -c "^$s" ../Data/ps.fake`
		echo $s $nr >> file
	fi
	
done
cat dirs
rm dirs
echo SUM: $sum
echo Number of files: $files
echo Files with read permission: $filesNames
echo
cat file
