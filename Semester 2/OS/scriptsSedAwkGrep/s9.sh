#!/bin/bash

grep ".*" ../Data/passwd.fake | \
sed  "s/[a-zA-Z0-9 ]//g" | \
sort | \
uniq

