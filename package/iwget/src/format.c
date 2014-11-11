// Copyright (C) 2009-2012 nomadnt.com

#include "format.h"

extern char * tolowercase(char *str){
	for(int i=0; str[i]; i++) str[i] = tolower(str[i]);
	return str;
}

extern char * format_bssid(unsigned char *value){
	static char bssid[18];

	snprintf(bssid, sizeof(bssid), "%02X:%02X:%02X:%02X:%02X:%02X",
		value[0], value[1], value[2], value[3], value[4], value[5]);

	return bssid;
}

extern char * format_essid(char *value){
	static char ssid[IWINFO_ESSID_MAX_SIZE+3];

	if (value && value[0])
		snprintf(ssid, sizeof(ssid), "%s", value);
	else
		snprintf(ssid, sizeof(ssid), " ");
		
	return ssid;
}

extern char * format_mode(int value){
	static char mode[128];

	snprintf(mode, sizeof(mode), "%s", IWINFO_OPMODE_NAMES[value]);

	return tolowercase(mode);
}

extern char * format_ccode(char *value){
	static char code[3];
	snprintf(code, sizeof(code), "%s", value);
	return code;
}

extern char * format_channel(int value){
	static char channel[8];

	if(value <= 0){
		snprintf(channel, sizeof(channel), "nd");
	}else{
		snprintf(channel, sizeof(channel), "%d", value);
	}

	return channel;
}

extern char * format_frequency(int value){
	static char frequency[10];

	if(value <= 0){
		snprintf(frequency, sizeof(frequency), "nd");
	}else{
		snprintf(frequency, sizeof(frequency), "%.3f GHz", ((float)value / 1000.0));
	}

	return frequency;
}

extern char * format_frequency_offset(int value){
	static char offset[10];

	if(value <= 0){
		snprintf(offset, sizeof(offset), "nd");
	}else{
		snprintf(offset, sizeof(offset), "%.3f GHz", ((float)value / 1000.0));
	}

	return offset;
}

extern char * format_txpower(int value){
	static char power[10];

	if(value < 0){
		snprintf(power, sizeof(power), "nd");
	}else{
		snprintf(power, sizeof(power), "%d dBm", value);
	}
	
	return power;
}

extern char * format_txpower_offset(int value){
	static char offset[10];

	if(value < 0){
		snprintf(offset, sizeof(offset), "nd");
	}else{
		snprintf(offset, sizeof(offset), "%d dBm", value);
	}

	return offset;
}

extern char * format_quality(int value){
	static char quality[8];

	if (value < 0){
		snprintf(quality, sizeof(quality), "nd");
	}else{
		snprintf(quality, sizeof(quality), "%d", value);
	}

	return quality;
}

extern char * format_quality_max(int value){
	static char qmax[8];

	if (value < 0){
		snprintf(qmax, sizeof(qmax), "nd");
	}else{
		snprintf(qmax, sizeof(qmax), "%d", value);
	}
	
	return qmax;
}

extern char * format_signal(int value){
	static char signal[10];

	snprintf(signal, sizeof(signal), "%d dBm", value);

	return signal;
}

extern char * format_noise(int value){
	static char noise[10];

	snprintf(noise, sizeof(noise), "%d dBm", value);
	
	return noise;
}

extern char * format_rate(int value){
	static char rate[14];

	if (value <= 0){
		snprintf(rate, sizeof(rate), "nd");
	}else{
		snprintf(rate, sizeof(rate), "%d.%d MBit/s",
			value / 1000, (value % 1000) / 100);
	}

	return rate;
}

extern char * format_packets(int value){
	static char packets[10];

	snprintf(packets, sizeof(packets), "%d", value);

	return packets;
}

extern char * format_encryption(struct iwinfo_crypto_entry *c){
	static char encryption[512];

	if (!c){
		snprintf(encryption, sizeof(encryption), "nd");
	}else if (c->enabled){
		/* WEP */
		if (c->auth_algs && !c->wpa_version){
			if ((c->auth_algs & IWINFO_AUTH_OPEN) && (c->auth_algs & IWINFO_AUTH_SHARED)){
				snprintf(encryption, sizeof(encryption), "WEP Open/Shared (%s)",
					format_encryption_ciphers(c->pair_ciphers));
			}else if (c->auth_algs & IWINFO_AUTH_OPEN){
				snprintf(encryption, sizeof(encryption), "WEP Open System (%s)",
					format_encryption_ciphers(c->pair_ciphers));
			}else if (c->auth_algs & IWINFO_AUTH_SHARED){
				snprintf(encryption, sizeof(encryption), "WEP Shared Auth (%s)",
					format_encryption_ciphers(c->pair_ciphers));
			}
		}

		/* WPA */
		else if (c->wpa_version){
			switch (c->wpa_version) {
				case 3:
					snprintf(encryption, sizeof(encryption), "mixed WPA/WPA2 %s (%s)",
						format_encryption_suites(c->auth_suites),
						format_encryption_ciphers(c->pair_ciphers | c->group_ciphers));
					break;

				case 2:
					snprintf(encryption, sizeof(encryption), "WPA2 %s (%s)",
						format_encryption_suites(c->auth_suites),
						format_encryption_ciphers(c->pair_ciphers | c->group_ciphers));
					break;

				case 1:
					snprintf(encryption, sizeof(encryption), "WPA %s (%s)",
						format_encryption_suites(c->auth_suites),
						format_encryption_ciphers(c->pair_ciphers | c->group_ciphers));
					break;
			}
		}else{
			snprintf(encryption, sizeof(encryption), "none");
		}
	}else{
		snprintf(encryption, sizeof(encryption), "none");
	}

	return encryption;
}

char * format_encryption_ciphers(int value){
	static char ciphers[128] = { 0 };
	char *pos = ciphers;

	if (value & IWINFO_CIPHER_WEP40)
		pos += sprintf(pos, "WEP-40, ");

	if (value & IWINFO_CIPHER_WEP104)
		pos += sprintf(pos, "WEP-104, ");

	if (value & IWINFO_CIPHER_TKIP)
		pos += sprintf(pos, "TKIP, ");

	if (value & IWINFO_CIPHER_CCMP)
		pos += sprintf(pos, "CCMP, ");

	if (value & IWINFO_CIPHER_WRAP)
		pos += sprintf(pos, "WRAP, ");

	if (value & IWINFO_CIPHER_AESOCB)
		pos += sprintf(pos, "AES-OCB, ");

	if (value & IWINFO_CIPHER_CKIP)
		pos += sprintf(pos, "CKIP, ");

	if (!value || (value & IWINFO_CIPHER_NONE))
		pos += sprintf(pos, "NONE, ");

	*(pos - 2) = 0;

	return ciphers;
}

char * format_encryption_suites(int value){
	static char suites[64] = { 0 };
	char *pos = suites;

	if (value & IWINFO_KMGMT_PSK)
		pos += sprintf(pos, "PSK/");

	if (value & IWINFO_KMGMT_8021x)
		pos += sprintf(pos, "802.1X/");

	if (!value || (value & IWINFO_KMGMT_NONE))
		pos += sprintf(pos, "NONE/");

	*(pos - 1) = 0;

	return suites;
}

extern char * format_hwmodes(int value){
	static char modes[12];

	if(value <= 0){
		snprintf(modes, sizeof(modes), "nd");
	}else{
		snprintf(modes, sizeof(modes), "802.11%s%s%s%s",
			(value & IWINFO_80211_A) ? "a" : "",
			(value & IWINFO_80211_B) ? "b" : "",
			(value & IWINFO_80211_G) ? "g" : "",
			(value & IWINFO_80211_N) ? "n" : "");
	}
	
	return modes;
}

extern char * format_station_rate(struct iwinfo_rate_entry *r){
	static char rate[40];
	char *p = rate;
	int l = sizeof(rate);

	if(r->rate <= 0){
		snprintf(rate, sizeof(rate), "nd");
	}else{
		p += snprintf(p, l, "%s", format_rate(r->rate));
		l = sizeof(rate) - (p - rate);

		if (r->mcs >= 0){
			p += snprintf(p, l, ", MCS %d, %dMHz", r->mcs, 20 + r->is_40mhz*20);
			l = sizeof(rate) - (p - rate);

			if (r->is_short_gi) p += snprintf(p, l, ", short GI");
		}
	}

	return rate;
}

extern char * format_hardware_id(struct iwinfo_hardware_id *ids){
	static char id[20];
	
	if(!ids){
		snprintf(id, sizeof(id), "nd");
	}else{
		snprintf(id, sizeof(id), "%04X:%04X %04X:%04X",
			ids->vendor_id, ids->device_id,
			ids->subsystem_vendor_id, ids->subsystem_device_id
		);
	}
	
	return id;
}

extern char * format_hardware_name(char *value){
	static char name[128];

	if (value && value[0]){
		snprintf(name, sizeof(name), "%s", value);
	}else{
		snprintf(name, sizeof(name), "nd");
	}

	return name;
}

extern char * format_mbssid_support(int value){
	static char support[6];

	snprintf(support, sizeof(support), "%s", value ? "yes" : "no");

	return support;
}
