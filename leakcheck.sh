#!/bin/bash
PID=$(pgrep -f minishell)

while true; do
	ps -o rss= -p "$PID"
	sleep 1
done
