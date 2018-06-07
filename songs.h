#define NUM_SONGS 6

const char * titles[NUM_SONGS];

void load_titles() 
{
    titles[0] = "After_the_Storm.txt";
    titles[1] = "Boo'd_Up.txt";
    titles[2] = "In_The_Morning.txt";
    titles[3] = "Season_2_Episode_3.txt";
    titles[4] = "Honey.txt";
    titles[5] = "Total.txt";
}

song_t load songs(void);

char * songs_get_title(song_t song);

char * songs_get_artist(song_t song);

char * songs_get_lyrics(song_t song);

int songs_init(void);
