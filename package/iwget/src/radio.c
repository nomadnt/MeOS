// Copyright (C) 2009-2012 nomadnt.com

#include "radio.h"

static char * get_ssid(const struct iwinfo_ops *iw, const char *ifname){
	char ssid[IWINFO_ESSID_MAX_SIZE + 1] = { 0 };

	if(iw->ssid(ifname, ssid)) memset(ssid, 0, sizeof(ssid));

	return format_essid(ssid);
}

static char * get_bssid(const struct iwinfo_ops *iw, const char *ifname){
	static char bssid[18] = { 0 };

	if(iw->bssid(ifname, bssid)) 
		snprintf(bssid, sizeof(bssid), "00:00:00:00:00:00");

	return bssid;
}

static char * get_mode(const struct iwinfo_ops *iw, const char *ifname){
	int mode;

	if(iw->mode(ifname, &mode)) mode = IWINFO_OPMODE_UNKNOWN;

	return format_mode(mode);
}

static char * get_country_code(const struct iwinfo_ops *iw, const char *ifname){
	char code[3];
	if (iw->country(ifname, code))
		memset(code, 0, sizeof(code));

	return format_ccode(code);
}

static char * get_channel(const struct iwinfo_ops *iw, const char *ifname){
	int channel;
	if (iw->channel(ifname, &channel)) channel = -1;

	return format_channel(channel);
}

static char * get_frequency(const struct iwinfo_ops *iw, const char *ifname){
	int frequency;
	if (iw->frequency(ifname, &frequency)) frequency = -1;

	return format_frequency(frequency);
}

static char * get_frequency_offset(const struct iwinfo_ops *iw, const char *ifname){
	int offset;
	
	if(iw->frequency_offset(ifname, &offset)) offset = -1;
	
	return format_frequency_offset(offset);
}

static char * get_txpower(const struct iwinfo_ops *iw, const char *ifname){
	int power, offset;
	if(iw->txpower_offset(ifname, &offset)) offset = 0;

	if (iw->txpower(ifname, &power)) power = -1;
	else power += offset;

	return format_txpower(power);
}

static char * get_txpower_offset(const struct iwinfo_ops *iw, const char *ifname){
	int offset;

	if(iw->txpower_offset(ifname, &offset)) offset = -1;

	return format_txpower_offset(offset);
}

static char * get_quality(const struct iwinfo_ops *iw, const char *ifname){
	int quality;
	
	if (iw->quality(ifname, &quality)) quality = -1;

	return format_quality(quality);
}

static char * get_quality_max(const struct iwinfo_ops *iw, const char *ifname){
	int qmax;
	
	if (iw->quality_max(ifname, &qmax)) qmax = -1;

	return format_quality_max(qmax);
}

static char * get_signal(const struct iwinfo_ops *iw, const char *ifname){
	int signal;
	
	if(iw->signal(ifname, &signal)) signal = 0;

	return format_signal(signal);
}

static char * get_noise(const struct iwinfo_ops *iw, const char *ifname){
	int noise;
	
	if(iw->noise(ifname, &noise)) noise = 0;

	return format_noise(noise);
}

static char * get_rate(const struct iwinfo_ops *iw, const char *ifname){
	int rate;
	
	if(iw->bitrate(ifname, &rate)) rate = -1;

	return format_rate(rate);
}

static char * get_encryption(const struct iwinfo_ops *iw, const char *ifname){
	struct iwinfo_crypto_entry c = { 0 };
	
	if(iw->encryption(ifname, (char *)&c))
		return format_encryption(NULL);

	return format_encryption(&c);
}

static char * get_type(const struct iwinfo_ops *iw, const char *ifname){
	const char *type = iwinfo_type(ifname);
	
	return type ? type : "nd";
}

static char * get_hwmodes(const struct iwinfo_ops *iw, const char *ifname){
	int modes;
	
	if (iw->hwmodelist(ifname, &modes)) modes = -1;

	return format_hwmodes(modes);
}

static char * get_hardware_id(const struct iwinfo_ops *iw, const char *ifname){
	struct iwinfo_hardware_id ids = { 0 };
	static char id[20];

	if(iw->hardware_id(ifname, (char *)&ids))
		return format_hardware_id(NULL);
	
	return format_hardware_id(&ids);
}

static char * get_hardware_name(const struct iwinfo_ops *iw, const char *ifname){
	static char name[128];

	if(iw->hardware_name(ifname, &name))
		return format_hardware_name(NULL);

	return format_hardware_name(name);
}

static char * get_mbssid_support(const struct iwinfo_ops *iw, const char *ifname){
	int support;

	if(iw->mbssid_support(ifname, &support)) support = 0;

	return format_mbssid_support(support);
}

extern void print_info(const struct iwinfo_ops *iw, const char *ifname){
	printf("COUNTRY=\"%s\"\n", get_country_code(iw, ifname));
	printf("SSID=\"%s\"\n", get_ssid(iw, ifname));
	printf("BSSID=\"%s\"\n", get_bssid(iw, ifname));
	printf("MODE=\"%s\"\n", get_mode(iw, ifname));
	printf("CHANNEL=\"%s\"\n", get_channel(iw, ifname));
	printf("FREQUENCY=\"%s\"\n", get_frequency(iw, ifname));
	printf("FREQUENCY_OFFSET=\"%s\"\n", get_frequency_offset(iw, ifname));
	printf("TXPOWER=\"%s\"\n", get_txpower(iw, ifname));
	printf("TXPOWER_OFFSET=\"%s\"\n", get_txpower_offset(iw, ifname));
	printf("LINK_QUALITY=\"%s\"\n", get_quality(iw, ifname));
	printf("LINK_QUALITY_MAX=\"%s\"\n", get_quality_max(iw, ifname));
	printf("SIGNAL=\"%s\"\n", get_signal(iw, ifname));
	printf("NOISE=\"%s\"\n", get_noise(iw, ifname));
	printf("BITRATE=\"%s\"\n", get_rate(iw, ifname));
	printf("ENCRYPTION=\"%s\"\n", get_encryption(iw, ifname));
	printf("HW_TYPE=\"%s\"\n", get_type(iw, ifname));
	printf("HW_MODE=\"%s\"\n", get_hwmodes(iw, ifname));
	printf("HW_INFO=\"%s [%s]\"\n", get_hardware_id(iw, ifname), get_hardware_name(iw, ifname));
	printf("VAP_SUPPORT=\"%s\"\n", get_mbssid_support(iw, ifname));
}

extern void print_airscan(const struct iwinfo_ops *iw, const char *ifname, const char *bssid){
	int i, j, x, len;
	
	char buf[IWINFO_BUFSIZE];
	struct iwinfo_scanlist_entry *e;
	
	if (iw->scanlist(ifname, buf, &len)){
		printf("scanning not possible\n\n");
		return;
	}else if (len <= 0){
		printf("no results found\n\n");
		return;
	}
	
	printf("%s   %-20s%-37s%-34s%-5s%-16s%-10s%s\n", 
		"ID", "BSSID", "SSID", "Encryption", "CH", "Mode", "Quality", "Signal");
		
	for (i = 0, x = 1; i < len; i += sizeof(struct iwinfo_scanlist_entry), x++){
		e = (struct iwinfo_scanlist_entry *) &buf[i];
		
		if(bssid && strcmp(format_bssid(e->mac), bssid) != 0) continue;
				
		printf("%02d   ", x);
		printf("%-20s", format_bssid(e->mac));
		printf("%-37s", format_essid(e->ssid));
		printf("%-34s", format_encryption(&e->crypto));
		printf("%-5s", format_channel(e->channel));
		printf("%-16s", format_mode(e->mode));
		printf("%s/%-7s", format_quality(e->quality), format_quality_max(e->quality_max));
		printf("%s\n", format_signal(e->signal - 0x100));
	}
}

extern void print_stations(const struct iwinfo_ops *iw, const char *ifname, const char *bssid){
	int i, len;
	char buf[IWINFO_BUFSIZE];
	struct iwinfo_assoclist_entry *e;

	if (iw->assoclist(ifname, buf, &len)){
		printf("no information available\n");
		return;
	}else if (len <= 0){
		printf("no results found\n");
		return;
	}
	
	printf("%-20s%-10s%-10s%-40s%-40s%-20s\n", 
		"Station", "Signal", "Noise", "RX Rate", "TX Rate", "RX/TX Packets");
	
	for (i = 0; i < len; i += sizeof(struct iwinfo_assoclist_entry)){
		e = (struct iwinfo_assoclist_entry *) &buf[i];

		if(bssid && strcmp(format_bssid(e->mac), bssid) != 0) continue;
		
		printf("%-20s", format_bssid(e->mac));
		printf("%-10s", format_signal(e->signal));
		printf("%-10s", format_noise(e->noise));
		printf("%-40s", format_station_rate(&e->rx_rate));
		printf("%-40s", format_station_rate(&e->tx_rate));
		printf("%s/", format_packets(e->rx_packets));
		printf("%s\n", format_packets(e->tx_packets));
	}
}

extern void print_channels(const struct iwinfo_ops *iw, const char *ifname){
	int i, len, ch;
	char buf[IWINFO_BUFSIZE];
	struct iwinfo_freqlist_entry *e;

	if (iw->freqlist(ifname, buf, &len) || len <= 0){
		printf("No frequency information available\n");
		return;
	}

	if(iw->channel(ifname, &ch)) ch = -1;
	
	for (i = 0; i < len; i += sizeof(struct iwinfo_freqlist_entry)){
		e = (struct iwinfo_freqlist_entry *) &buf[i];
		printf("[%s]  %-4s (%s)  %s\n",
			   (ch == e->channel) ? "*" : " ",
			   format_channel(e->channel),
			   format_frequency(e->mhz),
			   e->restricted ? "[restricted]" : ""
		);
	}
}

extern void print_txpowers(const struct iwinfo_ops *iw, const char *ifname){
	int len, pwr, off, i;
	char buf[IWINFO_BUFSIZE];
	struct iwinfo_txpwrlist_entry *e;

	if (iw->txpwrlist(ifname, buf, &len) || len <= 0){
		printf("No TX power information available\n");
		return;
	}

	if (iw->txpower(ifname, &pwr)) pwr = -1;
	if (iw->txpower_offset(ifname, &off)) off = 0;

	for (i = 0; i < len; i += sizeof(struct iwinfo_txpwrlist_entry)){
		e = (struct iwinfo_txpwrlist_entry *) &buf[i];
		printf("[%s] %3d dBm (%d mW)\n", (pwr == e->dbm) ? "*" : " ", (e->dbm + off), iwinfo_dbm2mw(e->dbm + off));
	}
}

static char * lookup_country(char *buf, int len, int iso3166){
	struct iwinfo_country_entry *c;
	int i;

	for (i = 0; i < len; i += sizeof(struct iwinfo_country_entry)){
		c = (struct iwinfo_country_entry *) &buf[i];
		if (c->iso3166 == iso3166)
			return c->ccode;
	}

	return NULL;
}

extern void print_countries(const struct iwinfo_ops *iw, const char *ifname){
	int len;
	char buf[IWINFO_BUFSIZE];
	char *ccode;
	char curcode[3];
	const struct iwinfo_iso3166_label *l;

	if (iw->countrylist(ifname, buf, &len)){
		printf("No country code information available\n");
		return;
	}

	if (iw->country(ifname, curcode))
		memset(curcode, 0, sizeof(curcode));

	for (l = IWINFO_ISO3166_NAMES; l->iso3166; l++){
		if ((ccode = lookup_country(buf, len, l->iso3166)) != NULL){
			printf("[%s]  %c%c  %s\n",
				strncmp(ccode, curcode, 2) ? " " : "*",
				(l->iso3166 / 256), (l->iso3166 % 256),
				l->name
			);
		}
	}
}
