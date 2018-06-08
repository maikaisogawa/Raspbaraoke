#include "mp3.h"

void main(void) {
    mp3_init();
    mp3_play_song(6);
    for (int i = 0; i < 6; i++) {
        timer_delay(1);
        mp3_volume_up();
        mp3_volume_up();
    }
}

