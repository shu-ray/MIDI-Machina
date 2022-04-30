// This sketch is used to debug listenNotePins() function in main.ino

const int notePin[4] = {22,23,24,25};
int lastNotePinStates[4][1] = {};
int notePrefix = 22;

void MIDI(byte statusByte, byte data1, byte data2){
  Serial.write(statusByte);
  Serial.write(data1);
  Serial.write(data2);
}

const byte noteON = 10010000;
const byte noteOFF = 10000000;

void listenNotePinsTest(){
    for (int i : notePin){
        int currentNotePinState = digitalRead(i);
        if (currentNotePinState != lastNotePinStates[i-notePrefix][0]){
            if (currentNotePinState == LOW){
                switch (i){
                case 22: MIDI(noteON,60,64); break;
                case 23: MIDI(noteON,63,64); break;
                case 24: MIDI(noteON,65,64); break;
                case 25: MIDI(noteON,67,64); break;
                }
                lastNotePinStates[i-notePrefix][0] = LOW;   
            }
            if (currentNotePinState == HIGH){
                switch (i){
                case 22: MIDI(noteOFF,60,0); break;
                case 23: MIDI(noteOFF,63,0); break;
                case 24: MIDI(noteOFF,65,0); break;
                case 25: MIDI(noteOFF,67,0); break;
                }
                lastNotePinStates[i-notePrefix][0] = HIGH;
            }
        }
    }
}

void setup(){
    Serial.begin(38400);

    // Initialize note pins and lastNotePinStates 2D array
    for (int i : notePin){
        pinMode(notePin[i-notePrefix],INPUT_PULLUP);
        lastNotePinStates[i-notePrefix][0] = HIGH;
    }
}

void loop(){
    listenNotePinsTest();

    // Delay for 1 milisecond for execution stability
    delay(1);

}
