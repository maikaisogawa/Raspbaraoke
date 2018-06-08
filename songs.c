#include "songs.h"
#include "strings.h"
#include "printf.h"
//struct includes: char * artist, char * title, and a char * lyrics

static struct song_t library;

char * find_lyrics(char * title) 
{
    if (strcmp(title, "After the Storm") == 0) {
        return "Ah\nWhatever goes around eventually comes back to you\nSo you gotta be careful, baby\nAnd look both ways before you cross my mind\nOoh, ah\nDid you ever wonder?\nYeah, do you ever wonder\nWhat he might be going through on his own?\nAnd the demons that he's facing alone\nI hate that sometimes I can't go home\nAnd it just ain't the same on the phone, no\nBut everybody's gotta go on, don't they?\nYes, we do, baby\nSo if you need a hero (if you need a hero)\nJust look in the mirror (just look in the mirror)\nNo one's gonna save you now\nSo you better save yourself\nAnd everybody's hurting\nEverybody's going through it\nBut you just can't give up now\n'Cause you gotta save yourself\nYeah, gotta hang on, baby\nThe sun'll come out\nNothing good ever comes easy\nI know times are rough\nBut winners don't quit\n So don't you give up\nThe sun'll come out\nBut we've been struggling endless     days\nSomeday we'll find the love\n'Cause after the storm's\nWhen the flowers bloom\nKali, what you mean?\nI take it offensive\n'Cause I'm the hottest flower boy\nThat popped up on the scene\nFeeling better, better than ever\n'Cause your umbrella, brella (brella, light)\nSun is beaming on me like headlights beaming on Bambi\nNow let's pretend the street is the room\nAnd you are a Camry\n'Cause your drama candid\nThe Tito to my Randy\nNow let's produce some thrillers\nMy chocolate wit' yo' vanilla, uh\nThe sun'll come out\nNothing good ever comes easy\nI know times are rough\nBut winners don't quit\nSo don't you give up\nThe sun'll come out\nBut we've been struggling endless days\nSomeday we'll find the love\n'Cause after the storm\nI know it's hard\nBut do you even really try?\nMaybe you could understand\nWhen all you had to do was ask\nAnd just open your mind\nWhen everything is passing by\nAnd all you had to do was try\nYeah, all you had to was try\nTry, try, try, try\nAll you had to do was try\nTry, try, try, try\n";
    } else if (strcmp(title, "Boo'd_Up") == 0) {
        return "Feelings, so deep in my feelings\nNo, this ain't really like me\nCan't control my anxiety\nFeeling, like I'm touching the ceiling\nWhen I'm with you I can't breathe\nBoy, you do something to me\nOoh, now I'll never get over you until I find something new\nThat get me high like you do, yeah yeah\nOoh, now I'll never get over you until I find something new\nThat get me high like you do\nListen my to heart go ba-dum, boo'd up\nBiddy-da-dum, boo'd up\nHear my heart go ba-dum, boo'd up\nBiddy-da-dum it just won't stop, it go\nBa-dum, boo'd up\nBiddy-da-dum, boo'd up\nHear my heart go ba-dum, boo'd up\nBiddy-da-dum, it just won't stop, it go\nHow many ways can I say that I need you baby, it's true\nI think I might die without you\nFeeling all over my body\nYou know how I like it\nAin't gotta tell you what to do, yeah yeah\nOoh, now I'll never get over you until I find something new\nThat get me high like you do, yeah yeah\nOoh, now I'll never get over you until I find something new\nThat get me high like you do\nListen my to heart go ba-dum, boo'd up\nBiddy-da-dum, boo'd up\nHear my heart go ba-dum, boo'd up\nBiddy-da-dum it just won't stop, it go\nBa-dum, boo'd up\nBiddy-da-dum, boo'd up\nHear my heart go ba-dum, boo'd up\nBiddy-da-dum, it just won't stop, it go\nHead over heels in love\nRight in front of you, ain't gotta look no more baby (hah)\nI wanna build this love\nAnd everything you want, you ain't gotta ask for\nYou got me boo'd up, boo'd up\nTold you from the jump I'm the one to choose\nGot me boo'd up, boo'd up\nGrab me by the waist baby, pull me closer\nOoh, now I'll never get over you until I find something new\nThat get me high like you do, yeah yeah\nOoh, now I'll never get over you until I find something new\nThat get me high like you do\nListen my to heart go ba-dum, boo'd up\nBiddy-da-dum, boo'd up\nHear my heart go ba-dum, boo'd up\nBiddy-da-dum it just won't stop, it go\nBa-dum, boo'd up\nBiddy-da-dum, boo'd up\nHear my heart go ba-dum, boo'd up\nBiddy-da-dum, it just won't stop, it go\nThis is such a crazy feeling, like\nI don't want to get too attached, but\nI feel like I already am\nMy mind's telling me one thing, but\nI guess I should listen to my heart\nRight?";
    }
}

char * find_title(char * title_code) 
{
    if (strcmp(title_code, "After_the_Storm") == 0) {
        return "After the Storm";
    } else if (strcmp(title_code, "Boo'd_Up") == 0) {
        return "Boo'd Up";
    } else {
        return '\0';
    }
}

song_t * load_songs(void)
{
    song_t * songs;
    char * title_code = "After_the_Storm";
    //  for (int i = 0; i < NUM_SONGS; i++) {
    song_t new_song;
    new_song.title = find_title(title_code);
    new_song.artist = "Kali Uchis";
    //   new_song.artist = //second line in .txt file
    new_song.lyrics = find_lyrics(new_song.title);
    //loop through the rest
    songs[0] = new_song;
    song_t song2;
    song2.title = find_title("Boo'd_Up");
    song2.artist = "Ella Mai";
    song2.lyrics = find_lyrics(song2.title);
    songs[1] = song2;
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
    song_t * library = load_songs();
    printf("song 1 title: %s, artist: %s\n", songs_get_title(library[0]), songs_get_artist(library[0]));
    printf("song 2 title: %s, artist: %s\n", songs_get_title(library[1]), songs_get_artist(library[1]));
    printf("lyrics: %s", songs_get_lyrics(library[1])); 
//    char * titles;
//    for (int i = 0; i < NUM_SONGS; i++) {
//
//    }
    return 0;
}
