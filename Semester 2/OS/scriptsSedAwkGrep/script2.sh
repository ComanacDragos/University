#!/bin/bash

for i in awk {'print $1 " " $7'} ../Data/last.fake;do
	echo bla $i
done

