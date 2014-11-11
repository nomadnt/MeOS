#include "main.h"

void usage(char *cmd){
	fprintf(stderr, "Usage:  %s [options] <device> <command>\n\n", cmd);
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "\t-b <bssid>  - filter by bssid\n\n");
	fprintf(stderr, "Commands:\n");
	fprintf(stderr, "\tairscan   -  scanning the air\n");
	fprintf(stderr, "\tchannels  -  show available channels\n");
	fprintf(stderr, "\tcountries -  show available countries\n");
	fprintf(stderr, "\tinfo      -  show info about device\n");
	fprintf(stderr, "\tstations  -  show info about joined stations\n");
	fprintf(stderr, "\ttxpowers  -  show available tx power list\n\n");	
}

int main(int argc, char **argv){
	int o;
	char *ifname = NULL;
	char *cmd = NULL;
	char *bssid = NULL;
	
	const struct iwinfo_ops *iw;

	opterr = 0;
	
	while ((o = getopt (argc, argv, "b:")) != -1){
		switch(o){
			case 'b':
				bssid = optarg;
				break;
			case '?':
				if(optopt == 'b'){
					fprintf(stderr, "option -%c requires an argument.\n\n", optopt);
				}else if(isprint(optopt)){
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				}else{
					fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
				}
				return 1;
			default:
				abort();
		}
	}
	
	if((argc - optind) > 1){
		ifname = argv[optind];
		
		iw = iwinfo_backend(ifname);
		if (!iw){
			fprintf(stderr, "No such wireless device: %s\n", ifname);
			return 1;
		}
		
		cmd = argv[optind + 1];
		
		if(strcmp(cmd, "info") == 0){
			if(bssid){
				fprintf(stderr, "Unknown option -b for command `%s'.\n", argv[optind + 1]);
				return -1;
			}
			print_info(iw, ifname);
		}else if(strcmp(cmd, "airscan") == 0){
			print_airscan(iw, ifname, bssid);
		}else if(strcmp(cmd, "channels") == 0){
			if(bssid){
				fprintf(stderr, "Unknown option -b for command `%s'.\n", argv[optind + 1]);
				return -1;
			}
			print_channels(iw, ifname);
		}else if(strcmp(cmd, "countries") == 0){
			if(bssid){
				fprintf(stderr, "Unknown option -b for command `%s'.\n", argv[optind + 1]);
				return -1;
			}
			print_countries(iw, ifname);
		}else if(strcmp(cmd, "stations") == 0){
			if(bssid){
				fprintf(stderr, "Unknown option -b for command `%s'.\n", argv[optind + 1]);
				return -1;
			}
			print_stations(iw, ifname, bssid);
		}else if(strcmp(cmd, "txpowers") == 0){
			if(bssid){
				fprintf(stderr, "Unknown option -b for command `%s'.\n", argv[optind + 1]);
				return -1;
			}
			print_txpowers(iw, ifname);
		}else{
			fprintf(stderr, "Unknown command `%s'.\n", argv[optind + 1]);
			return 1;
		}
		
		iwinfo_finish();
		
	}else{
		usage(argv[0]);
		return 1;
	}
	
	return 0;
}
