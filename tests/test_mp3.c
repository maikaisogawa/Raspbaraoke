#include "mp3.h"
#include "timer.h"

void main(void) {
    mp3_init();
    mp3_play_song(1);
    for (int i = 0; i < 6; i++) {
        timer_delay(3);
        mp3_volume_down();
    }
}

