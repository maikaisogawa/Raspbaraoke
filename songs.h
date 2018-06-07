#define NUM_SONGS 6

const char * titles[NUM_SONGS];

typedef struct
{
    char * artist;
    char * title;
    char * lyrics;
} song_t;

song_t load_songs(void);

char * songs_get_title(song_t song);

char * songs_get_artist(song_t song);

char * songs_get_lyrics(song_t song);

int songs_init(void);
