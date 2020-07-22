#!/bin/bash
grep ".*economica.*Sun" ../Data/last.fake | \
awk '{print $1}' | \
sort  | \
uniq -c 

