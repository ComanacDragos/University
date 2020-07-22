#!/bin/bash

ps=`tail -n +2 ../Data/ps.fake | awk '{print $1" "$2}' | head -n -1`

declare -A user_count
declare -A pid_sum

i=0
while read user pid;do
	i=$((i+1))
	user_count[$user]=$((user_count[user]+1))
	pid_sum[$user]=$((pid_sum[user]+pid))
	#echo $user $pid
		
done <<< "$ps"

for user in "${!user_count[@]}";do
	echo $user $((pid_sum[$user]/user_count[$user]))
done
