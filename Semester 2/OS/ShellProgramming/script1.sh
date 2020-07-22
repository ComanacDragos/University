#!/bin/bash

while [ 1 ]; do
	read  A
	echo $A | sed "s/./*/gi"
done
