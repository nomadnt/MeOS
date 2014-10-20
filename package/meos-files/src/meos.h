/**
 * Name        : meos.h
 * Author      : Filippo Sallemi
 * Version     : 0.3.0
 * Copyright   : copyright 2014 Nomad NT
 * Description : MeOS scripts scheduler header
 **/

#ifndef MEOS_H_
#define MEOS_H_

#define BINARY "meos"
#define PID_FILE "/var/run/meos.pid"

#define DEFAULT_INTERVAL 5
#define DEFAULT_SCRIPTS_DIR "/usr/share/meos/"

// Defining time to switch script
#define TTS_BIN "/usr/share/meos/tts"
#define TTS_INTERVAL 60

// Defining heartbeat script
#define HEARTBEAT_BIN "/usr/share/meos/heartbeat"
#define HEARTBEAT_INTERVAL 300

// Defining watchdog script
#define WATCHDOG_BIN "/usr/share/meos/watchdog"
#define WATCHDOG_INTERVAL 900

#endif /* MEOS_H_ */
