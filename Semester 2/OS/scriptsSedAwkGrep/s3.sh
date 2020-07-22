#!/bin/bash


awk '{print $1 " " $7}' ../Data/last.fake | \
sed "s/:/ /" | \
awk '$2 >= 23 {print $1 " " $2 " " $3}' | \
head -n -1 | \
awk '{print $1}' | \
sort | \
uniq 
