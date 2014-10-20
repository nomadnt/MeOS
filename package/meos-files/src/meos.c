/**
 * Name        : meos.c
 * Author      : Filippo Sallemi
 * Version     : 0.3.0
 * Copyright   : copyright 2014 Nomad NT
 * Description : MeOS scripts scheduler
 **/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <time.h>
#include "meos.h"

void teardown(int sig){
	syslog(LOG_INFO, "Stopping %s", BINARY);
	unlink(PID_FILE);
	exit(EXIT_SUCCESS);
}

void usage(){
	fprintf(stderr, "Usage:  %s [options]\n\n", BINARY);
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "\t-i <interval>   - scripts execution interval in minutes (default 5)\n");
	fprintf(stderr, "\t-d <directory>  - scripts directory (default /usr/share/meos)\n\n");
	exit(EXIT_SUCCESS);
}

int call(const char *command){
	char c;
	char *data;
	FILE *pipe;
	int offset = 1;

	data = (char *)malloc(sizeof(char) * (offset));
	data[0] = '\0';

	pipe = popen(command, "r");
	if(pipe == NULL){
		perror("Error on popen");
		return -1;
	}

	while((c = fgetc(pipe)) != EOF){
		offset++;
		data = realloc(data, (sizeof(char) * (offset)));
		data[offset - 2] = c;
	}
	data[offset - 1] = '\0';

	return pclose(pipe) / 256;
}

int do_daemon(unsigned int interval, char *dirname){
	FILE *pid_file;
	pid_t pid, sid;
	time_t clk;
	struct sigaction sa;
	DIR *fd;								// Scripts directory descriptor

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

	if((chdir("/")) < 0){ return EXIT_FAILURE; }

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	if((pid_file = fopen(PID_FILE, "w")) == NULL){
		syslog(LOG_ERR, "Can't create %s file", PID_FILE);
		return EXIT_FAILURE;
	}
	fprintf(pid_file, "%i", getpid());
	fclose(pid_file);

	syslog(LOG_INFO, "Starting %s", BINARY);

	while(1){
		(void) time(&clk);
		int time = (unsigned) ((interval * 60) - clk % (interval * 60));		// Seconds to the next full minute
		sleep(time); 															// Sleep till the next full minute

		fd = opendir(dirname);
		if(!fd){
			syslog(LOG_ERR, "Cannot open %s", dirname);
			exit(EXIT_FAILURE);
		}

		while(1){
			struct dirent * entry;        
			entry = readdir(fd);
			if(!entry) break;
			if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
				char *command = malloc((strlen(dirname) + strlen(entry->d_name) + 1) * sizeof(char));
				sprintf(command, "%s%s", dirname, entry->d_name);

				if(call(command) != 0){
					syslog(LOG_ERR, "An error as occurred calling %s", entry->d_name);
					break;
				}
			}
		}
		
		if(closedir(fd)){
			syslog(LOG_ERR, "Could not close %s", dirname);
			exit(EXIT_FAILURE);
		}
	}

	closelog();
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]){
	int opt;
	unsigned int interval = DEFAULT_INTERVAL;
	char *dirname = DEFAULT_SCRIPTS_DIR;

	opterr = 0;

	while ((opt = getopt (argc, argv, "i:d:h")) != -1){
		switch(opt){
			case 'i':
				interval = atoi(optarg);
				break;
			case 'd':
				dirname = optarg;
				if(optarg[strlen(optarg) - 1] != '/'){
					dirname = malloc(sizeof(char) * (strlen(optarg) + 1));
					sprintf(dirname, "%s/", optarg);
				}
				break;
			case 'h':
				usage();
				break;
			case '?':
				if(optopt == 'i' || optopt == 'd'){
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

	return do_daemon(interval, dirname);
}