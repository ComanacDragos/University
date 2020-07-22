#!/bin/bash

grep ".*" ../Data/passwd.fake | \
sed "s/[^r]//g" | \
sort | \
uniq 
