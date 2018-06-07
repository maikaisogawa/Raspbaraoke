#include "songs.h"
#include "printf.h"
//struct includes: char * artist, char * title, and a char * lyrics

static struct song_t library;

song_t load_songs(void)
{
    song_t songs;
    char * title = "After_the_Storm";
    //  for (int i = 0; i < NUM_SONGS; i++) {
    song_t new_song;
    new_song.title = title;
    new_song.artist = "Kali Uchis";
    //   new_song.artist = //second line in .txt file
    //   new_song.lyrics = //loop through the rest
    songs = new_song;
    return songs;
    //  }
}

char * songs_get_title(song_t song) {
    return song.title;
}

char * songs_get_artist(song_t song) {
    return song.artist;
}

char * songs_get_lyrics(song_t song) {
    return song.lyrics;
}

int songs_init(void)
{
    song_t library = load_songs();
    printf("song title: %s, artist: %s\n", songs_get_title(library), songs_get_artist(library));
//    char * titles;
//    for (int i = 0; i < NUM_SONGS; i++) {
//
//    }
    return 0;
}
