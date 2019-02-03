void setup() {
Serial1.begin(9600);
Serial.begin(9600);

}

void loop() {
  if (Serial1.available() > 0) {
    while(1==1){ 
int  noteon = B10010000;
int  note=B00111100;
int  pitch=B01111111;
Serial1.write(noteon);
Serial1.write(note);
Serial1.write(pitch);

//Serial.write(noteon);
//Serial.write(note);
Serial.write(pitch);
Serial.print("\n");

}
}
}
