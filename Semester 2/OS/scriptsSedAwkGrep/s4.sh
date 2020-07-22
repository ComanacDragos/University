#!/bin/bash

grep "^root" ../Data/ps.fake | \
awk '{print $6}' | \
sort | \
uniq


