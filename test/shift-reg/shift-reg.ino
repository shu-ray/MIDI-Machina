const int dataPin = 2;   /* Q7 */
const int clockPin = 3;  /* CP */
const int latchPin = 4;  /* PL */

// byte byte1 = 0;
// byte byte2 = 0;
// byte byte3 = 0;
// byte byte4 = 0;

// Documentation about MIDI programming - http://www.music-software-development.com/midi-tutorial.html - https://midi.org/specifications/midi1-specifications
void MIDI(byte statusByte, byte data1, byte data2){
  Serial.write(statusByte);
  Serial.write(data1);
  Serial.write(data2);
}

// We'll be using 5 shift registers,40 input
// 36 for 3 octave, the other 4 is for other uses
byte bytesReceived[4] = {};
byte buttonRead[32] = {};

unsigned long longReceived = 0;

// shiftIn() implementation that works
byte shiftInx(int myDataPin, int myClockPin) {
  int i; int temp = 0; int pinState; byte myDataIn = 0;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);

  /*  we will be holding the clock pin high 8 times (0,..,7) at the
    end of each time through the for loop
    at the beginning of each loop when we set the clock low, it will
    be doing the necessary low to high drop to cause the shift
    register's DataPin to change state based on the value
    of the next bit in its serial information flow.
    The register transmits the information about the pins from pin 7 to pin 0
    so that is why our function counts down
  */
  for (i=7; i>=0; i--){
    digitalWrite(myClockPin, 0);
    delayMicroseconds(2);
    temp = digitalRead(myDataPin);
    if (temp) {
      pinState = 1;

      //set the bit to 0 no matter what
      myDataIn = myDataIn | (1 << i);

    }
    else {
      //turn it off -- only necessary for debugging
     //print statement since myDataIn starts as 0
      pinState = 0;
    }
    //Debugging print statements
    //Serial.print(pinState);
    //Serial.print("     ");
    //Serial.println (dataIn, BIN);
    digitalWrite(myClockPin, 1);
  }
  //debugging print statements whitespace
  //Serial.println();
  //Serial.println(myDataIn, BIN);
  return myDataIn;
}

// literally combine 4 bytes to long
unsigned long byteCatToLong(byte bytes[]){
  unsigned long long0 = 0;
  for (int i = 0; i < 4; i++){
    long0 = long0 >> i * 8;
    long0 += bytes[i];
  }
  return long0;
}

// unpack compiled long from received bytes to invidual variables
void unpackLong(unsigned long longToUnpack,byte variables[]){
   for (int i = 0; i < 32; i++){
    variables[i] = bitRead(longToUnpack,i);
   }
}

const byte noteON = 0x90; const byte noteOFF = 0x80;
byte lastButtonStates[32] = {};
void listenNotePins(){
    for (int i : buttonRead){
        // Save current for button
        int currentState = buttonRead[i];
        if (currentState != lastButtonStates[i]){
            // HIGH is when the switch isn't pressed and LOW otherwise since using INPUT_PULLUP pin mode
            if (currentState == HIGH){
                switch (i){

                    // 1st octave
                case 0: MIDI(noteON,60,64); break;
                case 1: MIDI(noteON,61,64); break;
                case 2: MIDI(noteON,62,64); break;
                case 3: MIDI(noteON,63,64); break;
                case 4: MIDI(noteON,64,64); break;
                case 5: MIDI(noteON,65,64); break;
                case 6: MIDI(noteON,66,64); break;
                case 7: MIDI(noteON,67,64); break;
                case 8: MIDI(noteON,68,64); break;
                case 9: MIDI(noteON,69,64); break;
                case 10: MIDI(noteON,70,64); break;
                case 11: MIDI(noteON,71,64); break;
                    
                    // 2nd octave ==========
                case 12: MIDI(noteON,72,64); break;
                case 13: MIDI(noteON,73,64); break;
                case 14: MIDI(noteON,74,64); break;
                case 15: MIDI(noteON,75,64); break;
                case 16: MIDI(noteON,76,64); break;
                case 17: MIDI(noteON,77,64); break;
                case 18: MIDI(noteON,78,64); break;
                case 19: MIDI(noteON,79,64); break;
                case 20: MIDI(noteON,80,64); break;
                case 21: MIDI(noteON,81,64); break;
                case 22: MIDI(noteON,82,64); break;
                case 23: MIDI(noteON,83,64); break;
                
                case 24: MIDI(noteON,84,64); break;
                }
                // Set note pin of "i" latest state
                lastButtonStates[i] = HIGH;
            }
            if (currentState == LOW){
                switch (i){

                    // 1st octave
                case 0: MIDI(noteOFF,60,0); break;
                case 1: MIDI(noteOFF,61,0); break;
                case 2: MIDI(noteOFF,62,0); break;
                case 3: MIDI(noteOFF,63,0); break;
                case 4: MIDI(noteOFF,64,0); break;
                case 5: MIDI(noteOFF,65,0); break;
                case 6: MIDI(noteOFF,66,0); break;
                case 7: MIDI(noteOFF,67,0); break;
                case 8: MIDI(noteOFF,68,0); break;
                case 9: MIDI(noteOFF,69,0); break;
                case 10: MIDI(noteOFF,70,0); break;
                case 11: MIDI(noteOFF,71,0); break;
                    
                    // 2nd octave ==========
                case 12: MIDI(noteOFF,72,0); break;
                case 13: MIDI(noteOFF,73,0); break;
                case 14: MIDI(noteOFF,74,0); break;
                case 15: MIDI(noteOFF,75,0); break;
                case 16: MIDI(noteOFF,76,0); break;
                case 17: MIDI(noteOFF,77,0); break;
                case 18: MIDI(noteOFF,78,0); break;
                case 19: MIDI(noteOFF,79,0); break;
                case 20: MIDI(noteOFF,80,0); break;
                case 21: MIDI(noteOFF,81,0); break;
                case 22: MIDI(noteOFF,82,0); break;
                case 23: MIDI(noteOFF,83,0); break;
                
                case 24: MIDI(noteOFF,84,0); break;                
                }
                // Set note pin of "i" latest state
                lastButtonStates[i] = LOW;
            }
        }
    }
}

void setup() {
  Serial.begin(115200);
  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  // Step 1: Sample
  digitalWrite(latchPin, LOW);
  digitalWrite(latchPin, HIGH);

  // Step 2: Shift
  Serial.print("Bits: ");

  // byte1 = shiftInx(dataPin,clockPin);
  // byte2 = shiftInx(dataPin,clockPin);
  // byte3 = shiftInx(dataPin,clockPin);
  // byte4 = shiftInx(dataPin,clockPin);

  for (int i=0; i < 4; i++){
    bytesReceived[i] = shiftInx(dataPin,clockPin);
    // Serial.print(bytesReceived[i]);
    // Serial.print(",");
  }
  // Serial.println(" = ");
  longReceived = byteCatToLong(bytesReceived);
  unpackLong(longReceived,buttonRead);

  listenNotePins();

  delay(200);
}