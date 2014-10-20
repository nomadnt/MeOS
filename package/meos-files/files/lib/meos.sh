#!/bin/sh
# Copyright (C) 2009-2014 nomadnt.org

. /lib/functions.sh
. /usr/share/libubox/jshn.sh

include /lib/nnt

DEBUG=0

LOG_DIR="/var/log"			# MeOS default log directory
VAR_DIR="/var/meos"			# MeOS default var directory
RUN_DIR="/var/run/meos"		# MeOS default run directory

MSH_DEV="bat0" 				# Default mesh device name

sys_role(){
	local role="$1"
	if [ -n "$role" ]; then
		echo "$role" | grep -qs 'B\|G' && uci_toggle_state system @system[0] role "$role"
	else
		uci_get_state system @system[0] role
	fi
}

sys_version(){
	cat /etc/meos_version
}

sys_log(){
	logger -s -t "${3:-${0##*/}}" -p ${2:-INFO} "$1"
}

meos_debug(){
	[ $DEBUG -eq 1 ] && printf "[%s] %s: %s\n" "$(date '+%b %d %T')" "${0##*/}" "$@"
}

meos_default_wan(){
	local eth model

	[ -e /var/sysinfo/board_name ] && model="$(cat /var/sysinfo/board_name)"
	case "$model" in
		# ubnt
		"bullet-m") eth="eth0" ;;
		"nanostation-m") eth="eth0" ;;
		# alfa
		"hornet-ub") eth="eth1" ;;
		"tube-2h") eth="eth0" ;;
		*) eth="eth0"
	esac

	echo ${eth:-eth0}
}

[ -e $VAR_DIR ] || mkdir -p $VAR_DIR
[ -e $RUN_DIR ] || mkdir -p $RUN_DIR