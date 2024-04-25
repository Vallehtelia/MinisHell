#!/bin/bash

i=1
clear
echo "Shrek is sniffing for leaks..."
while true; do
	if leaks minishell | grep -q "LEAK"; then
		leaks minishell | grep "LEAK"
		while true; do
			printf "STUPID BOY! YOU HAVE TO FIX THE LEAKS!\n"
			printf "SHREK WILL BE ANGRY!\n"
			leaks minishell | grep "LEAK"
			tput setaf $i
			i=$((i+1))
			sleep 0.1
			clear
			if [ $i -gt 7 ]; then
				i=1
			fi
		done
		killall minishell
		exit 1
	fi
	sleep 1
done
