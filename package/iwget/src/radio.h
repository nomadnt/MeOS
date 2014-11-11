// Copyright (C) 2009-2012 nomadnt.com

#include "iwinfo.h"
#include "format.h"

struct radio_channel {
	int channel;
	int use;
	int snr;
	int val;
	struct radio_channel *next;
};

static char * get_ssid(const struct iwinfo_ops *iw, const char *ifname);
static char * get_bssid(const struct iwinfo_ops *iw, const char *ifname);
static char * get_mode(const struct iwinfo_ops *iw, const char *ifname);
static char * get_channel(const struct iwinfo_ops *iw, const char *ifname);
static char * get_frequency(const struct iwinfo_ops *iw, const char *ifname);
static char * get_frequency_offset(const struct iwinfo_ops *iw, const char *ifname);
static char * get_txpower(const struct iwinfo_ops *iw, const char *ifname);
static char * get_txpower_offset(const struct iwinfo_ops *iw, const char *ifname);
static char * get_quality(const struct iwinfo_ops *iw, const char *ifname);
static char * get_quality_max(const struct iwinfo_ops *iw, const char *ifname);
static char * get_signal(const struct iwinfo_ops *iw, const char *ifname);
static char * get_noise(const struct iwinfo_ops *iw, const char *ifname);
static char * get_rate(const struct iwinfo_ops *iw, const char *ifname);
static char * get_encryption(const struct iwinfo_ops *iw, const char *ifname);
static char * get_type(const struct iwinfo_ops *iw, const char *ifname);
static char * get_hwmodes(const struct iwinfo_ops *iw, const char *ifname);
static char * get_hardware_id(const struct iwinfo_ops *iw, const char *ifname);
static char * get_hardware_name(const struct iwinfo_ops *iw, const char *ifname);
static char * get_mbssid_support(const struct iwinfo_ops *iw, const char *ifname);

extern void print_info(const struct iwinfo_ops *iw, const char *ifname);
extern void print_airscan(const struct iwinfo_ops *iw, const char *ifname, const char *bssid);
extern void print_stations(const struct iwinfo_ops *iw, const char *ifname, const char *bssid);
extern void print_channels(const struct iwinfo_ops *iw, const char *ifname);
extern void print_txpowers(const struct iwinfo_ops *iw, const char *ifname);
extern void print_countries(const struct iwinfo_ops *iw, const char *ifname);

