#!/bin/bash

logFiles=`find ../Data/copyDir`

for i in `find ../Data/copyDir -type f -name "*.log"`; do
	echo -n `cat $i | sort > $i.new`
	echo -n `cat $i.new > $i`
	echo -n `rm $i.new`
done



