/**
 * Name        : blink.c
 * Author      : Filippo Sallemi
 * Version     : 0.3.0
 * Copyright   : copyright 2014 Nomad NT
 * Description : MeOS rssi leds daemon
 **/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#include <json/json.h>

#include "blink.h"
#include "iwinfo.h"

json_object *obj;

void usage(){
	fprintf(stderr, "Usage:  %s [options] <vendor> <model> <device>\n\n", BINARY);
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "\t-i <interval>  - Refresh interval\n\n");
}

int file_get_contents(const char *filename, char **data){
	if(access(filename, F_OK) != -1){
		FILE *fd;
		int size;

		if((fd = fopen(filename, "r")) == NULL){
			perror("Error on fopen");
			return -1;
		}

		fseek(fd , 0L , SEEK_END);
		size = ftell(fd);
		rewind(fd);

		*data = calloc(1, size + 1);
		if(fread(*data, size, 1, fd))
		fclose(fd);
		return 0;
	}else{
		return -1;
	}
}

int file_put_contents(const char *filename, char *data){
	FILE *fd;
	fd = fopen(filename, "w");
	if(fd == NULL) {
		perror("Error on fopen");
		return -1;
	}
	fputs(data, fd);
	fclose(fd);
	return 0;
}

int set_led(const char *led, char *key, char *value){
	char *file = (char *) malloc(strlen(LEDS_PATH) + strlen(led) + strlen(key) + 2);
	file = strcat(strcat(strcat(strcpy(file, LEDS_PATH), led), "/"), key);
	if(access(file, F_OK) != -1){
		return file_put_contents(file, value);
	}
	return -1;
}

int get_led(const char *led, char *key, char **value){
	char *file = (char *) malloc(strlen(LEDS_PATH) + strlen(led) + strlen(key) + 1);
	file = strcat(strcat(strcpy(file, LEDS_PATH), led), key);
	if(access(file, F_OK) != -1){
		return file_get_contents(file, value);
	}
	return -1;
}

int get_link_quality(const struct iwinfo_ops *iw, const char *ifname){
	int quality = 0;
	int max_quality = 0;

	if(!iw) return -1;
	if(max_quality < 1){
		if(iw->quality_max(ifname, &max_quality)) return -1;
	}
	if(iw->quality(ifname, &quality)) return -1;
	return (quality * 100) / max_quality;
}

int load_leds(char *vendor, char *model, json_object **obj){
	char *json;

	if(!file_get_contents(HARDWARE_DB, &json)){
		syslog(LOG_ERR, "Unable to open %s\n", HARDWARE_DB);
		return -1;
	}
	*obj = json_tokener_parse(json);
	if(!json_object_is_type(*obj, json_type_object)){
		syslog(LOG_ERR, "Unable to parse %s\n", HARDWARE_DB);
		return -1;
	}
	*obj = json_object_object_get(*obj, vendor);
	if(!json_object_is_type(*obj, json_type_object)){
		syslog(LOG_ERR, "%s is not type: object", vendor);
		return -1;
	}
	*obj = json_object_object_get(*obj, model);
	if(!json_object_is_type(*obj, json_type_object)){
		syslog(LOG_ERR, "%s is not type: object", model);
		return -1;
	}
	*obj = json_object_object_get(*obj, "leds");
	if(!json_object_is_type(*obj, json_type_array)){
		syslog(LOG_ERR, "Led is not type: array");
		return -1;
	}
	free(json);
	return 0;
}

int reset_leds(){
	int i = 0;
	const char *led;
	for(i = 0; i < json_object_array_length(obj); i++){
		led = json_object_get_string(json_object_array_get_idx(obj, i));
		if(set_led(led, "trigger", "none")){
			syslog(LOG_ERR, "Unable to set trigger on %s\n", led);
			return -1;
		}
		if(set_led(led, "brightness", "0")){
			syslog(LOG_ERR, "Unable to set brightness on %s\n", led);
			return -1;
		}
	}
	return 0;
}

void teardown(int sig){
	syslog(LOG_INFO, "Stopping %s", BINARY);
	reset_leds();
	unlink(PID_FILE);
	exit(EXIT_SUCCESS);
}

int do_daemon(char *vendor, char *model, char *device, int interval){
	FILE *pid_file;
	pid_t pid, sid;
	struct sigaction sa;

	const struct iwinfo_ops *iw = NULL;
	int quality = -1;
	int current_quality = -1;
	int leds = 0;

	sa.sa_handler = teardown;
	sa.sa_flags = SA_NOCLDWAIT | SA_RESTART;
	sigaction(SIGHUP,  &sa, NULL);
	sigaction(SIGINT,  &sa, NULL);
	sigaction(SIGPIPE, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	pid = fork();
	if(pid < 0){
		syslog(LOG_ERR, "Can't fork process");
		return EXIT_FAILURE;
	}
	if(pid > 0){
		// Leaving parent process
		return EXIT_SUCCESS;
	}
		// Starting child process
	umask(0);
	openlog(BINARY, 0, LOG_DAEMON);
	sid = setsid();
	if(sid < 0){ return EXIT_FAILURE; }
	if((chdir("/tmp")) < 0){ return EXIT_FAILURE; }

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	syslog(LOG_INFO, "Starting %s", BINARY);

	// Loading json configuration
	if(load_leds(vendor, model, &obj) < 0){
		syslog(LOG_ERR, "Unable to load leds definition");
		return -1;
	}

	// Check if object has some led definition
	if((leds = json_object_array_length(obj)) > 0){
		int i;
		const char *led;

		// Create pid file
		if((pid_file = fopen(PID_FILE, "w")) == NULL){
			syslog(LOG_ERR, "Can't create %s file", PID_FILE);
			return EXIT_FAILURE;
		}
		fprintf(pid_file, "%i", getpid());
		fclose(pid_file);

		if(reset_leds()){
			syslog(LOG_ERR, "Unable to reset leds\n");
			return -1;
		}

		do{
			quality = get_link_quality(iw, device);
			if(quality != current_quality){
				// Updating led bar
				for(i = 0; i < leds; i++){
					led = json_object_get_string(json_object_array_get_idx(obj, i));
					int seg = (100 / leds) * i;
					if(quality - seg > 0){
						if(set_led(led, "trigger", "default-on")){
							syslog(LOG_ERR, "Unable to set trigger on %s\n", led);
							return -1;
						}
					}else{
						if(set_led(led, "trigger", "none")){
							syslog(LOG_ERR, "Unable to set trigger on %s\n", led);
							return -1;
						}
						if(set_led(led, "brightness", "0")){
							syslog(LOG_ERR, "Unable to set brightness on %s\n", led);
							return -1;
						}
					}
				}
				current_quality = quality;
			}
			
			if(quality == -1 && current_quality == -1){
				if(iw){
					iwinfo_finish();
					iw = NULL;
					usleep(500000);
				}
				while(!(iw = iwinfo_backend(device))) usleep(500000);
			}
			sleep(interval);
		}while(1);
		iwinfo_finish();
	}else{
		syslog(LOG_ERR, "No leds definition found. Exit");
	}

	closelog();
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]){
	int option;
	int interval = 5;

	opterr = 0;
	while ((option = getopt(argc, argv, "i:")) != -1){
		switch(option){
			case 'i':
				interval = atoi(optarg);
				break;
			case '?':
				if(optopt == 'i'){
					fprintf(stderr, "option -%c requires an argument.\n\n", optopt);
					usage();
				}else if(isprint(optopt)){
					fprintf(stderr, "Unknown option `-%c'.\n\n", optopt);
					usage();
				}else{
					fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
					usage();
				}
				return EXIT_FAILURE;
			default:
				abort();
		}
	}

	if((argc - optind) < 3){
		usage();
		return EXIT_FAILURE;
	}

	return do_daemon(argv[optind], argv[optind + 1], argv[optind + 2], interval);
}
