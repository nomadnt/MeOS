// Copyright (C) 2009-2012 nomadnt.com

#ifndef IWINFO_ESSID_MAX_SIZE
#include "iwinfo.h"
#endif

extern char * tolowercase(char *str);
extern char * format_bssid(unsigned char *value);
extern char * format_essid(char *value);
extern char * format_mode(int value);
extern char * format_channel(int value);
extern char * format_frequency(int value);
extern char * format_frequency_offset(int value);
extern char * format_txpower(int value);
extern char * format_txpower_offset(int value);
extern char * format_quality(int value);
extern char * format_quality_max(int value);
extern char * format_signal(int value);
extern char * format_noise(int value);
extern char * format_rate(int value);
extern char * format_encryption(struct iwinfo_crypto_entry *c);
char * format_encryption_ciphers(int value);
char * format_encryption_suites(int value);
extern char * format_hwmodes(int modes);
extern char * format_station_rate(struct iwinfo_rate_entry *r);
extern char * format_hardware_id(struct iwinfo_hardware_id *ids);
extern char * format_hardware_name(char *value);
extern char * format_mbssid_support(int value);
