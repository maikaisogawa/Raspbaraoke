#include "songs.h"
#include "strings.h"
#include "printf.h"
#include "malloc.h"

/*
 * function: find_lyrics
 * Returns the lyrics of the song. Lyrics should be added to this function as
 * songs are added to the mp3.
 */
char * find_lyrics(char * title) 
{
    if(strcmp(title, "Eye of the Tiger") == 0) {
        return "%50*Musical Interlude*\n$%17Risin' up, back on the street\nDid my time, took my chances\nWent the distance,\nnow I'm back on my feet\nJust a man and his will to survive\n$%9So many times, it happens too fast\nYou trade your passion for glory\n$%8Don't lose your grip\non the dreams of the past\nYou must fight just to keep them alive\n$%9It's the eye of the tiger,\nit's the thrill of the fight\nRisin' up to the challenge of our rival\n$%9And the last known survivor\nstalks his prey in the night\nAnd he's watchin' us all with the eye\n$%6of the tiger\n$%9Face to face, out in the heat\nHangin' tough, stayin' hungry\n$%8They stack the odds\n'till we take to the street\nFor the kill with the skill to survive\n$%9It's the eye of the tiger,\nit's the dream of the fight\nRisin' up to the challenge of our rival\n$%9And the last known survivor\nstalks his prey in the night\nAnd he's watchin' us all with the eye\n$%10of the tiger\n$%17Risin' up, straight to the top\nHad the guts, got the glory\nWent the distance,\nnow I'm not gonna stop\nJust a man and his will to survive\n$%8It's the eye of the tiger,\nit's the dream of the fight\nRisin' up to the challenge of our rival\n$%10And the last known survivor\nstalks his prey in the night\nAnd he's watchin' us all with the eye\n$%11of the tiger\n$%60The eye of the tiger\n";
    } else {
        return "";
    }
}

/*
 * function: find_title
 * Returns the title of the song if present in the library. This funciton is
 * expanded as songs are added to the mp3 (only a single song because of size
 * restriciton. Returns a pointer to the title.
 */
char * find_title(char * title_code) 
{
    if(strcmp(title_code, "Eye of the Tiger") == 0) {
        return "Eye of the Tiger";
    } else {
        return '\0';
    }
}

/*
 * function: load_songs
 * Loads each component of the song_t struct such as title, artist, and lyrics
 */ 

song_t * load_songs(void)
{
    song_t * songs = malloc(500);
    char * title_code = "Eye of the Tiger";
    song_t new_song;
    new_song.title = find_title(title_code);
    new_song.artist = "Survivor";
    new_song.lyrics = find_lyrics(new_song.title);
    songs[0] = new_song;
    free(songs);
    return songs;
}

// returns the title of a song
char * songs_get_title(song_t song) {
    return song.title;
}

// returns the artist of a song
char * songs_get_artist(song_t song) {
    return song.artist;
}

// returns the lyrics of a song
char * songs_get_lyrics(song_t song) {
    return song.lyrics;
}
