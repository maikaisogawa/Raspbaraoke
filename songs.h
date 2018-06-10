#define NUM_SONGS 2

const char * titles[NUM_SONGS];

/* This struct contains the contents of a song. A song consists of an artist, a title, and a set of lyrics.
 */
typedef struct
{
    char * artist;
    char * title;
    char * lyrics;
} song_t;

// Function load_songs sets the artist, title, and lyrics for each song into a library
song_t * load_songs(void);

// returns a pointer to the title of a song
char * songs_get_title(song_t song);

// returns a pointer to the the artist of a song
char * songs_get_artist(song_t song);

// returns a pointer to the lyrics of a songer
char * songs_get_lyrics(song_t song);

// Initializes the songs library - not called within the main function, specifically for testing the functions
int songs_init(void);
