#include "mp3.h"
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
    unsigned char incr[5] = {0x7e, 0x03, 0x05, 0x06, 0xef};
    sender_send_code(incr, 5);
}

void mp3_volume_down(void) {
    unsigned char decr[5] = {0x7e, 0x03, 0x06, 0x05, 0xef};
    sender_send_code(decr, 5);
}

void mp3_stop(void) {
    unsigned char stop[5] = {0x7e, 0x03, 0x0e, 0x0d, 0xef};
    sender_send_code(stop, 5);
}
