//comparision value for last value to be read from fingers initilised outside the 
//main loop to stop it being rewritten each loop
int lastGray = 0;

//Serial1 is the baud rate for MIDI connections 
//the HC-06 has been modified with the AT commands neccassary to change its Baud rate
//Serial is the serial moniter baud rate used for debugging
void setup() {
  Serial1.begin(38400);
  Serial.begin(38400);
  pinMode(6, OUTPUT);
}

void loop() {
  //read finger values and shift 2 to the right to change max from 1024 to 127
  //from arduino values to MIDI values
  int middle = analogRead(A2) >> 2;
  int ring = analogRead(A3) >> 2;
  int pinkie = analogRead(A4) >> 2;

  int bit1 = 0;
  int bit2 = 0;
  int bit3 = 0;

  int note = 0;
  int noteconst = 0;

  //small delay to allow user to press multiple fingers
  delay(75);

  //set bits for notes and comparisions
  if (middle > 10)
  {
    bit1 = B001;
  }
  if (ring > 10)
  {
    bit2 = B010;
  }
  if (pinkie > 10)
  {
    bit3 = B100;
  }

  //combine bit patterns to create the code on which the notes will be played
  int grayCode = bit1 + bit2 + bit3;

  //checks for a change in notes being played or allows the note to ring out
  if (lastGray == grayCode) {
    //space for pitch modulation/other effects on notes being played by changing the cmd
  }

  //if not has been chnged play new note
  else {
    if (Serial1.read() != -1)
    {
      digitalWrite(6, HIGH);
      lastGray = grayCode;
      // if Chord Finger on go to case switch structure to play chord
      if (analogRead(A0) > 100)
      {
        switch (grayCode)
        {
          //defualt case for debugging purposes
          default:
            Serial1.write(0x90);
            Serial1.write(30);
            Serial1.write(1);
            break;
          //when all fingers released call turnoffNote function to clear notes being played
          case 0:
            turnoffNote();
            break;
          //calls the sendchord function with the name of each chord
          case 1:
            sendChord("C");
            break;

          case 2:
            sendChord("D");
            break;

          case 3:
            sendChord("E");
            break;

          case 4:
            sendChord("F");
            break;

          case 5:
            sendChord("G");
            break;

          case 6:
            sendChord("A");
            break;

          case 7:
            sendChord("B");
            break;
        }
      }
      //else prevents notes from being played while the chord is playing
      else {
        //if high finger on set the constat to 12, each MIDI note is equal to the same note an octave lower plus 12
        if (analogRead(A1) > 100)
        {
          noteconst = 12;
        }
        //high finger off++(play note without adding 12(shift up one octave))
        else
        {
          noteconst = 0;
        }
        switch (grayCode)
        {
          default:
            Serial1.write(0x90);
            Serial1.write(20);
            Serial1.write(1);
            break;

          //turns off all notes when nothing is being pressed
          case 0:
            turnoffNote();
            break;

          //calls noteon function with the note value either as the base value or shifted an octave up
          case 1:
            note = noteconst + 60;
            sendNote(note, 127);
            break;

          case 2:
            note = noteconst + 62;
            sendNote(note, 127);
            break;

          case 3:
            note = noteconst + 64;
            sendNote(note, 127);
            break;

          case 4:
            note = noteconst + 65;
            sendNote(note, 127);
            break;

          case 5:
            note = noteconst + 67;
            sendNote(note, 127);
            break;

          case 6:
            note = noteconst + 69;
            sendNote(note, 127);
            break;

          case 7:
            note = noteconst + 71;
            sendNote(note, 127);
            break;
        }
      }
    }
    else
    {
      //turns off connected LED if data being recieved on the HC-06 is -1(non-connect signal)
      digitalWrite(6, LOW);
    }
  }

}
////////////////////////////////////////////////////////////////////////////////////////////////
//send note command sends note with the note value and the volume
//command 0x90 is the MIDI note on command
void sendNote(int note, int volume)
{
  Serial1.write(0x90);
  Serial1.write(note);
  Serial1.write(volume);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//turn off function cycles through all notes and sends a note off MIDI command(0x80)
void turnoffNote()
{
  int noteoff = 48;
  while (noteoff < 83)
  {
    Serial1.write(0x80);
    Serial1.write(noteoff);
    Serial1.write(127);

    noteoff++;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////
//send chord command sends the three notes associated with a chord based on the integer value
//assigned to each chord name in the key of C
void sendChord(String chord)
{
  int chordInt = 0;
  //C Major
  if (chord == "C")
  {
    chordInt = 1;
  }

  //D Minor
  else if (chord == "D")
  {
    chordInt = 2;
  }

  //E Minor
  else if (chord == "E")
  {
    chordInt = 3;
  }

  //F Major
  else if (chord == "F")
  {
    chordInt = 4;
  }

  //G Major
  else if (chord == "G")
  {
    chordInt = 5;
  }

  //A Minor
  else if (chord == "A")
  {
    chordInt = 6;
  }

  //B Diminished
  else if (chord == "B")
  {
    chordInt = 7;
  }
  switch (chordInt)
  {
    case 1:
      sendNote(48, 127);
      sendNote(52, 127);
      sendNote(55, 127);
      break;

    case 2:
      sendNote(50, 127);
      sendNote(53, 127);
      sendNote(57, 127);
      break;

    case 3:
      sendNote(52, 127);
      sendNote(55, 127);
      sendNote(59, 127);
      break;

    case 4:
      sendNote(53, 127);
      sendNote(57, 127);
      sendNote(60, 127);
      break;

    case 5:
      sendNote(55, 127);
      sendNote(59, 127);
      sendNote(62, 127);
      break;

    case 6:
      sendNote(57, 127);
      sendNote(60, 127);
      sendNote(64, 127);
      break;

    case 7:
      sendNote(59, 127);
      sendNote(62, 127);
      sendNote(65, 127);
      break;
  }
}
