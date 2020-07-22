#!/bin/bash

names=`awk '{print $1}' ../Data/who.fake`


for name in $names; do
	psCount=`grep -c "^\<$name\>" ../Data/ps.fake`
	echo "$name $psCount"
done
