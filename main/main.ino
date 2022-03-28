// Total of 2 octaves + 1 more note for aesthethicc reason, starting from digital pin 22
const int notePin[25] = {22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46};   

// Storing every note pins latest state by using 2D array as key:value data pairs, except that the key is the index of the sublists itself , LOW is the initial state
int lastNotePinState[25][1] = {{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW},{LOW}};
// Used to prefix pin number when working with list indexes
int notePrefix = 22;


// Documentation about using MIDI - http://www.music-software-development.com/midi-tutorial.html - https://midi.org/specifications/midi1-specifications
void sendMIDIdata(byte statusByte, byte data1, byte data2)
{
  Serial.write(statusByte);
  Serial.write(data1);
  Serial.write(data2);
}
const byte noteON = 10010000;
const byte noteOFF = 10000000;

// Check every pins changes then send MIDI note data respectively
void listenNotePins(){
    for (int i = 22; i <= 46; i++){
        // Check for pin changes
        if (digitalRead(i) != lastNotePinState[i-notePrefix][0]){
            if (lastNotePinState[i-notePrefix][0] == HIGH){
                switch (i){
                    // 1st octave
                case 22:
                    sendMIDIdata(noteON,60,64);
                    break;
                case 23:
                    sendMIDIdata(noteON,61,64);
                    break;
                case 24:
                    sendMIDIdata(noteON,62,64);
                    break;
                case 25:
                    sendMIDIdata(noteON,63,64);
                    break;
                case 26:
                    sendMIDIdata(noteON,64,64);
                    break;
                case 27:
                    sendMIDIdata(noteON,65,64);
                    break;
                case 28:
                    sendMIDIdata(noteON,66,64);
                    break;
                case 29:
                    sendMIDIdata(noteON,67,64);
                    break;
                case 30:
                    sendMIDIdata(noteON,68,64);
                    break;
                case 31:
                    sendMIDIdata(noteON,69,64);
                    break;
                case 32:
                    sendMIDIdata(noteON,70,64);
                    break;
                case 33:
                    sendMIDIdata(noteON,71,64);
                    break;
                    // 2nd octave ==========
                case 34:
                    sendMIDIdata(noteON,72,64);
                    break;
                case 35:
                    sendMIDIdata(noteON,73,64);
                    break;
                case 36:
                    sendMIDIdata(noteON,74,64);
                    break;
                case 37:
                    sendMIDIdata(noteON,75,64);
                    break;
                case 38:
                    sendMIDIdata(noteON,76,64);
                    break;
                case 39:
                    sendMIDIdata(noteON,77,64);
                    break;
                case 40:
                    sendMIDIdata(noteON,78,64);
                    break;
                case 41:
                    sendMIDIdata(noteON,79,64);
                    break;
                case 42:
                    sendMIDIdata(noteON,80,64);
                    break;
                case 43:
                    sendMIDIdata(noteON,81,64);
                    break;
                case 44:
                    sendMIDIdata(noteON,82,64);
                    break;
                case 45:
                    sendMIDIdata(noteON,83,64);
                    break;
                case 46:
                    sendMIDIdata(noteON,84,64);
                    break;
                
                }
                // Set last pin state
                lastNotePinState[i-notePrefix][0] = HIGH;
            }
            if (lastNotePinState[i-notePrefix][0] == LOW){
                switch (i){
                    // 1st octave
                case 22:
                    sendMIDIdata(noteOFF,60,0);
                    break;
                case 23:
                    sendMIDIdata(noteOFF,61,0);
                    break;
                case 24:
                    sendMIDIdata(noteOFF,62,0);
                    break;
                case 25:
                    sendMIDIdata(noteOFF,63,0);
                    break;
                case 26:
                    sendMIDIdata(noteOFF,64,0);
                    break;
                case 27:
                    sendMIDIdata(noteOFF,65,0);
                    break;
                case 28:
                    sendMIDIdata(noteOFF,66,0);
                    break;
                case 29:
                    sendMIDIdata(noteOFF,67,0);
                    break;
                case 30:
                    sendMIDIdata(noteOFF,68,0);
                    break;
                case 31:
                    sendMIDIdata(noteOFF,69,0);
                    break;
                case 32:
                    sendMIDIdata(noteOFF,70,0);
                    break;
                case 33:
                    sendMIDIdata(noteOFF,71,0);
                    break;
                    // 2nd octave ==========
                case 34:
                    sendMIDIdata(noteOFF,72,0);
                    break;
                case 35:
                    sendMIDIdata(noteOFF,73,0);
                    break;
                case 36:
                    sendMIDIdata(noteOFF,74,0);
                    break;
                case 37:
                    sendMIDIdata(noteOFF,75,0);
                    break;
                case 38:
                    sendMIDIdata(noteOFF,76,0);
                    break;
                case 39:
                    sendMIDIdata(noteOFF,77,0);
                    break;
                case 40:
                    sendMIDIdata(noteOFF,78,0);
                    break;
                case 41:
                    sendMIDIdata(noteOFF,79,0);
                    break;
                case 42:
                    sendMIDIdata(noteOFF,80,0);
                    break;
                case 43:
                    sendMIDIdata(noteOFF,81,0);
                    break;
                case 44:
                    sendMIDIdata(noteOFF,82,0);
                    break;
                case 45:
                    sendMIDIdata(noteOFF,83,0);
                    break;
                case 46:
                    sendMIDIdata(noteOFF,84,0);
                    break;
                
                }
                // Set last pin state
                lastNotePinState[i-notePrefix][0] = HIGH;
            }
        }
    }
}

void setup(){
    
    // Initialize pins and lastNotePinState 2D array
    for (int i = 22; i <= 46; i++){
        pinMode(notePin[i], INPUT_PULLUP);
    }
}