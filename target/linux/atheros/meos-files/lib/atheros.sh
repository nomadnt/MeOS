#!/bin/sh
#
# Copyright (C) 2009-2011 OpenWrt.org
#

ATHEROS_BOARD_NAME=
ATHEROS_MODEL=

atheros_board_detect(){
	local machine
    local name

    machine=$(awk 'BEGIN{FS="[ \t]+:[ \t]"} /machine/ {print $2}' /proc/cpuinfo)

	[ -z "$name" ] && name="unknown"

    [ -z "$ATHEROS_BOARD_NAME" ] && ATHEROS_BOARD_NAME="$name"
    [ -z "$ATHEROS_MODEL" ] && ATHEROS_MODEL="$machine"

    [ -e "/tmp/sysinfo/" ] || mkdir -p "/tmp/sysinfo/"

    echo "$ATHEROS_BOARD_NAME" > /tmp/sysinfo/board_name
    echo "$ATHEROS_MODEL" > /tmp/sysinfo/model
}

atheros_board_name() {
    local name

    [ -f /tmp/sysinfo/board_name ] && name=$(cat /tmp/sysinfo/board_name)
    [ -z "$name" ] && name="unknown"

    echo "$name"
}
