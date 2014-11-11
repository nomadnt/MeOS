MeOS
====

MeOS is an opensource firmware based to openwrt and batman-adv used to build mesh network from small to big

## Build MeOS from scratch

### Ubuntu

Open your terminal and type:

```
~# sudo apt-get update
~# sudo apt-get install git-core build-essential subversion vim gawk zlib1g-dev libncurses5-dev
~# git clone git@github.com:nomadnt/MeOS.git meos
~# cd meos
~# ./scripts/feeds update
~# ./scripts/feeds install kmod-batman-adv
~# ./scripts/feeds install iperf
~# ./scripts/feeds install tinc
~# ./scripts/feeds install mini-smnpd
~# ./scripts/feeds install -p nomadnt libnnt
~# ./scripts/feeds install -p nomadnt iwget
~# ./scripts/feeds install -p nomadnt curl
```

```
~# make menuconfig
~# make
```
