#!/bin/sh
# Copyright (C) 2009-2014 nomadnt.com

BAT_DIR="/sys/kernel/debug/batman_adv"

get_mesh_originators(){
	local bat="$BAT_DIR/${1:-bat0}/originators"
	local gw
	[ -e $bat ] && {		
		gw=$(get_mesh_gateway ${1:-bat0} | awk '{print $1}')
		sed '1,2d;/^No/d;s/\((\|)\|\[\|\]:\)//g;s/  */\ /g' $bat | awk -v gw=$gw '{ \
			if($1 == gw){ \
				printf("[*]  %-18s %-4s %-18s %s\n", $1, $3, $4, $5) \
			}else{ \
				printf("[ ]  %-18s %-4s %-18s %s\n", $1, $3, $4, $5) \
			} \
		}'
	}
}

get_mesh_gateways(){
	local bat="$BAT_DIR/${1:-bat0}/gateways"
	[ -e $bat ] && {
		sed '1d;/^No/d;s/=>/*/;s/\((\|)\|\[\|\]:\)//g' $bat | awk '{ \
			if(NF > 7){ \
				printf("[%s]  %-18s %-4s %-18s %s\n", $1, $2, $3, $4, $5) \
			}else{ \
				printf("[%s]  %-18s %-4s %-18s %s\n", " ", $1, $2, $3, $4) \
			} \
		}'
	}
}

get_mesh_gateway(){
	local bat="$BAT_DIR/${1:-bat0}/gateways"
	[ -e $bat ] && {
		sed '/^No/d;/=>/!d;s/=> \(.*\) ( *\(.*\)) \(.*\) \[ *\(.*\)\]:.*/\1 \2 \3 \4/g' $bat
	}
}

get_mesh_nbs(){
	local bat=${1:-bat0}
	get_mesh_originators $bat | awk -F'  ' '$2 ~ $4 {print $1 " " $2 " " $3 " " $4 " " $5}'
}

get_mesh_hops(){
	local mac=${1:-$(get_mesh_gateway | awk '{print $1}')}
	local bat=${2:-bat0}
	
	[ -n "$mac" ] && {
		batctl -m $bat tr $mac -n | sed '$!d;s/^ //' | awk -F: '{print $1}'
	} || {
		echo 0
	}
}

get_mesh_topology(){
	local type=${1:-text}
    local bat=${2:-bat0}
	case "$type" in
		json)
			batctl -m $bat vd json -2Tn | awk \
				'BEGIN{printf("[")}{if(getline == 1) printf("%s,\n", $0)}END{printf("%s]\n", $0)}'
		;;
		dot)
			batctl -m $bat vd dot -2Tn
		;;
		text|*)
			[ -e $BAT_DIR/$bat/originators ] && {
				sed '1,2d;/No batman nodes/d;s/\((\|)\|\[\|\]:\)//g;s/  */\ /g' $BAT_DIR/$bat/originators
			}
		;;
	esac
}

get_mesh_route(){
    local dst=$1
    local bat=${2:-bat0}
    local route
    
    [ -n "$dst" ] && {
        for node in $(batctl -m $bat tr $dst | sed '1d' | awk '{print $2}'); do
            append route $node '.'
        done   
    }   
    echo $route
}

get_mesh_clients(){
	local exclude
	local bat="${1:-bat0}"
	local table="/sys/kernel/debug/batman_adv/$bat/transtable_local"
	local clients=0
	
	config_load network
	config_get type mesh type
	config_get ifname mesh ifname
	
	[ -n "$ifname" ] && {
		append exclude "$(net_get_macaddr $ifname)"
		[ "$type" == "bridge" ] && {
			config_get devices mesh device
			for device in $devices; do
				append exclude "$(net_get_macaddr $device)"
			done
		}
	}
	
	for client in $(sed 1,2d $table | awk '{print $2}'); do
        local found=0
        for mac in $exclude; do
			[ "$mac" == "$client" ] && {
				found=1
				break
			}
		done

		[ $found -eq 0 ] && {
			clients=$(($clients + 1))
		}
	done

	echo $clients
}
