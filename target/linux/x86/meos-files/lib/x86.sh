#!/bin/sh
#
# Copyright (C) 2009-2011 OpenWrt.org
#

X86_BOARD_NAME=
X86_MODEL=

x86_board_detect(){
	local machine
    local name

    #machine=$(awk 'BEGIN{FS="[ \t]+:[ \t]"} /vendor_id/ {print $2}' /proc/cpuinfo)
	machine=$(awk 'BEGIN{FS="[ \t]+:[ \t]"} /model name/ {print $2}' /proc/cpuinfo)

	case "$machine" in
		"QEMU Virtual"*)
			name="qemu"
			;;
		"Unknown")
			machine="Generic x86"
			;;
	esac
	
	[ -z "$name" ] && name="unknown"

    [ -z "$X86_BOARD_NAME" ] && X86_BOARD_NAME="$name"
    [ -z "$X86_MODEL" ] && X86_MODEL="$machine"

    [ -e "/tmp/sysinfo/" ] || mkdir -p "/tmp/sysinfo/"

    echo "$X86_BOARD_NAME" > /tmp/sysinfo/board_name
    echo "$X86_MODEL" > /tmp/sysinfo/model
}

x86_board_name() {
    local name

    [ -f /tmp/sysinfo/board_name ] && name=$(cat /tmp/sysinfo/board_name)
    [ -z "$name" ] && name="unknown"

    echo "$name"
}

