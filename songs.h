/* Change this constant as songs are added to the mp3
 * for the purpose of the CS 107E demonstration, the mp3 chip we are using
 * can only hold a single song.
 */
#define NUM_SONGS 1

const char * titles[NUM_SONGS];

/* This struct contains the contents of a song. A song consists of an artist, a title, and a set of lyrics.
 */
typedef struct
{
    char * artist;
    char * title;
    char * lyrics;
} song_t;

/*
 * function: find_lyrics
 * Returns the lyrics of the song. Lyrics should be added to this function as
 * songs are added to the mp3.
 */
char * find_lyrics(char * title);

/*
 * function: find_title
 * Returns the title of the song if present in the library. This funciton is
 * expanded as songs are added to the mp3 (only a single song because of size
 * restriciton. Returns a pointer to the title.
 */
char * find_title(char * title_code);

/*
 * function: load_songs
 * Loads each component of the song_t struct such as title, artist, and lyrics
 */
song_t * load_songs(void);

// returns a pointer to the title of a song
char * songs_get_title(song_t song);

// returns a pointer to the the artist of a song
char * songs_get_artist(song_t song);

// returns a pointer to the lyrics of a songer
char * songs_get_lyrics(song_t song);
