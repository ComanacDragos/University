#!/bin/bash

grep "^r" ../Data/ps.fake | \
awk '{print $1}' | \
sort | \
uniq | \
sed "s/\([aeiou]\)/\1\1/g"
