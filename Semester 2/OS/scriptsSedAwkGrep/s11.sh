#!/bin/bash

awk '{print $2}' ../Data/ps.fake | \
grep "^[0-9]" | \
awk -f ./awk11
