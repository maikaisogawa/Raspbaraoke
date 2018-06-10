#include "mp3.h"
#include "printf.h"
#include "sender.h"
#include "gpio.h"

/*
 * mp3.c
 * Implements functions for playing songs on the BY8301-16P MP3 module
 * Authors: Callan Hoskins
 *          Maika Isogawa
 *          Gen Singer
 * CS107E, Spring 2018
 */

#define VOLUME_INIT 15 
#define VOLUME_UNIT 3

static unsigned int VOLUME; //BY8301-16P has volume range 0-30 

void mp3_init(void){
    sender_init(GPIO_PIN20, GPIO_PIN21, 9600); //initialize serial com
}

void mp3_play_song(unsigned int SONG_NUM) {
    unsigned char HIGH = (char)SONG_NUM/256;
    unsigned char LOW = (char)SONG_NUM%256;
    unsigned char CHECKSUM = HIGH ^ LOW ^ 0X41 ^ 0x05;
    unsigned char play[7] = {0x7e, 0x05, 0x41, HIGH, LOW, CHECKSUM, 0xef};
    sender_send_code(play, 7);
}
    
void mp3_resume(void) {
    unsigned char resume[5] = {0x7e, 0x03, 0x01, 0x02, 0xef};
    sender_send_code(resume, 5);
}

void mp3_pause(void) {
    unsigned char pause[5] = {0x7e, 0x03, 0x02, 0x01, 0xef};
    sender_send_code(pause, 5);
}

void mp3_volume_up(void) {
    if (VOLUME >= 30) return;
    unsigned char incr[5] = {0x7e, 0x03, 0x05, 0x06, 0xef};
    sender_send_code(incr, 5);
}

void mp3_volume_down(void) {
    if (VOLUME > 0) {
        mp3_set_volume(VOLUME - 1);
    }
}

void mp3_stop(void) {
    unsigned char stop[5] = {0x7e, 0x03, 0x0e, 0x0d, 0xef};
    sender_send_code(stop, 5);
}

void mp3_set_volume(unsigned char LEVEL) {
    if (LEVEL < 0 || LEVEL > 30) return;
    unsigned char CHECKSUM = 0x04 ^ 0x31 ^ LEVEL;
    unsigned char vol[6] = {0x7e, 0x04, 0x31, LEVEL, CHECKSUM, 0xef};
    VOLUME = LEVEL;
    sender_send_code(vol, 6);
}
