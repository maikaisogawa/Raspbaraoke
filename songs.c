#include "songs.h"
//struct includes: char * artist, char * title, and a char * lyrics

char * titles;

struct song_t 
{
    char * artist;
    char * title;
    char * lyrics;
};

char * songs_init(void) 
{
    load_songs();
//    char * titles;
//    for (int i = 0; i < NUM_SONGS; i++) {
//
//    }
}

song_t * load_songs(void) 
{
    song_t * songs;
    for (int i = 0; i < NUM_SONGS; i++) {
        song_t new_song;
        
        new_song.title = //first line in .txt file
        new_song.artist = //second line in .txt file
        new_song.lyrics = //loop through the rest 
    }
}

char * songs_get_title(void) {
    return song_t.title;
}

char * songs_get_artist(void) {
    return song_t.artist;
}

char * songs_get_lyrics(void) {
    return song_t.lyrics;
}
