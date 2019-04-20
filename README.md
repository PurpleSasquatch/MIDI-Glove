# Fyp
Use the Bluettoth file to test the bluetooth connection works and is available on your machine ,
download and open the gui file which will load the python gui on to your screen and allow for its use.
All files should be commented for use.
The finished files are gui.py and FypGlove Final.ino all other files can be used for the testing of the bluetooth and python before the finished project is implemented
Any arduino board with six analog in pins, tx and rx pins or bluetooth capabilities can be used for this project.
the digital pins are only used for showing connection to the bluetooth gui and low and high battery this functionality is not needed for a usable glove as the python can tell if the connection has been made succesfully, when using the python terminal.

A hc-06/5 module can be used but only if the project is run from the 5v power connection either using a computer or a battery pack, a low energy bluetooth module ca be powered from the 3.3V power.

This project can be run with any synth that takes in a midi channel and changed in the python code. the code only opens the file path so will not affect the functionality.

Loop MIDI is used to manage the midi ports and is a required but free programme. This programme also shows the throughput of the midi port which shows if data transfer is taking place.

Interesting thing: Kraftwerk used a nintendo powerglove in some of their live sets as a MIDI synth

