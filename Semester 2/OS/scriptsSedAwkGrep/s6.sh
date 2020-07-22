#!/bin/bash

grep "^.*:x:23[0-9]:" ../Data/passwd.fake | \
awk -F: '{print $5}'
