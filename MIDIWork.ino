int lastGray = 0;
void setup() {
  Serial1.begin(38400);
  Serial.begin(38400);
  
}

void loop() {
  int middle = analogRead(A2) >> 2;
  int ring = analogRead(A3) >> 2;
  int pinkie = analogRead(A4) >> 2;

  int bit1 = 0;
  int bit2 = 0;
  int bit3 = 0;

  int note = 0;
  int noteconst = 0;

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

  int grayCode = bit1 + bit2 + bit3;

  if (lastGray == grayCode) {

  }
  else{
  if (Serial1.read() != -1)
  {
    lastGray = grayCode;
    if (analogRead(A0) > 100) // if Chord Finger on
    {
      switch (grayCode)
      {
        default:
          Serial1.write(0x90);
          Serial1.write(30);
          Serial1.write(1);
          break;

        case 1:
          sendChord("C");
          break;

        case 3:
          sendChord("D");
          break;

        case 2:
          sendChord("E");
          break;

        case 6:
          sendChord("F");
          break;

        case 7:
          sendChord("G");
          break;

        case 5:
          sendChord("A");
          break;

        case 4:
          sendChord("B");
          break;
      }
    }
    if (analogRead(A1) > 100) //if high finger on
    {
      noteconst = 12;
    }
    else //high finger off(play note without adding 12(shift up one octave))
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

      case 1:
        note = noteconst + 60;
        sendNote(note);
        break;

      case 3:
        note = noteconst + 62;
        sendNote(note);
        break;

      case 2:
        note = noteconst + 64;
        sendNote(note);
        break;

      case 6:
        note = noteconst + 65;
        sendNote(note);
        break;

      case 7:
        note = noteconst + 67;
        sendNote(note);
        break;

      case 5:
        note = noteconst + 69;
        sendNote(note);
        break;

      case 4:
        note = noteconst + 71;
        sendNote(note);
        break;
    }
  }
  }
  delay(100);
}

void sendNote(int note)
{
  Serial1.write(0x90);
  Serial1.write(note);
  Serial1.write(45);
}

void sendChord(String chord)
{
  int chordInt = 0;
  if (chord == "C")
  {
    chordInt = 1;
  }
  else if (chord == "D")
  {
    chordInt = 2;
  }
  else if (chord == "E")
  {
    chordInt = 3;
  }
  else if (chord == "F")
  {
    chordInt = 4;
  }
  else if (chord == "G")
  {
    chordInt = 5;
  }
  else if (chord == "A")
  {
    chordInt = 6;
  }
  else if (chord == "B")
  {
    chordInt = 7;
  }
  switch (chordInt)
  {
    case 1:
      sendNote(60);
      sendNote(64);
      sendNote(67);
      break;

    case 2:
      sendNote(62);
      sendNote(65);
      sendNote(69);
      break;

    case 3:
      sendNote(64);
      sendNote(67);
      sendNote(71);
      break;

    case 4:
      sendNote(65);
      sendNote(69);
      sendNote(72);
      break;

    case 5:
      sendNote(67);
      sendNote(71);
      sendNote(74);
      break;

    case 6:
      sendNote(69);
      sendNote(72);
      sendNote(76);
      break;

    case 7:
      sendNote(71);
      sendNote(74);
      sendNote(77);
      break;
  }
}
