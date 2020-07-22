#!/bin/bash

month=`date | awk '{print $2}'`
echo $month

grep "\<$month\>" ../Data/last2.fake | awk '{print $1}' | sort | uniq -c | sort -nr

