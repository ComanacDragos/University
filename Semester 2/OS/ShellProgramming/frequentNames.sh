#!/bin/bash

awk -F: '{print $5}' ../Data/passwd.fake | \
cut -d ' ' -f2  | \
sed "s/[ -]/\n/g" | \
tr '[A-Z]' '[a-z]' | \
grep -v "\.\|^.$" | \
sort | \
uniq -c | \
sort -n -r | \
less

 

