#!/bin/bash

TOTALDIM=0
NR=0
NRDIR=0
NUMBERS=""
DIRS=""
USERS=""
>numbers.txt
while [ 1 ];do
	read -p "Give input: " input
	if [ -f $input ];then
		NR=`expr $NR + 1`
		DIM=`du -b $input | awk '{print $1}'`
		TOTALDIM=`expr $TOTALDIM + $DIM`	
	elif [ -d $input ];then
		NRDIR=`expr $NRDIR + 1`
		if ls -l -d $input | grep -q "^...x";then
			if [ ! -n $DIRS ];then
				$DIRS=$input
			else
				DIRS=$DIRS" "$input
			fi	
		fi
	elif echo $input | grep -q "^[0-9]\+$";then
		NUMBERS=$input"\n"$NUMBERS
	elif [ -n $input ];then
		if [ $input = "Stop" ];then
			echo "Terminating..."
			break
		fi
		info=`grep "$input" ../Data/last.fake | grep "Mon" | awk '{print $1}' | uniq -c | awk '{print $2" "$1}'`
		if [ -n "$info" ];then
			if [ ! -n $USERS ];then
				USERS="$info"
			else
				USERS=$USERS"\n""$info"
			fi
		fi

	else 
		echo "Nonsense"
	fi
done

echo "Total dim of file: $TOTALDIM"
echo "Nr file: $NR"
echo "NRdirs: $NRDIR"
echo "DIRS: $DIRS"
echo -e $NUMBERS | sort -rn > numbers.txt
echo -e "USERS: $USERS"
