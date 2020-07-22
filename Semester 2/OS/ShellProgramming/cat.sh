#!/bin/bash

for f in `ls . | grep "\.txt$"`;do
	if grep -q "\<cat\>" $f;then
		echo $f
	fi
done
