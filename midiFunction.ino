////////////////////////////////////////////////////////////////////////////
//
// Set MIDI baud rate:
//
//
///////////////////////////////////////////////////////////////////////////

void setup() 
{
  Serial.begin(38400);
  Serial1.begin(38400);
  
}
/////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////
void sendNote(int note)
{
  Serial1.write(0x90);
  Serial1.write(note);
  Serial1.write(45); 
}
//////////////////////////////////////////////////////////////////////////
//
//
//
/////////////////////////////////////////////////////////////////////////
void sendChord(String chord)
{
  int chordInt = chord.toInt();
   
  switch(chordInt)
  {
    case 67://use test programme to find int of chord names values Based on MIDI
    sendNote(60);
    sendNote(64);
    sendNote(67);
    break;

    case 68:
    sendNote(60);
    sendNote(64);
    sendNote(67);
    break;

    case 69:
    sendNote(60);
    sendNote(64);
    sendNote(67);
    break;

    case 70:
    sendNote(60);
    sendNote(64);
    sendNote(67);
    break;

    case 71:
    sendNote(60);
    sendNote(64);
    sendNote(67);
    break;

    case 65:
    sendNote(60);
    sendNote(64);
    sendNote(67);
    break;

    case 66:
    sendNote(60);
    sendNote(64);
    sendNote(67);
    break;
  }
}

void loop() 
{
  int middle=analogRead(A2)>>2;
  int ring=analogRead(A3)>>2;
  int pinkie=analogRead(A4)>>2;
  
  int bit1=0;
  int bit2=0;
  int bit3=0;
  
  int note=0;
  int noteconst=0; 
  
  if (middle>10)
    {bit1 = B001;}
  else
    {bit1 = 000;}
  
  if (ring>10)
    {bit2 = B010;}
  else
    {bit2 = 000;}
  
  if (pinkie>10)
    {bit3 = B100;}
  else
    {bit3 = 000;}

     int grayCode = bit1 + bit2 + bit3;
    int lastReading = 0;

    //if serial1(Bluetooth not connected send empty note just to keep data stream)
    //when connected do code
   
  if(Serial1.read()==5)
  {   
    while(true)
    {
    if(lastReading!=grayCode)
    {
      lastReading=grayCode;
      if (analogRead(A0)>100)// if Chord Finger on
        {
         switch(grayCode)
         {
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
         if(analogRead(A1)>100)//if high finger on
         { 
          noteconst = 12;
         }
         else
         {
          noteconst = 0;
         }
         switch(grayCode)
         {
          case 1:
          note=noteconst+60;
          sendNote(note);
          break;
  
          case 3:
          note=noteconst+60;
          sendNote(note);
          break;
  
          case 2:
          note=noteconst+60;
          sendNote(note);
          break;
  
          case 6:
          note=noteconst+60;
          sendNote(note);
          break;
  
          case 7:
          note=noteconst+60;
          sendNote(note);
          break;
  
          case 5:
          note=noteconst+60;
          sendNote(note);
          break;
  
          case 4:
          note=noteconst+60;
          sendNote(note);
          break;      
         }
    }//if value 40 readings not working
    else
    {
    Serial1.write(0x90);
    Serial1.write(40);
    Serial1.write(1); 
    }
  }
  }
  else
  {//if value other side 50 connection message needs changing
    Serial1.write(0x90);
    Serial1.write(50);
    Serial1.write(1); 
  }
}
