#!/bin/bash

f=`cat ../Data/s7Input.txt`

s=""

for i in $f; do
	append="@scs.ubbcluj.ro"
	s="$s$i$append, "
done

s=`echo $s | sed "s/,$//"`

echo $s

