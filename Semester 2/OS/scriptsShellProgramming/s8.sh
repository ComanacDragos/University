#!/bin/bash
tail -n+2 ../Data/df.fake | \
sed "s/M//g" | \
sed "s/%//g" | \
awk '$4 < 1000 || $5 > 80{print $6}' 
