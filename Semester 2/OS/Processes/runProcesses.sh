#!/bin/bash

for i in $*;do
	if echo $i | grep -q "^...x";then
		./$i
	fi
done
