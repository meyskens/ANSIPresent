ANSIPresent
===========

ANSIPresent is an "8-bit PowerPoint/Keynote" experiment. This project started as a joke during a project: "why not present our Adruino project using only an Arduino". In a later presentation where this project was meantioned I accepted the challenge and wrote ANSIPresent.  
This project consists of `ANSIPresent` and `ANSIRemote`. The last as the name might suggests is the code for the remote to control ANSIPresent. This is also designed to run on the Arduino platform.

As the name might suggest this uses the ANSI encoding to render the slides in a terminal emulator, in my case I used `screen`. While this is possible in almost every programming language the fun was in doing this on low end embedded hardware like the ATMega328p (used in Arduino Uno and Nano). This allowed to use a USB connection to render the screen and wireless for comminucation to the remote. It is also more fun to give a presentation using an 8-bit CPU and a limit of 2KB ram.

## Should I use this?
Do you want have fun? Do you have the hardware? Are you comfortable with it failing on stage? Then sure! 

## Thank you
- [AnsiStream](https://github.com/neu-rah/AnsiStream) for doing all of the hard work on ANSI already!
- Ben De Breuker and Kristie Lim for being amazing teammates who helped me with this idea.