/*
    A few notes to self:
    - Minimize calling AnalogRead() and DigitalRead(), on a single pin as possible to avoid inconsistencies
*/

// Total of 2 octaves + 1 more note for aesthethicc reason, starting from digital pin 22
const int notePin[25] = {22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46};

// Pitch Bend pin
const int pBendPin_x = A0;
const int pBendPin_y = A1;
int pBendIdleVal_x = 0;
int pBendIdleVal_y = 0;

// Pitch Modulation pin
const int pModPin_x = A2;
const int pModPin_y = A3;
int pModIdleVal_x = 0;
int pModIdleVal_y = 0;

// Stores every note pins latest state by using 2D array as key:value data pairs, except that the key is the index of the sublists itself
int lastNotePinStates[25][1] = {};

// Used to prefix pin number when working with list indexes
int notePrefix = 22;


// Documentation about MIDI programming - http://www.music-software-development.com/midi-tutorial.html - https://midi.org/specifications/midi1-specifications
void MIDI(byte statusByte, byte data1, byte data2){
  Serial.write(statusByte);
  Serial.write(data1);
  Serial.write(data2);
}
const byte noteON = 10010000;
const byte noteOFF = 10000000;

// Check every note pins changes then send MIDI note data respectively
void listenNotePins(){
    for (int i : notePin){
        // Check for note pin changes
        int currentPinState = digitalRead(i);
        if (currentPinState != lastNotePinStates[i-notePrefix][0]){
            // HIGH is when the switch isn't pressed and LOW otherwise since using INPUT_PULLUP pin mode
            if (currentPinState == LOW){
                switch (i){

                    // 1st octave
                case 22: MIDI(noteON,60,64); break;
                case 23: MIDI(noteON,61,64); break;
                case 24: MIDI(noteON,62,64); break;
                case 25: MIDI(noteON,63,64); break;
                case 26: MIDI(noteON,64,64); break;
                case 27: MIDI(noteON,65,64); break;
                case 28: MIDI(noteON,66,64); break;
                case 29: MIDI(noteON,67,64); break;
                case 30: MIDI(noteON,68,64); break;
                case 31: MIDI(noteON,69,64); break;
                case 32: MIDI(noteON,70,64); break;
                case 33: MIDI(noteON,71,64); break;
                    
                    // 2nd octave ==========
                case 34: MIDI(noteON,72,64); break;
                case 35: MIDI(noteON,73,64); break;
                case 36: MIDI(noteON,74,64); break;
                case 37: MIDI(noteON,75,64); break;
                case 38: MIDI(noteON,76,64); break;
                case 39: MIDI(noteON,77,64); break;
                case 40: MIDI(noteON,78,64); break;
                case 41: MIDI(noteON,79,64); break;
                case 42: MIDI(noteON,80,64); break;
                case 43: MIDI(noteON,81,64); break;
                case 44: MIDI(noteON,82,64); break;
                case 45: MIDI(noteON,83,64); break;
                case 46: MIDI(noteON,84,64); break;
                }
                // Set note pin of "i" latest state
                lastNotePinStates[i-notePrefix][0] = LOW;
            }
            if (currentPinState == HIGH){
                switch (i){

                    // 1st octave
                case 22: MIDI(noteOFF,60,0); break;
                case 23: MIDI(noteOFF,61,0); break;
                case 24: MIDI(noteOFF,62,0); break;
                case 25: MIDI(noteOFF,63,0); break;
                case 26: MIDI(noteOFF,64,0); break;
                case 27: MIDI(noteOFF,65,0); break;
                case 28: MIDI(noteOFF,66,0); break;
                case 29: MIDI(noteOFF,67,0); break;
                case 30: MIDI(noteOFF,68,0); break;
                case 31: MIDI(noteOFF,69,0); break;
                case 32: MIDI(noteOFF,70,0); break;
                case 33: MIDI(noteOFF,71,0); break;
                    
                    // 2nd octave ==========
                case 34: MIDI(noteOFF,72,0); break;
                case 35: MIDI(noteOFF,73,0); break;
                case 36: MIDI(noteOFF,74,0); break;
                case 37: MIDI(noteOFF,75,0); break;
                case 38: MIDI(noteOFF,76,0); break;
                case 39: MIDI(noteOFF,77,0); break;
                case 40: MIDI(noteOFF,78,0); break;
                case 41: MIDI(noteOFF,79,0); break;
                case 42: MIDI(noteOFF,80,0); break;
                case 43: MIDI(noteOFF,81,0); break;
                case 44: MIDI(noteOFF,82,0); break;
                case 45: MIDI(noteOFF,83,0); break;

                case 46: MIDI(noteOFF,84,0); break;                
                }
                // Set note pin of "i" latest state
                lastNotePinStates[i-notePrefix][0] = HIGH;
            }
        }
    }
}

void pitchBend(){
        
}

void pitchModulate(){

}


void setup(){
    Serial.begin(38400);

    // Initialize note pins and lastNotePinState 2D array
    for (int i : notePin){
        pinMode(notePin[i-notePrefix], INPUT_PULLUP);

        // Set all note pins initial state as HIGH (unpressed)
        lastNotePinStates[i-notePrefix][0] = HIGH;
    }

    // Calibration
    int i = 0;
    while (millis() < 3000){
        if (millis() % 300 == 0){                      // Sum up 10 analog readings of joysticks that were read,
            pBendIdleVal_x += analogRead(pBendPin_x);   // for every 0.3 second in 3 seconds since the Arduino booted up
            pBendIdleVal_y += analogRead(pBendPin_y);
            pModIdleVal_x += analogRead(pModPin_x);
            pModIdleVal_y += analogRead(pModPin_y);
            i++;
        }
    }

    // Divide the sum of those analog readings by 10 to get the average value
    pBendIdleVal_x = round(pBendIdleVal_x / i);
    pBendIdleVal_y = round(pBendIdleVal_y / i);
    pModIdleVal_x = round(pModIdleVal_x / i);
    pModIdleVal_y = round(pModIdleVal_y / i);
}

void loop(){
    listenNotePins();

    // Delay for 1 milisecond for execution stability
    delay(1);
}