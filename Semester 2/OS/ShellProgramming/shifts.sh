#!/bin/bash

echo "Command: $0"
shift
shift
echo "Param count: $#"
for i in $*;do
	echo $i
done


echo "Exit code: $?"

false
 
echo "Exit code: $?"
