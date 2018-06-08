#include "../mp3.h"

void mp3_init(void);
void mp3_play_song(unsigned int x);

void main(void) {
    mp3_init();
    mp3_play_song(1);
    timer_delay(3);
    mp3_play_song(2);
    timer_delay(3);
    mp3_play_song(6);
}
