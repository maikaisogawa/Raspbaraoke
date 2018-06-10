#ifndef MP3_H
#define MP3_H

/*
 * Functions for controlling the BY8301-16P MP3 player module
 * Authors: Callan Hoskins
 *          Maika Isogawa
 *          Gen Singer
 * CS107E, Spring 2018
 */

/*
 * function: mp3_init
 * Initializes the MP3 player by setting up serial communication between
 * the Pi and BY8301-16P
 */
void mp3_init(void);

/*
 * function: mp3_play_song
 * Plays the song stored as SONG_NUM on the BY8301-16P
 */
void mp3_play_song(unsigned int SONG_NUM);

/* function: mp3_pause
 * Pauses the current song
 */
void mp3_pause(void);

/* function: mp3_resume
 * Resumes playing the current song
 */
void mp3_resume(void);

/* function: mp3_volume_up
 * The volume on the BY8301-16P has a range from 0-30. This function will
 * increase the volume by one unit. 
 */
void mp3_volume_up(void);

/* function: mp3_volume_down
 * The volume on the BY8301-16P has a range from 0-30. This function will
 * decrease the volume by one unit. 
 */
void mp3_volume_down(void);

/* function: mp3_set_volume
 * Sets the volume at the specified level
 * @param LEVEL - number 0 <= LEVEL <= 30
 * If LEVEL is outside that range, does nothing
 */
void mp3_set_volume(unsigned char LEVEL);

/* function: mp3_stop
 * Stops the current song, whether it's playing or paused
 */
void mp3_stop(void);

#endif
