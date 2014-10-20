#!/bin/sh

do_atheros() {
	. /lib/atheros.sh

	atheros_board_detect
}

boot_hook_add preinit_main do_atheros
