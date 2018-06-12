# singerg22-maikaisogawa-project

Project Title: Raspbaraoke

Authors: Maika Isogawa, Callan Hoskins, Genevieve Singer

Description: For our CS107E final project, we have built a ‘Karaoke machine.’ After loading the program, the user views and introductory screen and is prompted for input. The two main commands are ‘list’ and ‘play.’ ‘List’ will show the user all of the available songs loaded into the karaoke machine. ‘Play’ will automatically start playing the music, and the lyrics will flash on the screen at the appropriate moment. The user can have a lot of fun singing along to their favorite songs (or for the purposes of the demo, “Eye of the Tiger”). 

Hardware: Monitor, speakers, raspberry pi, keyboard, music chip.

Components: There were a number of milestones associated with the final outcome. Although we all had a hand in, and contributed to, all of the components, we definitely had leads on each section (however we all did actually work on each component rather than explicitly splitting up). The people most associated with each section are in the parenthesis.

  * Audio portion - loading the mp3, controlling the mp3 chip  (Callan) : To load the audio mp3 to the chip, one had to use a PC / other than a Mac computer. We used the chip’s documentation to understand the functionality of the chip (along with a lot of guidance from Chris). http://www.uctronics.com/download/BY8301-16P_voice_module_manual%20V1.2.pdf 
   * Bit Banging - sending instructions from pi to mp3 chip (Callan, Maika) : To send instructions from the pi to the mp3 chip, we had to set up a serial communication using the process of ‘bit banging.’ Through our software, we could now send the instructions to play any song, to change the volume, etc.
   * Hardware setup (Maika) - To connect all of the components together, we had to set up the pins on the pi, the speaker points to the audio jack, the keyboard, the monitor, and all of the other connections to make the project run. Designing this in a clean and minimal way assured that our program could run smoothly. 
   * Karaoke shell software (Maika) - the karaoke_shell.c file contains most of the functionality. After the initialization in main, karaoke_shell_run is called and, similarly to shell_run, executes commands as typed by the user.
   * Mp3 control software (Callan, Gen) - The software necessary to send instructions to play music on the mp3 chip. The functions in here are called from karaoke_shell.
   * Song structure (Gen) - The data structure necessary to hold the information for each song. This should be changed as more songs are added to the pi. It also includes the functions necessary to retrieve each portion of the song as necessary.
   * Display and User Interaction (Maika) - The console that the user interacts with to play and list songs and navigate the karaoke program.
   * Lyrics timing (Maika) - To display the lyrics with the right timing, timer delays are used, encoded directly into the string that the lyrics are held in. A few lines are displayed at a time.
   * Visuals (Gen, Maika) - The cover art displayed before the start of the song. Changing of the framebuffer at the appropriate moment, how it actually looks

Challenges and Pivots: Our original idea was a bit different from this final outcome. We wanted to create a looping machine, much like musicians use with guitar pedals to continuously loop sounds over each other. As we began our implementation, we found that there were a number of challenges with this idea, both with software and with hardware. One of the challenges was the inability to play two sounds at the same time over each other, another was the protocol to store the sounds on the mp3 chip we were using, among other things. 

We shifted towards the karaoke machine idea in order to be able to present a more robust final project that incorporated more aspects of what we learned throughout the course. Luckily, everything we had built until that point would fit well with the karaoke project. 

The biggest challenge was the size of the memory on the mp3 chip. Unfortunately, there was only space on the chip to hold one full song. For the purpose of the demonstration, we decided to keep the song and have it be the sole option. But if more songs were added, it would be quite simple to expand the karaoke software to be able to play all of the songs.
Takeaways and Reflection: We found that the workflow of this project went something like this - hit a major hurdle, work really hard, and once we overcame that hurdle, the work flowed smoothly until we hit the next hurdle. Our partnership was great, and we were able to divide the work, come together and discuss, and then divide the work again. 

If we were to approach this project again, having a larger mp3 file would be the biggest point of change. We also learned quite a bit about structuring code in a way that can be utilized by another person as a tool in their own code. The importance of writing clean code that is free of bugs and can handle user error because quite clear throughout the course of this process. Proper planning from the beginning about what file needs to do what would have greatly improved the process of debugging when we put all of the components together.

 We are quite happy with the functionality and outcome of our final CS107E project.
