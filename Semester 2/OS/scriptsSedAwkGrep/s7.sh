#!/bin/bash

grep "^t.*pts/9" ../Data/last.fake | \
awk '{print $1}' | \
sort | \
uniq
