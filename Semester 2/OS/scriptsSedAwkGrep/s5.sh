#!/bin/bash

grep "^[a-z]\{4,4\}[0-9]\{2,2\}88" ../Data/passwd.fake | \
awk -F: '{print $5}'
